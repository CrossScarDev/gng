#include "../utils.h"
#include "../collisions.h"

#ifndef GAMEOBJECT_HEADER_DEFINED
#define GAMEOBJECT_HEADER_DEFINED

extern const int SCREEN_HEIGHT;
extern const int SCREEN_START_X;
extern const int SCREEN_END_X;

class GameObject {
    private:
        Vector2 pos;
        float size;
    
    public:
        Vector2 getPos() {
            return pos;
        }

        void setPos(Vector2 newPos) {
            pos = newPos;
        }

        void setX(int newX) {
            pos.x = newX;
        }

        void setY(int newY) {
            pos.y = newY;
        }

        float getSize() {
            return size;
        }

        void setSize(float newSize) {
            size = newSize;
        }

        SDL_Rect toRect() {
            return (SDL_Rect){
                (int)getPos().x, // X
                (int)getPos().y, // Y
                (int)getSize(), // Width
                (int)getSize() // Height
            };
        }

        bool keepOnScreen() {
            if (pos.x + size > SCREEN_END_X) {
                pos.x = SCREEN_END_X - size;

                return true;
            }

            if (pos.x < SCREEN_START_X) {
                pos.x = SCREEN_START_X;

                return true;
            }

            if (pos.y + size > SCREEN_HEIGHT) {
                pos.y = SCREEN_HEIGHT - size;

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