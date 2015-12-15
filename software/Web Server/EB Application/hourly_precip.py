import urllib2, json, math, time, sys

def get_pqpf(amt, pop, qpf):
	# Returns the unconditional POE (aka PQPF) for the rainfall amount x, 
	# given x, Probabilility of Precip, and Quantitative Precip. Forecast.
	# Values returned are between 0 and 1
	# inputs:
	# - amt: the amount of rainfall to be exceeded, inches
	# - pop: an array of PoP forecasts
	# - qpf: an array of QPF forecasts
	# 
	# outputs:
	# - upoe: the unconditional Probability of Exceedance/percent QPF
	#
	cqpf = []; upoe = [];
	for x in range(0,len(pop)):
		upoe.append(pop[x])
		# 1. Divide the QPF by the PoP to get the conditional QPF (cQPF). 
		if pop[x] > 0:
			cqpf.append(qpf[x]/pop[x])
		else:
			cqpf.append(0)
		#
		# 2.  Apply one of the following equations: 
		#     a) When PoP =< 90%,  uPOE(x) = PoP * e ^(-x/cQPF) , where x is the rainfall to be exceeded. 
		# This is the exponential distribution or gamma distribution when alpha = 1. 
		#
		if pop[x] <= 0.9:
			if cqpf[x] > 0:
				upoe[x] = pop[x] * math.exp(-amt/cqpf[x])
			else:
				upoe[x] = 0
		#
		# 3. b) When PoP >90%,  uPOE(x) = PoP * 0.5 * e^(-x/b) * [(x^2)/b + (2x/b) + 2], where b = QPF/3
		# The statistical distributions are skewed toward lower values. So, the
		# unconditional probability of exceeding the mean QPF will always be less
		# than 50%; close to 35% for the exponential distribution and about 25% for
		# the gamma distribution when the alpha term is 3.
		#
		if pop[x] > .9:
			b = qpf[x]/3;
			upoe[x] = pop[x] * 0.5 * math.exp(-amt/b) * ((amt*amt)/b + (2*amt/b) + 2);
			
	return upoe



if __name__ == '__main__':

	amt = 0.10
	
	if len(sys.argv) > 1:
		amt = float(sys.argv[1])

	#url = 'http://api.wunderground.com/api/78493aea90691a28/geolookup/conditions/q/IA/Cedar_Rapids.json'
	#url = 'http://api.wunderground.com/api/78493aea90691a28/hourly/q/MI/Ann_Arbor.json'
	latlong = '42.324100,-83.711304'
	url = 'http://api.wunderground.com/api/78493aea90691a28/hourly/q/'+latlong+'.json'

	f = urllib2.urlopen(url)
	json_string = f.read()
	f.close()

	parsed_json = json.loads(json_string)

	hour = []; pop = []; qpf = []; amt = 0.10
	for x in range(0,len(parsed_json['hourly_forecast'])):
		hour.append(time.strftime('%Y-%m-%d %H:%M:%S', 
			time.localtime(float(parsed_json['hourly_forecast'][x]['FCTTIME']['epoch']))))
		#hour.append(parsed_json['hourly_forecast'][x]['FCTTIME']['pretty']) #'epoch', 'hour', etc.
		pop.append(float(parsed_json['hourly_forecast'][x]['pop'])/100)
		qpf.append(float(parsed_json['hourly_forecast'][x]['qpf']['english'])) #'metric'
		
	poe = get_pqpf(amt, pop, qpf)

	for x in range(0,len(pop)):
		print "Forecast at %20s........POP %2d...QPF %4s...PoE(%.2f) %2.2f \r" % (hour[x], pop[x]*100, qpf[x], amt, poe[x]*100)
