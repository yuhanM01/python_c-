import cv2 as cv
def super_resolution(img, scale=4):
    height, width = img.shape[:2]
    dsize = (width*scale, height*scale)
    big_img = cv.resize(img, dsize)
    return big_img
