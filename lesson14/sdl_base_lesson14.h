#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<stdio.h>

// Screen size constants
const int SCREEN_WIDTH{960}, SCREEN_HEIGHT{640};
// Shuka speed constant modifier
const int SPEED_MULTIPLIER{4};
const Uint8 COL_MULTIPLIER{32};

SDL_Rect getRectCenter(int x, int y, int w, int h);

class LTexture
{
public:
    LTexture();
    ~LTexture();

    //Loads image at specified path
    bool loadFromFile( const char* path );

    //Deallocates texture
    void free();

    //Set blending
    void sedBlendMode( SDL_BlendMode blending );

    // Set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );

    // Set Alpha
    void setAlpha( Uint8 alpha );

    //Selects a sprite by sprite size and number
    SDL_Rect spriteSelect(int sprite_w, int sprite_h, int number);

    //Renders texture at given point
    void render(
        int x, int y, SDL_Rect* clip = NULL,
        double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE
    );

    //Renders texture at given point
    void renderCenter(
        int x, int y, SDL_Rect* clip = NULL,
        double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE
    );

    //Resizes the texture
    void resize(int w, int h);

    //Gets image dimensions
    int getWidth();
    int getHeight();
private:
    //The actual hardware texture
    SDL_Texture* mTexture;

    //The actual texture path (for logging)
    const char* texture_path;

    //Image dimensions
    int width;
    int height;
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();