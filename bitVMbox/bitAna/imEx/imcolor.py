import cv2
import numpy as np

def handle_close(evt):
    print('Closed Figure!')

src = cv2.imread("../data/lena.jpg", cv2.IMREAD_COLOR)
b, g, r = cv2.split(src)
imgorg = cv2.merge((b,g,r))
cv2.imshow("ORG", imgorg)
height, width, channel = src.shape
print(height, width)
zero = np.zeros((height, width, 1), dtype = np.uint8)
imgB = cv2.merge((b, zero, zero))
imgG = cv2.merge((zero, b, zero))
imgR = cv2.merge((zero, zero, r))
cv2.imshow("b", imgB)
cv2.imshow("g", imgG)
cv2.imshow("r", imgR)
cv2.waitKey(0)
cv2.destroyAllWindows()