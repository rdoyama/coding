#	Script to test minefield functions

import unittest
import matplotlib.pyplot as plt
from minefield import board_dimension
import numpy as np

from minefield import PX_SIZE
from minefield import THICKNESS
from minefield import TOP_PROP


class TestBoardCreation(unittest.TestCase):
	def test_sizes(self):
		for w, h in [(650, 650), (700, 500), (602, 900)]:
			xmin, ymin, xmax, ymax, nlin, ncol = board_dimension(w, h)

			# Width
			width = xmin + ncol * PX_SIZE + w - xmax
			# print(f"width = {width}")
			self.assertTrue(np.isclose(width, w, atol=1),
						f"Width board dimensions for w x h = ({w}, {h}) are not good!")

			# Height
			height = ymin + nlin * PX_SIZE + h - ymax
			# print(f"height = {height}")
			self.assertTrue(np.isclose(height, h, atol=1),
						f"Height board dimensions for w x h = ({w}, {h}) are not good!")

			# Area (board must occupy at least 50% of the board)
			total_area = w * h
			board_area = (xmax - xmin) * (ymax - ymin)
			self.assertTrue(0.5 <= board_area / total_area <= 0.90,
						f"The ratio between board_area and total_area is not good!")


if __name__ == '__main__':
	# w, h = 603, 401
	# xmin, ymin, xmax, ymax, nlin, ncol = board_dimension(w, h)
	# x = [0, w, 0, w, xmin, xmax, xmin, xmax]
	# y = [0, h, h, 0, ymin, ymax, ymax, ymin]
	# print(f"xmin, ymin = {xmin}, {ymin}")
	# print(f"xmax, ymax = {xmax}, {ymax}")
	# print(f"nlin, ncol = {nlin}, {ncol}")
	# plt.scatter(x, y)
	# plt.show()

	unittest.main()