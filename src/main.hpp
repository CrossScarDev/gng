#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string>

#include "sdl2-funcs.h"
#include "utils.h"

#include "gameobjects/box.hpp"
#include "gameobjects/gameobject.hpp"
#include "gameobjects/player.hpp"

#include "gameobjects/tiles/base/events.hpp"
#include "levels.hpp"

#include "../assets/background.h"
#include "../assets/logo.h"
#include "../assets/toon-around.h"
#ifdef __MOBILE__
#include "../assets/dpad.h"
#include "../assets/drag.h"
#include <stdio.h>
#endif

const int SCREEN_WIDTH = 854;
const int SCREEN_HEIGHT = 480;
const float TILE_SIZE = SCREEN_HEIGHT / 15;
const int SCREEN_START_X = (SCREEN_WIDTH - SCREEN_HEIGHT) / 2;
const int SCREEN_END_X = SCREEN_WIDTH - SCREEN_START_X;

const int MARGIN = 8;

SDL_Window* window;
SDL_Surface* screenSurface;
SDL_Renderer* renderer;

const float MAX_FPS = 60.0f;
float fps = 0;
double delta = 0;
bool debug_shown = true;

SDL_Texture* background;
#ifdef __MOBILE__
SDL_Texture* dpad;
SDL_Texture* drag;
#endif
TTF_Font* font = NULL;

SDL_GameController* controller;

Player player;
Box box;

// to fix conveyer including itself
void setPlayerVel(Vector2 vel) { player.vel = vel; }

// to fix conveyer including itself
void setBoxVel(Vector2 vel) { box.pos += vel; }

// to fix conveyer including itself
SDL_Rect getPlayRect() { return player.toRect(); }

// to fix conveyer including itself
SDL_Rect getBoxRect() { return box.toRect(); }

// to fix conveyer including itself
Vector2 getPlayerVel() { return player.vel; }

// to fix conveyer including itself
Vector2 getBoxVel() { return box.pos - box.oldPos; }

// to fix conveyer including itself
void setPlayerPos(Vector2 pos) { player.pos = pos; }

Tile* getRelativeTile(Tile* tile, Vector2 offset) {
  return currentLevel->tileGrid
      ->tiles[(tile->pos.y + offset.y) * 15 + tile->pos.x + offset.x];
}

bool conveyorMovedPlayer = false;

#ifdef __MOBILE__
SDL_TouchID touchId = NULL;
std::array<Vector2, 6> touchPositions;

const SDL_Rect drag_rect = {
    MARGIN,                                    // X
    (int)(SCREEN_HEIGHT - 77.5 - DPAD_OFFSET), // Y
    80,                                        // Width
    80                                         // Height
};

const SDL_Rect dpad_rect = {
    SCREEN_END_X + MARGIN,        // X
    SCREEN_HEIGHT - 160 - MARGIN, // Y
    160,                          // Width
    160                           // Height
};

const int DPAD_OFFSET = 54;
#endif

void reset() {
  player.pos = currentLevel->playerPos;
  player.vel = {0.0f, 0.0f};
  player.size = {TILE_SIZE, TILE_SIZE};
  player.speed = 0.176470588235f;

  box.pos = currentLevel->boxPos;
  box.size = {TILE_SIZE, TILE_SIZE};
}

void draw() {
  SDL_Rect bgRect = {
      SCREEN_START_X,                // x
      0,                             // y
      SCREEN_END_X - SCREEN_START_X, // width
      SCREEN_HEIGHT                  // height
  };

  SDL_SetRenderDrawColor(renderer, 0x000000);
  SDL_RenderClear(renderer);

  SDL_RenderCopy(renderer, background, NULL, &bgRect);

  currentLevel->tileGrid->draw();

  player.draw();
  box.draw();

  if (debug_shown) {
    SDL_Surface* FPStext = TTF_RenderText_Solid(
        font, ("FPS: " + std::to_string((int)fps)).c_str(), hexColor(0xffffff));
    SDL_Texture* FPStextTexture =
        SDL_CreateTextureFromSurface(renderer, FPStext);
    SDL_Rect FPStextRect = {
        8,          // x
        0,          // y
        FPStext->w, // width
        FPStext->h  // height
    };
    SDL_RenderCopy(renderer, FPStextTexture, NULL, &FPStextRect);
    SDL_DestroyTexture(FPStextTexture);
    SDL_FreeSurface(FPStext);

    SDL_Surface* levelText = TTF_RenderText_Solid(font, ("Level: " + std::to_string(currentLevelIndex + 1)).c_str(), hexColor(0xffffff));
    SDL_Texture* levelTextTexture = SDL_CreateTextureFromSurface(renderer, levelText);
    SDL_Rect levelTextRect = {
        SCREEN_WIDTH - levelText->w - 8, // x
        0,                               // y
        levelText->w,                    // width
        levelText->h                     // height
    };
    SDL_RenderCopy(renderer, levelTextTexture, NULL, &levelTextRect);
    SDL_DestroyTexture(levelTextTexture);
    SDL_FreeSurface(levelText);
  }

#ifdef __MOBILE__
  SDL_RenderCopy(renderer, dpad, NULL, &dpad_rect);
  SDL_RenderCopy(renderer, drag, NULL, &drag_rect);
#endif

  SDL_RenderPresent(renderer);
}

void handleTileEvents() {
  for (auto& tile : currentLevel->tileGrid->tiles) {
    SDL_Rect tmpRect = tile->toRect();
    SDL_Rect tmpBoxRect = box.toRect();
    SDL_Rect tmpPlayerRect = player.toRect();

    if (SDL_HasIntersection(&tmpRect, &tmpBoxRect)) tile->onEvent({GAMEOBJECT_TILE_EVENT_BOXOVER, &box});
    if (SDL_HasIntersection(&tmpRect, &tmpPlayerRect)) tile->onEvent({GAMEOBJECT_TILE_EVENT_PLAYEROVER, &player});
  }
}

bool quit = false;
SDL_Event e;
void update() {
  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_QUIT) quit = true;
    if (e.type == SDL_KEYUP) {
      switch (e.key.keysym.sym) {
      case SDLK_F3:
        debug_shown = !debug_shown;
        break;
      case SDLK_r:
        reset();
        break;
      }
    }
    if (e.type == SDL_CONTROLLERDEVICEADDED) controller = SDL_GameControllerOpen(0);
    if (e.type == SDL_CONTROLLERBUTTONDOWN && e.cdevice.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(controller)) && e.cbutton.button == SDL_CONTROLLER_BUTTON_BACK) debug_shown = !debug_shown;
  }

  const Uint8* keystates = SDL_GetKeyboardState(NULL);
  if (keystates[SDL_SCANCODE_LCTRL] && keystates[SDL_SCANCODE_Q]) quit = true;

#ifdef __MOBILE__
  if (touchId == NULL) touchId = SDL_GetTouchDevice(0);

  touchPositions.fill({0, 0});

  for (int i = 0; i < SDL_GetNumTouchFingers(touchId); i++) {
    const SDL_Finger* finger = SDL_GetTouchFinger(touchId, i);
    touchPositions[i] = {finger->x * SCREEN_WIDTH, finger->y * SCREEN_HEIGHT};
  }
#endif

  conveyorMovedPlayer = false;
  handleTileEvents();
  currentLevel->tileGrid->update();
  player.update();
  box.update();

  player.vel = {0, 0};

  draw();
}

void init() {
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER);
  IMG_Init(IMG_INIT_PNG);
  TTF_Init();

  window = SDL_CreateWindow("Grab'n'Go!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  background = loadTexture(___assets_background_png, ___assets_background_png_len);
#ifdef __MOBILE__
  dpad = loadTexture(___assets_dpad_png, ___assets_dpad_png_len);
  drag = loadTexture(___assets_drag_png, ___assets_drag_png_len);
#endif

  SDL_RWops* fontRWops = SDL_RWFromMem(___assets_toon_around_ttf, ___assets_toon_around_ttf_len);
  font = TTF_OpenFontRW(fontRWops, 1, 32);

#ifndef __WIIU__
  SDL_RWops* iconRWops = SDL_RWFromMem(___assets_logo_png, ___assets_logo_png_len);
  SDL_Surface* icon = IMG_Load_RW(iconRWops, 1);
  SDL_SetWindowIcon(window, icon);
#endif

  if (SDL_NumJoysticks() > 0) controller = SDL_GameControllerOpen(0);

  reset();
}

void quit_sdl() {
  SDL_DestroyTexture(background);
#ifdef __MOBILE__
  SDL_DestroyTexture(dpad);
  SDL_DestroyTexture(drag);
#endif
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_GameControllerClose(controller);
  IMG_Quit();
  TTF_Quit();
  SDL_Quit();
}
