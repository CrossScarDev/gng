#include <SDL2/SDL.h>
#include "../utils.h"
#include "gameobject.hpp"

#ifndef PLAYER_HEADER_DEFINED
#define PLAYER_HEADER_DEFINED

class Player: public GameObject {
    private:
        Vector2 vel;
        float speed;

    public:
        Player(Vector2 defaultPos, Vector2 defaultVel, float defaultSpeed, int defaultSize) {
            setPos(defaultPos);
            vel = defaultVel;
            speed = defaultSpeed;
            setSize(defaultSize);
        }

        Vector2 getVel() {
            return vel;
        }

        void update() {
            vel = (Vector2){ 0, 0 };

            const Uint8* keystates = SDL_GetKeyboardState(NULL);

            if (keystates[SDL_SCANCODE_UP] || keystates[SDL_SCANCODE_W]) {
                vel.y -= speed;
            } else if (keystates[SDL_SCANCODE_DOWN] || keystates[SDL_SCANCODE_S]) {
                vel.y += speed;
            } else if (keystates[SDL_SCANCODE_LEFT] || keystates[SDL_SCANCODE_A]) {
                vel.x -= speed;
            } else if (keystates[SDL_SCANCODE_RIGHT] || keystates[SDL_SCANCODE_D]) {
                vel.x += speed;
            }

            setX(getPos().x + vel.x);
            setY(getPos().y + vel.y);

            keepOnScreen();
        }

        void draw() {
            SDL_Rect tmpRect = toRect();
            SDL_SetRenderDrawColor(renderer, 0x00, 0x79, 0xf1, 0xff);
            SDL_RenderFillRect(renderer, &tmpRect);
        }
};
#endif