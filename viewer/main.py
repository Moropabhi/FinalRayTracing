import pygame
import subprocess as sp
import threading 
# pygame setup
import time
pygame.init()
clock = pygame.time.Clock()
running = True
dt = 0

aspect_ratio=16.0/9
image_width=800
screen = pygame.display.set_mode((image_width,image_width/aspect_ratio))
vfov=20
defocus_angle=10
focal_dist=3.4
lookfrom=[-2.0,2.0,1.0]
lookat=[0.,0.,-1.0]
vup=[0.,1.,0.0]
sample_count = 5
max_depth=5

f = lambda : " ".join(map(str,[aspect_ratio,
image_width,
vfov,
defocus_angle,
focal_dist,
lookfrom[0],
lookfrom[1],
lookfrom[2],
lookat[0],
lookat[1],
lookat[2],
vup[0],
vup[1],
vup[2],
sample_count,
max_depth]))

player_pos = pygame.Vector2(screen.get_width() / 2, screen.get_height() / 2)

def runner():
    with open("viewer/transfer.txt","w") as file:
        file.write(f())
    sp.run("./a.out")
t1 = threading.Thread(target=runner, args=())
img = pygame.image.load("output/output.ppm")
t1.start()
while running:
    # poll for events
    # pygame.QUIT event means the user clicked X to close your window
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # fill the screen with a color to wipe away anything from last frame
    screen.fill("purple")
    try:
        img = pygame.image.load("output/output.ppm")
    except:
        pass
    screen.blit(img,(0,0))

    pygame.draw.circle(screen, "red", player_pos, 40)

    keys = pygame.key.get_pressed()
    if keys[pygame.K_w]:
        player_pos.y -= 300 * dt
    if keys[pygame.K_s]:
        player_pos.y += 300 * dt
    if keys[pygame.K_a]:
        player_pos.x -= 300 * dt
    if keys[pygame.K_d]:
        player_pos.x += 300 * dt

    # flip() the display to put your work on screen
    pygame.display.flip()

    # limits FPS to 60
    # dt is delta time in seconds since last frame, used for framerate-
    # independent physics.
    dt = clock.tick(60) / 1000

pygame.quit()
