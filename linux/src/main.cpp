#include <SDL2/SDL.h>
#include "../../src/main.hpp"

int main(void) {
    init();

    unsigned int a = SDL_GetTicks();
    unsigned int b = SDL_GetTicks();
    while (!quit) {
        a = SDL_GetTicks();
        delta = a - b;

        if (delta > 1000 / MAX_FPS) {
            fps = 1000 / delta;
            b = a;
            
            update();
        }
    }

    quit_sdl();
    return 0;
}