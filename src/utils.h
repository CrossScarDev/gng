#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rwops.h>
#include <cmath>

extern SDL_Renderer* renderer;

#ifndef UTILS_HEADER_DEFINED
#define UTILS_HEADER_DEFINED
typedef struct Vector2 {
  float x;
  float y;

  Vector2 operator+=(const Vector2 obj) {
    x += obj.x;
    y += obj.y;
    return *this;
  }

  Vector2 operator-=(const Vector2 obj) {
    x -= obj.x;
    y -= obj.y;
    return *this;
  }

  Vector2 operator-(const Vector2 obj) { return {x - obj.x, y - obj.y}; }

  Vector2 operator/(const int a) { return {x / a, y / a}; }

  bool operator!=(const Vector2 obj) { return x != obj.x || y != obj.y; }
} Vector2;

#define loadTexture(mem, size) IMG_LoadTexture_RW(renderer, SDL_RWFromMem(mem, size), 1)

#define getHexDigit(hexNumber, digit) ((hexNumber >> (digit << 2)) & 0x0f)

SDL_Color hexColor(unsigned int hex) {
  SDL_Color color;
  color.r = getHexDigit(hex, 4) + getHexDigit(hex, 5) * 16;
  color.g = getHexDigit(hex, 2) + getHexDigit(hex, 3) * 16;
  color.b = getHexDigit(hex, 0) + getHexDigit(hex, 1) * 16;
  color.a = 0xff;
  return color;
}

int distance(SDL_Point p1, SDL_Point p2) {
  return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) * 1.0);
}
#endif
