# 파이썬에서 openCV를 사용하기 위해
import cv2
# matplotlib 패키지에서 pyplot를 plt 라는 이름으로 임포트 한다.
from matplotlib import pyplot as plt
# 파일이 저장된 경로를 문자열 객체 지정
imageFile = '../data/lena.jpg'
# Grayscale 포맷으로 읽어서 imgGray 객체에 저장한다.
imgGray = cv2.imread(imageFile, cv2.IMREAD_GRAYSCALE)
# X, Y축을 표시하지 않는다.
#plt.axis('off')

# plt.figure 크기를 (6,6) 인치로 설정
plt.figure(figsize=(5,5))
# left = 0, right = 1, bottom = 0, top = 1로 설정 (일단 창
# 을 띄워서 값을 변경해 보자)
#plt.subplots_adjust(left=0.03, right=0.97, bottom=0.4, top=0.6)
plt.subplots_adjust(left=0, right=1, bottom=0, top=1)
#plt.subplots_adjust(left=0.03, right=0.97, bottom=0.03, top=0.97)

# plot에 컬러맵을 “gray”로 설정하고 imgGray를 그린다.
plt.imshow(imgGray, cmap = "gray", interpolation='bicubic')
plt.show()