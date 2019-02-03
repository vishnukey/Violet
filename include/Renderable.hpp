#ifndef RENDERABLE__H__
#define RENDERABLE__H__

#include <functional>

//SFML
#include <SFML/Graphics/Drawable.hpp>

namespace Violet{
        class Renderable
        {
                public:
                        virtual ~Renderable() = 0;

                        /*
                         * Takes in a function which will draw to the screen.
                         * This is so each object can specify how to draw
                         * themselves without having complete access
                         * to the window object
                         */
                        virtual void render(std::function<void(sf::Drawable&)> draw) = 0;
        };
};

#endif
