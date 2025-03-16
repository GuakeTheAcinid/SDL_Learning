#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<stdio.h>

// Screen size constants
const int SCREEN_WIDTH{960}, SCREEN_HEIGHT{640};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface* loadSurface(const char* path);