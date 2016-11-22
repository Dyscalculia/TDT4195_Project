from PIL import Image
from scipy import ndimage
import numpy as np
import copy
import math


#Check for fits
def includes_all(A, F, start_x, start_y):
    mid_x = math.floor(len(F[0]) / 2)
    mid_y = math.floor(len(F) / 2)
    for x in range(-mid_x, mid_x + 1):
        for y in range(-mid_y, mid_y + 1):
            if x + start_x >= len(A[0]) or y + start_y >= len(A): return False
            if x + start_x < len(A[0]) and y + start_y < len(A) and y + mid_y < len(F) and x + mid_x < len(F[0]):
                if A[y + start_y][x + start_x] == 0 and F[y + mid_y][x + mid_x] == 1: return False
    return True


'''
A   --  A 2D list representation of a binary PIL.Image
F   --  A 2D list representing a structuring element

Returns:
A morphed 2D list of a binary PIL.Image object

How it works:
Check if shape fits inside the structuring element for each pixel, if that is
the case, a 1 will be placed at the relative center position of the structuring
element, 0 otherwise.
'''
def erosion(A, F):
    new_matrix = copy.deepcopy(A)
    width, height = len(A[0]),len(A)
    for row_i in range(height):
        for col_i in range(width):
            if not includes_all(A, F, col_i, row_i):
                new_matrix[row_i][col_i] = 0
    return new_matrix


#Check for hits
def includes_any(A, F, start_x, start_y):
    mid_x = math.floor(len(F[0]) / 2)
    mid_y = math.floor(len(F) / 2)
    for x in range(-mid_x, mid_x):
        for y in range(-mid_y, mid_y):
            if x + start_x < len(A[0]) and y + start_y < len(A):
                if A[y + start_y][x + start_x] == 1:
                    if F[y + mid_y][x + mid_x] == 1: return True
    return False


'''
A   --  A 2D list representation of a binary PIL.Image
F   --  A 2D list representing a structuring element

Returns:
A morphed 2D list of a binary PIL.Image object

How it works:
Check if shape hits inside the structuring element for each pixel, if that is
the case, a 1 will be placed at the relative center position of the structuring
element, 0 otherwise.
'''
def dialation(A, F):
    new_matrix = [[0 for i in range(len(A[0]))] for j in range(len(A))]
    width,height = len(A[0]), len(A)
    for row_i in range(0, height):
        for col_i in range(0, width):
            if includes_any(A, F, col_i, row_i):
                new_matrix[row_i][col_i] = 1
    return new_matrix


'''
size    --  Radius of circle

Returns:
A 2D list representing a round structuring element
'''
def generate_circle_array(size):
    mid_point = size // 2
    A = [[0 for i in range(size)] for j in range(size)]
    for col_i in range(size):
        for row_i in range(size):
            if ((row_i-mid_point) ** 2 + (col_i-mid_point) ** 2) ** 0.5 <= size // 2:
                A[col_i][row_i] = 1
    return A
