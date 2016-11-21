from math import sqrt


'''
mx   --  2D list representing the gradient in x direction of an image
my   --  2D list representing the gradient in y direction of an image

Returns:
A 2D list representing the magnitude of the image
'''
def calculateMagnitude(mx, my):
    return [[sqrt((mx[y][x] ** 2) + (my[y][x] ** 2)) for x in range(len(mx[0]))] for y in range(len(mx))]


'''
m   --  2D list representing an image

Returns:
m rotated 180 degrees
'''
def rotateMatrix180(m):
    return list(reversed([list(reversed(row)) for row in m]))


#Sobel filter for x direction
sx = [[1, 0, -1],
      [2, 0, -2],
      [1, 0, -1]]

#Sobel filter for y direction
sy = [[1, 2, 1],
      [0, 0, 0],
      [-1, -2, -1]]
