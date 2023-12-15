#include "../utils.h"
#include "collisions.h"

#ifndef GAMEOBJECT_HEADER_DEFINED
#define GAMEOBJECT_HEADER_DEFINED

extern const int SCREEN_HEIGHT;
extern const int SCREEN_START_X;
extern const int SCREEN_END_X;

class GameObject {
    public:
        Vector2 pos;
        Vector2 size;

        SDL_Rect toRect() {
            return (SDL_Rect){
                (int)pos.x, // X
                (int)pos.y, // Y
                (int)size.x, // Width
                (int)size.y // Height
            };
        }

        bool keepOnScreen() {
            if (pos.x + size.x > SCREEN_END_X) {
                pos.x = SCREEN_END_X - size.x;

                return true;
            }

            if (pos.x < SCREEN_START_X) {
                pos.x = SCREEN_START_X;

                return true;
            }

            if (pos.y + size.y > SCREEN_HEIGHT) {
                pos.y = SCREEN_HEIGHT - size.y;

                return true;
            }

            if (pos.y < 0) {
                pos.y = 0;

                return true;
            }

            return false;
        }

        void update();
};
#endif