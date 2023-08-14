#include <SDL2/SDL.h>

#ifndef COLLISIONS_HEADER_DEFINED
#define COLLISIONS_HEADER_DEFINED

int onSide(SDL_Rect rect1, SDL_Rect rect2) {
    SDL_Rect tmpRect = (SDL_Rect){ rect1.x, rect1.y + 3, rect1.w, rect1.h };
    if (SDL_HasIntersection(&tmpRect, &rect2)) return 0;
    tmpRect = (SDL_Rect){ rect1.x, rect1.y - 3, rect1.w, rect1.h };
    if (SDL_HasIntersection(&tmpRect, &rect2)) return 1;
    tmpRect = (SDL_Rect){ rect1.x - 3, rect1.y, rect1.w, rect1.h };
    if (SDL_HasIntersection(&tmpRect, &rect2)) return 2;
    tmpRect = (SDL_Rect){ rect1.x + 3, rect1.y, rect1.w, rect1.h };
    if (SDL_HasIntersection(&tmpRect, &rect2)) return 3;

    return -1;
}
#endif