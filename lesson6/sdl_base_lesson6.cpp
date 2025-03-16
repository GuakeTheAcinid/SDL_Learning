#include"sdl_base_lesson6.h"

//Loads individual image as texture
SDL_Texture* loadTexture( const char* path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
//Used to render Textures
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gCurrentTexture = NULL;

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
SDL_Texture* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

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
            "SDL Tutorial",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
        );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
	}

    printf( "SUCCESSFUL!\n" );
	return success;
}

//Frees media and shuts down SDL
void close()
{
    //Free loaded image
    SDL_DestroyTexture( gCurrentTexture );
    gCurrentTexture = NULL;

    //Destroy window    
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    printf( "SUCCESSFUL COMPLETE.. wait. why do you see this\\n" );
	SDL_Delay(100);		// haha.. funny. DELETE LATER
						// SERIOUSLY
						// YOU MUST
						// Why else do you think
						// I would spend SO MANY
						// lines of code
						// SPECIFICALLY FOR THIS?!?!?!

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* loadTexture( const char* path )
{
    printf( "LOADING IMAGE: %s...\t", path );

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    printf( "SUCCESSFUL!\n" );
    return newTexture;
}

bool loadMedia()
{
    printf( "LOADING MEDIA:\n" );

    //Loading success flag
	bool success = true;

    //Load default surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadTexture( "img/Surina-MkII16.png" );
    if (gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] == NULL)
    {
        printf( "Failed to load default image!\n" );
        success = false;
    }

    //Load up surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadTexture( "img/ShukaUp.png" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] == NULL )
    {
        printf( "Failed to load up image!\n" );
        success = false;
    }

    //Load down surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadTexture( "img/ShukaDown.png" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] == NULL )
    {
        printf( "Failed to load down image!\n" );
        success = false;
    }

    //Load left surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadTexture( "img/ShukaLeft.png" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] == NULL )
    {
        printf( "Failed to load left image!\n" );
        success = false;
    }

    //Load right surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = loadTexture( "img/ShukaRight.png" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] == NULL )
    {
        printf( "Failed to load right image!\n" );
        success = false;
    }

    printf( "LOADING MEDIA IS SUCCESSFUL!\n" );
    return success;
}