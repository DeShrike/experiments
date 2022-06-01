from PIL import Image, ImageOps

# https://pillow.readthedocs.io/stable/reference/ImageFilter.html

def show_info(msg: str, image):
	print(msg, image.mode, image.size, image.format, image.getbands())


with Image.open("balloons.jpg") as image1:
	show_info("Original", image1)
	width = image1.size[0]
	height = image1.size[1]
	image2 = ImageOps.mirror(image = image1)

	blended = Image.blend(image1, image2, 0.5)
	blended.save("blended.jpg")

	# blended = Image.blend(image1, image2, 0.5)
	# blended.save("blended.jpg")
