#include"../lesson3/sdl_base_lesson3.cpp"

int main(int argc, char* args[])
{
	printf("SDL2 Lesson \"Key Presses\"\n");

    //Start up SDL and create window
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
		else
		{
            //Apply the image
			SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, NULL );
		}
	}

	// Main loop flag
	bool quit = false;
	// Event handler
	SDL_Event event;

    //Set default current surface
	gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];

	//While application is running
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
					// ESCAPE -> close
					case SDLK_ESCAPE:
						quit = true;
						break;
					
					// ARROW UP -> shuka up
					case SDLK_UP:
						gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
						break;
					
					// ARROW DOWN -> shuka down
					case SDLK_DOWN:
						gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
						break;
					
					// ARROW LEFT -> shuka left
					case SDLK_LEFT:
						gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
						break;
					
					// ARROW RIGHT -> shuka right
					case SDLK_RIGHT:
						gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
						break;
					
					// OTHER KEYS -> surina boat
					default:
						gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
						break;
				}
			}
		}
		
		SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, NULL );
	
		//Update the surface
		SDL_UpdateWindowSurface( gWindow );
	}
	
    //Free resources and close SDL
	close();

	return 0;
}