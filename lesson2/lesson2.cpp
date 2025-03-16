#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include <stdio.h>

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;
const int SCREEN_WIDTH{960}, SCREEN_HEIGHT{640};

bool init()
{

    printf( "INITIALISING" );
    //Initialization flag
	bool success = true;

    //Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
        //Create window
		gWindow = SDL_CreateWindow(
			"SDL Learning (fuckit_we_ball)",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN
		);
		if (gWindow==NULL)
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
            //Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}

	return success;
}

bool loadMedia(const char* sourceImage)
{
    //Loading success flag
	bool success = true;

    //Load splash image
	gHelloWorld = SDL_LoadBMP(sourceImage);
	if( gHelloWorld == NULL)
	{
        printf( "Unable to load image %s! SDL Error: %s\n", sourceImage, SDL_GetError() );
		success = false;
	}

	return success;
}

void close()
{
    printf( "CLOSING" );
    //Deallocate surface
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;

    //Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

    //Quit SDL subsystems
	SDL_Quit();
}

int main(int argc, char* args[])
{
	const char* str_input;
	printf( "SDL2 Lesson \"Event Driven Programming\"" );

    //Start up SDL and create window
	if (!init())
	{
        printf( "Failed to initialize!\n" );
	}
	else
	{
        //Load media
		str_input = "Surina-MkII16.bmp";
		if (!loadMedia(str_input))
		{
            printf( "Failed to load media!\n" );
		}
		else
		{
            //Apply the image
			SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );
		}
	}

	// Main loop flag
	bool quit = false;
	// Event handler
	SDL_Event e;

    //Update the surface
	SDL_UpdateWindowSurface( gWindow );

	//While application is running
	while( !quit )
	{
		while( SDL_PollEvent( &e ) )
		{
			if( e.type == SDL_QUIT ) quit = true;
		}
	}

    //Load media
	str_input = "Shuka.bmp";
	if (!loadMedia( "Shuka.bmp" ))
	{
        printf( "Failed to load media!\n" );
	}
	else
	{
        //Apply the image
		SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );
	}
	//Apply the image
	SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );
	//Update the surface
	SDL_UpdateWindowSurface( gWindow );

	/*
	Shows an image after the window CLOSE event is catched
	for 1.5 seconds
	then closes

	it's cringe I know
	*/
	SDL_Delay(1500);

    //Free resources and close SDL
	close();

	return 0;
}