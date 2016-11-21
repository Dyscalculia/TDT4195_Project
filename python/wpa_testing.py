from area_segmentation import *
from math import sqrt

board_colors = [(55, 45, 148), (214, 71, 53)]
colors = [(55, 45, 148), (214, 71, 53), (217, 208, 199), (59, 36, 36), (79, 122, 61), (226, 201, 59), (176, 63, 119)]


def wta1(p):
    closest_colors = sorted(colors, key=lambda color: distance(color, p))
    c = closest_colors[0]
    return (0, 0, 0) if c in board_colors else (255, 255, 255)

def wta2(p):
    closest_colors = sorted(colors, key=lambda color: distance(color, p))
    c = closest_colors[0]
    return c

def distance(color1, color2):
    r1, g1, b1 = color1
    r2, g2, b2 = color2
    return sqrt((r1 - r2) ** 2 + (g1 - g2) ** 2 + (b1 - b2) ** 2)

def map_color_wta(image, gray=True):
        im = image.copy()
        width, height = image.size
        wta = wta1 if gray else wta2
        for i in range(width):
            for j in range(height):
                im.putpixel((i, j), wta(im.getpixel((i, j))))
        return im

if __name__ == "__main__":
    im1 = Image.open(getImagePath("difficult01.png"))
    map_color_wta(im1).show()
