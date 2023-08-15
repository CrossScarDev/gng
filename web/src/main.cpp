#include <emscripten.h>
#include "../../src/main.hpp"

void web_update() {
    update();
    if (quit) {
        emscripten_cancel_main_loop();
        quit_sdl();
    }
}

int main(int argc, char* args[]) {
    init();
    emscripten_set_main_loop(web_update, 0, 1);

    return 0;
}