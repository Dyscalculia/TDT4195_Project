from task_2a import *
from area_segmentation import get_background_color
from sobel import *
from thresholding import from_bin_to_visual
from image_tools import *
from winner_takes_all import *
from shape_refining import *
from region_growing_method import region_growing_method
import numpy as np

def refine_shape(im):
    bin_im = inverter(region_growing_method(im, tuple([(3, 3)]), 1))
    bin_m = imageToMatrix(bin_im)
    bin_d = dialation(bin_m, generate_circle_array(6))
    bin_im2 = edge_padding(from_bin_to_visual(matrixToImage(bin_d)), 1)
    bin_im2.show()
    bin_im2 = region_growing_method(bin_im2, tuple([(5, 5)]), 1)
    from_bin_to_visual(bin_im2).show()
    return bin_im2


def edge_padding(im, padding):
    width, height = im.size
    background = Image.new('L', (width + padding * 2, height + padding * 2))
    background.paste(im, (padding, padding))
    return background


'''
im          --  A binary PIL.Image

Returns:
A binary PIL.Image object that is inverted if the background color is white
'''
def inverter(im):
    background = get_background_color(im)
    return invert_bin(im) if background == 1 else im


'''
im          --  A binary PIL.Image

Returns:
A binary PIL.Image object that is inverted
'''
def invert_bin(im):
    def f(p):
        return 1 - p
    return im.point(lambda i: f(i))
