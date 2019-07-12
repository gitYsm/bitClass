import cv2
import numpy as np
def nothing(x):
    pass

def onChange(pos): # 트랙바 핸들러
    global img
    ilowH = cv2.getTrackbarPos('lowH', 'image')
    ihighH = cv2.getTrackbarPos('highH', 'image')
    ilowS = cv2.getTrackbarPos('lowS', 'image')
    ihighS = cv2.getTrackbarPos('highS', 'image')
    ilowV = cv2.getTrackbarPos('lowV', 'image')
    ihighV = cv2.getTrackbarPos('highV', 'image')

    hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
    lower_hsv = np.array([ilowH, ilowS, ilowV])
    higher_hsv = np.array([ihighH, ihighS, ihighV])
    mask = cv2.inRange(hsv, lower_hsv, higher_hsv)

    frame = cv2.bitwise_and(img, img, mask=mask)

    # show thresholded image
    cv2.imshow('image', frame)

img = cv2.imread("../data/lena.jpg", cv2.IMREAD_COLOR)
cv2.namedWindow("Trackbars")

ilowH = 0
ihighH = 179

ilowS = 0
ihighS = 255
ilowV = 0
ihighV = 255
hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
lower_blue = (0-5, 150, 150)
upper_blue = (0+5, 255, 255)
img_mask = cv2.inRange(hsv, lower_blue, upper_blue)


img_result = cv2.bitwise_and(img, img, mask = img_mask)

# show thresholded image
cv2.imshow('image', img_result)
# create trackbars for color change
cv2.createTrackbar('lowH','image',ilowH,179,onChange)
cv2.createTrackbar('highH','image',ihighH,179,onChange)

cv2.createTrackbar('lowS','image',ilowS,255,onChange)
cv2.createTrackbar('highS','image',ihighS,255,onChange)

cv2.createTrackbar('lowV','image',ilowV,255,onChange)
cv2.createTrackbar('highV','image',ihighV,255,onChange)


# get trackbar positions
# ilowH = cv2.getTrackbarPos('lowH', 'image')
# ihighH = cv2.getTrackbarPos('highH', 'image')
# ilowS = cv2.getTrackbarPos('lowS', 'image')
# ihighS = cv2.getTrackbarPos('highS', 'image')
# ilowV = cv2.getTrackbarPos('lowV', 'image')
# ihighV = cv2.getTrackbarPos('highV', 'image')


k = cv2.waitKey(100000) & 0xFF # large wait time to remove freezing
if k == 113 or k == 27:
    cv2.destroyAllWindows()
    