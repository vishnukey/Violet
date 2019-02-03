#include <Tile.hpp>
#include <Constants.hpp>

namespace Violet{
        Tile::Tile(sf::Color color, sf::Vector2f init_pos)
        {
                gfx = sf::RectangleShape(
                        sf::Vector2f(
                                Constants::tileDim.x - 2,
                                Constants::tileDim.y - 2));
                gfx.setPosition(init_pos);
                gfx.setFillColor(color);
        }

        Tile::~Tile()
        {

        }

        void Tile::render(std::function<void(sf::Drawable&)> draw)
        {
                draw(gfx);
        }

};
