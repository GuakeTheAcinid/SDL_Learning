#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include <stdio.h>

SDL_Window* gWindow = NULL;
// SDL_Surface is a data type containing pixels of an image
// along with all data to render it
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

bool loadMedia()
{
    printf( "LOADING" );
    //Loading success flag
	bool success = true;

    //Load splash image
	gHelloWorld = SDL_LoadBMP( "Surina-MkII16.bmp" );
	if( gHelloWorld == NULL)
	{
        printf(
			"Unable to load image %s! SDL Error: %s\n",
			"Surina-MkII16.bmp",
			SDL_GetError()
		);
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
	printf( "SDL2 Lesson \"Getting an Image on the Screen\"" );

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
			SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );
		}
	}

    //Update the surface
	SDL_UpdateWindowSurface( gWindow );

	//Hack to get window to stay up
    SDL_Event e;
	bool quit = false;
	while( quit == false )
	{
		while( SDL_PollEvent( &e ) )
		{
			if( e.type == SDL_QUIT )
				quit = true;
		}
	}

    //Free resources and close SDL
	close();

	return 0;
}