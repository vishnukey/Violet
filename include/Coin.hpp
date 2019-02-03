#ifndef COIN__H__
#define COIN__H__

//SFML
#include <SFML/Graphics/CircleShape.hpp>

//Violet
#include <Tile.hpp>

namespace Violet{
        /*
         * Class representing a coin. It has sky Tile as its background
         */
        class Coin : public Tile
        {
                sf::CircleShape gfx;

                public:
                        Coin(sf::Vector2f init_pos);

                        ~Coin() override;
                        void render(std::function<void(sf::Drawable&)> draw) override;
        };
};

#endif
