#include <SDL2/SDL.h>
#include "../utils.h"
#include "gameobject.hpp"

#ifndef PLAYER_HEADER_DEFINED
#define PLAYER_HEADER_DEFINED

extern SDL_GameController* controller;
extern double delta;

#define CONTROLLER_DEADZONE_X 10000
#define CONTROLLER_DEADZONE_Y 18000

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
            float deltaSpeed = speed * delta;

            const Uint8* keystates = SDL_GetKeyboardState(NULL);
            float joyX = SDL_GameControllerGetAxis(controller, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX);
            float joyY = SDL_GameControllerGetAxis(controller, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY);

            if (keystates[SDL_SCANCODE_UP] || keystates[SDL_SCANCODE_W] || SDL_GameControllerGetButton(controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_UP) == 1 || joyY < -CONTROLLER_DEADZONE_Y) {
                vel.y -= deltaSpeed;
            } else if (keystates[SDL_SCANCODE_DOWN] || keystates[SDL_SCANCODE_S] || SDL_GameControllerGetButton(controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 1 || joyY > CONTROLLER_DEADZONE_Y) {
                vel.y += deltaSpeed;
            } else if (keystates[SDL_SCANCODE_LEFT] || keystates[SDL_SCANCODE_A] || SDL_GameControllerGetButton(controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 1 || joyX < -CONTROLLER_DEADZONE_X) {
                vel.x -= deltaSpeed;
            } else if (keystates[SDL_SCANCODE_RIGHT] || keystates[SDL_SCANCODE_D] || SDL_GameControllerGetButton(controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 1 || joyX > CONTROLLER_DEADZONE_X) {
                vel.x += deltaSpeed;
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