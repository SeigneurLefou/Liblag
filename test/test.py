import numpy as np										# only for the image array

r = 5											# radius of the circle

img = np.zeros([2 * r + 1]*2, dtype=int)				# image of size (2r + 1) x (2r + 1) to fit the circle
x, y, p = r, 0, 1 - r									# initial values x0 = r, y0 = 0, p0 = 1 - r
while x >= y:											# while the point (x, y) is in the first octant
	for j, k in [(1, 1), (1, -1), (-1, 1), (-1, -1)]:	# draw to all quadrants
		img[j * x + r, k * y + r] = 1
		img[k * y + r, j * x + r] = 1
	x, y = x - (1 if p > 0 else 0), y + 1				# update x and y according to the radius error p
	p += (1 - 2 * x + 2 * y) if p > 0 else 1 + 2 * y		# update the radius error p with updated x and y
print(img);
