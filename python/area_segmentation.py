from sobel import *
from thresholding import from_bin_to_visual
from image_tools import *
from winner_takes_all import *
from morph import *
from region_growing_method import region_growing_method
from collections import Counter
import numpy as np
import sys


#Dictionaries translating values
color_to_shape = {(55, 45, 148): "star", (214, 71, 53): "pacman",
                  (217, 208, 199): "hexagon1", (59, 36, 36): "hexagon2",
                  (79, 122, 61): "square", (226, 201, 59): "v",
                  (176, 63, 119): "triangle"}

cmd_to_board = {"e1": "easy01.png", "e2": "easy02.png",
                "d1": "difficult01.png", "d2": "difficult02.png"}

color_to_name = {(55, 45, 148): "blue", (214, 71, 53): "red"}


'''
im          --  A binary PIL.Image

Returns:
A refined binary PIL.Image object

How it works:
Converts image to binary. Some of the images will only have edges and thus need
to be filled inn. In order to do that we must make sure the edge has no holes
where the area growing method can leak. We close these holes with dialation.
We then do an inverse fill, by applying region growing to the background and
put everything else as white. Lastly we erode the image, so the shape returns
to its original size and remove noise.
'''
def refine_shape(im):
    bin_im = region_growing_method(edge_padding(im, 1), tuple([(0, 0)]), 1)
    bin_m = imageToMatrix(bin_im)
    bin_d = dialation(bin_m, generate_circle_array(6))
    bin_im2 = edge_padding(matrixToImage(bin_d), 1)
    bin_im2 = region_growing_method(bin_im2, tuple([(0, 0)]), 1)
    bin_m2 = imageToMatrix(bin_im2)
    bin_e = erosion(bin_m2, generate_circle_array(8))
    bin_im3 = matrixToImage(bin_e)
    return bin_im3


'''
im              --  A PIL.Image
dimensions      --  A tuple with dimensions of the board of form (width in cells, height in cells)
thresh_range    --  Integer representing the tolerance used to evaluate if a cell is empty

Returns:
A list of tuples of the form (x, y) representing cells that contain an object on the board
as well as a tuple representing the size of a cell of the form (width, height)

How it works:
It works by parting the image up into cells based on dimension and size of
image. For each cell it runs is_empty which does an evaluation on whether a
cell is empty or not.
'''
def extract_legals(im, dimensions, thresh_range):
    width, height = im.size
    p_width, p_height = width / dimensions[0], height / dimensions[1]
    cells = []
    for y in range(dimensions[1]):
        for x in range(dimensions[0]):
            x1, x2 = x * p_width, (x + 1) * p_width
            y1, y2 = y * p_height, (y + 1) * p_height
            im2 = im.crop((x1, y1, x2, y2)).crop((8, 8, p_width - 10,  p_height - 10))
            if not is_empty(im2, thresh_range):
                cells.append((x, y))
    return cells, (p_width, p_height)


'''
im          --  A PIL.Image
legals      --  List of tuples of the form (x, y) representing cells to extract
dimensions  --  A tuple with dimensions of the board of form (width in cells, height in cells)

Returns:
A list of PIL.Image objects of the cells spesificied by legals

How it works:
Works in a similar fashion to extract_legals, however it uses legals know
whether or not to add a cell to the list.
'''
def extract_all(im, legals, dimensions):
    width, height = im.size
    p_width, p_height = width / dimensions[0], height / dimensions[1]
    cells = []
    for y in range(dimensions[1]):
        for x in range(dimensions[0]):
            x1, x2 = x * p_width, (x + 1) * p_width
            y1, y2 = y * p_height, (y + 1) * p_height
            im2 = im.crop((x1, y1, x2, y2)).crop((2, 2, p_width - 4,  p_height - 4))
            if (x, y) in legals:
                cells.append((im2, (x, y)))
    return cells


'''
im          --  A PIL.Image
pos         --  A tuple of cell coordinates with the form (x, y)
dimensions  --  A tuple with dimensions of the board of form (width in cells, height in cells)

Returns:
A PIL.Image object of the single cell spesificied

How it works:
Works in the exact same way as extract_all, however for a single cell.
'''
def extract_cell(im, pos, dimensions):
    x, y = pos
    width, height = im.size
    p_width, p_height = width / dimensions[0], height / dimensions[1]
    x1, x2 = x * p_width, (x + 1) * p_width
    y1, y2 = y * p_height, (y + 1) * p_height
    im = im.crop((x1, y1, x2, y2)).crop((4, 4, p_width - 4,  p_height - 4))
    return im


'''
im              --  A PIL.Image
thresh_range    --  Integer representing the tolerance

Returns:
True if cell is empty, False otherwise

How it works:
It first applies a gaussian blur to remove noise. Then we apply the sobel
operator and look at the magnitue, once this is done we run a custom area
growing method to create a binary image with only the strongest of edges visible.
Lastly we sum up all the values in the picture, only when the picture has strong
edges will the sum be greater than zero implying there is something in the cell.
'''
def is_empty(im, thresh_range, debug=False):
    im = applyFilter(im, hg)
    mx = imageToMatrix(applyFilter(im, rotateMatrix180(sx)))
    my = imageToMatrix(applyFilter(im, rotateMatrix180(sy)))
    mm = matrixToImage(calculateMagnitude(mx, my))
    mm2 = region_growing_method(mm, tuple([(0, 0)]), thresh_range)
    m = np.array(mm2)
    if debug:
        from_bin_to_visual(mm2).show()
        mm.show()
    return np.sum(m) <= 0


'''
im      --  A binary PIL.Image
pos     --  A tuple of cell coordinates with the form (x, y)
size    --  A tuple representing dimensions of a cell with form (width, height)

Returns:
Tuple of the form (x, y) representing real coordinates for the center of the shape

How it works:
It works by creating a bounding box around the shape and then find the center
of the box.
'''
def get_center_pos(im, pos, size):
    im = edge_padding(im, int((size[0] - im.size[0]) / 2))
    width, height = size
    b_x, b_y = pos
    m = imageToMatrix(im)
    min_x = len(m[0]) - 1
    min_y = len(m) - 1
    max_x = 0
    max_y = 0
    for y in range(len(m)):
        for x in range(len(m[0])):
            if m[y][x]:
                min_x = min(min_x, x)
                min_y = min(min_y, y)
                max_x = max(max_x, x)
                max_y = max(max_y, y)
    r_x = int((abs(max_x - min_x) / 2) + (b_x * width) + min(min_x, max_x))
    r_y = int((abs(max_y - min_y) / 2) + (b_y * height) + min(min_y, max_y))
    return r_x, r_y


'''
im      --  A PIL.Image

Returns:
Varies on image input;
    Gray scale images: A single gray scale value
    RGB images: An RGB tuple of form (red value, green value, blue value)

How it works:
A wta-modified image has gotten various shades of one color set to one spesific
shade, as in all blues become one blue. We can therefore count up number of
pixels with each color. We want the highest instance of color that is not the
background color. This color represent the shape and is thus used to identify
it. Background color is found just like in get_background_color.
If the highest instance color that is not background color covers less than
10 percent of the image, it assumes the background color is also the shape
color (a star or packman).
'''
def get_background_color(im):
    width, height = im.size
    edge_colors = []
    for i in range(width):
        for j in range(height):
            pixel = im.getpixel((i, j))
            if i == 0 or j == 0 or i == width - 1 or j == height - 1:
                edge_colors.append(pixel)
    return Counter(edge_colors).most_common(1)[0][0]


'''
im      --  A wta-modified RGB PIL.Image

Returns:
A string classification of the shape

How it works:
A wta-modified image has gotten various shades of one color set to one spesific
shade, as in all blues become one blue. We can therefore count up number of
pixels with each color. We want the highest instance of color that is not the
background color. This color represent the shape and is thus used to identify
it. Background color is found just like in get_background_color.
If the highest instance color that is not background color covers less than
10 percent of the image, it assumes the background color is also the shape
color (a star or packman).
'''
def classify(im):
    width, height = im.size
    colors = []
    edge_colors = []
    for i in range(width):
        for j in range(height):
            pixel = im.getpixel((i, j))
            if i == 0 or j == 0 or i == width - 1 or j == height - 1:
                edge_colors.append(pixel)
            colors.append(pixel)
    background_color = Counter(edge_colors).most_common(1)[0][0]
    ordered_colors = Counter(colors).most_common()
    shape_color = ordered_colors[0][0]
    if background_color == shape_color and len(ordered_colors) > 1:
        prob_shape_color, instances = ordered_colors[1]
        color_percentage = instances / (width * height)
        if color_percentage > 0.1:
            shape_color = prob_shape_color
    return color_to_shape[shape_color]


if __name__ == "__main__":
    board, display = cmd_to_board[sys.argv[1]], int(sys.argv[2])  # Revies command of which board to use and to display segments
    thresh_range = 65 if board[:4] == "easy" else 58
    board_image = Image.open(get_image_path(board))
    size = board_image.size
    coords, cell_size = extract_legals(board_image, (8, 5), thresh_range)
    cells = extract_all(map_color_wta(board_image).convert('L'), coords, (8, 5))
    wta_board_image = map_color_wta(board_image, False)
    background = get_background_color(extract_cell(wta_board_image, (0, 0), (8, 5)))
    rgb_cells = extract_all(wta_board_image, coords, (8, 5))
    print(size, color_to_name[background])  # Sends tuple representing board size of form (width, height) and color of first cell
    for i in range(len(cells)):
        im, pos = cells[i]  # Get PIL.Image of cell i and its board position
        rgb_im, _ = rgb_cells[i]  # Get RGB PIL.Image of cell i
        bin_im = refine_shape(im)  # Extract a binary segmented image of im
        print(get_center_pos(bin_im, pos, cell_size), classify(rgb_im))  # Sends tuple representing real center position of object and its shape
        if display:  # Whether to show RGB wta-modified version of a cell
            from_bin_to_visual(bin_im).show()
