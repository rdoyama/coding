import pygame
import os
import time
import random
import numpy as np

pygame.font.init()

# Display
WIDTH, HEIGHT = 650, 650
WINDOW = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Minefield")

# Other Images
BOMB = pygame.image.load(os.path.join("assets", "explosion.png"))
GREEN_FLAG = pygame.image.load(os.path.join("assets", "green-flag.png"))
RED_FLAG = pygame.image.load(os.path.join("assets", "red-flag.png"))
CELL = pygame.image.load(os.path.join("assets", "cell.png"))
CELL_FILLED = pygame.image.load(os.path.join("assets", "cell_high.png"))

BACKGROUND = pygame.image.load(os.path.join("assets", "background.png"))
BACKGROUND = pygame.transform.scale(BACKGROUND, (WIDTH, HEIGHT))

# Board parameters
PX_SIZE   = 32		# Lenght of each cell in pixels
THICKNESS = 20		# Thickness of the sides of the board in pixels
TOP_PROP  = 0.15	# Proportion of the top of the board reserved to statistics

# Font
MAIN_FONT = pygame.font.SysFont("chilanka", 50)


def board_dimension(width, height):
	'''
	Receives the width and height of the game window and returns
	two points (in pixels) to position the board as well as the
	number of lines and columns
	'''
	ncol = (width - THICKNESS) // PX_SIZE
	xmin = (width - ncol * PX_SIZE) // 2
	nlin = int(height * (1 - TOP_PROP) - THICKNESS) // PX_SIZE
	ymin = int(height * TOP_PROP) + int((height * (1 - TOP_PROP) - nlin * PX_SIZE) // 2)
	xmax = int(xmin + ncol * PX_SIZE)
	ymax = int(ymin + nlin * PX_SIZE)

	return xmin, ymin, xmax, ymax, nlin, ncol


class Cell:

	STATES = {
			-1: 
	}

	def __init__(self, state):
		self.state = state


class Board:
	def __init__(self, xmin, ymin, xmax, ymax, nlin, ncol):
		self.xmin = xmin
		self.ymin = ymin
		self.xmax = xmax
		self.ymax = ymax
		self.nlin = nlin
		self.ncol = ncol

		self.cells = []

	def draw(self, window):
		pass


class Button:
	def __init__(self, txt, pos, img=None):
		self.txt = txt
		self.img = img
		self.pos = pos

	def draw(self, window, color=(255, 255, 255)):
		text = MAIN_FONT.render(self.txt)
		w, h = text.get_width(), text.get_height

		rect = pygame.draw.rect(window, color, ())


def main():
	pass


def main_menu():
	run = True
	title_font = pygame.font.SysFont("comicsans", 50)

	while run:

		WINDOW.blit(BACKGROUND, (0, 0))
		title_label = title_font.render("START", 1, (255, 255, 255))
		WINDOW.blit(title_label, (WIDTH // 2 - title_label.get_width() // 2,
					HEIGHT // 2 - title_label.get_height() // 2))
		pygame.display.update()

		for event in pygame.event.get():
			if event.type == pygame.QUIT:
				run = False
			elif event.type == pygame.MOUSEBUTTONDOWN:
				main()

	pygame.quit()


if __name__ == '__main__':
	main_menu()