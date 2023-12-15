#include <array>
#include "tiles.hpp"

#ifndef TILEGRID_HEADER_DEFINED
#define TILEGRID_HEADER_DEFINED

class TileGrid {
    public:
        std::array<int, 255> tileIds;
        std::array<Tile*, 255> tiles;

        TileGrid(std::array<int, 255> defaultTileIds) {
            tileIds = defaultTileIds;

            for (int i = 0; i < (int)tileIds.size(); i++) {
                const int tileId = tileIds[i];
                tiles[i] = tileMap[tileId]();
                tiles[i]->id = tileId;
                tiles[i]->pos = { (float)(i % 15), (float)(i / 15) };
            }
        };

        void update() {
            for (const auto& tile : tiles) {
                tile->update();
            }
        }

        void draw() {
            for (const auto& tile : tiles) {
                tile->draw();
            }
        }
};
#endif