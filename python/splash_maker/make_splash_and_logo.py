import cv2
import numpy as np
from os.path import join

splash_output_list = [
    (1125, 2436, "1125x2436.png"),
    (1134, 750, "1134x750.png"),
    (1136, 640, "1136x640.png"),
    (1242, 2208, "1242x2208.png"),
    (1536, 2048, "1536x2048.png"),
    (1668, 2224, "1668x2224.png"),
    (2048, 1536, "2048x1536.png"),
    (2048, 2732, "2048x2732.png"),
    (2208, 1242, "2208x1242.png"),
    (2224, 1668, "2224x1668.png"),
    (2436, 1125, "2436x1125.png"),
    (2732, 2048, "2732x2048.png"),
    (640, 1136, "640x1136.png"),
    (750, 1134, "750x1134.png")
]
logo_output_list = [
    (192, "android-chrome-192x192.png"),
    (24, "android-chrome-24x24.png"),
    (46, "android-chrome-46x46.png"),
    (512, "android-chrome-512x512.png"),
    (120, "apple-touch-icon-120x120.png"),
    (152, "apple-touch-icon-152x152.png"),
    (180, "apple-touch-icon-180x180.png"),
    (60, "apple-touch-icon-60x60.png"),
    (76, "apple-touch-icon-76x76.png"),
    (150, "mstile-150x150.png")
]


# MPP #1E7848   (30, 120, 72)
#output_folder = "mpp"
#logo_file = "mpp-logo.png"
#accent_color = (30, 120, 72)
#logo_background_color = (255, 255, 255)
#splash_background_color = (255, 255, 255)

# ODM #E30613   (227, 6, 19)
#output_folder = "odm"
#logo_file = "odm-logo.png"
#accent_color = (227, 6, 19)
#logo_background_color = (0, 0, 0)
#splash_background_color = (255, 255, 255)

# L&S #BC1823   (188, 24, 35)
output_folder = "lns"
logo_file = "lns-logo.png"
accent_color = (188, 24, 35)
logo_background_color = (255, 255, 255)
splash_background_color = (255, 255, 255)

def overlay_image_alpha(img, img_overlay, x, y, alpha_mask):
    """Overlay `img_overlay` onto `img` at (x, y) and blend using `alpha_mask`.
    `alpha_mask` must have same HxW as `img_overlay` and values in range [0, 1].
    """
    # Image ranges
    y1, y2 = max(0, y), min(img.shape[0], y + img_overlay.shape[0])
    x1, x2 = max(0, x), min(img.shape[1], x + img_overlay.shape[1])

    # Overlay ranges
    y1o, y2o = max(0, -y), min(img_overlay.shape[0], img.shape[0] - y)
    x1o, x2o = max(0, -x), min(img_overlay.shape[1], img.shape[1] - x)

    # Exit if nothing to do
    if y1 >= y2 or x1 >= x2 or y1o >= y2o or x1o >= x2o:
        return

    # Blend overlay within the determined ranges
    img_crop = img[y1:y2, x1:x2]
    img_overlay_crop = img_overlay[y1o:y2o, x1o:x2o]
    alpha = alpha_mask[y1o:y2o, x1o:x2o, np.newaxis]
    alpha_inv = 1.0 - alpha

    img_crop[:] = alpha * img_overlay_crop + alpha_inv * img_crop

def generate(width:int, height:int, logo_file:str, bg_color, mode:str):
    logo = cv2.imread(logo_file, cv2.IMREAD_UNCHANGED)

    logo_width = logo.shape[1]
    logo_height = logo.shape[0]

    image = np.zeros((height, width, 4), np.uint8)
    color = (*tuple(reversed(bg_color)), 255)
    image[:] = color

    target_width = width
    if mode == "SPLASH":
        target_width = min(width // 2, logo_width)

    if target_width != logo_width:
        ratio = logo_width / target_width
        target_height = int(logo_height / ratio)
        dim = (target_width, target_height)
        logo = cv2.resize(logo, dim, interpolation = cv2.INTER_AREA)
        logo_width = logo.shape[1]
        logo_height = logo.shape[0]

    logo_x = (width - logo_width) // 2
    logo_y = (height - logo_height) // 2

    alpha_mask = logo[:, :, 3] / 255.0
    img_result = image[:, :, :3].copy()
    img_overlay = logo[:, :, :3]
    overlay_image_alpha(img_result, img_overlay, logo_x, logo_y, alpha_mask)

    return img_result

def main():
    for o in splash_output_list:
        print(o[2])
        img = generate(o[0], o[1], logo_file, splash_background_color, "SPLASH")
        outputfile = join(output_folder, o[2])
        cv2.imwrite(outputfile, img)

    for o in logo_output_list:
        print(o[1])
        img = generate(o[0], o[0], logo_file, logo_background_color, "LOGO")
        outputfile = join(output_folder, o[1])
        cv2.imwrite(outputfile, img)

if __name__ == "__main__":
    main()
