import math

# https://adventofcode.com/2018

inputfile = "input-day1.txt"
inputdata = []

#########################################
#########################################

def ReadInput():
	file = open(inputfile, "r")
	for line in file:
		inputdata.append(int(line.strip()))
	file.close()

#########################################
#########################################

def TestData():
	inputdata.append(7)
	inputdata.append(7)
	inputdata.append(-2)
	inputdata.append(-7)
	inputdata.append(-4)

#########################################
#########################################

def PartA():
	print("Part A")
	total = 0
	for m in inputdata:
		total += m

	print("Answer:", total)

#########################################
#########################################

def PartB():
	print("Part B")

	loop = 0
	total = 0
	history = []
	found = False
	while found == False:
		loop += 1
		print(loop, total, len(history))
		for m in inputdata:
			total += m
			if total in history:
				found = True
				break
			history.append(total)

	print("Answer:", total)

#########################################
#########################################

if __name__ == "__main__":
	print("Day 1")
	ReadInput()
	# TestData()
	PartA()
	PartB()


