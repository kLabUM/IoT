import xively, datetime, random

read_key = "GOgGb3IPwNgwyvKavBJPa1FAg1rqdkL4D0uZI2UNlLj93qWx"
feed_id = 1821537225

api = xively.XivelyAPIClient(read_key)
feed = api.feeds.get(feed_id)

# Test 1
z_stream = feed.datastreams.get('z')

z_stream.datapoints = [xively.Datapoint(datetime.datetime.utcnow(), random.random())]
z_stream.update()

# Test 2
streams = feed.datastreams
for s in streams:
  print s 

depth = feed.datastreams.get('depth_press',end=datetime.datetime(2014,7,4,14,0,0),limit=10,interval=0,duration=600)
depth.datapoints[:]
depth[-1].value
depth[-1].at
[float(d.value) for d in depth.datapoints[-10:]]



if __name__ == '__main__':
    print "Serving on port 8000..."


read_key = "0K4mhTWfaO6T7oO9F6oInk8WHpmx57PUs4WPllIA0QTbbpcB"
feed_id = 643150575
 
api = xively.XivelyAPIClient(read_key)
feed = api.feeds.get(feed_id)


import urllib2, xively, datetime#, scipy.interpolate, scipy.signal
import json
from hourly_precip import get_pqpf as calc_pqpf
# Set Xively Keys and Feed
read_key    = '0K4mhTWfaO6T7oO9F6oInk8WHpmx57PUs4WPllIA0QTbbpcB'
trigger_key = 'POrYI0SaySTf9h9WbgCqQz09mkDVzSSE304KnLaYQAm4EGsu'
p_rain_key  = '6qQdISUcAGj8L6Y3A4vpmgECnPwFwI8pq5yEPVEoyPVmdtz3'
feed_id     =  643150575
# Set Weather Underground Info
latlong = '42.324100,-83.711304'
url = 'http://api.wunderground.com/api/78493aea90691a28/hourly/q/'+latlong+'.json'
amt = 0.10

def test_scipy():
  x = range(-20,20)
  y = [0.0066,-0.0000,-0.0000,-0.0000,0.0033,0.0016,0.0033,0.0033,-0.0000,0.0033,0.0049,0.0049,-0.0000,0.0049,-0.0000,0.0098,0.0016,-0.0000,0.0000,-0.0016,0.0066,0.0016,0.0000,0.0033,0.0115,0.0049,0.0180,0.0115,0.0148,0.0082,0.0049,0.0066,0.0098,0.0115,0.0082,0.0016,0.0049,0.0066,0.0066,0.0082]
  # first, make a function to linearly interpolate the data
  f = interp(x,y)
  # resample with 1000 samples
  xx = np.linspace(-20,19, 1000)
  # compute the function on this finer interval
  yy = f(xx)
  # make a gaussian window
  window = gauss(200, 60)
  # convolve the arrays
  smoothed = conv(yy, window/window.sum(), mode='same')
  # get the maximum
  return xx[np.argmax(smoothed)]

# Set Weather Underground Info
latlong = '42.324100,-83.711304'
url = 'http://api.wunderground.com/api/78493aea90691a28/hourly/q/'+latlong+'.json'
amt = 0.10
def get_forecast(link = url):
  f = urllib2.urlopen(link)
  json_string = f.read()
  f.close()
  parsed_json = json.loads(json_string)
  return parsed_json

def get_pqpf(parsed_json, amt = 0.10):
  epoch = float(parsed_json['hourly_forecast'][0]['FCTTIME']['epoch'])
  pop   = float(parsed_json['hourly_forecast'][0]['pop'])/100
  qpf   = float(parsed_json['hourly_forecast'][0]['qpf']['english'])
  pqpf  = calc_pqpf(amt, [pop], [qpf])
  return pqpf, pop, qpf, epoch


def update_channel(channel, value, key, feedID, at):
    # Connect to Xively  
  api = xively.XivelyAPIClient(key)
  feed = api.feeds.get(feedID)
  stream = feed.datastreams.get(channel)
  stream.datapoints = [xively.Datapoint(at, value)]
  stream.update()


def post_forecast(pqpf = 0.0, channel = 'p_rain', key = p_rain_key, feedID = feed_id):  
  # Connect to Xively  
  # api = xively.XivelyAPIClient(key)
  # feed = api.feeds.get(feedID)
  # stream = feed.datastreams.get(channel)
  # stream.datapoints = [xively.Datapoint(datetime.datetime.utcnow(), pqpf)]
  # stream.update()
  update_channel(value = pqpf, channel = channel, key = key, feedID = feedID, at = datetime.datetime.utcnow())


def post_trigger(value = 0, channel = 'trigger_sampler', key = trigger_key, feedID = feed_id):
  # Connect to Xively  
  # api = xively.XivelyAPIClient(key)
  # feed = api.feeds.get(feedID)
  # stream = feed.datastreams.get(channel)
  # stream.datapoints = [xively.Datapoint(datetime.datetime.utcnow(), value)]
  # stream.update()  
  update_channel(value = value, channel = channel, key = key, feedID = feedID, at = datetime.datetime.utcnow())

def get_history(channel = 'bottle', duration = 60, key = read_key, feedID = feed_id, interval = 0):
  # Retrieve the data taken within [duration] minutes ago,
  # [duration] can at most be 6 hours if interval is 0
  if duration > 300 and interval == 0:
    duration = 300
  elif duration <= 0:
    duration = 60
    interval = 0    
  dur_string = str(duration) + "minutes"
  # Connect to XivelyAPIClient
  api = xively.XivelyAPIClient(key)
  feed = api.feeds.get(feedID)
  stream = feed.datastreams.get(channel)
  # Get data from past [duration] minutes and store values in lists
  data   = stream.datapoints.history(duration = dur_string, interval = interval, end = datetime.datetime.utcnow() ) 
  points = [d for d in data]                  # List of xively.Datapoints
  values = [float(p.value) for p in points]   # List of floats
  times  = [p.at for p in points]             # List of datetimes
  return values, times

def sampled_recently(channel = 'bottle', duration = 60, key = read_key, feedID = feed_id, interval = 0):
  # Check oldest sample within [duration] minutes ago, and if the value is the same
  # as the current value, then the channel hasn't been sampled recently
  # Another method could be to check the number of samples between now and 
  # [duration] minutes ago  
  values, _ = get_history(channel, duration, key, feedID, interval)  
  # Alternatively...
  # points=feed.datastreams.get('x',end=datetime.datetime.utcnow(),interval=interval,duration=dur_string)
  # [d.value for d in points.datapoints]
  # [d.at for d in points.datapoints]
  # Check if oldest value is the same as current value.  
  # Sampled recently taken if the two values are different
  return values[0] != values[-1]


forecast = get_forecast(url)
pqpf, pop, qpf, epoch = get_pqpf(forecast)
post_forecast(pqpf[0]*100)
logger.info("Received message from worker: at: %f, pop: %2d, qpf: %4s, pqpf: %2.2f" % (epoch, pop, qpf, pqpf[0]*100))
pqpf, pop, qpf, epoch = get_pqpf(forecast,amt=0.01)
post_forecast(pqpf[0]*100, channel = 'p_rain001')


from math import exp, sqrt, pi
from numpy import array

x = [734991.0000000031,734991.0208333364, 734991.0416666698, 734991.0625000032, 734991.0833333365, 734991.1041666699, 734991.1250000033, 734991.1458333366, 734991.1666666700, 734991.1875000034]
y = [437.0000,421.0000,423.0000,428.0000,401.0000,413.0000,403.0000,412.0000,406.0000,406.0000]
out = y*0
h = 0.3

def kernel(x_in):
  x = float(x_in)
  return exp(-x*x/2)/sqrt(2*pi)

[gauss(x) for x in float(range(-5,6))]

N=length(x);
r.x=x;%linspace(min(x),max(x),N);
r.f=zeros(1,N);
for k=1:N
    z=kerf((r.x(k)-x)/h);
    r.f(k)=sum(z.*y)/sum(z);
end

for k in range(0,len(x)):
  z = [kernel(el) for el in (x[k]-x)/h]
  out[k] = sum(z*y)/sum(z)

forecast = get_forecast(url)

pqpf = get_pqpf(forecast,amt=0.01)[0]
post_forecast(pqpf*100, channel = 'p_rain001')
pqpf, pop, qpf, epoch = get_pqpf(forecast)
post_forecast(pqpf*100)
tf_bottle = sampled_recently(duration = 60)
tf_sonic  = sampled_recently(duration = 60, channel = 'depth_sonic')
logger.info("Received message from worker: Recently sampled.. bottle: %s; sonic: %s" % (str(tf_bottle),str(tf_sonic)))

dxdt = dchannel_dt(channel = 'depth_sonic')
dxdt = [-d/12 for d in dxdt] #invert values for sonic sensor, convert to mm/5 mins
update_channel(value=dxdt[-1], channel='delta_depth_sonic')

info = """
{
    "id":39489,
    "url":"http://api.xively.com/v2/triggers/39489",
    "type":"change",
    "threshold_value":"",
    "timestamp":"2014-07-04T18:30:08.738433Z",
    "environment": {
        "id":643150575,
        "feed":"http://api.xively.com/v2/feeds/643150575",
        "title":"HRW Node",
        "description":null,
        "private":true
  },
  "triggering_datastream":{
        "id":"depth_press",
        "url":"http://api.xively.com/v2/feeds/643150575/datastreams/depth_press",
        "at":"2014-07-04T18:30:08.648948Z",
        "value":{
              "max_value":10.4215,
              "min_value":10.0562,
              "value":"10.286900"
        },
        "units":{
              "type":null,
              "symbol":"",
              "label":""
    }
  }
}
"""
    