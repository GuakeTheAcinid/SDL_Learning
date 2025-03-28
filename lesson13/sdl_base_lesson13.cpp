#include"sdl_base_lesson13.h"

//Loads individual image as texture
SDL_Texture* loadTexture( const char* path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
//Used to render Textures
SDL_Renderer* gRenderer = NULL;

LTexture::LTexture()
{
    // Initialize
    mTexture = NULL;
    texture_path = "NULL";
    width = 0;
    height = 0;
}

LTexture::~LTexture()
{
    // Deallocate
    free();
}

bool LTexture::loadFromFile(const char* path)
{
    printf( "texture loading from: %s ...\n", path );
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path );
    if ( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
    }
    else
    {
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0xFF, 0xFF, 0xFF ) );

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if (newTexture == NULL)
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
        }
        else
        {
            width = loadedSurface->w;
            height = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
        printf( "successful.\n" );
    }

    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

void LTexture::free()
{
    //Free texture if it exists
    if (mTexture != NULL)
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        texture_path = "NULL";
        width = 0;
        height = 0;
    }
}

void LTexture::sedBlendMode( SDL_BlendMode blending )
{
    //Set blending function
    SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    //Modulate texture
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setAlpha( Uint8 alpha )
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

SDL_Rect LTexture::spriteSelect( int sprite_w, int sprite_h, int number )
{
    int x_len = width / sprite_w;
    int y_len = height / sprite_h;

    return SDL_Rect( { sprite_w * (number % x_len), sprite_h * (number / x_len), sprite_w, sprite_h} );
}

void LTexture::render( int x, int y, SDL_Rect* clip )
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, width, height };

    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}

void LTexture::resize(int w, int h)
{
    if ( w < 0 || h < 0 )
    {
        printf( "ERROR: Texture:%s:InvalidSize:%s,%s", texture_path, w, h );
        return;
    }
    else
    {
        width = w;
        height = h;
    }
}

int LTexture::getWidth()
{
    return width;
}

int LTexture::getHeight()
{
    return height;
}

//Current displayed texture
LTexture gCurrentTexture;

//My sprite sheet from C:DDA
LTexture spriteSheetTexture;

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
LTexture gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

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
            // I'll need this one a bit later (just a reminder)
            //gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );

            //Create VSynced renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
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
    //Free loaded images
    for( LTexture texture : gKeyPressSurfaces )
    {
        texture.free();
    }
    gCurrentTexture.free();

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

bool loadMedia()
{
    printf( "LOADING MEDIA:\n" );

    //Loading success flag
	bool success = true;

    //Load default surface
    // it looks very odd due to it's outline being white
    // very cool tho
    if ( !gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ].loadFromFile( "img/Surina-MkII16.png" ) )
    {
        printf( "Failed to load default image!\n" );
        success = false;
    }

    for (int i = 1; i < sizeof(gKeyPressSurfaces) / 20 - 1; i++)
    {
        char buffer[3];
        char string[32] = {"img/Shuka"};
        strcat(string, itoa( i, buffer, 10 ));
        strcat(string, ".png");
        if( !gKeyPressSurfaces[ i ].loadFromFile( string ) )
        {
            printf( "Failed to load up image!\n" );
            success = false;
        }
        else
        {
            //Set standard alpha blending
            gKeyPressSurfaces[ i ].sedBlendMode( SDL_BLENDMODE_BLEND );
        }
    }

    //Load right surface
    if( !spriteSheetTexture.loadFromFile( "img/GuakeItemsSmall.png" ) )
    {
        printf( "Failed to load right image!\n" );
        success = false;
    }

    return success;
}