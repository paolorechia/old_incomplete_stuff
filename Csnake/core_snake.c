#ifndef STDLIB_H
#include <stdlib.h>
#endif

#ifndef TIME_H
#include <time.h>
#endif

#ifndef STRING_H
#include <string.h>
#endif

#ifndef STDIO_H
#include <stdio.h>
#endif 


int run_core(SDL_Window * window){

    // setup basic colors
    SDL_Color white={255,255,255};
    SDL_Color black={0,0,0};
    SDL_Color blue={0,0,205};

    // initialize image extension (enables .PNG loading)
    int imgFlags = IMG_INIT_PNG;

    if (!( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf ("SDL_image could not initialize! SDL_image Error: %s\n",
        IMG_GetError());
        return 1;
    }
    
    // load images
    SDL_Surface* board = IMG_Load("sprites/board16x16.png");
    if (board == NULL)
    {
        printf("Couldn't load image! Error: %s\n", IMG_GetError());
        return 1;
    }
    // snake sprites
    SDL_Surface* snake_up = IMG_Load("sprites/snake_up.png");
    if (snake_up == NULL)
    {
        printf("Couldn't load image! Error: %s\n", IMG_GetError());
        return 1;
    }
    SDL_Surface* snake_down = IMG_Load("sprites/snake_down.png");
    if (snake_down == NULL)
    {
        printf("Couldn't load image! Error: %s\n", IMG_GetError());
        return 1;
    }
    SDL_Surface* snake_left = IMG_Load("sprites/snake_left.png");
    if (snake_left == NULL)
    {
        printf("Couldn't load image! Error: %s\n", IMG_GetError());
        return 1;
    }
    SDL_Surface* snake_right = IMG_Load("sprites/snake_right.png");
    if (snake_right == NULL)
    {
        printf("Couldn't load image! Error: %s\n", IMG_GetError());
        return 1;
    }
    SDL_Surface* snake_body = IMG_Load("sprites/snake_block.png");
    if (snake_body == NULL)
    {
        printf("Couldn't load image! Error: %s\n", IMG_GetError());
        return 1;
    }
    // n' apple!
    SDL_Surface* apple = IMG_Load("sprites/red_block.png");
    if (apple == NULL)
    {
        printf("Couldn't load image! Error: %s\n", IMG_GetError());
        return 1;
    }

    // snake head starts facing up!
    SDL_Surface* snake_head = snake_up;

    // create rectangles for the surfaces

    SDL_Rect snake_head_rect;
    SDL_Rect snake_body_rect;
    SDL_Rect apple_rect;

    // global variables initialization

    // general
    int block = hop;
    int direction = 0;
    int speed = initial_speed;
    int score = 0;
    int turbo = 0;

    // collision
    int collision = 0;
    int border_crash_up=2;
    int border_crash_down=3;
    int border_crash_left=4;
    int border_crash_right=5;
    int snake_crash=6;
    int apple_found=7;

	
    //apple
    int total_eaten=0;

    // initialize random seed
    srand (time(NULL));
    int apple_x = (rand() % ((width - 2*block)/block)) * block + block; 
    int apple_y = (rand() % ((height - 2*block)/block)) * block + block;

    // boolean variable
    int eaten_apple=0;

    // snake
    int max_size=10;
    int snake_size=3;

    // snake as a vector
    
    int snake_x[20];
    int snake_y[20];
    int temp_snake_x[20];
    int temp_snake_y[20];
    int i;
    
    // initialize it's body with invalid values (negative coordinates)
    for (i=0;i<20;i++){
        snake_x[i]=-1;
        snake_y[i]=-1;
        temp_snake_x[i]=-1;
        temp_snake_y[i]=-1;
    }

    // properly initialize the snake with actual coordinates up to it's size
    snake_x[0]=width/2;
    snake_y[0]=height/2;
    for (i=1;i<snake_size;i++){
        snake_x[i]=width/2;
        snake_y[i]=height/2 + i*16;
    }
    

    // reset surface and blit board
    SDL_Surface * background = SDL_GetWindowSurface( window);
    SDL_FillRect( background, NULL, 
                SDL_MapRGB(background->format,
                0xFF, 0xFF, 0xFF));
    SDL_BlitSurface(board, NULL, background, NULL);
    SDL_UpdateWindowSurface(window);
    

    // main l00p
	SDL_Event e;
	int running = 1;
    int moved = 1;
	while (running == 1)
    {

        collision = 0;

        // get mouse coordinates
		int x, y;
		SDL_GetMouseState(&x, &y);

        // evaluate poll event only if snaked has moved
        if (moved){
        // quit if X is closed or Esc is pressed down
		while (SDL_PollEvent( &e) != 0){
			if ( e.type == SDL_QUIT){
				running = 0;
			}
			else if ( e.type == SDL_KEYDOWN && 
					e.key.keysym.sym == SDLK_ESCAPE)
				running = 0;
            
            // actual snake commands (up, left, down, right, turbo)
            else if (e.type == SDL_KEYDOWN &&
                    e.key.keysym.sym == SDLK_UP)
                {
                    if (direction == 2)
                        break;
                    direction = 0;
                    snake_head=snake_up;
                }
            else if (e.type == SDL_KEYDOWN &&
                    e.key.keysym.sym == SDLK_LEFT)
                {
                    if (direction == 3)
                        break;
                    direction = 1;
                    snake_head=snake_left;
                }
            else if (e.type == SDL_KEYDOWN &&
                    e.key.keysym.sym == SDLK_DOWN)
                {
                    if (direction == 0)
                        break;
                    direction = 2;
                    snake_head=snake_down;
                }
            else if (e.type == SDL_KEYDOWN &&
                    e.key.keysym.sym == SDLK_RIGHT)
                {
                    if (direction == 1)
                        break;
                    direction = 3;
                    snake_head=snake_right;
                }
            else if (e.type == SDL_KEYDOWN &&
                    e.key.keysym.sym == SDLK_SPACE)
                {
                    turbo = 1;
                    speed = speed/2;
                }
            else if (e.type == SDL_KEYUP &&
                    e.key.keysym.sym == SDLK_SPACE)
                {
                    turbo = 0;
                    speed = speed * 2;
                }
            moved = 0;
        }
        }
        // snake movement logic

        // save last state of snake body
        for (i=1; i<snake_size; i++){
            temp_snake_x[i]=snake_x[i-1];
            temp_snake_y[i]=snake_y[i-1];
        }

        // update snake's head
        if (direction == 0)
            snake_y[0]-=hop;
        else if (direction == 1)
            snake_x[0]-=hop;
        else if (direction == 2)
            snake_y[0]+=hop;
        else if (direction == 3)
            snake_x[0]+=hop;

        // update snake's body
        for (i=1; i<snake_size; i++){
            snake_x[i]=temp_snake_x[i];
            snake_y[i]=temp_snake_y[i];
        }

        moved = 1;

        // collision test
        // border test
		
		// printf("Coordinates: %d %d\n", snake_x[0], snake_y[0]);

        if (snake_y[0] < block)
            collision=border_crash_up;

        else if (snake_y[0] > (height - block*2))
            collision=border_crash_down;

        else if (snake_x[0] < block)
            collision=border_crash_left;

        else if(snake_x[0] > (width - block * 2))
            collision=border_crash_right;

        // body test
        for (i=1; i<snake_size; i++)
            if (snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i])
            {
                collision=snake_crash;
            }
        
        if (snake_x[0] == apple_x && snake_y[0] == apple_y)
        {
            eaten_apple=1; 
        }
        

        if (collision >= 1 && collision <=6){
            printf("COLLISION TYPE: %d\n", collision); 
            running = collision;
        }
    
        if (eaten_apple){
            // generate new apple
			apple_x = (rand() % ((width - 2*block)/block)) * block + block; 
			apple_y = (rand() % ((height - 2*block)/block)) * block + block; 

            // and set it as not eaten
            eaten_apple=0;
            // increase score and speed


            score += (240 - speed)/20;
            if (speed > max_speed)
                speed -= acceleration;

            // snake grows in size
            snake_size += 1;
            snake_x[snake_size-1];
        }

        // screen bliting!
        
        
           
        SDL_Surface * background = SDL_GetWindowSurface( window);
        SDL_FillRect( background, NULL, 
                    SDL_MapRGB(background->format,
                    0xFF, 0xFF, 0xFF));
        SDL_BlitSurface(board, NULL, background, NULL);

        snake_head_rect.x = snake_x[0];
        snake_head_rect.y = snake_y[0];
        SDL_BlitSurface(snake_head, NULL, background, &snake_head_rect);

        for (i=0; i< snake_size; i++){
            snake_body_rect.x = snake_x[i];
            snake_body_rect.y = snake_y[i];
            SDL_BlitSurface(snake_body, NULL, background, &snake_body_rect);
        }
		apple_rect.x=apple_x;
		apple_rect.y=apple_y;
		
        SDL_BlitSurface(apple, NULL, background, &apple_rect);

        SDL_UpdateWindowSurface(window);
        
		SDL_Delay(speed);
	}


	SDL_FreeSurface(board);
	SDL_FreeSurface(apple);

	SDL_FreeSurface(snake_up);
	SDL_FreeSurface(snake_right);
	SDL_FreeSurface(snake_left);
	SDL_FreeSurface(snake_down);
	SDL_FreeSurface(snake_body);
	
return 0;
}
/* buggy code section -- second event loop causes segmentation fault
	if (collision >= 1 && collision <= 6){

		// initialize font extension
		if (TTF_Init()==-1){
			printf("TTF_Init: %s\n", TTF_GetError());
			return 1;
		}

		// initialize font pointers
		TTF_Font * font;
		TTF_Font * font_small;

		// open font files
		font = TTF_OpenFont("font/VeraBd.ttf", 16);
		if (!font){
			printf("TTF_OpenFont: %s\n", TTF_GetError());
			return 1;
		}

		font_small = TTF_OpenFont("font/VeraBd.ttf", 12); 
		if (!font_small){
			printf("TTF_OpenFont: %s\n", TTF_GetError());
			return 1;
		}

		// render text surfaces
		SDL_Surface * game_over;
		SDL_Surface * text_surface;
		SDL_Surface * text2_surface;


		if (!(game_over=TTF_RenderText_Solid(font, "Game Over!", black)))

		{
			printf("Cannot render text! Error: %s\n", TTF_GetError());
			return 1;
    	}

		if (!(text_surface=TTF_RenderText_Solid(font_small,
            "Press ESCAPE to return to the main menu.",
            black)))
		{
			printf("Cannot render text! Error: %s\n", TTF_GetError());
			return 1;
    	}
		if (!(text2_surface=TTF_RenderText_Solid(font_small,
		    "TIP: You can speed up by pressing space bar!",
            black)))
		{
			printf("Cannot render text! Error: %s\n", TTF_GetError());
			return 1;
    	}

		SDL_Rect game_over_rect;
		game_over_rect.x=width/2.2;
		game_over_rect.y=100;

		SDL_Rect score_rect;
		score_rect.x=width/2.2;
		score_rect.y=150;

		SDL_Rect text_rect;
		score_rect.x=width/3;
		score_rect.y=200;

		SDL_Rect text2_rect;
		score_rect.x=width/3;
		score_rect.y=250;

		// Close Fonts
		TTF_CloseFont(font);
		font = NULL;

		TTF_CloseFont(font_small);
		font_small = NULL;

		SDL_BlitSurface(game_over, NULL, background, &game_over_rect);
		SDL_BlitSurface(text_surface, NULL, background, &text_rect);
		SDL_BlitSurface(text2_surface, NULL, background, &text2_rect);

		SDL_UpdateWindowSurface(window);

		SDL_FreeSurface(game_over);
		SDL_FreeSurface(text_surface);
		SDL_FreeSurface(text2_surface);
		running = 1;
    
        SDL_PumpEvents;
		while (running == 1){
			while (SDL_PollEvent(&e) != 0){
                printf("morri?7\n");
				if ( e.type == SDL_QUIT){
					running = -1;
				}
				else if ( e.type == SDL_KEYDOWN && 
						e.key.keysym.sym == SDLK_ESCAPE)
					running = 0;
			}
		if (running == -1)
            printf("morri?8\n");
			SDL_Quit();
			return 0;
		}
    */
