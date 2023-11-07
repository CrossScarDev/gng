#include "base/tile.hpp"
#include "base/events.hpp"
#include "../../utils.h"

extern void nextLevel();

#ifndef GOAL_HEADER_DEFINED
#define GOAL_HEADER_DEFINED

class Goal : public Tile {
    public:
        Goal() : Tile({1, 1}, false, 0x3b8a3f) {};
        void onEvent(GameObjectTileEvent e) {
            if (e.type == GAMEOBJECT_TILE_EVENT_BOXOVER)
                nextLevel();
        }
};
#endif