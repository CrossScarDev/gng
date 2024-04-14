#include "../../src/main.hpp"
#include <SDL2/SDL.h>
#include <switch.h>

int main() {
  init();

  unsigned int a;
  unsigned int b = SDL_GetTicks();
  while (appletMainLoop()) {
    a = SDL_GetTicks();
    delta = a - b;
    if (delta > 1000 / MAX_FPS) {
      fps = 1000 / delta;
      b = a;

      update();
    }
  }

  quit_sdl();
}
