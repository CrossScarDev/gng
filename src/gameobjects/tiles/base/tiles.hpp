#include "tile.hpp"
#include "../air.hpp"
#include "../wall.hpp"
#include "../goal.hpp"

#ifndef TILES_HEADER_DEFINED
#define TILES_HEADER_DEFINED

template<typename T> Tile* tileInstantiator() {
    return new T;
}
typedef Tile* (*tileInstantiator_ptr)();

tileInstantiator_ptr tileMap[] = {
    &tileInstantiator<Air>,
    &tileInstantiator<Wall>,
    &tileInstantiator<Goal>
};
#endif