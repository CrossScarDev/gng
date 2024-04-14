#include "../../utils.h"
#include "base/events.hpp"
#include "base/tile.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>

#ifndef CONVEYER_HEADER_DEFINED
#define CONVEYER_HEADER_DEFINED

extern double delta;
extern void setPlayerVel(Vector2 vel);
extern void setBoxVel(Vector2 vel);
extern SDL_Rect getPlayRect();
extern SDL_Rect getBoxRect();
extern Vector2 getPlayerVel();
extern Vector2 getBoxVel();
extern void setPlayerPos(Vector2 pos);
extern Tile* getRelativeTile(Tile* tile, Vector2 offset);
extern bool conveyorMovedPlayer;

#define CONVEYERSPEED 0.088235294f

class Conveyer : public Tile {
public:
  Conveyer() : Tile({1, 1}, {0, 0}, false, 0x333333){};
};

class ConveyerLeft : public Conveyer {
public:
  void onEvent(GameObjectTileEvent e) {
    if (e.type == GAMEOBJECT_TILE_EVENT_PLAYEROVER) {
      if (conveyorMovedPlayer) return;
      SDL_Rect newPlayerRect = getPlayRect();
      newPlayerRect.x -= CONVEYERSPEED * (float)delta + 3;

      SDL_Rect tmpRect = getRelativeTile(this, {-1, 0})->toRect();
      if (getRelativeTile(this, {-1, 0})->solid && SDL_HasIntersection(&newPlayerRect, &tmpRect)) {
        setPlayerPos({(float)tmpRect.x + (float)tmpRect.w, (float)getPlayRect().y});
        return;
      }
      tmpRect = getRelativeTile(this, {-1, -1})->toRect();
      if (getRelativeTile(this, {-1, -1})->solid && SDL_HasIntersection(&newPlayerRect, &tmpRect)) {
        setPlayerPos({(float)tmpRect.x + (float)tmpRect.w, (float)getPlayRect().y});
        return;
      }
      tmpRect = getRelativeTile(this, {-1, 1})->toRect();
      if (getRelativeTile(this, {-1, 1})->solid && SDL_HasIntersection(&newPlayerRect, &tmpRect)) {
        setPlayerPos({(float)tmpRect.x + (float)tmpRect.w, (float)getPlayRect().y});
        return;
      }
      conveyorMovedPlayer = true;
      setPlayerVel({-(CONVEYERSPEED * (float)delta), 0});
      return;
    }
  }
};

class ConveyerRight : public Conveyer {
public:
  void onEvent(GameObjectTileEvent e) {
    if (e.type == GAMEOBJECT_TILE_EVENT_PLAYEROVER) {
      if (conveyorMovedPlayer) return;
      SDL_Rect newPlayerRect = getPlayRect();
      newPlayerRect.x += CONVEYERSPEED * (float)delta + 3;

      SDL_Rect tmpRect = getRelativeTile(this, {1, 0})->toRect();
      if (getRelativeTile(this, {1, 0})->solid && SDL_HasIntersection(&newPlayerRect, &tmpRect)) {
        setPlayerPos({(float)tmpRect.x - (float)getPlayRect().w, (float)getPlayRect().y});
        return;
      }
      tmpRect = getRelativeTile(this, {1, -1})->toRect();
      if (getRelativeTile(this, {1, -1})->solid && SDL_HasIntersection(&newPlayerRect, &tmpRect)) {
        setPlayerPos({(float)tmpRect.x - (float)getPlayRect().w, (float)getPlayRect().y});
        return;
      }
      tmpRect = getRelativeTile(this, {1, 1})->toRect();
      if (getRelativeTile(this, {1, 1})->solid && SDL_HasIntersection(&newPlayerRect, &tmpRect)) {
        setPlayerPos({(float)tmpRect.x - (float)getPlayRect().w, (float)getPlayRect().y});
        return;
      }
      conveyorMovedPlayer = true;
      setPlayerVel({CONVEYERSPEED * (float)delta, 0});
      return;
    }
  }
};

class ConveyerUp : public Conveyer {
public:
  void onEvent(GameObjectTileEvent e) {
    if (e.type == GAMEOBJECT_TILE_EVENT_PLAYEROVER) {
      if (conveyorMovedPlayer) return;
      SDL_Rect newPlayerRect = getPlayRect();
      newPlayerRect.y -= CONVEYERSPEED * (float)delta + 3;

      SDL_Rect tmpRect = getRelativeTile(this, {0, -1})->toRect();
      if (getRelativeTile(this, {0, -1})->solid && SDL_HasIntersection(&newPlayerRect, &tmpRect)) {
        setPlayerPos({(float)getPlayRect().x, (float)tmpRect.y + (float)tmpRect.h});
        return;
      }
      tmpRect = getRelativeTile(this, {1, -1})->toRect();
      if (getRelativeTile(this, {1, -1})->solid && SDL_HasIntersection(&newPlayerRect, &tmpRect)) {
        setPlayerPos({(float)getPlayRect().x, (float)tmpRect.y + (float)tmpRect.h});
        return;
      }
      tmpRect = getRelativeTile(this, {-1, 1})->toRect();
      if (getRelativeTile(this, {-1, 1})->solid && SDL_HasIntersection(&newPlayerRect, &tmpRect)) {
        setPlayerPos({(float)getPlayRect().x, (float)tmpRect.y + (float)tmpRect.h});
        return;
      }
      conveyorMovedPlayer = true;
      setPlayerVel({0, -(CONVEYERSPEED * (float)delta)});
      return;
    }
  }
};

class ConveyerDown : public Conveyer {
public:
  void onEvent(GameObjectTileEvent e) {
    if (e.type == GAMEOBJECT_TILE_EVENT_PLAYEROVER) {
      if (conveyorMovedPlayer) return;
      SDL_Rect newPlayerRect = getPlayRect();
      newPlayerRect.y += CONVEYERSPEED * (float)delta + 3;

      SDL_Rect tmpRect = getRelativeTile(this, {0, 1})->toRect();
      if (getRelativeTile(this, {0, 1})->solid && SDL_HasIntersection(&newPlayerRect, &tmpRect)) {
        setPlayerPos({(float)getPlayRect().x, (float)tmpRect.y - (float)getPlayRect().h});
        return;
      }
      tmpRect = getRelativeTile(this, {1, 1})->toRect();
      if (getRelativeTile(this, {1, 1})->solid && SDL_HasIntersection(&newPlayerRect, &tmpRect)) {
        setPlayerPos({(float)getPlayRect().x, (float)tmpRect.y - (float)getPlayRect().h});
        return;
      }
      tmpRect = getRelativeTile(this, {-1, 1})->toRect();
      if (getRelativeTile(this, {-1, 1})->solid && SDL_HasIntersection(&newPlayerRect, &tmpRect)) {
        setPlayerPos({(float)getPlayRect().x, (float)tmpRect.y - (float)getPlayRect().h});
        return;
      }
      conveyorMovedPlayer = true;
      setPlayerVel({0, CONVEYERSPEED * (float)delta});
      return;
    }
  }
};
#endif
