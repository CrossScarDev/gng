#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "screen.h"

#ifndef UTILS_HEADER_DEFINED
#define UTILS_HEADER_DEFINED
typedef struct Vector2 {
    float x;
    float y;
} Vector2;

SDL_Texture* loadTexture(const char* path) {
    SDL_Surface* loadedSurface = IMG_Load(path);
    SDL_Texture* loadedTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    return loadedTexture;
}
#endif