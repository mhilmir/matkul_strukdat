import cv2

img = cv2.imread("assets/images/wolf.png")

cv2.imshow("g", img)
print(img.shape)

cv2.waitKey(0)