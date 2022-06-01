from PIL import Image, ImageColor, ImageDraw

# https://pillow.readthedocs.io/stable/reference/ImageFilter.html

def show_info(msg: str, image):
	print(msg, image.mode, image.size, image.format, image.getbands())


with Image.open("balloons.jpg") as image:
	show_info("Original", image)
	width = image.size[0]
	height = image.size[1]

	draw = ImageDraw.Draw(image)

	draw.save("drawing1.jpg")
