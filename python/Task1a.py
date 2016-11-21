from ImageTools import *
import numpy as np

def global_threshold(I, Ti, Td):
    intensities = I.getdata()
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

def segment(I, T):
    return I.point(lambda i: 1 if i > T else 0)

def from_bin_to_visual(I):
    return I.point(lambda i: 255 if i == 1 else 0)

if __name__ == "__main__":
    I1 = Image.open(getImagePath("Fig1043(a)(yeast_USC).tif")).convert('L')
    T = global_threshold(I1, 100, 1)  # Chose 128 because it is half of max intensity, and 1 for high precision
    I2 = from_bin_to_visual(segment(I1, T))
    I2.show()
    print(T)
    '''
    I2.save(getImagePath("Task-1b-threshold.png", True))
    '''
