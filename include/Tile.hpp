#ifndef TILE__H__
#define TILE__H__

//SFML
#include <SFML/System/Vector2.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>


//Violet
#include <Renderable.hpp>

namespace Violet{
        class Tile : public Renderable{
                sf::RectangleShape gfx;

                public:
                        Tile(sf::Color color, sf::Vector2f init_pos);

                        virtual ~Tile();
                        virtual void render(std::function<void(sf::Drawable&)> draw);
        };
};

#endif
