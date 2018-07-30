import pygame, sys, snake_core, settings, settings_menu

pygame.init()

width = 640
height = 480
size = width, height
white = 255, 255, 255
screen = pygame.display.set_mode(size)
screen.fill(white)
title = pygame.image.load("sprites/main_title.png")
play =  pygame.image.load("sprites/play.png")
play_blue =  pygame.image.load("sprites/play_blue.png")
settings =  pygame.image.load("sprites/settings.png")
settings_blue =  pygame.image.load("sprites/settings_blue.png")
exit_button =  pygame.image.load("sprites/exit.png")
exit_button_blue =  pygame.image.load("sprites/exit_blue.png")
mouse_pos = []

running = True
while running:

    for event in pygame.event.get():
        if event.type == pygame.QUIT: running = False
        if event.type == pygame.KEYDOWN and event.key == pygame.K_SPACE:
            snake_core.play()
    screen.fill(white)
    screen.blit(title, (width/4, 20))
    mouse_pos = pygame.mouse.get_pos()
    mouse_state = pygame.mouse.get_pressed()
    if mouse_pos[0] > width/2.2 and mouse_pos[0] < (width/2.2) + 37 and mouse_pos[1] > 200 and mouse_pos[1] < 200 + 20:
        screen.blit(play_blue, (width/2.2, 200))
        if mouse_state[0] == 1: snake_core.play()
    else:
        screen.blit(play, (width/2.2, 200))
    if mouse_pos[0] > width/2.2 and mouse_pos[0] < (width/2.2) + 76 and mouse_pos[1] > 300 and mouse_pos[1] < 300 + 20:
        screen.blit(settings_blue, (width/2.2, 300))
        if mouse_state[0] == 1: settings_menu.run()
    else:
        screen.blit(settings, (width/2.2, 300))
    if mouse_pos[0] > width/2.2 and mouse_pos[0] < (width/2.2) + 36 and mouse_pos[1] > 400 and mouse_pos[1] < 400 + 20:
        screen.blit(exit_button_blue, (width/2.2, 400))
        if mouse_state[0] == 1: running = False
    else:
        screen.blit(exit_button, (width/2.2,400))
    pygame.display.update()

pygame.quit()
sys.exit()
