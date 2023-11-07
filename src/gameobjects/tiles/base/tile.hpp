#include <SDL2/SDL.h>
#include "../../../utils.h"
#include "../../gameobject.hpp"
#include "events.hpp"

#ifndef TILE_HEADER_DEFINED
#define TILE_HEADER_DEFINED

extern SDL_Renderer* renderer;
extern const float TILE_SIZE;
extern const int SCREEN_START_X;

class Tile : GameObject {
    public:
        Vector2 pos;
        Vector2 size;
        SDL_Texture* texture = NULL;
        unsigned int color;
        bool solid;
        int id;

        Tile(Vector2 defaultSize, bool defaultSolid, void* textureMem, int textureSize) {
            size = defaultSize;
            texture = loadTexture(textureMem, textureSize);
            solid = defaultSolid;
        };

        Tile(Vector2 defaultSize, bool defaultSolid, unsigned int defaultColor) {
            size = defaultSize;
            color = defaultColor;
            solid = defaultSolid;
        };

        SDL_Rect toRect() {
            return {
                (int)(pos.x * TILE_SIZE + SCREEN_START_X),
                (int)(pos.y * TILE_SIZE),
                (int)(size.x * TILE_SIZE),
                (int)(size.y * TILE_SIZE)
            };
        };

        virtual void update() {};
        virtual void onEvent(GameObjectTileEvent e) {};

        void draw() {
            if (id == 0) return;

            SDL_Rect tmpRect = toRect();

            if (texture == NULL) {
                SDL_SetRenderDrawColor(renderer, color);
                SDL_RenderFillRect(renderer, &tmpRect);
            } else {
                SDL_RenderCopy(renderer, texture, NULL, &tmpRect);
            }
        }
};
#endif