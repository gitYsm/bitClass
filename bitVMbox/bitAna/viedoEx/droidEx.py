# import
import cv2
cap = cv2.VideoCapture('http://192.168.1.58:4747/video') # droid cam
frame_size = (int(cap.get(cv2.CAP_PROP_FRAME_WIDTH)),
int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT)))
print('frame_size =', frame_size)
while True:
    retval, frame = cap.read() # 프레임 캡처
    if not retval:
        break
    cv2.imshow('frame',frame)
    key = cv2.waitKey(25)
    if key == 27: # Esc
        break
    if cap.isOpened():
        cap.release()
cv2.destroyAllWindows()