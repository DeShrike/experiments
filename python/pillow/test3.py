from PIL import Image, ImageColor, ImageEnhance

# https://pillow.readthedocs.io/stable/reference/ImageEnhance.html

def show_info(msg: str, image):
	print(msg, image.size, image.format)


with Image.open("balloons.jpg") as image:
	show_info("Original", image)
	width = image.size[0]
	height = image.size[1]

	color_enhancer = ImageEnhance.Color(image)
	enhanced1 = color_enhancer.enhance(2)
	show_info("Enhanced 1", enhanced1)
	enhanced1.save("enhanced1.jpg")

	contrast_enhancer = ImageEnhance.Contrast(image)
	enhanced2 = contrast_enhancer.enhance(2)
	show_info("Enhanced 2", enhanced2)
	enhanced2.save("enhanced2.jpg")

	brightness_enhancer = ImageEnhance.Brightness(image)
	enhanced3 = brightness_enhancer.enhance(2)
	show_info("Enhanced 3", enhanced3)
	enhanced3.save("enhanced3.jpg")

	sharpness_enhancer = ImageEnhance.Sharpness(image)
	enhanced4 = sharpness_enhancer.enhance(2)
	show_info("Enhanced 4", enhanced4)
	enhanced4.save("enhanced4.jpg")
