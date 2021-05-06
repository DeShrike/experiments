from PIL import Image, ImageDraw, ImageFont, ImageOps
from os import walk
import numpy as np
import random

# https://www.tutorialspoint.com/python_pillow/python_pillow_quick_guide.htm
# https://pillow.readthedocs.io/en/stable/reference/ImageDraw.html#methods

def create():
	img = Image.new("RGB", (32, 32), color = "white")

	draw = ImageDraw.Draw(img)
	font1 = ImageFont.truetype("PetitaMedium.ttf", 32)
	font2 = ImageFont.truetype("Retroica.ttf", 32)

	for label in range(10):
		print(label)
		ix = 0
		for j in range(25):
			ix += 1
			rx = random.randint(0, 8) - 4
			ry = random.randint(0, 4) - 2
			draw.rectangle([0,0, img.width, img.height], fill = (255, 255, 255))
			draw.text((img.width // 2 + rx, img.height // 2 + ry), str(label), fill = (0, 0, 0), font = font1, align = "center", anchor = "mm")  
			img.save(f"digits/{label}-{ix:03}.png")
			ix += 1
			rx = random.randint(0, 8) - 4
			ry = random.randint(0, 4) - 2
			draw.rectangle([0,0, img.width, img.height], fill = (255, 255, 255))
			draw.text((img.width // 2 + rx, img.height // 2 + ry), str(label), fill = (0, 0, 0), font = font2, align = "center", anchor = "mm")  
			img.save(f"digits/{label}-{ix:03}.png")

	for label in range(10):
		print(label)
		ix = 0
		for j in range(25):
			ix += 1
			rx = random.randint(0, 8) - 4
			ry = random.randint(0, 4) - 2
			draw.rectangle([0,0, img.width, img.height], fill = (255, 255, 255))
			draw.text((img.width // 2 + rx, img.height // 2 + ry), str(label), fill = (0, 0, 0), font = font1, align = "center", anchor = "mm")  
			img.save(f"digits/{label}-{ix:03}.png")
			ix += 1
			rx = random.randint(0, 8) - 4
			ry = random.randint(0, 4) - 2
			draw.rectangle([0,0, img.width, img.height], fill = (255, 255, 255))
			draw.text((img.width // 2 + rx, img.height // 2 + ry), str(label), fill = (0, 0, 0), font = font2, align = "center", anchor = "mm")  
			img.save(f"predict/{label}-{ix:03}.png")

def test():
	img = Image.new("RGB", (640, 640), color = "white")

	draw = ImageDraw.Draw(img)
	draw.ellipse((0, 0, img.width / 2, img.height / 2), fill = (0, 0, 0), outline = (128, 0, 0), width = 5)
	draw.rectangle((100, 100, img.width - 100, img.height - 100), fill = (0, 0, 0), outline = (0, 128, 0), width = 5)

	draw.polygon(
	   ((200, 200), (300, 100), (250, 50)),
	   fill = (255, 0, 0),
	   outline = (0, 0, 0))

	draw.line((0, 0, img.width, img.height), fill = (0, 0, 255), width = 10)

	draw.point([(100, 100)], fill = "yellow")

	imgr = img.rotate(10, fillcolor = "white", resample = Image.BILINEAR)

	imgr.save("test.png")

def readall():
	files = []
	for (dirpath, dirnames, filenames) in walk("digits"):
		files.extend(filenames)

	labels = []
	X = np.empty( (0, 32 * 32) )
	for file in files:
		print(file)
		labels.append(file[0:1])
		img = Image.open("digits/" + file)
		img = ImageOps.grayscale(img)
		np_img = np.array(img) 
		np_img = (1 - (np_img / 255.0))
		np_img = np_img.reshape( (1, 32 * 32) )
		X = np.append(X, np_img, axis = 0)
	
	y = np.array(labels)
	print(X.shape)
	print(y)
	print(y.shape)

def readimg():
	img = Image.open("digits/0-002.png") 
	img = ImageOps.grayscale(img)

	np_img = np.array(img) 
  
	np_img = (1 - (np_img / 255.0))
	np_img = np_img.reshape( (32 * 32,) )
	print(np_img.size)
	print(np_img.shape)
	print(np_img)

def main():
	#test()
	create()
	#readimg()
	#readall()

if __name__ == "__main__":
	main()
