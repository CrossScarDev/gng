#include "../../src/main.hpp"
#include <SDL2/SDL.h>

int main(int argc, char* argv[]) {
  init(argc, argv);

  unsigned int a;
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
