from area_segmentation import *
from Task2b import *


def is_empty(im, thresh_range, debug=False):
    #im.show()
    im = applyFilter(im, hg)
    #im = g2(im, 1.3)
    mx = imageToMatrix(applyFilter(im, rotateMatrix180(sx)))
    my = imageToMatrix(applyFilter(im, rotateMatrix180(sy)))
    mm = matrixToImage(calculateMagnitude(mx, my))
    mm2 = region_growing_method(mm, tuple([(0, 0)]), thresh_range)
    m = np.array(mm2)
    if debug:
        from_bin_to_visual(mm2).show()
        mm.show()
    return np.sum(m) <= 0

if __name__ == "__main__":
    '''
    im1 = extract_piece(Image.open(getImagePath("difficult01.png")), 7, 4).convert('L')
    print(is_empty(im1))
    '''
    pieces = extract_all(Image.open(getImagePath("difficult02.png")).convert('L'), (8, 5))
    for piece in pieces:
        print(is_empty(piece, False))
