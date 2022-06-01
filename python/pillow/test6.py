from PIL import Image, ImageColor, ImageOps

# https://pillow.readthedocs.io/stable/reference/ImageFilter.html

def show_info(msg: str, image):
	print(msg, image.mode, image.size, image.format, image.getbands())


with Image.open("balloons.jpg") as image:
	show_info("Original", image)
	width = image.size[0]
	height = image.size[1]

	image_contrast = ImageOps.autocontrast(image = image, cutoff = 20)
	image_contrast.save("autocontrast.jpg")

	image_inverted = ImageOps.invert(image = image)
	image_inverted.save("inverted.jpg")

	image_solarized = ImageOps.solarize(image = image, threshold = 100)
	image_solarized.save("solarized.jpg")

	image_posterize = ImageOps.posterize(image = image, bits = 2)
	image_posterize.save("posterize.jpg")

	image_grayscale = ImageOps.grayscale(image = image)
	image_grayscale.save("grayscale.jpg")

	image_equalized = ImageOps.equalize(image = image)
	image_equalized.save("equalized.jpg")

	image_colorized = ImageOps.colorize(image = image.convert("L"), black = "black", white = "red")
	image_colorized.save("colorized1.jpg")

	image_colorized = ImageOps.colorize(image = image.convert("L"), black = "red", white = "white")
	image_colorized.save("colorized2.jpg")

	mirror = ImageOps.mirror(image = image)
	mirror.save("mirror.jpg")

	flip = ImageOps.flip(image = image)
	flip.save("flip.jpg")

	scaled = ImageOps.scale(image = image, factor = 0.5)
	scaled.save("scaled.jpg")

	# contain = ImageOps.contain(image = image, size = (200, 200))
	# contain.save("contain.jpg")

	border = ImageOps.expand(image = image, border = 100, fill = ImageColor.getcolor("yellow", "RGB"))
	border.save("border.jpg")

	padded = ImageOps.pad(image = image, size = (width + 200, height + 100))
	padded.save("padded.jpg")

	fitted = ImageOps.fit(image = image, size = (width // 2, height // 2))
	fitted.save("fitted.jpg")

	cropped = ImageOps.crop(image = image, border = 100)
	cropped.save("cropped.jpg")

	class Deformer1():
		def getmesh(self, image):
			# define shape in original image
			source_shape = (0, 0, 0, height, width // 2, height, width, 0)

			# define rectangle in new image
			target_rect = (0, 0, width // 2, height // 2) # left, top, right, bottom

			# return all shapes
			return [(target_rect, source_shape)]

	deformed1 = ImageOps.deform(image, Deformer1())
	deformed1.save("deformed1.jpg")

	class Deformer2():
		def getmesh(self, image):
			left_t = (0, 0, width // 2, height)
			left_s = (0, 0, 0, height, width // 2, height, width // 2, 0)
			left = (left_t, left_s)

			right_t = (width // 2, 0, width, height)
			right_s = (width // 2, 0, width // 2, height, 0, height, 0, 0)
			right = (right_t, right_s)

			return [left, right]

	deformed2 = ImageOps.deform(image, Deformer2())
	deformed2.save("deformed2.jpg")
