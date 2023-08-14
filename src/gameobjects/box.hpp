#include <SDL2/SDL.h>
#include "../utils.h"
#include "gameobject.hpp"
#include "player.hpp"

extern Player player;

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

            if (keystates[SDL_SCANCODE_SPACE] && (onSide(toRect(), player.toRect()) == 2 || onSide(toRect(), player.toRect()) == 3)) {
                setY(getPos().y + player.getVel().y);

                if (keepOnScreen()) {
                    player.setPos((Vector2){
                        player.getPos().x - player.getVel().x,
                        player.getPos().y - player.getVel().y
                    });
                }
            }

            if (keystates[SDL_SCANCODE_SPACE] && (onSide(toRect(), player.toRect()) == 0 || onSide(toRect(), player.toRect()) == 1)) {
                setX(getPos().x + player.getVel().x);

                if (keepOnScreen()) {
                    player.setPos((Vector2){
                        player.getPos().x - player.getVel().x,
                        player.getPos().y - player.getVel().y
                    });
                }
            }

            SDL_Rect tmpRect = toRect();
            SDL_Rect tmpPlayerRect = player.toRect();
            if (SDL_HasIntersection(&tmpRect, &tmpPlayerRect)) {
                setX(getPos().x + player.getVel().x);
                setY(getPos().y + player.getVel().y);

                if (keepOnScreen()) {
                    player.setPos((Vector2){
                        player.getPos().x - player.getVel().x,
                        player.getPos().y - player.getVel().y
                    });
                }
            }
        }

        void draw() {
            SDL_Rect tmpRect = toRect();
            SDL_FillRect(screenSurface, &tmpRect, SDL_MapRGB(screenSurface->format, 0xd3, 0xb0, 0x83));
        }
};
#endif