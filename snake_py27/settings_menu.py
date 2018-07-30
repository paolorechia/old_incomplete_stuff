import pygame, settings, sys

def increase_speed():
    if (settings.initial_speed > 20):
        settings.initial_speed -= 20

def decrease_speed():
    if (settings.initial_speed < 220):
        settings.initial_speed += 20


def run():

    pygame.init()
    white = 255, 255, 255
    black = 0, 0, 0
    blue = 0, 0, 205
    screen = pygame.display.set_mode(settings.size)
    pygame.font.init()
    font = pygame.font.Font("font/comicbd.ttf", 16)
    title_font = pygame.font.Font("font/comicbd.ttf", 76)
    title = title_font.render("Settings", 0, black, white)
    speed = font.render("Snake Speed:", 0, black, white)
    back = font.render("Go Back", 0, black, white)
    back_blue = font.render("Go Back", 0, blue, white)
    bar = pygame.image.load("sprites/bar.png")
    plus = pygame.image.load("sprites/plus_button.png")
    plus_blue = pygame.image.load("sprites/plus_button_blue.png")
    plus_purple = pygame.image.load("sprites/plus_button_purple.png")
    minus = pygame.image.load("sprites/minus_button.png")
    minus_blue = pygame.image.load("sprites/minus_button_blue.png")
    minus_purple = pygame.image.load("sprites/minus_button_purple.png")
    running = 1

    while running == 1:

        for event in pygame.event.get():
            if event.type == pygame.QUIT: running = -1
            elif event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:
                running = 0    

        mouse_pos = pygame.mouse.get_pos()
        mouse_state = pygame.mouse.get_pressed()
        
        screen.fill(white)
        screen.blit(title, (settings.width/4, 20))
        screen.blit(speed, (settings.width/2.2, 200))
        number_bars = 11 - (settings.initial_speed / 20)
        for i in range(int(number_bars)):
                    screen.blit(bar, ((settings.width/2.2 + 8 * i), 250))
        if (mouse_pos[0] > (settings.width/2.2 - 50)) and mouse_pos[0] < (settings.width/2.2 - 15) and mouse_pos[1] > 248 and mouse_pos[1] < 248 + 34:
            screen.blit(minus_blue, (settings.width/2.2 - 50, 248))
            if mouse_state[0] == 1:
                 screen.blit(minus_purple, (settings.width/2.2 - 50, 248))
                 decrease_speed()
        else:
            screen.blit(minus, (settings.width/2.2 - 50, 248))


        if (mouse_pos[0] > (settings.width/2.2 + 95)) and mouse_pos[0] < (settings.width/2.2 + 140) and mouse_pos[1] > 248 and mouse_pos[1] < 248 + 34:
            screen.blit(plus_blue, (settings.width/2.2 + 95, 248))
            if mouse_state[0] == 1:
                 screen.blit(plus_purple, (settings.width/2.2 + 95, 248))
                 increase_speed()
        else:
            screen.blit(plus, (settings.width/2.2 + 95, 248))

            

        if mouse_pos[0] > settings.width/2.2 and mouse_pos[0] < (settings.width/2.2) + 76 and mouse_pos[1] > 350 and mouse_pos[1] < 350 + 20:
            screen.blit(back_blue, (settings.width/2.2, 350))
            if mouse_state[0] == 1: running = False
        else:
            screen.blit(back, (settings.width/2.2,350))
        pygame.display.update()
        pygame.time.delay(100)


    if (running == -1):
        pygame.quit()

