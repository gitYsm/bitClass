import cv2
def handle_close(evt):
    print('Closed Figure!')

src = cv2.imread("../data/lena.jpg", cv2.IMREAD_COLOR)
hsv = cv2.cvtColor(src, cv2.COLOR_BGR2HSV)
b, g, r = cv2.split(hsv)
inversebgr = cv2.merge((r, g, b))
cv2.imshow("b", b)
cv2.imshow("g", g)
cv2.imshow("r", r)
cv2.imshow("inverse", inversebgr)
cv2.waitKey(0)
cv2.destroyAllWindows()