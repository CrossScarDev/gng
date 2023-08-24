#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

extern SDL_Renderer* renderer;

#ifndef UTILS_HEADER_DEFINED
#define UTILS_HEADER_DEFINED
typedef struct Vector2 {
    float x;
    float y;
} Vector2;

SDL_Texture* loadTexture(void* mem, int size) {
    SDL_RWops* loadedRWops = SDL_RWFromMem(mem, size);
    SDL_Surface* loadedSurface = IMG_Load_RW(loadedRWops, 1);
    SDL_Texture* loadedTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    return loadedTexture;
}

int getHexDigit(unsigned int hexNumber, int digit) {
    return (hexNumber >> (digit << 2)) & 0x0f;
}

SDL_Color hexColor(unsigned int hex) {
    SDL_Color color;
    color.r = getHexDigit(hex, 4) + getHexDigit(hex, 5) * 16;
    color.g = getHexDigit(hex, 2) + getHexDigit(hex, 3) * 16;
    color.b = getHexDigit(hex, 0) + getHexDigit(hex, 1) * 16;
    color.a = 0xff;
    return color;
}
#endif