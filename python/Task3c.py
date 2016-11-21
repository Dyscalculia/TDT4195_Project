from Task3a import *
from math import sqrt


def calculateMagnitude(Mx, My):
    return [[sqrt((Mx[y][x] ** 2) + (My[y][x] ** 2)) for x in range(len(Mx[0]))] for y in range(len(Mx))]

def rotateMatrix180(M):
    return list(reversed([list(reversed(row)) for row in M]))

sx = [[1, 0, -1],
      [2, 0, -2],
      [1, 0, -1]]

sy = [[1, 2, 1],
      [0, 0, 0],
      [-1, -2, -1]]

if __name__ == "__main__":
    M1 = imageToMatrix(Image.open(getImagePath("4.2.06-lake.tiff")).convert('L'))
    Mx = applyFilter(M1, rotateMatrix180(sx))
    My = applyFilter(M1, rotateMatrix180(sy))
    Mm = calculateMagnitude(Mx, My)
    Ix = matrixToImage(Mx)
    Iy = matrixToImage(My)
    Im = matrixToImage(Mm)
    Ix.show()
    Iy.show()
    Im.show()
    #Ix.save(getImagePath("Task-3c-XGradient.bmp", True))
    #Iy.save(getImagePath("Task-3c-YGradient.bmp", True))
    #Im.save(getImagePath("Task-3c-Magnitude.bmp", True))
