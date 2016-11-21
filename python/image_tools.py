from PIL import Image
from random import randint
from math import floor
import os


'''
im      --  A PIL.Image

Returns:
A PIL.Image with the same image padded around it, mirrored in all directions,
as well as a tuple representing the position of the first pixel of
the padded image.
'''
def padding(im):
    trans = [Image.ROTATE_180, Image.FLIP_LEFT_RIGHT, Image.FLIP_LEFT_RIGHT,
             Image.FLIP_TOP_BOTTOM, Image.FLIP_LEFT_RIGHT, Image.FLIP_LEFT_RIGHT,
             Image.FLIP_TOP_BOTTOM, Image.FLIP_LEFT_RIGHT, Image.FLIP_LEFT_RIGHT]
    img_w, img_h = im.size
    background = Image.new('RGB', (img_w * 3, img_h * 3))
    bg_w, bg_h = background.size
    for i in range(9):
        im = im.transpose(trans[i])
        x = i % 3
        y = floor(i / 3)
        pos = (x * img_w, y * img_h)
        background.paste(im, pos)
    offset = (img_w, img_h)
    return background, offset


#Used by applyFilter to find the value to place down by the kernel
def applyPixel(m, k, x, y):
    value = 0
    for i in range(len(k)):
        for j in range(len(k)):
            value += floor(m[y + i][x + j] * k[i][j])
    return value


'''
im      --  A gray scale PIL.Image
k       --  A 2d list representing a kernel

Returns:
A PIL.Image with a filter applied to it

How it works:
It moves the kernel accross the image multiplying the kernel values with the
corresponding image values and summing them together, placing the sum at the
center position of the kernel. This is done for every pixel of the actual
image (as in the center is never placed over the padding).
'''
def applyFilter(im, k):
    im, offset = padding(im)
    m = imageToMatrix(im)
    width, height = offset
    newM = [row[:] for row in m]
    for y in range(height, height * 2):
        for x in range(width, width * 2):
            newM[y][x] = applyPixel(m, k, x, y)
    newI = matrixToImage(newM).crop((width, height, width * 2, height * 2))
    return newI


'''
m      --  A 2d list representation of a PIL.image

Returns:
A PIL.Image of m
'''
def matrixToImage(m):
    line = [i for row in m for i in row]
    im = Image.new('L', (len(m[0]), len(m)))
    im.putdata(line)
    return im


'''
im      --  A PIL.image

Returns:
A 2d list representation of im
'''
def imageToMatrix(im):
    data = list(im.convert('L').getdata())
    width, height = im.size
    return [data[row * width:(row + 1) * width] for row in range(height)]


'''
im      --  A string of the name of an image

Returns:
The static path to the given image
'''
def get_image_path(imageName):
    path = os.path.dirname(os.path.abspath(__file__))
    path += "\\images\\" + imageName
    return path

#Box filter
ha = [[1/9 for _ in range(3)] for _ in range(3)]

k = [[1, 4, 6, 4, 1],
     [4, 16, 24, 16, 4],
     [6, 24, 32, 24, 6],
     [4, 16, 24, 16, 4],
     [1, 4, 6, 4, 1]]

#Gaussian filter
hg = [[i * 1/256 for i in row] for row in k]
