#include "../air.hpp"
#include "../conveyer.hpp"
#include "../goal.hpp"
#include "../half_walls.hpp"
#include "../wall.hpp"
#include "tile.hpp"

#ifndef TILES_HEADER_DEFINED
#define TILES_HEADER_DEFINED

template <typename T>
Tile* tileInstantiator() { return new T; }
typedef Tile* (*tileInstantiator_ptr)();

tileInstantiator_ptr tileMap[] = {&tileInstantiator<Air>,
                                  &tileInstantiator<Wall>,
                                  &tileInstantiator<Goal>,
                                  &tileInstantiator<HalfWallLeft>,
                                  &tileInstantiator<HalfWallRight>,
                                  &tileInstantiator<HalfWallTop>,
                                  &tileInstantiator<HalfWallBottom>,
                                  &tileInstantiator<ConveyerLeft>,
                                  &tileInstantiator<ConveyerRight>,
                                  &tileInstantiator<ConveyerUp>,
                                  &tileInstantiator<ConveyerDown>};
#endif
