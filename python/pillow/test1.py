from PIL import Image

# image = Image.open("balloons.jpg")

with Image.open("balloons.jpg") as image:
	print(image.size)
	print(image.filename)
	print(image.format)
	print(image.format_description)

image_blank = Image.new("RGBA", (800, 600))

image_blank.save("test1.png")

