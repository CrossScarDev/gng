#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#ifndef __WIIU__
#include <SDL2/SDL_ttf.h>
#endif

#include <string>

#include "utils.h"
#include "gameobjects/gameobject.hpp"
#include "gameobjects/player.hpp"
#include "gameobjects/box.hpp"

#include "gameobjects/tiles/base/tileGrid.hpp"

#include "../assets/background.h"
#include "../assets/logo.h"
#include "../assets/toon-around.h"

const int SCREEN_WIDTH = 854;
const int SCREEN_HEIGHT = 480;
const float TILE_SIZE = SCREEN_HEIGHT / 15;
const int SCREEN_START_X = (SCREEN_WIDTH - SCREEN_HEIGHT) / 2;
const int SCREEN_END_X = SCREEN_WIDTH - SCREEN_START_X;

SDL_Window* window;
SDL_Surface* screenSurface;
SDL_Renderer* renderer;

const float MAX_FPS = 60.0f;
float fps = 0;
double delta = 0;
bool fps_shown = true;

SDL_Texture* background;
#ifndef __WIIU__
TTF_Font* font;
#endif

SDL_GameController* controller;

TileGrid tileGrid({
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
});

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

    tileGrid.draw();

    player.draw();
    box.draw();

    #ifndef __WIIU__
    if (fps_shown) {
        SDL_Surface* FPStext = TTF_RenderText_Solid(font, ("FPS: " + std::to_string((int)fps)).c_str(), hexColor(0xffffff));
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
        if (e.type == SDL_CONTROLLERDEVICEADDED) controller = SDL_GameControllerOpen(0);
    }

    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    if (keystates[SDL_SCANCODE_LCTRL] && keystates[SDL_SCANCODE_Q]) quit = true;

    tileGrid.update();
    player.update();
    box.update();

    draw();
}

void init() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER);
    IMG_Init(IMG_INIT_PNG);
    #ifndef __WIIU__
    TTF_Init();
    #endif

    window = SDL_CreateWindow("Grab'n'Go!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    screenSurface = SDL_GetWindowSurface(window);
    #ifdef __EMSCRIPTEN__
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    #else
    renderer = SDL_GetRenderer(window);
    #endif

    background = loadTexture(___assets_background_png, ___assets_background_png_len);

    #ifndef __WIIU__
    SDL_RWops* fontRWops = SDL_RWFromMem(___assets_toon_around_ttf, ___assets_toon_around_ttf_len);
    font = TTF_OpenFontRW(fontRWops, 1, 32);

    SDL_RWops* iconRWops = SDL_RWFromMem(___assets_logo_png, ___assets_logo_png_len);
    SDL_Surface* icon = IMG_Load_RW(iconRWops, 1);
    SDL_SetWindowIcon(window, icon);
    #endif

    if (SDL_NumJoysticks() > 0) controller = SDL_GameControllerOpen(0);
}

void quit_sdl() {
    SDL_DestroyTexture(background);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_GameControllerClose(controller);
    IMG_Quit();
    #ifndef __WIIU__
    TTF_Quit();
    #endif
    SDL_Quit();
}