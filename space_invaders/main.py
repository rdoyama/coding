import pygame
import os, sys
import time
import random

pygame.font.init()

# Display
WIDTH, HEIGHT = 650, 650
WINDOW = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Space Invaders")

# Load images
# Lasers
BLUE_LASER = pygame.image.load(os.path.join("assets", "pixel_laser_blue.png"))
GREEN_LASER = pygame.image.load(os.path.join("assets", "pixel_laser_green.png"))
RED_LASER = pygame.image.load(os.path.join("assets", "pixel_laser_red.png"))
YELLOW_LASER = pygame.image.load(os.path.join("assets", "pixel_laser_yellow.png"))

# Ships
BLUE_SHIP = pygame.image.load(os.path.join("assets", "pixel_ship_blue_small.png"))
GREEN_SHIP = pygame.image.load(os.path.join("assets", "pixel_ship_green_small.png"))
RED_SHIP = pygame.image.load(os.path.join("assets", "pixel_ship_red_small.png"))
YELLOW_SHIP = pygame.image.load(os.path.join("assets", "pixel_ship_yellow.png"))

# Background
BACKGROUND = pygame.image.load(os.path.join("assets", "background-black.png"))
BACKGROUND = pygame.transform.scale(BACKGROUND, (WIDTH, HEIGHT))


class Ship:

	COOLDOWN = 30

	def __init__(self, x, y, health=100):
		self.x = x
		self.y = y
		self.health = health
		self.ship_img = None
		self.laser_img = None
		self.lasers = []
		self.cooldown_counter = 0

	def draw(self, window):
		window.blit(self.ship_img, (self.x, self.y))
		self.cooldown()
		for laser in self.lasers:
			laser.draw(window)

	def move_lasers(self, vel, obj):
		for laser in self.lasers:
			laser.move(vel)
			if laser.off_screen():
				self.lasers.remove(laser)
			elif laser.collision(obj):
				obj.health -= 10
				self.lasers.remove(laser)

	def get_width(self):
		return self.ship_img.get_width()

	def get_height(self):
		return self.ship_img.get_height()

	def cooldown(self):
		if self.cooldown_counter >= self.COOLDOWN:
			self.cooldown_counter = 0
		elif self.cooldown_counter > 0:
			self.cooldown_counter += 1

	def shoot(self):
		if self.cooldown_counter == 0:
			laser = Laser(self.x, self.y, self.laser_img)
			self.lasers.append(laser)
			self.cooldown_counter = 1


class Player(Ship):
	def __init__(self, x, y, health=100):
		super().__init__(x, y, health)
		self.ship_img = YELLOW_SHIP
		self.laser_img = YELLOW_LASER
		self.mask = pygame.mask.from_surface(self.ship_img) # Handles colision
		self.max_health = health

	def move_lasers(self, vel, objs):
		for laser in self.lasers:
			laser.move(vel)
			if laser.off_screen():
				self.lasers.remove(laser)
			else:
				for obj in objs:
					if laser.collision(obj):
						objs.remove(obj)
						self.lasers.remove(laser)

	def draw(self, window):
		super().draw(window)
		self.healthbar(window)

	def healthbar(self, window):
		pygame.draw.rect(window, (255, 255, 255), (self.x, self.y + self.ship_img.get_height() + 10,
						 self.ship_img.get_width(), 10), 1)
		pygame.draw.rect(window, (255, 0, 0), (self.x + 1, self.y + self.ship_img.get_height() + 11,
						 int((self.ship_img.get_width() - 2) * self.health / self.max_health), 8))



class Enemy(Ship):

	COLOR_MAP = {
		"red": (RED_SHIP, RED_LASER),
		"green": (GREEN_SHIP, GREEN_LASER),
		"blue": (BLUE_SHIP, BLUE_LASER)
	}

	def __init__(self, x, y, color, health=100):
		super().__init__(x, y, health)
		self.ship_img, self.laser_img = self.COLOR_MAP[color]
		self.mask = pygame.mask.from_surface(self.ship_img)

	def move(self, vel):
		self.y += vel

	def shoot(self):
		if self.cooldown_counter == 0:
			laser = Laser(self.x - self.get_width() // 2, self.y, self.laser_img)
			self.lasers.append(laser)
			self.cooldown_counter = 1


class Laser:
	def __init__(self, x, y, img):
		self.x = x
		self.y = y
		self.img = img
		self.mask = pygame.mask.from_surface(self.img)

	def draw(self, window):
		window.blit(self.img, (self.x, self.y))

	def move(self, vel):
		self.y += vel

	def off_screen(self):
		return 0 > self.y or self.y > HEIGHT

	def collision(self, obj):
		return collide(obj, self)


def collide(obj1, obj2):
	offset_x = obj2.x - obj1.x
	offset_y = obj2.y - obj1.y
	return obj1.mask.overlap(obj2.mask, (offset_x, offset_y)) != None


def main():
	run = True
	FPS = 60
	level = 0
	lives = 5
	main_font = pygame.font.SysFont("comicsans", 50)
	lost_font = pygame.font.SysFont("comicsans", 100)
	player_vel = 5
	laser_vel = 4

	player = Player(300, 500)

	enemies = []
	wave_lenght = 8
	enemy_vel = 1
	
	clock = pygame.time.Clock()

	lost = False
	lost_count = 0
	
	def redraw_window():
		# Insert background image
		WINDOW.blit(BACKGROUND, (0, 0))

		# Draw text
		lives_label = main_font.render(f"Lives: {lives}", 1, (255, 0, 0))
		level_label = main_font.render(f"Level: {level}", 1, (255, 255, 255))
		WINDOW.blit(lives_label, (10, 10))
		WINDOW.blit(level_label, (WIDTH - level_label.get_width() - 10, 10))

		# Draw enemies
		for enemy in enemies:
			enemy.draw(WINDOW)

		# Draw player ship
		player.draw(WINDOW)

		if lost:
			lost_label = lost_font.render("GAME OVER!", 1, (255, 0, 255))
			WINDOW.blit(lost_label, ((WIDTH - lost_label.get_width()) // 2,
									 (HEIGHT - lost_label.get_height()) // 2))
		
		pygame.display.update()
	
	while run:
		# Ensures all the events in the game are syncronized, independent of the fps
		clock.tick(FPS)

		redraw_window()

		if lives < 0 or player.health <= 0:
			lost = True
			lost_count += 1

		if lost:
			if lost_count > FPS * 3:
				run = False
			else:
				continue

		if len(enemies) == 0:
			level += 1
			player.health = player.health + 5 if player.health <= 95 else 100
			wave_lenght += 1
			for i in range(wave_lenght):
				enemy = Enemy(random.randrange(100, WIDTH - 100),
							  random.randrange(-1500, -100),
							  random.choice(["red", "blue", "green"]))
				enemies.append(enemy)
		
		for event in pygame.event.get():
			if event.type == pygame.QUIT:
				quit()

		keys = pygame.key.get_pressed()
		if keys[pygame.K_a] and player.x >= 0:  # Left
			player.x -= player_vel
		if keys[pygame.K_d] and player.x + player.get_width() <= WIDTH:  # Right
			player.x += player_vel
		if keys[pygame.K_w] and player.y >= 0:  # Top
			player.y -= player_vel
		if keys[pygame.K_s] and player.y + player.get_height() + 20 <= HEIGHT:  # Bottom
			player.y += player_vel
		if keys[pygame.K_SPACE]:
			player.shoot()

		for enemy in enemies[:]:
			enemy.move(enemy_vel)
			enemy.move_lasers(laser_vel, player)

			if random.randrange(0, 2*FPS) == 1:
				enemy.shoot()

			if collide(enemy, player):
				player.health -= 10
				enemies.remove(enemy)

			if enemy.y > HEIGHT:
				enemies.remove(enemy)
				lives -= 1

		player.move_lasers(-laser_vel, enemies)


def main_menu():
	run = True
	title_font = pygame.font.SysFont("comicsans", 50)

	while run:

		WINDOW.blit(BACKGROUND, (0, 0))
		title_label = title_font.render("Press any mouse button to start", 1, (255, 255, 255))
		WINDOW.blit(title_label, (WIDTH // 2 - title_label.get_width() // 2,
					HEIGHT // 2 - title_label.get_height() // 2))
		pygame.display.update()

		for event in pygame.event.get():
			if event.type == pygame.QUIT:
				run = False
			elif event.type == pygame.MOUSEBUTTONDOWN:
				main()

	pygame.quit()


if __name__ == "__main__":
	main_menu()
