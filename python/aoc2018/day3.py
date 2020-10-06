import math
import re

# https://adventofcode.com/2018

day = "day3"
Day = "Day 3"

inputfile = "input-" + day + ".txt"
inputdata = []

claims = []

#########################################
#########################################

def ReadInput():
	file = open(inputfile, "r")
	for line in file:
		inputdata.append(line.strip())
	file.close()

#########################################
#########################################

class Claim():
	def __init__(self, id, left, top, width, height):
		self.id = id
		self.left = left
		self.top = top
		self.width = width
		self.height = height

def Parse(line, rx):
	match = rx.search(line)
	if match:
		id = int(match["id"])
		left = int(match["left"])
		top = int(match["top"])
		width = int(match["width"])
		height = int(match["height"])
		# print(line, id, left, top, width, height)
		return Claim(id, left, top, width, height)
	else:
		return None

def ParseInput():
	rx = re.compile("#(?P<id>[0-9]*) @ (?P<left>[0-9]*),(?P<top>[0-9]*): (?P<width>[0-9]*)x(?P<height>[0-9]*)")

	claims.clear()
	for line in inputdata:
		c = Parse(line, rx)
		if c is not None:
			claims.append(c)
		else:
			print("Parse error: ", line)

#########################################
#########################################

def TestData():
	inputdata.clear()
	inputdata.append("#1 @ 1,3: 4x4")
	inputdata.append("#2 @ 3,1: 4x4")
	inputdata.append("#3 @ 5,5: 2x2")

	# Answer Part A = 4
	# Answer Part B = 3

#########################################
#########################################

def FindExtends():
	# Finding extends
	maxx = 0
	maxy = 0
	for claim in claims:
		if claim.left + claim.width > maxx:
			maxx = claim.left + claim.width
		if claim.top + claim.height > maxy:
			maxy = claim.top + claim.height

	print(f"Extends: {maxx}x{maxy}")
	return maxx, maxy	

def PartA():
	print("Part A")

	maxx, maxy = FindExtends()
	grid = [ [ 0 for x in range(maxx) ] for y in range(maxy)]

	for claim in claims:
		for x in range(claim.left, claim.left + claim.width):
			for y in range(claim.top, claim.top + claim.height):
				grid[y][x] += 1

	overlaps = 0
	for y in range(maxy):
		for x in range(maxx):
			if grid[y][x] > 1:
				overlaps += 1

	print("Answer:", overlaps)

#########################################
#########################################

def PartB():
	print("Part B")

	maxx, maxy = FindExtends()
	grid = [ [ 0 for x in range(maxx) ] for y in range(maxy)]

	# apply claims
	for claim in claims:
		for x in range(claim.left, claim.left + claim.width):
			for y in range(claim.top, claim.top + claim.height):
				grid[y][x] += claim.id

	# verify claims
	goodclaimid = None
	for claim in claims:
		bad = False
		for x in range(claim.left, claim.left + claim.width):
			for y in range(claim.top, claim.top + claim.height):
				if grid[y][x] != claim.id:
					bad = True
					break
		if bad == False:
			goodclaimid = claim.id

	print("Answer:", goodclaimid)

#########################################
#########################################

if __name__ == "__main__":
	print(Day)
	ReadInput()
	# TestData()
	ParseInput()
	PartA()
	PartB()
