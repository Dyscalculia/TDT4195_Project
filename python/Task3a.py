from PIL import Image
from random import randint
from math import floor
import os

def padding(I):
    trans = [Image.ROTATE_180, Image.FLIP_LEFT_RIGHT, Image.FLIP_LEFT_RIGHT,
             Image.FLIP_TOP_BOTTOM, Image.FLIP_LEFT_RIGHT, Image.FLIP_LEFT_RIGHT,
             Image.FLIP_TOP_BOTTOM, Image.FLIP_LEFT_RIGHT, Image.FLIP_LEFT_RIGHT]
    img_w, img_h = I.size
    background = Image.new('RGB', (img_w * 3, img_h * 3))
    bg_w, bg_h = background.size
    for i in range(9):
        I = I.transpose(trans[i])
        x = i % 3
        y = floor(i / 3)
        pos = (x * img_w, y * img_h)
        background.paste(I, pos)
    offset = (img_w, img_h)
    return background, offset

def applyPixel(M, h, x, y):
    value = 0
    for i in range(len(h)):
        for j in range(len(h)):
            value += floor(M[y + i][x + j] * h[i][j])
    return value

def applyFilter(I, h):
    I, offset = padding(I)
    M = imageToMatrix(I)
    width, height = offset
    newM = [row[:] for row in M]
    for y in range(height, height * 2):
        for x in range(width, width * 2):
            newM[y][x] = applyPixel(M, h, x, y)
    newI = matrixToImage(newM).crop((width, height, width * 2, height * 2))
    return newI

def matrixToImage(M):
    line = [i for row in M for i in row]
    I = Image.new('L', (len(M[0]), len(M)))
    I.putdata(line)
    return I

def imageToMatrix(I):
    data = list(I.convert('L').getdata())
    width, height = I.size
    return [data[row * width:(row + 1) * width] for row in range(height)]

def printMatrix(A):
    for row in A:
        print(row)

def getImagePath(imageName, save=False):
    path = os.path.dirname(os.path.abspath(__file__))
    path += ("\\processed images\\" if save else "\\images\\") + imageName
    return path

ha = [[1/9 for _ in range(3)] for _ in range(3)]
h = [[1, 4, 6, 4, 1],
     [4, 16, 24, 16, 4],
     [6, 24, 32, 24, 6],
     [4, 16, 24, 16, 4],
     [1, 4, 6, 4, 1]]
hg = [[i * 1/256 for i in row] for row in h]

if __name__ == "__main__":
    M1 = imageToMatrix(Image.open(getImagePath("5.1.10-aerial.tiff")))
    I2 = matrixToImage(applyFilter(M1, ha))
    I3 = matrixToImage(applyFilter(M1, hg))
    I2.show()
    I3.show()
    #I2.save(getImagePath("Task-3a-haFilter.bmp", True))
    #I3.save(getImagePath("Task-3a-hgFilter.bmp", True))
