from PIL import Image
from Task3a import getImagePath


def f(p):
    return p/255

def g1(I, gamma):
    In = Image.new('RGB', I.size)
    M = [tuple([int((f(color) ** gamma)*255) for color in p]) for p in I.getdata()]
    In.putdata(M)
    return In

def g2(I, gamma):
    In = Image.new('L', I.size)
    M = [(f(p) ** gamma)*255 for p in I.getdata()]
    In.putdata(M)
    return In

if __name__ == "__main__":
    I1 = Image.open(getImagePath("5.2.09-aerial.tiff"))
    I1.show()
    gamma = 0.1
    I2 = g(I1, gamma)
    I2.show()
    #I2.save(getImagePath("Task-2b-gammaFilter.bmp", True))
