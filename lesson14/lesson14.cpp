#include"../lesson14/sdl_base_lesson14.cpp"

int main(int argc, char* args[])
{
    printf( "LAUNCHING LESSON 14\n" );
	printf( "SDL2 Lesson \"Rotation and Flipping\"\n" );
	
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
		
		double angle = 0;
		bool go_rotate = false;

		//Flip type
		SDL_RendererFlip flipType = SDL_FLIP_NONE;
		double rotation = 0;

		//RGB components
		Uint8 col_r = 255;
		Uint8 col_g = 255;
		Uint8 col_b = 255;

		//Alpha component
		Uint8 col_a = 255;

		int sprite_w = 20;
		int sprite_h = 20;
		SDL_Rect sprite_rect;

		int frame = 0;

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
							rotation = 0;
                            flipType = SDL_FLIP_NONE;
							break;
						
						case SDLK_DOWN:
							y_pos += 1 * SPEED_MULTIPLIER;
							gCurrentTexture = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
							rotation = 180;
                            flipType = SDL_FLIP_NONE;
							break;
						
						case SDLK_LEFT:
							x_pos -= 1 * SPEED_MULTIPLIER;
							gCurrentTexture = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
							rotation = 90;
							flipType = SDL_FLIP_VERTICAL;
							break;
						
						case SDLK_RIGHT:
							x_pos += 1 * SPEED_MULTIPLIER;
							gCurrentTexture = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
							rotation = 90;
                            flipType = SDL_FLIP_NONE;
							break;
						
						case SDLK_1:
							col_r += ( col_r + COL_MULTIPLIER > 255 ? 0 : COL_MULTIPLIER );
							break;
						
						case SDLK_2:
							col_g += ( col_g + COL_MULTIPLIER > 255 ? 0 : COL_MULTIPLIER );
							break;
						
						case SDLK_3:
							col_b += ( col_b + COL_MULTIPLIER > 255 ? 0 : COL_MULTIPLIER );
							break;
						
						case SDLK_q:
							col_r -= ( col_r - COL_MULTIPLIER < 0 ? 0 : COL_MULTIPLIER );
							break;
						
						case SDLK_w:
							col_g -= ( col_g - COL_MULTIPLIER < 0 ? 0 : COL_MULTIPLIER );
							break;
						
						case SDLK_e:
							col_b -= ( col_b - COL_MULTIPLIER < 0 ? 0 : COL_MULTIPLIER );
							break;
						
						case SDLK_x:
							col_a += ( col_a + COL_MULTIPLIER > 255 ? 0 : COL_MULTIPLIER );
							break;
						
						case SDLK_z:
							col_a -= ( col_a - COL_MULTIPLIER < 0 ? 0 : COL_MULTIPLIER );
							break;
						
						case SDLK_r:
							go_rotate = true;
							break;
						
						default:
							gCurrentTexture = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
							break;
					}
				}
			}
			
			// new frame each window frame
			frame += 1;

			if (go_rotate)
			{
				angle += 2;
				if (angle > 361)
				{
					angle = 0;
					go_rotate = false;
				}
			}

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
			gCurrentTexture.resize( SCREEN_HEIGHT / 8, SCREEN_WIDTH / 8 );
			gCurrentTexture.renderCenter( x_pos, y_pos, NULL, rotation + angle, NULL, flipType );

            //Render top left sprite
            sprite_rect = spriteSheetTexture.spriteSelect( sprite_w, sprite_h, ((frame / 4) + 0) % 4 );
			spriteSheetTexture.render( 0, 0, &sprite_rect );

            //Render top right sprite
            sprite_rect = spriteSheetTexture.spriteSelect( sprite_w, sprite_h, ((frame / 4) + 1) % 4 );
			spriteSheetTexture.render( SCREEN_WIDTH - sprite_w, 0, &sprite_rect );

            //Render bottom left sprite
            sprite_rect = spriteSheetTexture.spriteSelect( sprite_w, sprite_h, ((frame / 4) + 2) % 4 );
			spriteSheetTexture.render( 0, SCREEN_HEIGHT - sprite_h, &sprite_rect );

            //Render bottom right sprite
            sprite_rect = spriteSheetTexture.spriteSelect( sprite_w, sprite_h, ((frame / 4) + 3) % 4 );
			spriteSheetTexture.render( SCREEN_WIDTH - sprite_w, SCREEN_HEIGHT - sprite_h, &sprite_rect );
			
			// Render red square
			SDL_Rect fillRect = getRectCenter(
				x_pos - (x_pos - SCREEN_WIDTH / 2) / 2,
				y_pos - (y_pos - SCREEN_HEIGHT / 2) / 2,
				SCREEN_WIDTH / 2,
				SCREEN_HEIGHT / 2);
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
			SDL_RenderDrawLine( gRenderer, 0, y_pos, SCREEN_WIDTH, y_pos );

			//Draw vertical line of yellow dots
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF );
			for( int i = 0; i < SCREEN_HEIGHT; i += 4 )
			{
				SDL_RenderDrawPoint( gRenderer, x_pos, i );
			}

			//Update screen
			SDL_RenderPresent( gRenderer );
		}
	}
	
    //Free resources and close SDL
	close();

	return 0;
}