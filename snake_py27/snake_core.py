def play():
        import sys, pygame, random, settings

        # pygame initialization, resolution setup
        pygame.init()
        white = 255, 255, 255
        black = 0, 0, 0
        screen = pygame.display.set_mode(settings.size)

        #sprite loading
        background = pygame.image.load("sprites/board16x16.png")
        snake_up_sprite = pygame.image.load("sprites/snake_up.png")
        snake_down_sprite = pygame.image.load("sprites/snake_down.png")
        snake_left_sprite = pygame.image.load("sprites/snake_left.png")
        snake_right_sprite = pygame.image.load("sprites/snake_right.png")
        snake_head_sprite = snake_up_sprite
        snake_body_sprite = pygame.image.load("sprites/snake_block.png")
        apple_sprite = pygame.image.load("sprites/red_block.png")
        game_over = pygame.image.load("sprites/game_over.png")
        font = pygame.font.Font("font/comicbd.ttf", 16)
        font_small = pygame.font.Font("font/comicbd.ttf", 12)

        #game global variables initialization

        #general
        random.seed
        block = settings.hop
        direction=0
        settings.initial_speed
        speed = settings.initial_speed
        score = 0
        turbo = 0

        #collision
        collision = 0
        border_crash_up=2
        border_crash_down=3
        border_crash_left=4
        border_crash_right=5
        snake_crash=6
        apple_found=7



        #apple
        total_eaten=0
        apple_x_sample = []
        i =1
        while (i*block<settings.width - block):
                apple_x_sample.append(i*16)
                i += 1
        apple_y_sample = []
        i =1
        while (i*block<settings.height - block):
                apple_y_sample.append(i*16)
                i += 1


        temp_ax = (random.sample(apple_x_sample, 1))
        temp_ay = (random.sample(apple_y_sample, 1))
        apple_x=int(temp_ax[0])
        apple_y=int(temp_ay[0])

        eaten_apple = 0

        #snake
        max_size=10
        snake_size=3

        snake_x=[]
        snake_x.append(settings.width/2)
        snake_y=[]
        snake_y.append(settings.height/2)
        temp_snake_x=[0]
        temp_snake_y=[0]

        for i in range(1, snake_size, 1):
            snake_x.append(settings.width/2)
            snake_y.append(settings.height/2 + i * 16)
            temp_snake_x.append(0)
            temp_snake_y.append(0)

        running = 1
        #main loop
        while running == 1:


            collision = 0
            #event handling
            for event in pygame.event.get():
                if event.type == pygame.QUIT: running = -1
                elif event.type ==  pygame.KEYDOWN and event.key == pygame.K_UP:
                    if direction == 2: break
                    direction=0
                    snake_head_sprite=snake_up_sprite
                elif event.type ==  pygame.KEYDOWN and event.key == pygame.K_LEFT:
                    if direction == 3: break
                    direction=1
                    snake_head_sprite=snake_left_sprite
                elif event.type ==  pygame.KEYDOWN and event.key == pygame.K_DOWN:
                    if direction == 0: break
                    direction=2
                    snake_head_sprite=snake_down_sprite
                elif event.type ==  pygame.KEYDOWN and event.key == pygame.K_RIGHT:
                    if direction == 1: break
                    direction=3
                    snake_head_sprite=snake_right_sprite
                elif event.type ==  pygame.KEYDOWN and event.key == pygame.K_ESCAPE:
                    running = -2
                    
        # snake turbo test block
                elif event.type ==  pygame.KEYDOWN and event.key == pygame.K_SPACE:
                    turbo = 1
                    speed /= 2
                    speed = int(speed)
                elif event.type == pygame.KEYUP and event.key == pygame.K_SPACE:
                    turbo = 0
                    speed *= 2
                    speed= int(speed)
       
            #snake movement block

            for i in range(1, snake_size, 1):
                temp_snake_x[i]=snake_x[i-1]
                temp_snake_y[i]=snake_y[i-1]
                
            if direction == 0:
                snake_y[0]-=settings.hop
            elif direction == 1:
                snake_x[0]-=settings.hop
            elif direction == 2:
                snake_y[0]+=settings.hop
            elif direction == 3:
                snake_x[0]+=settings.hop

            for i in range(1, snake_size, 1):
                snake_x[i]=temp_snake_x[i]
                snake_y[i]=temp_snake_y[i]

            #collision test
            #border test
            if snake_y[0] < block:
                collision=border_crash_up
            elif snake_y[0]> settings.height - block * 2:
                collision=border_crash_down
            elif snake_x[0] < block:
                collision=border_crash_left
            elif snake_x[0] > settings.width - block * 2:
                collision=border_crash_right
            #body test
            for i in range(1, snake_size):
                if snake_x[0] == snake_x[i] and snake_y[0] == snake_y[i]:
                    collision=snake_crash

            if snake_x[0] == apple_x and snake_y[0] == apple_y:
                collision=apple_found
                eaten_apple=1


            if (collision >= 1 and collision <=5):
                print("COLLISION TYPE: " + str(collision))
                print("fodeu")
                running = collision

            #randomic apple generation
            if (eaten_apple):
                temp_ax = (random.sample(apple_x_sample, 1))
                temp_ay = (random.sample(apple_y_sample, 1))
                apple_x=int(temp_ax[0])
                apple_y=int(temp_ay[0])
                eaten_apple=0
                score += (240 - speed)/20
                if (speed > settings.max_speed):
                    speed -= settings.acceleration

            #snake growth
                snake_size += 1
                snake_x.append(snake_x[snake_size-2])
                snake_y.append(snake_y[snake_size-2])
                temp_snake_x.append(0)
                temp_snake_y.append(0)


            speed = int(speed)

                
            # screen_blitting
            screen.fill(white)
            screen.blit(background, (0,0))
            screen.blit(snake_head_sprite, (snake_x[0], snake_y[0]))
            for i in range (1, snake_size, 1):
                 screen.blit(snake_body_sprite, (snake_x[i], snake_y[i]))
            screen.blit(apple_sprite, (apple_x, apple_y))

            pygame.display.update()
            pygame.time.delay(speed)
#            print(running)
            if (collision >= 1 and collision <=6):
                score = int(score)
                score_number_text = str(score)
                score_text = "Score: "
                text = "Press ESCAPE to return to the main menu."
                text2 = "TIP: You can speed up by pressing space bar!"
                score_number_image = font.render(score_number_text, 1, black, white)
                score_text_image = font.render(score_text, 1, black, white)
                text_image = font_small.render(text, 1, black, white)
                text2_image = font_small.render(text2, 1, black, white)
                screen.blit(game_over, (settings.width/4, 20))
                screen.blit(score_text_image, (settings.width/2.2, 300))
                screen.blit(score_number_image, (settings.width/2.2 + 60, 300))
                screen.blit(text_image, (settings.width/3, 330))
                screen.blit(text2_image, (settings.width/3, 360))
                pygame.display.update()
                end = 1
                while end == 1:
                        for event in pygame.event.get():
                                if event.type == pygame.QUIT: end = -1
                                elif event.type ==  pygame.KEYDOWN and event.key == pygame.K_ESCAPE: end = 0
                if end == -1:
                        pygame.quit()
                        sys.exit()
#        print("GAME STOPPED")
        if running == -1:
                pygame.quit()
                sys.exit()
        
