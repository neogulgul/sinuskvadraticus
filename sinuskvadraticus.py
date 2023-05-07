import math

def sink(v):
	v = v % 360

	if (v >= 45 and v <= 135):
		return 1

	elif (v >= 135 and v <= 225):
		v = math.radians(v)
		return -math.tan(v)

	elif (v >= 225 and v <= 315):
		return -1

	else:
		v = math.radians(v)
		return math.tan(v)

def cosk(v):
	if (v >= 45 and v <= 135):
		v = math.radians(v)
		return 1 / math.tan(v)

	elif (v >= 135 and v <= 225):
		return -1

	elif (v >= 225 and v <= 315):
		v = math.radians(v)
		return -1 / math.tan(v)

	else:
		return 1

def asink(y, printValues = False):
	if (y < -1 or y > 1): return "only defined for -1 >= y <= 1"
	if (y == 1):
		return "between 45 and 135 degrees"
	elif (y == -1):
		return "between 225 and 315 degrees"
	else:
		v = math.degrees(math.atan(y))
		if (printValues): print(f"{v} or {180 - v}")
		return [v, 180 - v]

def acosk(x, printValues = False):
	if (x < -1 or x > 1): return "only defined for -1 >= x <= 1"
	if (x == 0):
		return [90, 270]
	elif (x == 1):
		return "between 270 and 45 degrees"
	elif (x == -1):
		return "between 135 and 225 degrees"
	else:
		v = math.degrees(math.atan(1 / x))
		if (printValues): print(f"{v} or {360 - v}")
		return [v, 360 - v]
