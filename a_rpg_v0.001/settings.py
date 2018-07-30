import pygame

pygame.init()
video = pygame.display.Info()
print(video.current_w)
print(video.current_h)
pygame.quit()

max_size = 4
if video.current_w < 1900 or video.current_h < 1080:
    max_size = 3
    if video.current_w < 1600 or video.current_h < 900:
        max_size = 2
        if video.current_w < 1024 or video.current_h < 768:
            max_size = 1
            if video.current_w < 800 or video.current_h < 640:
                max_size = 0
                if video.current_w < 640 or video.current_h < 480:
                    max_size = -1
                    

white = 255, 255, 255
black = 0, 0, 0
screen_size = [2]
aspect_ratio = [0] # 0 = 4:3 aspectio ratio
width = video.current_w
height = video.current_h
block_size = 32
board_width = 25
board_height = 20
full_screen = 0
size = width, height

min_size = 0




def change_full_screen():
    global full_screen
    if full_screen == 0:
        full_screen = pygame.FULLSCREEN
    else:
        full_screen = 0
    print("full screen FLAG: " + str(full_screen))

def update():
    global aspect_ratio
    global screen_size
    global width
    global height
    global block_size
    global size
    if screen_size[0] == 0:
            width = 640
            height = 480
            block_size = 24
    elif screen_size[0] == 1:
            width = 800
            height = 640
            block_size = 32
    elif screen_size[0] == 2:
            width = 1024
            height = 768
            block_size = 38
    elif screen_size[0] == 3:
            width = 1600
            height = 900
            block_size = 45
    elif screen_size[0] == 4:
            width = 1920
            height = 1080
            block_size = 54
    else:
        print("uh no!")
    size = width, height
    
update()
print("Settings...")
print(width)
print(height)
print(block_size)
print(size)


# width[0]: 640, 800, 1024, 1360, 1600, 1920
# height[0]: 480, 640, 768, 768, 900, 1080
