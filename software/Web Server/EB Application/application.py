import logging, logging.handlers
import urllib2, xively, time, datetime
#import numpy as np

from wsgiref.simple_server import make_server
from flask import json
from hourly_precip import get_pqpf as calc_pqpf
from math import exp, sqrt, pi
from numpy import array
from cgi import parse_qs
#from scipy.signal import gaussian as gauss
#from scipy.signal import convolve as conv


# Set Xively Keys and Feed
read_key    = 'Insert Xively Key Here' # Key to read from all channels
trigger_key = 'Insert Xively Key Here' # Key to read/write "trigger" channel that notifies the autosampler when a sample is requested
p_rain_key  = 'Insert Xively Key Here' # Key to read/write "p_rain" channel
feed_id     =  987654321 # Replace w Xively feed ID here

# Set Weather Underground Info
wx_api_key = 'Insert Weather Underground API Key Here'
latlong    = '42.324100,-83.711304'
url = 'http://api.wunderground.com/api/'+wx_api_key+'/hourly/q/'+latlong+'.json'
amt = 0.20

# Set Tuning Params
min_dflow = 6.25 # 75 mm/hr == 6.25 mm/5 mins
bandwidth = 0.10

# Set State Variables
BASEFLOW        = 0
RISING          = 1
PEAKING         = 2
PEAK            = 3
FALLING         = 4
current_state   = BASEFLOW

# Create logger
logger = logging.getLogger(__name__)
logger.setLevel(logging.INFO)

# Handler 
LOG_FILE = '/tmp/sample-app.log'
handler = logging.handlers.RotatingFileHandler(LOG_FILE, maxBytes=1048576, backupCount=5)
handler.setLevel(logging.INFO)

# Formatter
formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')

# Add Formatter to Handler
handler.setFormatter(formatter)

# add Handler to Logger
logger.addHandler(handler)

response = """
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
{style}
<head>
  <!--
    Copyright 2012 Amazon.com, Inc. or its affiliates. All Rights Reserved.

    Licensed under the Apache License, Version 2.0 (the "License"). You may not use this file except in compliance with the License. A copy of the License is located at

        http://aws.Amazon/apache2.0/

    or in the "license" file accompanying this file. This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.
  -->
  <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
  <title>Welcome</title>
</head>
<body id="sample">
  <div class="textColumn">
    <h1>The Internet of Water Lab</h1>
    <p>Civil Infrastructure Systems<br>University of Michigan, Ann Arbor</p>
  </div>
  <div class="linksColumn"> 
      <h2>Precipitation Forecast for {amt}":</h2>
      <pre class="forecast"> {pqpf_str} </pre>
      <h2>Useful Links:</h2>
    <ul>
    <li><a href="http://bpwong-um.github.com/channel-viz/index.html">Our Live Sensor Data</a></li>
    <li><a href="http://www.wunderground.com/?apiref=328451b95d475114">Weather Underground</a></li>
    <li><a href="http://docs.amazonwebservices.com/elasticbeanstalk/latest/dg/">AWS Elastic Beanstalk overview</a></li>
    <li><a href="http://www.cee.umich.edu/Branko_Kerkez">Contact Us</a></li>
     
    <!--  
    <li><a href="http://docs.amazonwebservices.com/elasticbeanstalk/latest/dg/index.html?concepts.html">AWS Elastic Beanstalk concepts</a></li>
    <li><a href="http://docs.amazonwebservices.com/elasticbeanstalk/latest/dg/create_deploy_Python_django.html">Deploy a Django Application to AWS Elastic Beanstalk</a></li>
    <li><a href="http://docs.amazonwebservices.com/elasticbeanstalk/latest/dg/create_deploy_Python_flask.html">Deploy a Flask Application to AWS Elastic Beanstalk</a></li>
    <li><a href="http://docs.amazonwebservices.com/elasticbeanstalk/latest/dg/create_deploy_Python_custom_container.html">Customizing and Configuring a Python Container</a></li>
    <li><a href="http://docs.amazonwebservices.com/elasticbeanstalk/latest/dg/using-features.loggingS3.title.html">Working with Logs</a></li>
    -->

    </ul>
  </div>   
</body>
</html>
"""

style = """
  <style>
  body {
    color: #ffffff;
    background-color: #E0E0E0;
    font-family: Arial, sans-serif;
    font-size:14px;
    -moz-transition-property: text-shadow;
    -moz-transition-duration: 4s;
    -webkit-transition-property: text-shadow;
    -webkit-transition-duration: 4s;
    text-shadow: none;
  }
  body.blurry {
    -moz-transition-property: text-shadow;
    -moz-transition-duration: 4s;
    -webkit-transition-property: text-shadow;
    -webkit-transition-duration: 4s;
    text-shadow: #fff 0px 0px 25px;
  }
  a {
    color: #0188cc;
  }
  .textColumn, .linksColumn {
    padding: 2em;
  }
  .textColumn {
    position: absolute;
    top: 0px;
    right: 50%;
    bottom: 0px;
    left: 0px;

    text-align: right;
    padding-top: 11em;
    background-color: #1B9DA8;
    background-image: -moz-radial-gradient(left top, circle, #6AEEF9 0%, #0087b3 60%);
    background-image: -webkit-gradient(radial, 0 0, 1, 0 0, 500, from(#6AEEF9), to(#0087b3));
  }
  .textColumn p {
    width: 75%;
    float:right;
  }
  .linksColumn {
    position: absolute;
    top:0px;
    right: 0px;
    bottom: 0px;
    left: 50%;

    background-color: #E0E0E0;
  }

  h1 {
    font-size: 500%;
    font-weight: normal;
    margin-bottom: 0em;
  }
  h2 {
    font-size: 200%;
    font-weight: normal;
    margin-bottom: 0em;
  }
  ul {
    padding-left: 1em;
    margin: 0px;
  }
  li {
    margin: 1em 0em;
  }
  .forecast {
    color: #999999;
  }
  
  </style>
"""
#http://www.colorhexa.com/1b9da8
#http://stackoverflow.com/questions/7042695/advanced-string-formatting-python
url_info = {
  'style':style,
  'amt':amt,
  'pqpf_str':'<a href="http://default-environment-38qi3aipzm.elasticbeanstalk.com/?pqpf=0.2">Click</a> to Show Forecast'
}

#http://stackoverflow.com/questions/6999726/python-converting-datetime-to-millis-since-epoch-unix-time
def unix_time(dt):
    epoch = datetime.datetime.utcfromtimestamp(0)
    delta = dt - epoch
    return delta.total_seconds()

def unix_time_millis(dt):
    return unix_time(dt) * 1000.0

def unix_time_hours(dt):
    return unix_time(dt) / 3600.0

def kernel(x_in):
  x = float(x_in)
  return exp(-x*x/2)/sqrt(2*pi)

def diff(x_in):
  x = [float(el) for el in x_in]
  return [x[k+1]-x[k] for k in range(0,len(x)-1)]

def d_dt(x,t):
  # Get the time-change in data 
  # Returns a list of rate
  
  # Convert t from datetime to unix time
  if type(t[1]) == datetime.datetime:
    t = [unix_time_hours(el) for el in t]  

  dx = diff(x)
  dt = diff(t)
  dxdt = array(dx)/array(dt)
  return list(dxdt)

def smooth(x,y,h=bandwidth):
  # Use a Gaussian kerne to smooth the input array, x
  # with a bandwidth of h
  
  # If a list is input instead of an array, 
  # convert to array
  if type(x) == type([]):
    x = array(x)
  if type(y) == type([]):
    y = array(y)    

  # Apply kernel
  out = 0*y
  for k in range(0,len(x)):
    z = [kernel(el) for el in (x[k]-x)/h]
    out[k] = sum(z*y)/sum(z)

  return out

def get_forecast(link = url):
  f = urllib2.urlopen(link)
  json_string = f.read()
  f.close()
  parsed_json = json.loads(json_string)

  return parsed_json

def get_pqpf(parsed_json, amt = 0.20):
  epoch = float(parsed_json['hourly_forecast'][0]['FCTTIME']['epoch'])
  pop   = float(parsed_json['hourly_forecast'][0]['pop'])/100
  qpf   = float(parsed_json['hourly_forecast'][0]['qpf']['english'])
  pqpf  = calc_pqpf(amt, [pop], [qpf])

  return pqpf[0], pop, qpf, epoch


def update_channel(channel, value, key = p_rain_key, feedID = feed_id, at = -1):
  if at == -1:
    at = datetime.datetime.utcnow()

  # Connect to Xively  
  api = xively.XivelyAPIClient(key)
  feed = api.feeds.get(feedID)
  stream = feed.datastreams.get(channel)

  stream.datapoints = [xively.Datapoint(at, value)]
  stream.update()


def post_forecast(pqpf = 0.0, channel = 'p_rain', key = p_rain_key, feedID = feed_id):  
  update_channel(value = pqpf, channel = channel, key = key, feedID = feedID, at = datetime.datetime.utcnow())


def post_trigger(value = 2, channel = 'trigger_sampler', key = p_rain_key, feedID = feed_id):
  update_channel(value = value, channel = channel, key = key, feedID = feedID, at = datetime.datetime.utcnow())

def get_current_value(channel = 'bottle', key = read_key, feedID = feed_id):
  # Retrieve the current value for a given channel

  # Connect to XivelyAPIClient
  api = xively.XivelyAPIClient(key)
  feed = api.feeds.get(feedID)
  stream = feed.datastreams.get(channel)

  return float(stream.current_value)

def get_history(channel = 'bottle', duration = 60, key = read_key, feedID = feed_id, interval = 0, end = -1):
  # Retrieve the data taken within [duration] minutes ago,
  # [duration] can at most be 6 hours if interval is 0
  if duration > 300 and interval == 0:
    duration = 300
  elif duration <= 0:
    duration = 60
    interval = 0    

  if end == -1:
    end = datetime.datetime.utcnow()
  
  dur_string = str(duration) + "minutes"

  # Connect to XivelyAPIClient
  api = xively.XivelyAPIClient(key)
  feed = api.feeds.get(feedID)
  stream = feed.datastreams.get(channel)

  # Get data from past [duration] minutes and store values in lists
  data   = stream.datapoints.history(duration = dur_string, interval = interval, end = end ) 
  points = [d for d in data]                  # List of xively.Datapoints
  values = [float(p.value) for p in points]   # List of floats
  times  = [p.at for p in points]             # List of datetimes

  return values, times

def dchannel_dt(channel = 'depth_sonic', dur = 60, end = -1, h = bandwidth):
  # Get the time-change in data over [duration] in minutes.  
  # Returns a list of rate in terms of change per hour
  x,dates = get_history(channel=channel, end=end, duration=dur)  
  
  if len(dates) < 2:
    logger.info("dchannel_dt(): Less than 2 datapoints within %d minutes" % dur)
    return [0]

  t = [unix_time_hours(date) for date in dates]
  x_filt = smooth(t,x,h)
  dxdt = d_dt(x_filt,t)
  return dxdt


def sampled_recently(channel = 'bottle', duration = 60, key = read_key, feedID = feed_id, interval = 0):
  # Check oldest sample within [duration] minutes ago, and if the value is the same
  # as the current value, then the channel hasn't been sampled recently
  # Another method could be to check the number of samples between now and 
  # [duration] minutes ago  

  values, _ = get_history(channel=channel, duration=duration, key=key, feedID=feedID, interval=interval)  

  # Alternatively...
  # points=feed.datastreams.get('x',end=datetime.datetime.utcnow(),interval=interval,duration=dur_string)
  # [d.value for d in points.datapoints]
  # [d.at for d in points.datapoints]
  # Check if oldest value is the same as current value.  
  # Sampled recently taken if the two values are different

  return values[0] != values[-1]


def application(environ, start_response):
    path    = environ['PATH_INFO']
    method  = environ['REQUEST_METHOD']
    if method == 'POST':
        try:
            request_body_size = int(environ['CONTENT_LENGTH'])
            request_body = environ['wsgi.input'].read(request_body_size)

            #http://stackoverflow.com/questions/17417620/python-requests-encoding-post-data
            decoded_request = urllib2.unquote(request_body).decode('utf-8')
            logger.info("Received message from worker: %s" % decoded_request[5:])

            parsed = json.loads(decoded_request[5:])  # Skip first 5 characters ("body=...")
            info = "FeedID: " + str(parsed['environment']['id']) + ", Channel: " + str(parsed['triggering_datastream']['id']) + ", Value: " + str(parsed['triggering_datastream']['value']['value']) + ", Time: " + str(parsed['triggering_datastream']['at'])
            logger.info("Received message from worker: %s" % info)
            #logger.info("Received message from worker: %s" % str(scipy.version.version))

            # Begin Processing for Xively
            forecast = get_forecast(url)

            # Forecast for 0.1"
            pqpf, pop, qpf, epoch = get_pqpf(forecast)
            post_forecast(pqpf*100)
                        
            # Forecast for 0.01"
            pqpf_01 = get_pqpf(forecast,amt=0.01)[0]
            post_forecast(pqpf_01*100, channel = 'p_rain001')            
            logger.info("Received message from worker: at: %f, pop: %2d, qpf: %4s, pqpf(0.1): %2.2f, pqpf(0.01): %2.2f" % (epoch, pop, qpf, pqpf*100, pqpf_01*100))
                        
            # Get Change in Depth over Time
            dxdt = dchannel_dt(channel = 'depth_sonic')
            dxdt = [-d/12 for d in dxdt] #invert values for sonic sensor, convert to mm/5 mins
            update_channel(value=dxdt[-1], channel='delta_depth_sonic')
            logger.info("Received message from worker: dQ/dt: %f" % dxdt[-1])

            #tf_bottle = sampled_recently(duration = 60)
            #tf_sonic  = sampled_recently(duration = 60, channel = 'depth_sonic')
            #logger.info("Received message from worker: Recently sampled.. bottle: %s; sonic: %s" % (str(tf_bottle),str(tf_sonic)))

            algorithm_enabled = get_current_value(channel = 'enable_sampler')

            if algorithm_enabled > 0:  
              # # Take a sample if conditions are met
              # if dxdt[-1] >= min_dflow :  # Water level is rising faster than min_dflow
              #   flag = not( sampled_recently(duration = 30) )
              #   if ( flag ):
              #     post_trigger()
              #     logger.info("Received message from worker: dQ/dt: %f and 30+ minutes since a sample" % dxdt[-1])

              # elif pqpf >= 0.50 :  # Probability of exceeding rainfall is greater than 50%
              #   flag = not( sampled_recently(duration = 60) )
              #   if ( flag ):
              #     post_trigger()
              #     logger.info("Received message from worker: pqpf: %2.2f and 60+ minutes since a sample" % pqpf*100)

              current_state = get_current_value(channel = 'hydrograph_state')
              depth_peak    = get_current_value(channel = 'depth_peak')
              depth_base    = get_current_value(channel = 'depth_base')
              dxdt_max      = get_current_value(channel = 'delta_depth_max')
              pqpf_list     = get_history(channel = 'p_rain')[0]
              depth_list    = get_history(channel = 'depth_sonic')[0]
              pqpf_avg  = .3*pqpf_list[-3] + .4*pqpf_list[-2] + .3*pqpf_list[-1]  # 3-pt Welch Window
              depth = depth_list[-1]

              # CHECK THIS
              if dxdt[-1] >= min_dflow :  # Water level is rising faster than min_dflow
                # hydrograph is now rising
                if not(current_state == RISING or current_state == PEAKING):
                  current_state = RISING
                  # take sample if one hasn't been taken in past 10 mins
                  flag = not( sampled_recently(duration = 10) )

                # inflection in hydrograph: discharge started increasing again 
                # before a peak was reached      
                elif current_state == PEAKING and dxdt[-1] > dxdt[-2]:
                  current_state = RISING  
                  # take sample if one hasn't been taken in past 10 mins
                  flag = not( sampled_recently(duration = 10) )

                if ( flag ):
                  post_trigger()
                
                  logger.info("Received message from worker: dQ/dt: %f triggered and 10+ minutes since a sample" % dxdt[-1])                
  
                if dxdt[-1] > dxdt_max: # update dxdt_max
                  #dxdt_max = dxdt[-1]
                  update_channel(channel='delta_depth_max',value=dxdt[-1])
                
                              
              if current_state == BASEFLOW and pqpf_avg/100 >= 0.10 :
                update_channel(channel='depth_base',value=depth) # update depth_base to baseflow value

                flag = not( sampled_recently(duration = 120) )
                if ( flag ):
                  post_trigger()
                  logger.info("Received message from worker: pqpf: %2.2f and 60+ minutes since a sample" % (pqpf*100))

              if current_state == RISING and dxdt[-1] < dxdt_max and dxdt[-1] > 0:
                # hydrograph was rising, but now the rate is slowing down
                current_state = PEAKING

                # take sample if one hasn't been taken in past 10 mins
                flag = not( sampled_recently(duration = 10) )
                if ( flag ):                
                  post_trigger()
                
                logger.info("Received message from worker: dQ/dt: %f falling" % dxdt[-1])                


              elif (current_state == RISING or current_state == PEAKING) and dxdt[-1] <= 0 :
                # hydrograph has stopped rising and is now transitioning to falling limb
                current_state = PEAK
                #depth_peak = depth  # update depth_peak to value closest to peak
                update_channel(channel='depth_peak',value=depth)

                # take sample if one hasn't been taken in past 10 mins
                flag = not( sampled_recently(duration = 10) )
                if ( flag ):
                  post_trigger()
                
                logger.info("Received message from worker: dQ/dt max: %f now increasing less" % dxdt_max)

              elif current_state == PEAK and depth >= (depth_base - .75*(depth_base - depth_peak)) :
                # for ultrasonic, depth_base is always greater than depth_peak
                # hydrograph now on falling limb.  Currently below 75% max
                current_state = FALLING
                
                # take sample if one hasn't been taken in past 10 mins
                flag = not( sampled_recently(duration = 10) )
                if ( flag ):                
                  post_trigger()
                
                logger.info("Received message from worker: Falling past .75 max depth")

              # Sample if hydrograph rises back above 75% max
              # elif current_state == FALLING and depth < (depth_base - .75*(depth_base - depth_peak)) :
              #   # for ultrasonic, depth_base is always greater than depth_peak
              #   current_state = RISING
              #   if dxdt[-1] > dxdt_max: # update dxdt_max
              #     #dxdt_max = dxdt[-1]
              #     update_channel(channel='delta_depth_max',value=dxdt[-1])
              #
              #   # take sample if one hasn't been taken in past 60 mins
              #   flag = not( sampled_recently(duration = 60) )
              #   if ( flag ):
              #     post_trigger()
              #     logger.info("Received message from worker: Rising past .75 max depth")

              # Hydrograph is approaching baseflow.  Reset depth variables
              elif current_state == FALLING and depth >= (depth_base - .10*(depth_base - depth_peak)) :
                # for ultrasonic, depth_base is always greater than depth_peak
                current_state = BASEFLOW
                update_channel(channel='depth_peak',value=depth_base) #depth_peak = depth_base
                update_channel(channel='delta_depth_max',value=0) #dxdt_max = 0
                
                # take sample if one hasn't been taken in past 10 mins
                flag = not( sampled_recently(duration = 10) )
                if ( flag ):
                  post_trigger()
                
                logger.info("Received message from worker: Returning to baseflow")                

              update_channel(channel='hydrograph_state',value=current_state)


        except (TypeError, ValueError):
            logger.warning('Error retrieving request body for async work.')

    elif method == 'GET':
        #https://gist.github.com/davidbgk/1311056
        d = parse_qs(environ['QUERY_STRING'])  # turns the qs to a dict

        query = 'From GET: %s' % ''.join('%s: %s' % (k, v) for k, v in d.iteritems())      
        logger.info("Received message from worker: %s" % query)

        if 'pqpf' in d:
          
            parsed_json = get_forecast(url)

            hour = []; pop = []; qpf = [];
            for x in range(0,len(parsed_json['hourly_forecast'])):
                hour.append(time.strftime('%Y-%m-%d %H:%M', 
                    time.gmtime(float(parsed_json['hourly_forecast'][x]['FCTTIME']['epoch'])) ))
                pop.append(float(parsed_json['hourly_forecast'][x]['pop'])/100)
                qpf.append(float(parsed_json['hourly_forecast'][x]['qpf']['english'])) #'metric'
              
            poe = calc_pqpf( float(d['pqpf'][0]), pop, qpf )

            out = '<br>'
            for x in range(0,12):
                out += "Forecast for %16s GMT.....POP %2d...QPF %4s...PoE(%.2f) %2.2f <br>" % (hour[x], pop[x]*100, qpf[x], float(d['pqpf'][0]), poe[x]*100)

            url_info['amt'] = d['pqpf'][0]
            url_info['pqpf_str'] = out
        
        else:

          url_info['amt'] = amt
          url_info['pqpf_str'] = '<a href="?pqpf=0.2">Click</a> to Show Forecast'

    status = '200 OK'
    headers = [('Content-type', 'text/html')]
    
    start_response(status, headers)

    return [response.format(**url_info)]


if __name__ == '__main__':
    httpd = make_server('', 8000, application)
    print "Serving on port 8000..."
    httpd.serve_forever()
