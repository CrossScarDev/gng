#include <array>
#include "gameobjects/tiles/base/tileGrid.hpp"
#include "utils.h"

extern void reset();

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const float TILE_SIZE;
extern const int SCREEN_START_X;
extern const int SCREEN_END_X;

#ifndef LEVELS_HEADER_DEFINED
#define LEVELS_HEADER_DEFINED

class Level {
    public:
        TileGrid* tileGrid;
        Vector2 playerPos;
        Vector2 boxPos;

        Level(Vector2 defaultPlayerPos, Vector2 defaultBoxPos, std::array<int, 255> tiles) {
            playerPos = defaultPlayerPos;
            boxPos = defaultBoxPos;
            tileGrid = new TileGrid(tiles);
        }
};

Level* levels[]={new Level({507,416},{603,416},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,5,5,5,5,5,5,1,0,0,0,0,0,1,3,8,8,8,8,8,8,10,1,0,0,0,0,0,1,3,9,1,1,1,1,10,4,1,3,0,0,0,0,1,3,9,1,1,1,1,10,4,1,1,0,0,0,0,1,3,9,1,1,1,1,10,7,7,0,0,0,0,0,1,3,9,1,1,1,1,10,4,1,3,0,0,0,0,1,1,9,7,7,7,7,10,4,1,3,0,0,0,0,1,1,6,6,6,6,6,7,4,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0})};

int currentLevelIndex = 0;
Level* currentLevel = levels[currentLevelIndex];

void setLevel(int levelIndex) {
    currentLevelIndex = levelIndex;
    currentLevel = levels[levelIndex];
    reset();
}

void nextLevel() {
    setLevel(currentLevelIndex + 1);
}
#endif