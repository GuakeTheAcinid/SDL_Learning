#include"../lesson6/sdl_base_lesson6.cpp"

int main(int argc, char* args[])
{
    printf( "LAUNCHING LESSON 6\n" );
	printf( "SDL2 Lesson \"Texture Loading and Rendering\"\n" );
	// I forgor what it all was about
	// блять
	
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

		//Set default current texture
		gCurrentTexture = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];

		//While application is running
		while( !quit )
		{
			//Handle events on queue
			while( SDL_PollEvent( &event ) != 0 )
			{
				//User requests quit
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
							gCurrentTexture = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
							break;
						
						case SDLK_DOWN:
							gCurrentTexture = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
							break;
						
						case SDLK_LEFT:
							gCurrentTexture = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
							break;
						
						case SDLK_RIGHT:
							gCurrentTexture = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
							break;
						
						default:
							gCurrentTexture = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
							break;
					}
				}
			}

			//Clear screen
			SDL_RenderClear( gRenderer );

			//Render texture to screen
			SDL_RenderCopy( gRenderer, gCurrentTexture, NULL, NULL );

			//Update screen
			SDL_RenderPresent( gRenderer );
		}
	}
	
    //Free resources and close SDL
	close();

	return 0;
}