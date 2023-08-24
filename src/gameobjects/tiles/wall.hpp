#include "base/tile.hpp"
#include "../../utils.h"

#ifndef WALL_HEADER_DEFINED
#define WALL_HEADER_DEFINED

class Wall : public Tile {
    public:
        Wall() : Tile({1, 1}, true, hexColor(0x696783)) {};
};
#endif