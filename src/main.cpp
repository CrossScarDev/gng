#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
/* #include <SDL2/SDL_ttf.h> */

#include <iostream>
/* #include <string.h> */

#include "utils.h"
#include "screen.h"
#include "gameobjects/gameobject.hpp"
#include "gameobjects/player.hpp"
#include "gameobjects/box.hpp"

const float MAX_FPS = 60.0f;

SDL_Surface* background;

Player player(
    (Vector2){ SCREEN_START_X + TILE_SIZE, TILE_SIZE }, // Position
    (Vector2){ 0.0f, 0.0f }, // Velocity
    3.0f, // Speed
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
    
    SDL_BlitScaled(background, NULL, screenSurface, &bgRect);

    player.draw();
    box.draw();

    SDL_UpdateWindowSurface(window);
}

int main(void) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    IMG_Init(IMG_INIT_PNG);
    /* TTF_Init(); */
    window = SDL_CreateWindow("Grab'n'Go", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    screenSurface = SDL_GetWindowSurface(window);
    renderer = SDL_GetRenderer(window);

    background = SDL_LoadBMP("././assets/background.bmp");

    /* TTF_Font* font = TTF_OpenFont("assets/OpenSans-SemiBold.ttf", 24); */

    SDL_Surface* icon = SDL_LoadBMP("././assets/logo.bmp");
    SDL_SetWindowIcon(window, icon);

    bool quit = false;
    SDL_Event e;

    unsigned int a = SDL_GetTicks();
    unsigned int b = SDL_GetTicks();
    double delta = 0;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) quit = true;
        }

        a = SDL_GetTicks();
        delta += a - b;

        if (delta > 1000 / MAX_FPS) {
            // std::cout << "FPS: " << 1000 / delta << std::endl;

            player.update();
            box.update();

            draw();

/*             SDL_Surface* FPStext = TTF_RenderText_Solid(font, ("FPS: " + std::to_string(1000 / delta)).c_str(), (SDL_Color){ 0xff, 0xff, 0xff });
            SDL_Texture* FPStextTexture = SDL_CreateTextureFromSurface(renderer, FPStext);
            SDL_Rect FPStextRect = (SDL_Rect){
                0, // x
                0, // y
                FPStext->w, // width
                FPStext->h // height
            };
            SDL_RenderCopy(renderer, FPStextTexture, NULL, &FPStextRect);
            SDL_DestroyTexture(FPStextTexture);
            SDL_FreeSurface(FPStext); */

            delta = 0;
        }

        b = SDL_GetTicks();
    }

    SDL_FreeSurface(background);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
