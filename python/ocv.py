import cv2
import numpy as np

img = cv2.imread("hotel.jpg", cv2.IMREAD_COLOR)
print(img.shape)
# img = imread("dome.jpg", cv2.IMREAD_GRAYSCALE)
# img = imread("dome.jpg", cv2.IMREAD_UNCHANGED))

# img2 = cv2.resize(img, (100, 100))
img2 = cv2.resize(img, (0, 0), fx = 0.5, fy = 0.5)
print(img2.shape)

# img3 = cv2.rotate(img2, cv2.cv2.ROTATE_90_CLOCKWISE)
# img3 = cv2.rotate(img2, cv2.cv2.ROTATE_180)
img3 = img2
print(img3.shape)

cv2.imwrite("new.jpg", img3)

# copy: take row 10 to 40, col 30 to 80
tag = img3[10:40, 30:80]
img3[30:60, 50:100] = tag

cv2.imwrite("new2.jpg", img3)

width = img3.shape[1]
height = img3.shape[0]
smaller = cv2.resize(img3, (0, 0), fx = 0.5, fy = 0.5)
swidth = smaller.shape[1]
sheight = smaller.shape[0]
print("smaller: {smaller.shape}")

hsv = cv2.cvtColor(smaller, cv2.COLOR_BGR2HSV)
hsv2 = cv2.cvtColor(smaller, cv2.COLOR_RGB2HSV)
print("hsv: {hsv.shape}")
print("hsv2: {hsv2.shape}")
lower_blue = np.array([110, 50, 50])
upper_blue = np.array([130, 255, 255])

mask = cv2.inRange(hsv, lower_blue, upper_blue)
result = cv2.bitwise_and(smaller, smaller, mask = mask)

newshape = (sheight * 2, swidth * 2, img3.shape[2])

img4 = np.zeros(newshape, np.uint8)
img4[:sheight, :swidth] = smaller
img4[sheight:, :swidth] = hsv
img4[:sheight, swidth:] = hsv2
img4[sheight:, swidth:] = result

cv2.imwrite("new3.jpg", img4)

grey = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)
corners = cv2.goodFeaturesToTrack(grey, 100, 0.1, 10)
corners = np.int0(corners)

for corner in corners:
    x, y =corner.ravel()
    cv2.circle(img2, (x,y), 5, (255,0,0), -1)

for i in range(len(corners)):
    for j in range(i + 1, len(corners)):
        corner1 = tuple(corners[i][0])
        corner2 = tuple(corners[j][0])
        color = np.random.randint(0, 255, size = 3)
        color = tuple(map(lambda x: int(x), color))
        # cv2.line(img2, corner1, corner2, color, 1)



cv2.imwrite("new4.jpg", grey)
cv2.imwrite("new5.jpg", img2)

print(cv2.data.haarcascades)

# blue = img2[:, :, 0]

blue, green, red = cv2.split(img2)

cv2.imwrite("new5.jpg", img2)

#img_merged = cv2.merge(blue, green, red)

cv2.imwrite("new6.jpg", blue)
cv2.imwrite("new7.jpg", green)
cv2.imwrite("new8.jpg", red)

