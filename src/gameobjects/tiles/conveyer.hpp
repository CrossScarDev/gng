#include "base/tile.hpp"
#include "base/events.hpp"
#include "../../utils.h"
#include <SDL2/SDL.h>

#ifndef CONVEYER_HEADER_DEFINED
#define CONVEYER_HEADER_DEFINED

extern double delta;
extern void setPlayerVel(Vector2 vel);
extern void setBoxVel(Vector2 vel);
extern SDL_Rect getPlayRect();
extern SDL_Rect getBoxRect();
extern Vector2 getPlayerVel();
extern Vector2 getBoxVel();

#define CONVEYERSPEED 0.088235294f

class Conveyer : public Tile {
    public:
        Conveyer() : Tile({ 1, 1 }, { 0, 0 }, false, 0x333333) {};
};

class ConveyerLeft : public Conveyer {
    public:
        void onEvent(GameObjectTileEvent e) {
            if (e.type == GAMEOBJECT_TILE_EVENT_PLAYEROVER) {
                setPlayerVel({ -(CONVEYERSPEED * (float)delta), 0 });
                return;
            }

            if (e.type == GAMEOBJECT_TILE_EVENT_BOXOVER) {
                if (getBoxVel().x != 0 || getBoxVel().y != 0) return;
                setBoxVel({ -(CONVEYERSPEED * (float)delta), 0 });
                
                const SDL_Rect tmpPlayerRect = getPlayRect();
                const SDL_Rect tmpBoxRect = getBoxRect();
                if (SDL_HasIntersection(&tmpPlayerRect, &tmpBoxRect)) {
                    setPlayerVel({ -(CONVEYERSPEED * (float)delta), 0 });
                }
            }
        }
};

class ConveyerRight : public Conveyer {
    public:
        void onEvent(GameObjectTileEvent e) {
            if (e.type == GAMEOBJECT_TILE_EVENT_PLAYEROVER) {
                setPlayerVel({ CONVEYERSPEED * (float)delta, 0 });
                return;
            }

            if (e.type == GAMEOBJECT_TILE_EVENT_BOXOVER) {
                setBoxVel({ CONVEYERSPEED * (float)delta, 0 });
                
                const SDL_Rect tmpPlayerRect = getPlayRect();
                const SDL_Rect tmpBoxRect = getBoxRect();
                if (SDL_HasIntersection(&tmpPlayerRect, &tmpBoxRect)) {
                    setPlayerVel({ CONVEYERSPEED * (float)delta, 0 });
                }
            }
        }
};

class ConveyerUp : public Conveyer {
    public:
        void onEvent(GameObjectTileEvent e) {
            if (e.type == GAMEOBJECT_TILE_EVENT_PLAYEROVER) {
                setPlayerVel({ 0, -(CONVEYERSPEED * (float)delta) });
                return;
            }

            if (e.type == GAMEOBJECT_TILE_EVENT_BOXOVER) {
                setBoxVel({ 0, -(CONVEYERSPEED * (float)delta) });
                
                const SDL_Rect tmpPlayerRect = getPlayRect();
                const SDL_Rect tmpBoxRect = getBoxRect();
                if (SDL_HasIntersection(&tmpPlayerRect, &tmpBoxRect)) {
                    setPlayerVel({ 0, -(CONVEYERSPEED * (float)delta) });
                }
            }
        }
};

class ConveyerDown : public Conveyer {
    public:
        void onEvent(GameObjectTileEvent e) {
            if (e.type == GAMEOBJECT_TILE_EVENT_PLAYEROVER) {
                setPlayerVel({ 0, CONVEYERSPEED * (float)delta });
                return;
            }

            if (e.type == GAMEOBJECT_TILE_EVENT_BOXOVER) {
                setBoxVel({ 0, CONVEYERSPEED * (float)delta });
                
                const SDL_Rect tmpPlayerRect = getPlayRect();
                const SDL_Rect tmpBoxRect = getBoxRect();
                if (SDL_HasIntersection(&tmpPlayerRect, &tmpBoxRect)) {
                    setPlayerVel({ 0, CONVEYERSPEED * (float)delta });
                }
            }
        }
};
#endif
