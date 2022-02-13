import cv2
from pyzbar.pyzbar import decode

img = cv2.imread("RSL.png")

results = decode(img)

for ix, rec in enumerate(results):
   print(rec)
   #print(ix, rec["type"], rec["data"])


