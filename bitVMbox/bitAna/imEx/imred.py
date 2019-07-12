import cv2
import matplotlib.pyplot as plt

img_color = cv2.imread('../data/hsv2.jpg')
height,width = img_color.shape[:2]

img_hsv = cv2.cvtColor(img_color, cv2.COLOR_BGR2HSV)


lower_blue = (0-5, 150, 150)
upper_blue = (0+5, 255, 255)
img_mask = cv2.inRange(img_hsv, lower_blue, upper_blue)


img_result = cv2.bitwise_and(img_color, img_color, mask = img_mask)

# cv2.imshow('img_hsv', img_hsv)
# cv2.imshow('img_color', img_color)
cv2.imshow('img_mask', img_mask)
# cv2.imshow('img_result', img_result)

fig, ax = plt.subplots(2, 2, figsize=(5,5), sharey=False, sharex=False)
fig.canvas.set_window_title('Sample Pictures')

img_hsv = cv2.cvtColor(img_hsv,cv2.COLOR_BGR2RGB)
img_color = cv2.cvtColor(img_color,cv2.COLOR_BGR2RGB)
#img_mask = cv2.cvtColor(img_mask,cv2.COLOR_BGR2RGB)
img_result = cv2.cvtColor(img_result,cv2.COLOR_BGR2RGB)
ax[0][0].axis('off')
ax[0][0].imshow(img_hsv, aspect = 'auto')
ax[0][1].axis('off')
ax[0][1].imshow(img_color, aspect = 'auto')
ax[1][0].axis("off")
ax[1][0].imshow(img_mask, aspect = "auto")
ax[1][1].axis("off")
ax[1][1].imshow(img_result, aspect = 'auto')


plt.show()