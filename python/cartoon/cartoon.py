import cv2
import numpy as np
from os import listdir
from os.path import isfile, join

def process_file(inputFile: str, outputFile: str):

	print(f"Reading {inputFile} ...", end = "", flush = True)
	img = cv2.imread(inputFile)

	print(" Step A...", end = "", flush = True)
	gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

	smoothness = 5

	print(" B...", end = "", flush = True)
	gray = cv2.medianBlur(gray, smoothness)

	width = 19
	detail = 5

	print(" C...", end = "", flush = True)
	edges = cv2.adaptiveThreshold(gray, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY, width, detail)

	print(" D...", end = "", flush = True)
	color = cv2.bilateralFilter(img, 9, 250, 250)

	print(" E...", end = "", flush = True)
	cartoon = cv2.bitwise_and(color, color, mask = edges)

	print(f" Writing {outputFile} ...", end = "", flush = True)
	cv2.imwrite(outputFile, cartoon)

	print(" Done")


def isJpeg(filename):
	return filename[-4:] == ".jpg"


def process_folder(folderName: str):
	onlyfiles = [f for f in listdir(folderName) if isfile(join(folderName, f)) and isJpeg(f) and "cartoon" not in f]
	for f in onlyfiles:
		of = f[0:-4] + ".cartoon" + f[-4:]
		# print(join(folderName, f), join(folderName, of))
		process_file(join(folderName, f), join(folderName, of))

if __name__ == "__main__":
	process_folder(".")
