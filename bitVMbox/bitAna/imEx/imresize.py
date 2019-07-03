from PIL import Image

# 이미지 열기
im = Image.open('../data/lena.jpg').convert('RGB')
# 이미지 크기 및 이미지 출력
print(im.size)


# 이미지 JPG로 저장
#im.save('../data/pillow1.jpg')
im.save('pillow1.jpg')

# size = (64, 64)
# im.thumbnail(size)
# im.show()
# im.save('../data/lena-thumb.jpg')

# cropImage = im.crop((100, 100, 350, 350))
# cropImage.show()
# cropImage.save('../data/lena-crop.jpg')
