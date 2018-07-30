#include <stdio.h>
#include <stdlib.h>
#include "settings.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


void increase_speed(){
    if (initial_speed > 20)
        initial_speed -= 20;
}

void decrease_speed(){
    if (initial_speed < 220)
        initial_speed += 20;
}

int run_settings(SDL_Window * window){

    // setup basic colors
    SDL_Color white={255,255,255};
    SDL_Color black={0,0,0};
    SDL_Color blue={0,0,205};

    // create a graphical window.

    SDL_Surface * background = SDL_GetWindowSurface( window);
    SDL_FillRect( background, NULL, 
                SDL_MapRGB(background->format,
                0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(window);
    


    // initialize font extension
    if (TTF_Init()==-1){
        printf("TTF_Init: %s\n", TTF_GetError());
        return 1;
    }

    // initialize font pointers
    TTF_Font * font;
    TTF_Font * title_font;

    // open font files
    font = TTF_OpenFont("font/VeraBd.ttf", 16);
    if (!font){
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        return 1;
    }

    title_font = TTF_OpenFont("font/VeraBd.ttf", 76); 
    if (!title_font){
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        return 1;
    }

    // render title font surface
    SDL_Surface * title;
    if (!(title=TTF_RenderText_Solid(title_font, "Settings", black)))

    {
        printf("Cannot render text! Error: %s\n", TTF_GetError());
        return 1;
    }

    // close title font since it is no longer used
    // (the surface has already been rendered and we only need that for
    // blitting)

    TTF_CloseFont(title_font);
    title_font = NULL;

    // render other text surfaces
    SDL_Surface * speed;
    SDL_Surface * back;
    SDL_Surface * back_blue;

    if (!(speed=TTF_RenderText_Solid(font, "Snake Speed:", black))) 
    {
        printf("Cannot render text! Error: %s\n", TTF_GetError());
        return 1;
    }

    if (!(back=TTF_RenderText_Solid(font, "Back", black))) 
    {
        printf("Cannot render text! Error: %s\n", TTF_GetError());
        return 1;
    }

    if (!(back_blue=TTF_RenderText_Solid(font, "Back", blue))) 
    {
        printf("Cannot render text! Error: %s\n", TTF_GetError());
        return 1;
    }

    // assign rectangles to text surfaces
    SDL_Rect title_rect;
    title_rect.x=width/4;
    title_rect.y=20;

    SDL_Rect speed_rect;
    speed_rect.x=width/2.2;
    speed_rect.y=200;
    
    SDL_Rect back_rect;
    back_rect.x=width/2.2;
    back_rect.y=350;


    // initialize image extension (enables .PNG loading)
    int imgFlags = IMG_INIT_PNG;

    if (!( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf ("SDL_image could not initialize! SDL_image Error: %s\n",
        IMG_GetError());
        return 1;
    }
    
    // load images
    SDL_Surface* bar = IMG_Load("sprites/bar.png");
    if (bar == NULL)
    {
        printf("Couldn't load image! Error: %s\n", IMG_GetError());
        return 1;
    }
    SDL_Surface* plus = IMG_Load("sprites/plus_button.png");
    if (plus == NULL)
    {
        printf("Couldn't load image! Error: %s\n", IMG_GetError());
        return 1;
    }
    SDL_Surface* plus_blue = IMG_Load("sprites/plus_button_blue.png");
    if (plus_blue == NULL)
    {
        printf("Couldn't load image! Error: %s\n", IMG_GetError());
        return 1;
    }
    SDL_Surface* plus_purple = IMG_Load("sprites/plus_button_purple.png");
    if (plus_purple == NULL)
    {
        printf("Couldn't load image! Error: %s\n", IMG_GetError());
        return 1;
    }
    SDL_Surface* minus = IMG_Load("sprites/minus_button.png");
    if (minus == NULL)
    {
        printf("Couldn't load image! Error: %s\n", IMG_GetError());
        return 1;
    }
    SDL_Surface* minus_blue = IMG_Load("sprites/minus_button_blue.png");
    if (minus_blue == NULL)
    {
        printf("Couldn't load image! Error: %s\n", IMG_GetError());
        return 1;
    }
    SDL_Surface* minus_purple = IMG_Load("sprites/minus_button_purple.png");
    if (minus_purple == NULL)
    {
        printf("Couldn't load image! Error: %s\n", IMG_GetError());
        return 1;
    }

    // create rectangles for the surfaces
    SDL_Rect bar_rect;
    bar_rect.x=width/2.2;
    bar_rect.y=250;

    SDL_Rect plus_rect;
    plus_rect.x=width/2.2 + 110, 248;
    plus_rect.y=248;

    SDL_Rect minus_rect;
    minus_rect.x=width/2.2 - 50;
    minus_rect.y=248;


    // blit 'em all
	

	SDL_Event e;
	int running = 1;
	while (running){
		int x, y;
		SDL_GetMouseState(&x, &y);
		while (SDL_PollEvent( &e) != 0){
			if ( e.type == SDL_QUIT){
				running = 0;
			}
			else if ( e.type == SDL_KEYDOWN && 
					e.key.keysym.sym == SDLK_ESCAPE)
				running = 0;

		}
    	SDL_FillRect( background, NULL, 
                SDL_MapRGB(background->format,
                0xFF, 0xFF, 0xFF));
		SDL_BlitSurface(title, NULL, background, &title_rect);
		SDL_BlitSurface(speed, NULL, background, &speed_rect);
		SDL_BlitSurface(back, NULL, background, &back_rect);


		 if (x > (width/2.2 - 50) &&
			 x < (width/2.2 - 15) &&
		     y > 248 && y < 248 + 34){
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				SDL_BlitSurface(minus_purple, NULL, background, &minus_rect);
				decrease_speed();
			}
				
			else
				SDL_BlitSurface(minus_blue, NULL, background, &minus_rect);

		 }
		 else
			SDL_BlitSurface(minus, NULL, background, &minus_rect);
		 if (x > (width/2.2 + 110) &&
			 x < (width/2.2 + 150) &&
			 y > 248 && y < 248 + 34){
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				SDL_BlitSurface(plus_purple, NULL, background, &plus_rect);
				increase_speed();
			}
				
			else
				SDL_BlitSurface(plus_blue, NULL, background, &plus_rect);

		 }
		 else
			SDL_BlitSurface(plus, NULL, background, &plus_rect);

		 if (x > (width/2.2) &&
			 x < (width/2.2 + 76) &&
			 y > 350 && y < 350 + 20){
			 if (e.type == SDL_MOUSEBUTTONDOWN)
				 running = 0;
			 else
				 SDL_BlitSurface(back, NULL, background, &back_rect);
		 }


		int number_bars = 11 - (initial_speed/20);
		int i, pos;
		SDL_Rect temp;
		temp = bar_rect;
		for (i = 0; i < number_bars; i++)
		{
			temp.x = temp.x + 8;
			SDL_BlitSurface(bar, NULL, background, &temp);
		}
		
		SDL_UpdateWindowSurface(window);
		SDL_Delay(100);
	}



    // Free time!
    // Destroy surfaces
    SDL_FreeSurface(title);
    SDL_FreeSurface(speed);
    SDL_FreeSurface(back);

    SDL_FreeSurface(bar);
    SDL_FreeSurface(plus);
    SDL_FreeSurface(plus_blue);
    SDL_FreeSurface(plus_purple);
    SDL_FreeSurface(minus);
    SDL_FreeSurface(minus_blue);
    SDL_FreeSurface(minus_purple);

    // Then window
    return 0;
}
