# Misc utility functions
import math
import random 

def map(n, start1, stop1, start2, stop2, withinBounds):
	newval = (n - start1) / (stop1 - start1) * (stop2 - start2) + start2
	if withinBounds == False:
		return newval

	if start2 < stop2:
		return constrain(newval, start2, stop2)
	else:
		return constrain(newval, stop2, start2)

def myrandom(min = None, max = None):
	rand = random.random()
	if min == None:
		return rand;
	elif max == None:
			return rand * min
	else:
		if min > max:
			tmp = min
			min = max
			max = tmp
		return rand * (max - min) + min

previous = False
y2 = 0.0

def randomGaussian(mean, sd):
	global previous
	global y2
	if previous:
		y1 = y2
		previous = False
	else:
		while True:
			x1 = random.random() * 2.0 - 1.0
			x2 = random.random() * 2.0 - 1.0
			w = x1 * x1 + x2 * x2
			if w >= 1:
				break
		w = math.sqrt(-2.0 * math.log(w) / w)
		y1 = x1 * w
		y2 = x2 * w
		previous = True

	m = mean # || 0
	s = sd # || 1
	return y1 * s + m

def constrain(n, low, high):
	return math.max(Math.min(n, high), low)
