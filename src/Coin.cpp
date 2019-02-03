#include <Coin.hpp>
#include <Constants.hpp>

namespace Violet{
        Coin::Coin(sf::Vector2f init_pos) : Tile::Tile(Pallette::sky, init_pos)
        {
                gfx = sf::CircleShape(Constants::TILE_SIZE / 2 - 4); // scale it to fit within a tile
                gfx.setPosition({init_pos.x + 3, init_pos.y + 3}); // Move it to the center of a tile
                gfx.setFillColor(Pallette::coin);
        }

        Coin::~Coin()
        {

        }

        void Coin::render(std::function<void(sf::Drawable&)> draw)
        {
                Tile::render(draw); //render sky tile first
                draw(gfx);
        }

};
