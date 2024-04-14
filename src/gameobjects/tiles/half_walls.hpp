#include "../../utils.h"
#include "base/tile.hpp"

#ifndef HALF_WALLS_HEADER_DEFINED
#define HALF_WALLS_HEADER_DEFINED

class HalfWall : public Tile {
public:
  HalfWall(Vector2 defaultSize, Vector2 defaultOffset) : Tile(defaultSize, defaultOffset, true, 0x696783){};
};

class HalfWallLeft : public HalfWall {
public:
  HalfWallLeft() : HalfWall({0.5, 1}, {0, 0}) {}
};

class HalfWallRight : public HalfWall {
public:
  HalfWallRight() : HalfWall({0.5, 1}, {0.5, 0}) {}
};

class HalfWallTop : public HalfWall {
public:
  HalfWallTop() : HalfWall({1, 0.5}, {0, 0}) {}
};

class HalfWallBottom : public HalfWall {
public:
  HalfWallBottom() : HalfWall({1, 0.5}, {0, 0.5}) {}
};
#endif
