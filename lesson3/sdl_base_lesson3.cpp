#include"sdl_base_lesson3.h"

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//Current displayed image
SDL_Surface* gCurrentSurface = NULL;

//Key press surfaces constants
enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

//The images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

//Starts up SDL and creates window
bool init()
{
    printf( "INITIALISING...\t" );
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

    printf( "SUCCESSFUL!\n" );
	return success;
}

//Frees media and shuts down SDL
void close()
{
    printf( "CLOSING...\t" );
    //Deallocate surface
	SDL_FreeSurface(gCurrentSurface);
	gCurrentSurface = NULL;

    //Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

    printf( "SUCCESSFUL COMPLETE.. wait. why do you see this\\n" );
	SDL_Delay(100);		// haha.. funny. DELETE LATER
						// SERIOUSLY
						// YOU MUST
						// Why else do you think
						// I would spend SO MANY
						// lines of code
						// SPECIFICALLY FOR THIS?!?!?!
    //Quit SDL subsystems
	SDL_Quit();
}

//Loads individual image
SDL_Surface* loadSurface(const char* path)
{
    printf( "LOADING IMAGE: %s...\t", path );
    //Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path);
	if (loadedSurface == NULL)
	{
		printf( "Unable to load image %s! SDL Error: %s\n", path, SDL_GetError() );
	}

    printf( "SUCCESSFUL!\n" );
	return loadedSurface;
}

bool loadMedia()
{
    printf( "LOADING MEDIA:\n" );

    //Loading success flag
	bool success = true;

    //Load default surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface( "img/Surina-MkII16.bmp" );
    if (gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] == NULL)
    {
        printf( "Failed to load default image!\n" );
        success = false;
    }

    //Load up surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadSurface( "img/ShukaUp.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] == NULL )
    {
        printf( "Failed to load up image!\n" );
        success = false;
    }

    //Load down surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadSurface( "img/ShukaDown.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] == NULL )
    {
        printf( "Failed to load down image!\n" );
        success = false;
    }

    //Load left surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadSurface( "img/ShukaLeft.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] == NULL )
    {
        printf( "Failed to load left image!\n" );
        success = false;
    }

    //Load right surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = loadSurface( "img/ShukaRight.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] == NULL )
    {
        printf( "Failed to load right image!\n" );
        success = false;
    }

    printf( "LOADING MEDIA IS SUCCESSFUL!\n" );
    return success;
}