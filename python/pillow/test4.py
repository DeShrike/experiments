from PIL import Image, ImageColor, ImageFilter

# https://pillow.readthedocs.io/stable/reference/ImageFilter.html

def show_info(msg: str, image):
	print(msg, image.size, image.format)

filters = [
	ImageFilter.BLUR,
	ImageFilter.CONTOUR,
	ImageFilter.DETAIL,
	ImageFilter.EDGE_ENHANCE,
	ImageFilter.EDGE_ENHANCE_MORE,
	ImageFilter.FIND_EDGES,
	ImageFilter.EMBOSS,
	ImageFilter.SHARPEN,
	ImageFilter.SMOOTH,
	ImageFilter.SMOOTH_MORE
]

with Image.open("balloons.jpg") as image:
	show_info("Original", image)
	width = image.size[0]
	height = image.size[1]

	for ix, fil in enumerate(filters):
		filtered = image.filter(fil)
		show_info(f"Filtered {ix}", filtered)
		filtered.save(f"filtered{ix}.jpg")

	filtered_min = image.filter(ImageFilter.MinFilter(size = 5))
	show_info("Filtered Min", filtered_min)
	filtered_min.save("filtered_min.jpg")

	filtered_median = image.filter(ImageFilter.MedianFilter(size = 5))
	show_info("Filtered Median", filtered_median)
	filtered_median.save("filtered_median.jpg")

	filtered_max = image.filter(ImageFilter.MaxFilter(size = 5))
	show_info("Filtered Max", filtered_max)
	filtered_max.save("filtered_max.jpg")

	filtered_boxblur = image.filter(ImageFilter.BoxBlur(radius = 20))
	show_info("Filtered BoxBlur", filtered_boxblur)
	filtered_boxblur.save("filtered_boxblur.jpg")


	filtered_gaussblur = image.filter(ImageFilter.GaussianBlur(radius = 20))
	show_info("Filtered GaussianBlur", filtered_gaussblur)
	filtered_gaussblur.save("filtered_gaussblur.jpg")


	filtered_unsharp = image.filter(ImageFilter.UnsharpMask(radius = 20))
	show_info("Filtered Unsharp", filtered_unsharp)
	filtered_unsharp.save("filtered_boxblur.jpg")
