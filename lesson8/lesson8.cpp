#include"../lesson8/sdl_base_lesson8.cpp"

int main(int argc, char* args[])
{
    printf( "LAUNCHING LESSON 8\n" );
	printf( "SDL2 Lesson \"The Viewport\"\n" );
	
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
			// this SDL_SetRenderDrawColor needed to reset the color from previous loop (to white)
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear( gRenderer );

			// Top left corner viewport
			SDL_Rect fullscreenViewport = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
			SDL_Rect topLeftViewport = { 0, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
			SDL_Rect topRightViewport = { SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
			SDL_Rect bottomViewport = { 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 };
			

			//Render texture to screen
			SDL_RenderSetViewport( gRenderer, &topLeftViewport ); 
			SDL_RenderCopy( gRenderer, gCurrentTexture, NULL, NULL );

			SDL_RenderSetViewport( gRenderer, &topRightViewport ); 
			SDL_RenderCopy( gRenderer, gCurrentTexture, NULL, NULL );

			SDL_RenderSetViewport( gRenderer, &bottomViewport ); 
			SDL_RenderCopy( gRenderer, gCurrentTexture, NULL, NULL );

			SDL_RenderSetViewport( gRenderer, &fullscreenViewport );

			// Render red square
			SDL_Rect fillRect = {
				SCREEN_WIDTH / 4,
				SCREEN_HEIGHT / 4,
				SCREEN_WIDTH / 2,
				SCREEN_HEIGHT / 2
			};
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderFillRect( gRenderer, &fillRect );

			// Render green outline
			SDL_Rect outlineRect = {
				SCREEN_WIDTH / 6,
				SCREEN_HEIGHT / 6,
				SCREEN_WIDTH * 2 / 3,
				SCREEN_HEIGHT * 2 / 3
			};
			SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF);
			SDL_RenderDrawRect( gRenderer, &outlineRect );

			// Draw blue horizontal line
			SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );
			SDL_RenderDrawLine( gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 );

			//Draw vertical line of yellow dots
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF );
			for( int i = 0; i < SCREEN_HEIGHT; i += 4 )
			{
				SDL_RenderDrawPoint( gRenderer, SCREEN_WIDTH / 2, i );
			}

			//Update screen
			SDL_RenderPresent( gRenderer );
		}
	}
	
    //Free resources and close SDL
	close();

	return 0;
}