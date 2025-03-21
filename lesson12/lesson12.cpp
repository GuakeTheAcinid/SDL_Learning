#include"../lesson12/sdl_base_lesson12.cpp"

int main(int argc, char* args[])
{
    printf( "LAUNCHING LESSON 12\n" );
	printf( "SDL2 Lesson \"Alpha Blending\"\n" );
	
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

		int x_pos = SCREEN_WIDTH / 2;
		int y_pos = SCREEN_HEIGHT / 2;

		//RGB components
		Uint8 col_r = 255;
		Uint8 col_g = 255;
		Uint8 col_b = 255;

		//Alpha component
		Uint8 col_a = 255;

		int sprite_w = 20;
		int sprite_h = 20;
		SDL_Rect sprite_rect;

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
							y_pos -= 1 * SPEED_MULTIPLIER;
							gCurrentTexture = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
							break;
						
						case SDLK_DOWN:
							y_pos += 1 * SPEED_MULTIPLIER;
							gCurrentTexture = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
							break;
						
						case SDLK_LEFT:
							x_pos -= 1 * SPEED_MULTIPLIER;
							gCurrentTexture = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
							break;
						
						case SDLK_RIGHT:
							x_pos += 1 * SPEED_MULTIPLIER;
							gCurrentTexture = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
							break;
						
						case SDLK_1:
							col_r += 1 * COL_MULTIPLIER;
							break;
						
						case SDLK_2:
							col_g += 1 * COL_MULTIPLIER;
							break;
						
						case SDLK_3:
							col_b += 1 * COL_MULTIPLIER;
							break;
						
						case SDLK_q:
							col_r -= 1 * COL_MULTIPLIER;
							break;
						
						case SDLK_w:
							col_g -= 1 * COL_MULTIPLIER;
							break;
						
						case SDLK_e:
							col_b -= 1 * COL_MULTIPLIER;
							break;
						
						case SDLK_x:
							col_a += 1 * COL_MULTIPLIER;
							break;
						
						case SDLK_z:
							col_a -= 1 * COL_MULTIPLIER;
							break;
						
						default:
							gCurrentTexture = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
							break;
					}
				}
			}

			gCurrentTexture.resize( SCREEN_WIDTH / 8, SCREEN_HEIGHT / 8 );

			//Clear screen
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear( gRenderer );

            //Render background texture to screen
			gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ].setColor( col_r, col_g, col_b );
			gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ].setAlpha( 255 );
			gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ].render( 0, 0 );

			//Render texture to screen
			gCurrentTexture.setColor( col_r, col_g, col_b );
			gCurrentTexture.setAlpha( col_a );
			gCurrentTexture.render( x_pos, y_pos );

            //Render top left sprite
            sprite_rect = spriteSheetTexture.spriteSelect( sprite_w, sprite_h, 0 );
			spriteSheetTexture.render( 0, 0, &sprite_rect );

            //Render top right sprite
            sprite_rect = spriteSheetTexture.spriteSelect( sprite_w, sprite_h, 1 );
			spriteSheetTexture.render( SCREEN_WIDTH - sprite_w, 0, &sprite_rect );

            //Render bottom left sprite
            sprite_rect = spriteSheetTexture.spriteSelect( sprite_w, sprite_h, 2 );
			spriteSheetTexture.render( 0, SCREEN_HEIGHT - sprite_h, &sprite_rect );

            //Render bottom right sprite
            sprite_rect = spriteSheetTexture.spriteSelect( sprite_w, sprite_h, 3 );
			spriteSheetTexture.render( SCREEN_WIDTH - sprite_w, SCREEN_HEIGHT - sprite_h, &sprite_rect );
			
			// Render red square
			SDL_Rect fillRect = {
				SCREEN_WIDTH / 4,
				SCREEN_HEIGHT / 4,
				SCREEN_WIDTH / 2,
				SCREEN_HEIGHT / 2
			};
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF);
			//SDL_RenderFillRect( gRenderer, &fillRect );
			SDL_RenderDrawRect( gRenderer, &fillRect );

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