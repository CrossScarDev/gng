#include "../../utils.h"
#include "base/tile.hpp"

#ifndef WALL_HEADER_DEFINED
#define WALL_HEADER_DEFINED

class Wall : public Tile {
public:
  Wall() : Tile({1, 1}, {0, 0}, true, 0x696783){};
};
#endif