from Task1b import *
from Task2b import *
from Task3c import *
from wpa_testing import *
from empty_check import *
from collections import Counter
from PIL import ImageEnhance, ImageFilter
import sys

color_to_shape = {(55, 45, 148): "star", (214, 71, 53): "pacman",
                  (217, 208, 199): "hexagon1", (59, 36, 36): "hexagon2",
                  (79, 122, 61): "square", (226, 201, 59): "v",
                  (176, 63, 119): "triangle"}

cmd_to_board = {"e1": "easy01.png", "e2": "easy02.png",
                "d1": "difficult01.png", "d2": "difficult02.png"}

color_to_name = {(55, 45, 148): "blue", (214, 71, 53): "red"}

def extract_piece(im, pos, dimensions):
    x, y = pos
    width, height = im.size
    p_width, p_height = width / dimensions[0], height / dimensions[1]
    x1, x2 = x * p_width, (x + 1) * p_width
    y1, y2 = y * p_height, (y + 1) * p_height
    im = im.crop((x1, y1, x2, y2)).crop((5, 5, 95, 95))
    return im


def extract_all(im, legals, dimensions):
    width, height = im.size
    p_width, p_height = width / dimensions[0], height / dimensions[1]
    pieces = []
    for y in range(dimensions[1]):
        for x in range(dimensions[0]):
            x1, x2 = x * p_width, (x + 1) * p_width
            y1, y2 = y * p_height, (y + 1) * p_height
            im2 = im.crop((x1, y1, x2, y2)).crop((5, 5, 95, 95))
            if (x, y) in legals:
                pieces.append((im2, (x, y)))
    return pieces


def extract_coords(im, dimensions, thresh_range):
    width, height = im.size
    p_width, p_height = width / dimensions[0], height / dimensions[1]
    pieces = []
    for y in range(dimensions[1]):
        for x in range(dimensions[0]):
            x1, x2 = x * p_width, (x + 1) * p_width
            y1, y2 = y * p_height, (y + 1) * p_height
            im2 = im.crop((x1, y1, x2, y2)).crop((8, 8, 90, 90))
            if not is_empty(im2, thresh_range):
                pieces.append((x, y))
    return pieces, (p_width, p_height)


def inverter(im):
    width, height = im.size
    m = imageToMatrix(im)
    corner_sum = m[0][0] + m[0][1] + m[1][0]
    corner_sum += m[0][-1] + m[0][-2] + m[1][-1]
    corner_sum += m[-1][0] + m[-1][1] + m[-2][0]
    corner_sum += m[-1][-1] + m[-1][-2] + m[-2][-1]
    return invert_bin(im) if corner_sum > 6 else im


def invert_bin(im):
    def f(p):
        return 1 - p
    return im.point(lambda i: f(i))

def get_center_pos(im, pos, size):
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
    r_x = int(((max_x - min_x) / 2) + (b_x * width))
    r_y = int(((max_y - min_y) / 2) + (b_y * height))
    return r_x, r_y


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


def get_background_color(im):
    width, height = im.size
    edge_colors = []
    for i in range(width):
        for j in range(height):
            pixel = im.getpixel((i, j))
            if i == 0 or j == 0 or i == width - 1 or j == height - 1:
                edge_colors.append(pixel)
    return Counter(edge_colors).most_common(1)[0][0]

if __name__ == "__main__":
    board, display = cmd_to_board[sys.argv[1]], int(sys.argv[2])
    thresh_range = 65 if board[:4] == "easy" else 58
    im1 = Image.open(getImagePath(board))
    size = im1.size
    coords, cell_size = extract_coords(im1, (8, 5), thresh_range)
    pieces = extract_all(map_color_wta(im1).convert('L'), coords, (8, 5))
    color_board = map_color_wta(im1, False)
    background = get_background_color(extract_piece(color_board, (0, 0), (8, 5)))
    rgb_pieces = extract_all(color_board, coords, (8, 5))
    for i in range(len(pieces)):
        im, pos = pieces[i]
        rgb_im, _ = rgb_pieces[i]
        if i == 0:
            print(size, color_to_name[background])
        m = inverter(region_growing_method(im, tuple([(1, 1)]), 1))
        print(get_center_pos(m, pos, cell_size), classify(rgb_im))
        if display:
            rgb_im.show()
