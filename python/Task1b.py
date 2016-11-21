from Task1a import *


'''
I           --  A PIL.Image
seeds       --  Tuple of coordinates with the form (y, x)
thresh_lim  --  A manually set threshold which is the range seed's intensity -+ thresh_lim
                If it is not defined, thresholds will be generated in a slighly more sophisticated manner
neumann     --  If set to True, the growth function will use neumann connectivity to find neighbours
                If not defined, the growth function uses moor connectivity

Returns:
A PIL.Image that has gotten the region growing method applied to it

How it works:
to_visit are pixels that have not been looked at yet. When a pixel is looked at it checks the
homogeneity criteria for whether this pixel belongs in this region. If it does belong,
it will be given the same value as the seed and its neighbours will be added to to_visit.
This process continues until to_visit is empty and it tries the same process with a new seed
until it has gone through all the seeds.

get_neighbours ensures only new unvisited pixels are added that are within the edge of the
image.
'''
def region_growing_method(I, seeds, thresh_lim=None, neumann=False):
    width, height = I.size
    m = np.matrix(I)
    s = np.full((width, height), 1, dtype=int)
    thresholds = gen_thresholds(m, seeds)
    visited = set()
    for seed in seeds:
        to_visit = set([seed])
        seed_inte = m.item(seed)
        while to_visit:
            coord = to_visit.pop()
            if homogeneity_criteria(m.item(coord), thresholds[seed], seed_inte, thresh_lim):
                s.itemset(coord, 0)
                [to_visit.add(n) for n in get_neighbours(m, coord, visited, neumann)]
                visited.add(coord)
    return Image.fromarray(s).convert('L')


'''
inte        --  Intensity value for a pixel we are currently checking
bounds      --  A tuple holding a low bound and a top bound intensity value calculated from the seed
                we are currently working from.
seed_inte   --  Intensity value of the seed, this is only used if a thresh_lim is set
thresh_lim  --  A manually set threshold which is the range seed's intensity -+ thresh_lim
                If it is not defined, inte and bounds will be used to check the criteria

Returns:
A boolean determining if the given intensity inte holds the homogeneity criteria

How it works:
It will either check criteria based on the genereated bounds using inte and bound or if thresh_lim
is defined, it will use a more primitive check for criteria using seed_inte and thresh_lim
'''
def homogeneity_criteria(inte, bounds, seed_inte, thresh_lim=None):
    if thresh_lim is None and inte >= bounds[0] and inte <= bounds[1]:
        return True
    return thresh_lim is not None and abs(seed_inte - inte) < thresh_lim


'''
Input:
m           --  A numpy.matrix representation of the image
coord_tuple --  Tuple of coordinate with the form (y, x) for the pixel we are getting neighbours from
visited     --  A set of coordinates representing all pixels that has already been visited
neumann     --  If set to True, the function will use neumann connectivity to find neighbours
                If not defined, the function uses moor connectivity

Returns:
A list of coordinates being legal neighbours of the given coord_tuple

How it works:
It finds all adjecent pixels and only return those who have not been visited and are within
the bounds of the matrix.
'''
def get_neighbours(m, coord_tuple, visited, neumann=False):
    y, x = coord_tuple
    max_y, max_x = m.shape
    coords = []
    for val in -1, 1:
        coord_pair = [(y, x + val), (y + val, x)]
        if neumann:
            coord_pair += [(y + val, x + val), (y - val, x + val)]
        for coord in coord_pair:
            c_y, c_x = coord
            if (coord not in visited) and c_x >= 0 and c_x < max_x and c_y >= 0 and c_y < max_y:
                coords.append(coord)
    return coords


'''
m       --  A numpy.matrix representation of the image
seeds   --  Tuple of coordinates with the form (y, x)

Returns:
A dictionary with the coordinate tuple of a seed as key, and a tuple holding the lower and upper bound
for the intensity belonging to the seed.

How it works:
It finds a range between the intensities of each seed.
For example:
seed_1 has intensity 80, seed_2 has intensity 170 and seed_3 has intensity 210
Then the bound for:
seed_1: [0, 125], seed_2: [126, 190], seed_3: [191, 255]
'''
def gen_thresholds(m, seeds):
    thresholds = dict()
    intensities = sorted([(seed, m.item(seed)) for seed in seeds], key=lambda x: x[1])
    ranges = [-1]
    for i in range(0, len(intensities) - 1):
        seed, inte0 = intensities[i]
        _, inte1 = intensities[i + 1]
        ranges.append(ceil((inte0 + inte1)/2))
        thresholds[seed] = (ranges[i] + 1, ranges[i + 1])
    thresholds[intensities[-1][0]] = (ranges[-1] + 1, 255)
    return thresholds


if __name__ == "__main__":
    I1 = Image.open(getImagePath("Fig1051(a)(defective_weld).tif")).convert('L')
    I2 = region_growing_method(I1, ((255, 140), (200, 315), (50, 275), (450, 290)))
    I2.show()
    '''
    I2.save(getImagePath("Task-1b-growth-method.png", True))
    '''
