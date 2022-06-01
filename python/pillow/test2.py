from PIL import Image, ImageColor

# https://pillow.readthedocs.io/stable/reference/Image.html

def show_info(msg: str, image):
	print(msg, image.size, image.format)

with Image.open("balloons.jpg") as image:
	show_info("Original", image)
	width = image.size[0]
	height = image.size[1]

	rotated1 = image.rotate(60)
	show_info("Rotated 1", rotated1)
	rotated1.save("rotated1.png")

	rotated2 = image.rotate(60, expand=True, fillcolor=(200, 100, 50))
	show_info("Rotated 2", rotated2)
	rotated2.save("rotated2.png")

	rotated3 = image.rotate(10, expand=True, fillcolor=ImageColor.getcolor("yellow", "RGB"))
	show_info("Rotated 3", rotated3)
	rotated3.save("rotated3.png")


	cropped1 = image.crop((300, 100, 400, 200))
	show_info("Cropped 1", cropped1)
	cropped1.save("cropped1.png")

	"""
	flipped1 = image.transpose(Image.Transpose.FLIP_LEFT_RIGHT)
	show_info("Flipped 1", flipped1)
	flipped1.save("flipped1.png")

	flipped2 = image.transpose(Image.Transpose.FLIP_LEFT_RIGHT)
	show_info("Flipped 2", flipped2)
	flipped2.save("flipped2.png")

	flipped3 = image.transpose(Image.Transpose.TRANSPOSE)
	show_info("Flipped 3", flipped3)
	flipped3.save("flipped3.png")

	flipped4 = image.transpose(Image.Transpose.TRANSVERSE)
	show_info("Flipped 4", flipped4)
	flipped4.save("flipped4.png")
	"""

	resized1 = image.resize((width // 10, height // 10))
	show_info("Resized 1", resized1)
	resized1.save("resized1.png")


	resized2 = image.resize((width // 10, height // 10))
	show_info("Resized 1", resized1)
	resized1.save("resized1.png")
