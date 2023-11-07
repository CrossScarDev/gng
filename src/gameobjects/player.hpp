#include <SDL2/SDL.h>
#ifdef __MOBILE__
#include <array>
#endif
#include "../utils.h"
#include "gameobject.hpp"
#include "../levels.hpp"

#ifndef PLAYER_HEADER_DEFINED
#define PLAYER_HEADER_DEFINED

extern SDL_GameController* controller;
extern SDL_Renderer* renderer;
extern double delta;

#ifdef __MOBILE__
extern const SDL_Rect dpad_rect;
extern const int DPAD_OFFSET;
extern std::array<Vector2, 6> touchPositions;
#endif

#define CONTROLLER_DEADZONE_X 10000
#define CONTROLLER_DEADZONE_Y 18000

class Player: public GameObject {
    public:
        Vector2 vel;
        float speed;

        void update() {
            vel = (Vector2){ 0, 0 };
            float deltaSpeed = speed * delta;

            const Uint8* keystates = SDL_GetKeyboardState(NULL);
            float joyX = SDL_GameControllerGetAxis(controller, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX);
            float joyY = SDL_GameControllerGetAxis(controller, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY);

            // Touch Inputs
            #ifdef __MOBILE__
            for (int i = 0; i < touchPositions.size(); i++) {
                SDL_Point touchPos = (SDL_Point){ (int)touchPositions[i].x, (int)touchPositions[i].y };
                SDL_Rect tmpDPadRect;

                // Up
                tmpDPadRect = {
                    dpad_rect.x + DPAD_OFFSET, // X
                    dpad_rect.y + 0, // Y
                    dpad_rect.w - DPAD_OFFSET * 2, // Width
                    dpad_rect.h - DPAD_OFFSET * 2 // Height
                };
                if (SDL_PointInRect(&touchPos, &tmpDPadRect))
                    vel.y -= deltaSpeed;
                
                // Down
                tmpDPadRect = {
                    dpad_rect.x + DPAD_OFFSET, // X
                    dpad_rect.y + dpad_rect.h - DPAD_OFFSET, // Y
                    dpad_rect.w - DPAD_OFFSET * 2, // Width
                    dpad_rect.h - DPAD_OFFSET * 2 // Height
                };
                if (SDL_PointInRect(&touchPos, &tmpDPadRect))
                    vel.y += deltaSpeed;

                // Left
                tmpDPadRect = {
                    dpad_rect.x, // X
                    dpad_rect.y + DPAD_OFFSET, // Y
                    dpad_rect.w - DPAD_OFFSET * 2, // Width
                    dpad_rect.h - DPAD_OFFSET * 2 // Height
                };
                if (SDL_PointInRect(&touchPos, &tmpDPadRect))
                    vel.x -= deltaSpeed;
                
                // Right
                tmpDPadRect = {
                    dpad_rect.x + dpad_rect.w - DPAD_OFFSET, // X
                    dpad_rect.y + DPAD_OFFSET, // Y
                    dpad_rect.w - DPAD_OFFSET * 2, // Width
                    dpad_rect.h - DPAD_OFFSET * 2 // Height
                };
                if (SDL_PointInRect(&touchPos, &tmpDPadRect))
                    vel.x += deltaSpeed;
            }
            #endif

            // Keyboard + Controller Inputs
            if (keystates[SDL_SCANCODE_UP] || keystates[SDL_SCANCODE_W] || SDL_GameControllerGetButton(controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_UP) == 1 || joyY < -CONTROLLER_DEADZONE_Y) {
                vel.y -= deltaSpeed;
            } else if (keystates[SDL_SCANCODE_DOWN] || keystates[SDL_SCANCODE_S] || SDL_GameControllerGetButton(controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 1 || joyY > CONTROLLER_DEADZONE_Y) {
                vel.y += deltaSpeed;
            } else if (keystates[SDL_SCANCODE_LEFT] || keystates[SDL_SCANCODE_A] || SDL_GameControllerGetButton(controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 1 || joyX < -CONTROLLER_DEADZONE_X) {
                vel.x -= deltaSpeed;
            } else if (keystates[SDL_SCANCODE_RIGHT] || keystates[SDL_SCANCODE_D] || SDL_GameControllerGetButton(controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 1 || joyX > CONTROLLER_DEADZONE_X) {
                vel.x += deltaSpeed;
            }

            const SDL_Rect tmpRect = {
                (int)(pos.x + vel.x),
                (int)(pos.y + vel.y),
                (int)size.x,
                (int)size.y
            };

            // Collision
            for (const auto& tile : currentLevel->tileGrid->tiles) {
                if (tile->solid) {
                    const SDL_Rect tmpTileRect = tile->toRect();
                    if (SDL_HasIntersection(&tmpRect, &tmpTileRect)) {
                        if (vel.x > 0) {
                            vel.x = tmpTileRect.x - (this->pos.x + this->size.x);
                        } else if (vel.x < 0) {
                            vel.x = (tmpTileRect.x + tmpTileRect.w) - this->pos.x;
                        } else if (vel.y > 0) {
                            vel.y = tmpTileRect.y - (this->pos.y + this->size.x);
                        } else if (vel.y < 0) {
                            vel.y = (tmpTileRect.y + tmpTileRect.h) - this->pos.y;
                        }

                        break;
                    }
                }
            }

            pos += vel;

            keepOnScreen();
        }

        void draw() {
            SDL_Rect tmpRect = toRect();
            SDL_SetRenderDrawColor(renderer, 0x0079f1);
            SDL_RenderFillRect(renderer, &tmpRect);
        }
};
#endif
