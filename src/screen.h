#include <SDL2/SDL.h>

#ifndef SCREEN_HEADER_DEFINED
#define SCREEN_HEADER_DEFINED
const int SCREEN_WIDTH = 854;
const int SCREEN_HEIGHT = 480;
const float TILE_SIZE = SCREEN_HEIGHT / 15;
const int SCREEN_START_X = (SCREEN_WIDTH - SCREEN_HEIGHT) / 2;
const int SCREEN_END_X = SCREEN_WIDTH - SCREEN_START_X;

SDL_Window* window;
SDL_Surface* screenSurface;
SDL_Renderer* renderer;
#endif