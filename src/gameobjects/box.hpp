#include <SDL2/SDL.h>
#ifdef __MOBILE__
#include <array>
#endif
#include "../utils.h"
#include "gameobject.hpp"
#include "player.hpp"
#include "../levels.hpp"
#include "../sdl2-funcs.h"

extern Player player;
extern SDL_GameController* controller;

#ifndef BOX_HEADER_DEFINED
#define BOX_HEADER_DEFINED

#ifdef __MOBILE__
extern const SDL_Rect drag_rect;
extern std::array<Vector2, 6> touchPositions;
#endif

class Box: public GameObject {
    public:
        void update() {
            const Uint8* keystates = SDL_GetKeyboardState(NULL);
            bool collideTile = false;
            SDL_Rect collideTileRect;
            bool dragPressed = false;
            #ifdef __MOBILE__
            for (int i = 0; i < touchPositions.size(); i++) {
                SDL_Point touchPos = (SDL_Point){ (int)touchPositions[i].x, (int)touchPositions[i].y };

                if (distance(touchPos, {
                    drag_rect.x + drag_rect.w / 2,
                    drag_rect.y + drag_rect.h / 2
                }) <= drag_rect.w) dragPressed = true;
            }        
            #endif

            if ((keystates[SDL_SCANCODE_SPACE] || SDL_GameControllerGetButton(controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A) == 1 || dragPressed) && (onSide(toRect(), player.toRect()) == 2 || onSide(toRect(), player.toRect()) == 3)) {
                pos.y += player.vel.y;

                const SDL_Rect tmpRect = toRect();
                for (const auto& tile : currentLevel->tileGrid->tiles) {
                    if (tile->solid) {
                        const SDL_Rect tmpTileRect = tile->toRect();
                        if (SDL_HasIntersection(&tmpRect, &tmpTileRect)) {
                            collideTile = true;
                            collideTileRect = tmpTileRect;
                            
                            break;
                        }
                    }
                }

                if (collideTile) {
                    if (player.vel.x > 0) {
                        player.vel.x = collideTileRect.x - (this->pos.x + this->size.x);
                    } else if (player.vel.x < 0) {
                        player.vel.x = (collideTileRect.x + collideTileRect.w) - this->pos.x;
                    } else if (player.vel.y > 0) {
                        player.vel.y = collideTileRect.y - (this->pos.y + this->size.x);
                    } else if (player.vel.y < 0) {
                        player.vel.y = (collideTileRect.y + collideTileRect.h) - this->pos.y;
                    }

                    pos.y += player.vel.y;
                }
            }

            if ((keystates[SDL_SCANCODE_SPACE] || SDL_GameControllerGetButton(controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A) == 1 || dragPressed) && (onSide(toRect(), player.toRect()) == 0 || onSide(toRect(), player.toRect()) == 1)) {
                pos.x += player.vel.x;

                const SDL_Rect tmpRect = toRect();
                for (const auto& tile : currentLevel->tileGrid->tiles) {
                    if (tile->solid) {
                        const SDL_Rect tmpTileRect = tile->toRect();
                        if (SDL_HasIntersection(&tmpRect, &tmpTileRect)) {
                            collideTile = true;
                            collideTileRect = tmpTileRect;
                            
                            break;
                        }
                    }
                }

                if (collideTile) {
                    if (player.vel.x > 0) {
                        player.vel.x = collideTileRect.x - (this->pos.x + this->size.x);
                    } else if (player.vel.x < 0) {
                        player.vel.x = (collideTileRect.x + collideTileRect.w) - this->pos.x;
                    } else if (player.vel.y > 0) {
                        player.vel.y = collideTileRect.y - (this->pos.y + this->size.x);
                    } else if (player.vel.y < 0) {
                        player.vel.y = (collideTileRect.y + collideTileRect.h) - this->pos.y;
                    }

                    pos.x += player.vel.x;
                }
            }

            SDL_Rect tmpRect = toRect();
            SDL_Rect tmpPlayerRect = player.toRect();
            if (SDL_HasIntersection(&tmpRect, &tmpPlayerRect)) {
                pos += player.vel;
                tmpRect = toRect();

                for (const auto& tile : currentLevel->tileGrid->tiles) {
                    if (tile->solid) {
                        const SDL_Rect tmpTileRect = tile->toRect();
                        if (SDL_HasIntersection(&tmpRect, &tmpTileRect)) {
                            collideTile = true;
                            collideTileRect = tmpTileRect;
                            
                            break;
                        }
                    }
                }

                if (collideTile) {
                    if (player.vel.x > 0) {
                        player.vel.x = collideTileRect.x - (this->pos.x + this->size.x);
                    } else if (player.vel.x < 0) {
                        player.vel.x = (collideTileRect.x + collideTileRect.w) - this->pos.x;
                    } else if (player.vel.y > 0) {
                        player.vel.y = collideTileRect.y - (this->pos.y + this->size.x);
                    } else if (player.vel.y < 0) {
                        player.vel.y = (collideTileRect.y + collideTileRect.h) - this->pos.y;
                    }

                    pos += player.vel;

                    player.pos += player.vel;

                    return;
                }
            }
            if (keepOnScreen()) {
                if (player.vel.x > 0) {
                    player.vel.x = this->pos.x - (player.pos.x + player.size.x);
                } else if (player.vel.x < 0) {
                    player.vel.x = (this->pos.x + this->size.y) - player.pos.x;
                } else if (player.vel.y > 0) {
                    player.vel.y = this->pos.y - (player.pos.y + player.size.x);
                } else if (player.vel.y < 0) {
                    player.vel.y = (this->pos.y + this->size.y) - player.pos.y;
                }

                player.pos += player.vel;
            }
        }

        void draw() {
            SDL_Rect tmpRect = toRect();
            SDL_SetRenderDrawColor(renderer, 0xd3b083);
            SDL_RenderFillRect(renderer, &tmpRect);
        }
};
#endif