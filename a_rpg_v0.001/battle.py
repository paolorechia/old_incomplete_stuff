import pygame, sys, settings, gf

pygame.init()
#global variables


def update_dialog_box():
    global dialog_box
    dialog_box = pygame.Rect(0, settings.block_size * 15, settings.width, (settings.height/4 * 3))

def init_board():

    screen=pygame.display.set_mode((settings.block_size, settings.block_size))
    screen.fill(settings.white)
    pygame.draw.rect(screen, settings.black, (0,0,settings.block_size, settings.block_size), 1) 
    pygame.image.save(screen, "media/sprites/block.png")
    block = pygame.image.load("media/sprites/block.png")
    screen=pygame.display.set_mode((settings.size), settings.full_screen)
    for i in range(0, settings.board_width * settings.block_size, settings.block_size):
        for j in range(0, settings.board_height * settings.block_size, settings.block_size):
             screen.blit(block, (i, j))
            
    pygame.image.save(screen, "media/sprites/board.png")

# old version that uses blocks drawn by hand instead of run-time generated ones
#    block_string = "media/sprites/board_block" + str(settings.block_size) + "x" + str(settings.block_size) + ".png"
#    block = pygame.image.load(block_string)
#    for i in range(0, settings.board_width * settings.block_size, settings.block_size):
#        for j in range(0, settings.board_height * settings.block_size, settings.block_size):
#            screen.blit(block, (i, j))
#    pygame.image.save(screen, "media/sprites/board.png")

def board_decrease(screen_size, min_size, size):
    global board
    global screen

    gf.decrease_screen(settings.screen_size, min_size)
    settings.update()
    screen=pygame.display.set_mode((settings.size), settings.full_screen)
    init_board()
    board=pygame.image.load("media/sprites/board.png").convert()
    update_dialog_box()
       
def board_increase(screen_size, max_size, size):
    global board
    global screen
    
    gf.increase_screen(settings.screen_size, max_size)
    settings.update()
    screen=pygame.display.set_mode((settings.size), settings.full_screen)
    init_board()
    board=pygame.image.load("media/sprites/board.png").convert()
    update_dialog_box()
  
def pause(screen):
    screen
    pause_box = pygame.Rect(settings.width/4, settings.height/20, settings.width/2, (settings.height/3 * 2))
    running = 1
    while running == 1:
        for event in pygame.event.get():
            if event.type == pygame.QUIT: running = 0
            elif event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:
                running = 0
        pygame.draw.rect(screen, settings.black, pause_box)
        pygame.display.update()
     

def init():
    global screen
    global board
    global dialog_box
    board=pygame.image.load("media/sprites/board.png").convert()
    buttons_text=[" "]
    buttons_coor = [(0, 0)]
    buttons_wh = [(0, 0)]
    rendered_buttons = [board]
    rendered_hovered_buttons = [board]
    pygame.font.init()
    button_font = pygame.font.Font("media/font/candara.ttf", 14)

    text_margin = 0
    text_line_space = 20
    
    gf.create_button(text_margin, 0, "decrease window", buttons_text, buttons_coor, buttons_wh, button_font)    
    gf.create_button(text_margin, buttons_coor[1][1] + text_line_space, "increase window", buttons_text, buttons_coor, buttons_wh, button_font)
    gf.create_button(text_margin, buttons_coor[2][1] + text_line_space, "FULLSCREEN", buttons_text, buttons_coor, buttons_wh, button_font)

    gf.render_buttons(buttons_text, rendered_buttons, button_font)
    gf.render_hovered_buttons(buttons_text, rendered_hovered_buttons, button_font)

    print(buttons_coor)
    print(buttons_wh)
    print(buttons_text)
    print(rendered_buttons)
    print(type(rendered_buttons))
    5
    update_dialog_box()

    running = 1
    while running == 1:

        hover = 0
        test = 0
        mouse_x=pygame.mouse.get_pos()[0]
        mouse_y=pygame.mouse.get_pos()[1]
        hover = gf.check_buttons_hover(mouse_x, mouse_y, buttons_coor, buttons_wh)
        print("test = " + str(test))
        for event in pygame.event.get():
            if event.type == pygame.QUIT: running = 0
            elif event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:
                pause(screen)
            elif (hover != 0 and pygame.mouse.get_pressed()[0] == 1):
                test = hover
                print("Button " + str(test) + " clicked!")



#            OLD CODE (test cliick before hover)     
#            elif (pygame.mouse.get_pressed()[0] == 1):
#                test = gf.check_buttons_hover(mouse_x, mouse_y, buttons_coor, buttons_wh)

        if test != 0:
            if test == 1:
                board_decrease(settings.screen_size, settings.min_size, settings.size)
            elif test == 2:
                board_increase(settings.screen_size, settings.max_size, settings.size)
            elif test == 3:
                settings.change_full_screen()
                pygame.display.set_mode((settings.size), settings.full_screen)


        screen.fill(settings.white)
        screen.blit(board, (0,0))
        pygame.draw.rect(screen, (settings.white), dialog_box)
    
        for i in range(1, len(rendered_buttons)):
            screen.blit(rendered_buttons[i], buttons_coor[i])

        if (hover != 0):
            print("hover!")
            screen.blit(rendered_hovered_buttons[hover], buttons_coor[hover])
        
        pygame.display.update()

    pygame.quit()

if (settings.min_size == -1):
    print("video resolution too low!!!")
else:
    init_board()
    screen=pygame.display.set_mode((settings.size), settings.full_screen)
    board=pygame.image.load("media/sprites/block.png").convert()
    dialog_box = (0, 0, 0, 0)
    init()

