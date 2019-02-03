#ifndef PLAYER__H__
#define PLAYER__H__

//SFML
#include <SFML/System/Vector2.hpp>

#include <SFML/Graphics/RectangleShape.hpp>

//Violet
#include <Renderable.hpp>

namespace Violet{
        class Player : public Renderable
        {
                // Configuration Constants
                //TODO: Clean these up somewhat, or at least make them consistent
                static constexpr float speed = 2.1f;
                static const sf::Vector2f drag;
                static const sf::Vector2f gravity;
                static constexpr float SCALE = 100;
                static constexpr float maxSpeed = 750;


                sf::Vector2f velocity;

                sf::RectangleShape gfx;

                /*
                 * Apply a drag calculation so that you come to a stop when the
                 * keys have been all released
                 */
                void applyDrag(float elapsedTime);

                /*
                 * Caps the speed at maxSpeed so that you don't start phasing
                 * through walls and other weirdness like that
                 */
                void capSpeed(float elapsedTime);

                /*
                 * Actually performs the move, while also checking for
                 * collisions with walls in and resolves such collisions
                 */
                void move(const sf::Vector2f& moveDir);

                public:
                        Player(sf::Vector2f init_pos);

                        ~Player() override;
                        void render(std::function<void(sf::Drawable&)> draw) override;

                        /*
                         * Called once per frame, used to update
                         * player state and check for input
                         */
                        void update(float elapsedTime);
        };
};

#endif
