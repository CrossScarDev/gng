#include <emscripten.h>
#include <SDL2/SDL.h>
#include "../../src/main.hpp"

unsigned int a = SDL_GetTicks();
unsigned int b = SDL_GetTicks();
double delta = 0;

void web_update() {
    a = SDL_GetTicks();
    delta = a - b;

    if (delta > 1000 / MAX_FPS) {
        fps = 1000 / delta;
        b = a;

        update();

        if (quit) {
            emscripten_cancel_main_loop();
            quit_sdl();
        }
    }
}

int main(int argc, char* args[]) {
    init();
    emscripten_set_main_loop(web_update, 0, 1);

    return 0;
}