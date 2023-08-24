#include "base/tile.hpp"
#include "../../utils.h"

#ifndef AIR_HEADER_DEFINED
#define AIR_HEADER_DEFINED

class Air : public Tile {
    public:
        Air() : Tile({1, 1}, false, hexColor(0xffffff)) {};
};
#endif