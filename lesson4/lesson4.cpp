#include"../lesson4/sdl_base_lesson4.cpp"

int main(int argc, char* args[])
{
    printf( "LAUNCHING LESSON 4\n" );
	printf( "SDL2 Lesson \"Optimized Surface Loading and Soft Stretching\"\n" );
	
	if (!init())
	{
        printf( "Failed to initialize!\n" );
	}
	else
	{
        //Load media
		if (!loadMedia())
		{
            printf( "Failed to load media!\n" );
		}

		// Main loop flag
		bool quit = false;
		// Event handler
		SDL_Event event;

		//Set default current surface
		gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];

		//While application is running
		printf( "Entering main loop.\n" );
		while( !quit )
		{
			while( SDL_PollEvent( &event ) != 0 )
			{
				if( event.type == SDL_QUIT )
				{
					quit = true;
				}
				else if (event.type == SDL_KEYDOWN)
				{
					switch (event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							quit = true;
							break;
							
						case SDLK_UP:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
							break;
						
						case SDLK_DOWN:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
							break;
						
						case SDLK_LEFT:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
							break;
						
						case SDLK_RIGHT:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
							break;
						
						default:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
							break;
					}
				}
			}
			
			//Apply the image stretched
			SDL_Rect stretchRect;
			stretchRect.x = 0;
			stretchRect.y = 0;
			stretchRect.w = SCREEN_WIDTH;
			stretchRect.h = SCREEN_HEIGHT;

			// Now images are stretched up to window size
			// BULK shuka is real lmao
			SDL_BlitScaled( gCurrentSurface, NULL, gScreenSurface, &stretchRect );
		
			//Update the surface
			SDL_UpdateWindowSurface( gWindow );
		}
	}
	
    //Free resources and close SDL
	close();

	return 0;
}