from PIL import Image, ImageColor, ImageFilter

# https://pillow.readthedocs.io/stable/reference/ImageFilter.html

def show_info(msg: str, image):
	print(msg, image.mode, image.size, image.format, image.getbands())


with Image.open("balloons.jpg") as image:
	show_info("Original", image)
	width = image.size[0]
	height = image.size[1]

	red_channel = image.getchannel("R")
	red_channel.save("red_channel.jpg")

	green_channel = image.getchannel("G")
	green_channel.save("green_channel.jpg")

	blue_channel = image.getchannel("B")
	blue_channel.save("blue_channel.jpg")

	grey_1bit = image.convert("1")
	show_info("1 bit greyscale", grey_1bit)
	grey_1bit.save("grey_1bit.jpg")

	greyscale = image.convert("L")
	show_info("greyscale", greyscale)
	greyscale.save("greyscale.jpg")

	palette = image.convert("P")
	show_info("palette", palette)
	palette.save("palette.png")

	# new_palette = [x // 2 for x in palette.getpalette()]
	# palette.putpallete(new_palette)
	# palette.save("palette2.png")

	# palette_16 = image.convert("P", palette = Image.Palette.ADAPTIVE, colors = 16)
	# show_info("palette 16", palette_16)
	# palette_16.save("palette_16.png")

	for x in range(200, width - 200):
		for y in range(100, height - 100):
			pi = image.getpixel((x, y))
			if pi[0] > 150:
				image.putpixel((x, y), (pi[0] // 2, pi[2], pi[1]))
	image.save("recolor.jpg")
