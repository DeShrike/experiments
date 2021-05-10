from NeuralNetwork import NeuralNetwork
from PIL import Image, ImageDraw, ImageFont, ImageOps
from os import walk
import numpy as np
import random

# OR
X = [ [0, 0], [0, 1], [1, 0], [1, 1] ]
y = [ [0], [1], [1], [1]]
par = { "inn": 2, "hl": 1, "hn": 4, "oun": 1}

X = [ [0, 0, 0], [0, 0, 1], [0, 1, 0], [0, 1, 1], [1, 0, 0], [1, 0, 1], [1, 1, 1] ]
y = [ [0], [0], [0], [1], [0], [1], [0]]
par = { "inn": 3, "hl": 1, "hn": 4, "oun": 1}

# XOR
#X = [ [0, 0], [0, 1], [1, 0], [1, 1] ]
#y = [ [0], [1], [1], [0]]
#par = { "inn": 2, "hl": 1, "hn": 2, "oun": 1}

X = None
y = None
nn = None
testfiles = []
stats = {}

def create():
	global X, y, nn

	X, y = read_all()

	par = { "inn": 32 * 32, "hl": 3, "hn": 32 * 32 // 2, "oun": 10 }

	print(X.shape)
	print(y.shape)

	nn = NeuralNetwork(**par)

	testfiles.clear()
	for (dirpath, dirnames, filenames) in walk("predict"):
		testfiles.extend(filenames)

def train(nn):
	epochs = 10
	print("Training")
	nn.train(X, y, 0.1, epochs)
	return epochs

def test(nn, epochs):
	results = []
	total = 0
	correct = 0
	for file in testfiles:
		total += 1
		img = Image.open("predict/" + file)
		img = ImageOps.grayscale(img)
		np_img = np.array(img) 
		np_img = (1 - (np_img / 255.0))
		np_img = np_img.reshape( (1, 32 * 32) )

		y = nn.predict(np_img)
		ylist = y.tolist()[0]
		m = max(ylist)
		ix = ylist.index(m)
		label = int(file[0:1])

		success = ix == label
		if success:
			correct += 1
		print(ix, file, "" if success else "BAD")
		if success:
			results.append((ix, file, "" if success else "BAD", ylist))
	
	proc = (correct / total) * 100.0
	msg = f"Correct: {correct}/{total}  {proc:.3f}%  after {epochs} epochs"
	print(msg)
	stats[epochs] = proc

	print("Saving")
	with open("results.txt", "a") as f:
		for res in results:
			f.write(str(res) + "\n")
		f.write(msg + "\n")

def read_all():
	files = []
	for (dirpath, dirnames, filenames) in walk("digits"):
		files.extend(filenames)

	random.shuffle(files)

	labels = []
	X = np.empty( (0, 32 * 32) )
	for file in files:
		print(file, end = "\r")
		label = [0 for _ in range(10)]
		label[int(file[0:1])] = 1
		labels.append(label)
		img = Image.open("digits/" + file)
		img = ImageOps.grayscale(img)
		np_img = np.array(img) 
		np_img = (1 - (np_img / 255.0))
		np_img = np_img.reshape( (1, 32 * 32) )
		X = np.append(X, np_img, axis = 0)
	
	y = np.array(labels)
	#y = y.reshape( ( len(labels), 1) )
	print(X.shape)
	print(y.shape)
	return X, y

def simple_test():

	XX = np.array(X)
	yy = np.array(y)
	nn = NeuralNetwork(**par)

	print(XX.shape)
	print(yy.shape)

	#nn.train(XX, yy, 0.1, 10000)

	for XXX in X:
		XX = np.array(XXX)
		yy = nn.predict(XX)
		print(XXX, yy)

def main():
	#simple_test()
	total_epochs = 0
	create();
	for i in range(100):
		total_epochs += train(nn)
		test(nn, total_epochs)

	print(stats)

	with open("results.txt", "a") as f:
		f.write(str(stats) + "\n")

if __name__ == "__main__":
	main()
