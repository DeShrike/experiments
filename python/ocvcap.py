import requests
import cv2
import numpy as np

url = "http://192.168.0.100:8080/shot.jpg"

while True:

    data = requests.get(url)
    img_arr = np.array(bytearray(data.content, dtype = np.uint8)
    img = cv2.imdecode(img_arr, -1)

    cv2.imshow("Cam", img)

    if cv2.waitKey(1) == 27:
        break

cv2.destroyAllWindows()

