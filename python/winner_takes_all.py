from area_segmentation import *
from math import sqrt


#Approximate background colors
background_colors = [(55, 45, 148), (214, 71, 53)]

#Color space
colors = [(55, 45, 148), (214, 71, 53), (217, 208, 199), (59, 36, 36),
          (79, 122, 61), (226, 201, 59), (176, 63, 119)]


'''
p   --  RGB tuple representing a pixel in an image

Returns:
Returns a binary PIL.Image object parted by being a background color or not

How it works:
We create a color space where red, green, blue are the three axis. In this
space we have a set of points. For each color, we try to find the closest point
in the color space and set it to that point. We can then check whether this
color was a shade of red or blue, which would mean a background color. If it is
the case it is set to black, otherwise white.
'''
def wta1(p):
    closest_colors = sorted(colors, key=lambda color: distance(color, p))
    c = closest_colors[0]
    return (0, 0, 0) if c in background_colors else (255, 255, 255)


'''
p   --  RGB tuple representing a pixel in an image

Returns:
Returns a binary PIL.Image object parted by being a background color or not

How it works:
Works in the exact same way as wta1 except it returns the closest color in our
color space instead or black or white.
'''
def wta2(p):
    closest_colors = sorted(colors, key=lambda color: distance(color, p))
    c = closest_colors[0]
    return c


'''
color1   --  RGB tuple representing a pixel in an image
color2   --  RGB tuple representing a pixel in an image

Returns:
The distance between the two colors in color space

How it works:
Simple vector distance calculation
'''
def distance(color1, color2):
    r1, g1, b1 = color1
    r2, g2, b2 = color2
    return sqrt((r1 - r2) ** 2 + (g1 - g2) ** 2 + (b1 - b2) ** 2)


'''
im     --  An RGB PIL.Image
bin    --  Boolean on whether the image should become binary or not

Returns:
A wta-modied PIL.Image

How it works:
It applies eiter one of the wta functions to each pixel, which snaps shades of
a color to one color.
'''
def map_color_wta(im, binary=True):
        im_c = im.copy()
        width, height = im.size
        wta = wta1 if binary else wta2
        for i in range(width):
            for j in range(height):
                im_c.putpixel((i, j), wta(im_c.getpixel((i, j))))
        return im_c
