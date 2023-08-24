#include <SDL2/SDL.h>
#include "../utils.h"
#include "gameobject.hpp"
#include "player.hpp"
#include "tiles/base/tileGrid.hpp"

extern Player player;
extern SDL_GameController* controller;
extern TileGrid tileGrid;

#ifndef BOX_HEADER_DEFINED
#define BOX_HEADER_DEFINED

class Box: public GameObject {
    public:
        Box(Vector2 defaultPos, int defaultSize) {
            setPos(defaultPos);
            setSize(defaultSize);
        }

        void update() {
            const Uint8* keystates = SDL_GetKeyboardState(NULL);

            if ((keystates[SDL_SCANCODE_SPACE] || SDL_GameControllerGetButton(controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A) == 1) && (onSide(toRect(), player.toRect()) == 2 || onSide(toRect(), player.toRect()) == 3)) {
                setY(getPos().y + player.getVel().y);

                const SDL_Rect tmpRect = toRect();
                bool collideTile = false;
                for (const auto& tile : tileGrid.tiles) {
                    if (tile->solid) {
                        const SDL_Rect tmpTileRect = tile->toRect();
                        if (SDL_HasIntersection(&tmpRect, &tmpTileRect))
                            collideTile = true;
                    }
                }

                if (keepOnScreen() || collideTile) {
                    setY(getPos().y - player.getVel().y);
                }
            }

            if ((keystates[SDL_SCANCODE_SPACE] || SDL_GameControllerGetButton(controller, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A) == 1) && (onSide(toRect(), player.toRect()) == 0 || onSide(toRect(), player.toRect()) == 1)) {
                setX(getPos().x + player.getVel().x);

                const SDL_Rect tmpRect = toRect();
                bool collideTile = false;
                for (const auto& tile : tileGrid.tiles) {
                    if (tile->solid) {
                        const SDL_Rect tmpTileRect = tile->toRect();
                        if (SDL_HasIntersection(&tmpRect, &tmpTileRect))
                            collideTile = true;
                    }
                }

                if (keepOnScreen() || collideTile) {
                    setX(getPos().x - player.getVel().x);
                }
            }

            SDL_Rect tmpRect = toRect();
            SDL_Rect tmpPlayerRect = player.toRect();
            if (SDL_HasIntersection(&tmpRect, &tmpPlayerRect)) {
                setX(getPos().x + player.getVel().x);
                setY(getPos().y + player.getVel().y);
                tmpRect = toRect();

                bool collideTile = false;
                for (const auto& tile : tileGrid.tiles) {
                    if (tile->solid) {
                        const SDL_Rect tmpTileRect = tile->toRect();
                        if (SDL_HasIntersection(&tmpRect, &tmpTileRect))
                            collideTile = true;
                    }
                }

                if (keepOnScreen() || collideTile) {
                    setX(getPos().x - player.getVel().x);
                    setY(getPos().y - player.getVel().y);

                    player.setPos((Vector2){
                        player.getPos().x - player.getVel().x,
                        player.getPos().y - player.getVel().y
                    });
                }
            }
        }

        void draw() {
            SDL_Rect tmpRect = toRect();
            const SDL_Color color = hexColor(0xd3b083);
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(renderer, &tmpRect);
        }
};
#endif