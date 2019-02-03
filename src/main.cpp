//STD
#include <chrono>
#include <string>
#include <vector>
#include <array>
#include <memory>
#include <iostream>

//SFML
#include <SFML/Graphics.hpp>

//Violet
#include <Utility.hpp>
#include <Player.hpp>

//Mostly contains the map, for now
std::vector<std::unique_ptr<Violet::Renderable>> renderables;

int main(void){
        /* INITIALIZATION */
        Violet::Util::loadMap(Violet::Constants::map, renderables);
        Violet::Player player(sf::Vector2f(32, 256));

        // Create the main window
        sf::RenderWindow window(
                sf::VideoMode(
                        Violet::Constants::WINDOW_SIZE,
                        Violet::Constants::WINDOW_SIZE),
                "My Game");

        auto previousTime = std::chrono::system_clock::now();
        //auto nowTime = std::chrono::system_clock::now(); //might help with performance by not constantly creating and destorying struct

        auto draw = [&](sf::Drawable& toDraw){ window.draw(toDraw); };

        /* GAME LOOP */
        while (window.isOpen())
        {
                // Timing
                auto now = std::chrono::system_clock::now();
                std::chrono::duration<float> elapsedTimeChrono = now - previousTime;
                previousTime = now;

                float elapsedTime = elapsedTimeChrono.count(); //multiply by this for smooth movement

                // Process events
                sf::Event event;
                while (window.pollEvent(event))
                //if (window.pollEvent(event))
                {
                        // Close window: exit
                        if (event.type == sf::Event::Closed)
                                window.close();

                        if (event.type == sf::Event::Resized)
                        {
                                // update the view to the new size of the window
                                sf::FloatRect visibleArea(
                                        0.f, 0.f,
                                        event.size.width, event.size.height);
                                window.setView(sf::View(visibleArea));
                        }
                }

                /* UPDATE */
                player.update(elapsedTime);

                /*DRAW*/

                // Clear screen
                window.clear();

                for (auto& renderable : renderables){
                        renderable->render(draw);
                }

                player.render(draw);

                // Update the window
                window.display();
        }

        return EXIT_SUCCESS;
}
