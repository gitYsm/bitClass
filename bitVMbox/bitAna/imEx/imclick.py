import cv2
import matplotlib.pyplot as plt
import numpy as np
imageFile = '../data/lena.jpg'

img = cv2.imread(imageFile) # cv2.IMREAD_COLOR
fig = plt.figure()
angle = 0
def onclick(event):
    global angle
    angle = angle+90%360
    height, width, channel = img.shape
    matrix = cv2.getRotationMatrix2D((width/2, height/2), angle, 1)
    dst = cv2.warpAffine(img, matrix, (width, height))
    
    plt.imshow(dst)
    plt.draw()
    

cid = fig.canvas.mpl_connect('button_press_event', onclick)



height, width, channel = img.shape
matrix = cv2.getRotationMatrix2D((width/2, height/2), 0, 1)
dst = cv2.warpAffine(img, matrix, (width, height))

plt.imshow(dst)
plt.show()