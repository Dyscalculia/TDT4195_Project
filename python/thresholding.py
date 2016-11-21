from PIL import Image
import numpy as np


'''
im      --  A PIL.Image
Ti      --  Initial threshold value
Td      --  Precision value

Returns:
A global threshold value
'''
def global_threshold(im, Ti, Td):
    intensities = im.getdata()
    Tp = 0
    T = Ti
    while np.abs(T - Tp) > Td:
        S1, S2 = [], []
        for x in intensities:
            S1.append(x) if x > T else S2.append(x)
        u1 = np.mean(S1) if S1 else 0
        u2 = np.mean(S2) if S2 else 0
        Tp = T
        T = (1/2) * (u1 + u2)
    return T


'''
im      --  A PIL.Image
T       --  Threshold value

Returns:
A binary PIL.Image object parted by the T value
'''
def segment(im, T):
    return im.point(lambda i: 1 if i > T else 0)


'''
im      --  A binary PIL.Image

Returns:
A gray scale PIL.Image representation of the binary image
'''
def from_bin_to_visual(im):
    return im.point(lambda i: 255 if i == 1 else 0)
