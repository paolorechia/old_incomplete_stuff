#include "settings_menu.c"
#include "core_snake.c"

int big_interaction(SDL_Event e, 
                    int running,
                    SDL_Surface ** surface_array,
                    SDL_Rect * rect_array,
                    SDL_Color * colors, 
                    TTF_Font ** font_array,
                    SDL_Window * window)
{
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
        // fill background
    	SDL_FillRect( surface_array[0], NULL, 
                SDL_MapRGB(surface_array[0]->format,
               0xFF, 0xFF, 0xFF));

        // blit title
        SDL_BlitSurface(surface_array[1], NULL, surface_array[0], &rect_array[1]);

		 if (x > (width/2.2) &&
			 x < (width/2.2 + 50 ) &&
		     y > 200 && y < 200 + 34){
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
               run_core(window);
			}
			else
                // color[2] play button
				SDL_BlitSurface(surface_array[5],   
                                 NULL, surface_array[0], 
                                &rect_array[2]);
        }
        else
                // color[1] play button
				SDL_BlitSurface(surface_array[2], 
                                NULL, surface_array[0], 
                                &rect_array[2]);
            

		 if (x > (width/2.2) &&
			 x < (width/2.2 + 100) &&
			 y > 248 && y < 248 + 34){
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
                run_settings(window);
			}
				
			else
                // color[2] settings
				SDL_BlitSurface(surface_array[6], NULL, surface_array[0], &rect_array[3]);

		 }
		 else
                // color[1] settings
			SDL_BlitSurface(surface_array[3], NULL, surface_array[0], &rect_array[3]);

		 if (x > (width/2.2) &&
			 x < (width/2.2 + 50) &&
			 y > 300 && y < 300 + 20){
			 if (e.type == SDL_MOUSEBUTTONDOWN)
				 running = 0;
			 else
                //color[2] exit
				 SDL_BlitSurface(surface_array[7], NULL, surface_array[0], &rect_array[4]);
		 }
                //color[1] exit
         else    SDL_BlitSurface(surface_array[4], NULL, surface_array[0], &rect_array[4]);

		SDL_UpdateWindowSurface(window);
		SDL_Delay(10);
    return running;
}

int main(){
    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("\nUnable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    // setup basic colors
    SDL_Color color[3]={{255,255,255},{0,0,0}, {0,0,205}};

/*
    color[0]{255,255,255};          // white
    color[1]={0,0,0};               // black
    color[2]={0,0,205};             // blue
    */

    // create a graphical window.
    SDL_Window * window;
    window = SDL_CreateWindow(
        "Settings",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_OPENGL);
    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface * surface_array[20];
    surface_array[0] = SDL_GetWindowSurface( window);
    SDL_FillRect( surface_array[0], NULL, 
                SDL_MapRGB(surface_array[0]->format,
                0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(window);

    // initialize font extension
    if (TTF_Init()==-1){
        printf("TTF_Init: %s\n", TTF_GetError());
        return 1;
    }

    TTF_Font * font_array[2];

    // open font files
    font_array[0] = TTF_OpenFont("font/VeraBd.ttf", 16);
    if (!font_array[0]){
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        return 1;
    }

    font_array[1] = TTF_OpenFont("font/VeraBd.ttf", 76); 
    if (!font_array[1]){
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        return 1;
    }
    
    // render texts
    if (!(surface_array[1]=TTF_RenderText_Solid(font_array[1], "5N4K3", color[1]))) 
    {
        printf("Cannot render text! Error: %s\n", TTF_GetError());
        return 1;
    }

    if (!(surface_array[2]=TTF_RenderText_Solid(font_array[0], "PLAY", color[1]))) 
    {
        printf("Cannot render text! Error: %s\n", TTF_GetError());
        return 1;
    }

    if (!(surface_array[3]=TTF_RenderText_Solid(font_array[0], "SETTINGS", color[1]))) 
    {
        printf("Cannot render text! Error: %s\n", TTF_GetError());
        return 1;
    }

    if (!(surface_array[4]=TTF_RenderText_Solid(font_array[0], "EXIT", color[1]))) 
    {
        printf("Cannot render text! Error: %s\n", TTF_GetError());
        return 1;
    }

    if (!(surface_array[5]=TTF_RenderText_Solid(font_array[0], "PLAY", color[2]))) 
    {
        printf("Cannot render text! Error: %s\n", TTF_GetError());
        return 1;
    }

    if (!(surface_array[6]=TTF_RenderText_Solid(font_array[0], "SETTINGS", color[2]))) 
    {
        printf("Cannot render text! Error: %s\n", TTF_GetError());
        return 1;
    }

    if (!(surface_array[7]=TTF_RenderText_Solid(font_array[0], "EXIT", color[2]))) 
    {
        printf("Cannot render text! Error: %s\n", TTF_GetError());
        return 1;
    }
    // assign rectangles to text surfaces
    SDL_Rect rect_array[10];

    // title rect
    rect_array[1].x=width/4;
    rect_array[1].y=20;

   // play button
    rect_array[2].x=width/2.2;
    rect_array[2].y=200;

    // settings
    rect_array[3].x=width/2.2;
    rect_array[3].y=250;
    
    // exit
    rect_array[4].x=width/2.2;
    rect_array[4].y=300;
    

    // prep big loop
	SDL_Event e;
	int running = 1;

	while (running == 1){
        running = big_interaction(e, 
                    running,
                    surface_array,
                    rect_array,
                    color, 
                    font_array,
                    window);
    }

    // Free time!
    // Destroy surfaces
    int i;
    for (i=0; i<7; i++){
        SDL_FreeSurface(surface_array[i]);
    }

    // Then window
    SDL_DestroyWindow(window);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}
