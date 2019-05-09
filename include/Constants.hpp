#ifndef CONSTANTS__H__
#define CONSTANTS__H__

//STD
#include <array>
#include <string>

//SFML
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

namespace Violet{
        namespace Constants{
                constexpr int TILE_SIZE = 32;
                constexpr int WINDOW_SIZE = 800;
                constexpr int TILES_PER_LINE = WINDOW_SIZE / TILE_SIZE;
                const sf::Vector2f tileDim(TILE_SIZE, TILE_SIZE);

                /*
                 * Current map of the game, will probs change soon
                 * . is sky
                 * # is wall
                 * o is coin
                 */
                // TODO: parse this into a sane structure that maps Index => Tile Object
                const std::array<std::string, TILES_PER_LINE> map = {
                        "#########################",
                        "#.......................#",
                        "#.................#.....#",
                        "#...........ooooo#......#",
                        "#...........#####.......#",
                        "#...######..............#",
                        "#...######..............#",
                        "#..........o............#",
                        "#..........##...........#",
                        "#..........##...........#",
                        "#.............o.........#",
                        "#.............##........#",
                        "#.............##........#",
                        "#................o......#",
                        "#................##.....#",
                        "#................##.....#",
                        "#...oooooo..............#",
                        "##################.######",
                        "##################.######",
                        "##################.######",
                        "#..................#oooo#",
                        "#..ooo.....#########oooo#",
                        "#..ooo..............oooo#",
                        "#...................oooo#",
                        "#########################"
                };
        };

        namespace Pallette {
                using namespace sf;

                const Color wall   = {180, 160, 0  }; // gold
                const Color sky    = {80 , 140, 200}; // light blue
                const Color player = {200, 50 , 50 }; // red
                const Color coin   = {230, 200, 0  }; // Bright Yellow
        };
};

#endif
