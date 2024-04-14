#include "../../gameobject.hpp"

#ifndef EVENTS_HEADER_DEFINED
#define EVENTS_HEADER_DEFINED

#define GAMEOBJECT_TILE_EVENT_BOXOVER 0x0
#define GAMEOBJECT_TILE_EVENT_PLAYEROVER 0x2
typedef struct GameObjectTileEvent {
  int type;
  GameObject* gameObject;
} TileEvent;
#endif