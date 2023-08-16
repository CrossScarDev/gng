#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#ifndef __WIIU__
#include <SDL2/SDL_ttf.h>
#endif

/* #include <iostream> */
#include <string>

#include "utils.h"
#include "screen.h"
#include "gameobjects/gameobject.hpp"
#include "gameobjects/player.hpp"
#include "gameobjects/box.hpp"

const float MAX_FPS = 60.0f;
float fps = 0;
double delta = 0;
bool fps_shown = true;

SDL_Texture* background;
#ifndef __WIIU__
TTF_Font* font;
#endif

SDL_Joystick* joy;

Player player(
    (Vector2){ SCREEN_START_X + TILE_SIZE, TILE_SIZE }, // Position
    (Vector2){ 0.0f, 0.0f }, // Velocity
    0.176470588235f, // Speed
    TILE_SIZE // Size
);

Box box((Vector2){
    SCREEN_END_X - TILE_SIZE * 2, // x
    SCREEN_HEIGHT - TILE_SIZE * 2 // y
}, TILE_SIZE);

void draw() {
    SDL_Rect bgRect = {
        SCREEN_START_X, // x
        0, // y
        SCREEN_END_X - SCREEN_START_X, // width
        SCREEN_HEIGHT // height
    };
    
    SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xff);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, background, NULL, &bgRect);

    player.draw();
    box.draw();

    #ifndef __WIIU__
    if (fps_shown) {
        SDL_Surface* FPStext = TTF_RenderText_Solid(font, ("FPS: " + std::to_string((int)fps)).c_str(), (SDL_Color){ 0xff, 0xff, 0xff });
        SDL_Texture* FPStextTexture = SDL_CreateTextureFromSurface(renderer, FPStext);
        SDL_Rect FPStextRect = {
            8, // x
            0, // y
            FPStext->w, // width
            FPStext->h // height
        };
        SDL_RenderCopy(renderer, FPStextTexture, NULL, &FPStextRect);
        SDL_DestroyTexture(FPStextTexture);
        SDL_FreeSurface(FPStext);
    }
    #endif

    SDL_RenderPresent(renderer);
}

bool quit = false;
SDL_Event e;
void update() {
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) quit = true;
        if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_F3) fps_shown = !fps_shown;
        if (e.type == SDL_JOYDEVICEADDED) joy = SDL_JoystickOpen(0);
    }

    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    if (keystates[SDL_SCANCODE_LCTRL] && keystates[SDL_SCANCODE_Q]) quit = true;

    player.update();
    box.update();

    draw();
}

void init() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_JOYSTICK);
    IMG_Init(IMG_INIT_PNG);
    #ifndef __WIIU__
    TTF_Init();
    #endif

    window = SDL_CreateWindow("Grab'n'Go", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    screenSurface = SDL_GetWindowSurface(window);
    #ifdef __EMSCRIPTEN__
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    #else
    renderer = SDL_GetRenderer(window);
    #endif

    #ifndef __WIIU__
    background = loadTexture("../assets/background.png");
    font = TTF_OpenFont("../assets/toon-around.ttf", 32);

    SDL_Surface* icon = IMG_Load("../assets/logo.png");
    SDL_SetWindowIcon(window, icon);
    #else
    background = loadTexture("romfs:/assets/background.png");
    #endif
}

void quit_sdl() {
    SDL_DestroyTexture(background);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_JoystickClose(joy);
    IMG_Quit();
    #ifndef __WIIU__
    TTF_Quit();
    #endif
    SDL_Quit();
}

/* int main(void) {
    init();

    unsigned int a = SDL_GetTicks();
    unsigned int b = SDL_GetTicks();
    double delta = 0;
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
 */
