from PIL import Image
from random import randint
from math import floor, ceil
import os


def __applyPixel(M, h, x, y):
    value = 0
    for i in range(len(h)):
        for j in range(len(h)):
            value += floor(M[y + i][x + j] * h[i][j])
    return value

"""Applies a filter h in the form of a 2D list to a PIL.Image I"""
def applyFilterInSD(I, h):
    M = imageToMatrix(I)
    hSize = len(h)
    width, height = I.size
    offset = floor(hSize/2)
    newM = [row[:] for row in M]
    for y in range(height - hSize + 1):
        for x in range(width - hSize + 1):
            newM[y + offset][x + offset] = __applyPixel(M, h, x, y)
    return matrixToImage(newM)

"""Converts a 2D list M to a PIL.Image"""
def matrixToImage(M):
    line = [i for row in M for i in row]
    I = Image.new('L', (len(M[0]), len(M)))
    I.putdata(line)
    return I

"""Converts a PIL.Image to a 2D list"""
def imageToMatrix(I):
    data = list(I.convert('L').getdata())
    width, height = I.size
    return [data[row * width:(row + 1) * width] for row in range(height)]

"""Prints a 2D list in a more lucid manner"""
def printMatrix(A):
    for row in A:
        print(row)

"""Gets the path to the images folder of a project or processed images folder for saving"""
def getImagePath(imageName, save=False):
    path = os.path.dirname(os.path.abspath(__file__))
    path += ("\\processed images\\" if save else "\\images\\") + imageName
    return path

"""A box filter ha and a gaussian filter hg"""
ha = [[1/9 for _ in range(3)] for _ in range(3)]
h = [[1, 4, 6, 4, 1],
     [4, 16, 24, 16, 4],
     [6, 24, 32, 24, 6],
     [4, 16, 24, 16, 4],
     [1, 4, 6, 4, 1]]
hg = [[i * 1/256 for i in row] for row in h]
