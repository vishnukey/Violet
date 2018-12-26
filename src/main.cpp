#include <chrono>
#include <string>
#include <vector>
#include <array>
#include <memory>
#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>

constexpr int TILE_SIZE = 32;
constexpr int WINDOW_SIZE = 800;
constexpr int TILES_PER_LINE = WINDOW_SIZE / TILE_SIZE;

sf::Vector2f velocity;
sf::Vector2f gravity(0, 2);
sf::Vector2f drag(.1,0);
float scale = 100;
float speed = 2.1f;

std::array<std::string, TILES_PER_LINE> map = {
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

std::vector<std::unique_ptr<sf::Shape>> tiles;
sf::Vector2f tileDim(TILE_SIZE, TILE_SIZE);

namespace Pallette {
        using namespace sf;

        const Color wall   = {180, 160, 0  }; // gold
        const Color sky    = {80 , 140, 200}; // light blue
        const Color player = {200, 50 , 50 }; // red
        const Color coin   = {230, 200, 0  }; // Bright Yellow
};

template <typename T>
T sign(T x){
        if (x > 0) return 1;
        if (x == 0) return 0;
        if (x < 0) return -1;

        return 0;
}

sf::RectangleShape& makePlayer(std::vector<std::unique_ptr<sf::Shape>>& tiles, sf::Vector2f pos, sf::Color col)
{
        auto player = std::make_unique<sf::RectangleShape>(tileDim);
        player->setPosition(pos);
        player->setFillColor(col);
        auto& tmp = *player;
        tiles.push_back(std::move(player));
        return tmp;
}

void loadMap(std::array<std::string, TILES_PER_LINE>& map, std::vector<std::unique_ptr<sf::Shape>>& tiles)
{
        for (int i = 0; i < map.size(); i++){
                for (int j = 0; j < map[i].size(); j++){
                        switch (map[i][j]){
                                case '#':
                                        {
                                                auto wall = std::make_unique<sf::RectangleShape>(sf::Vector2f(tileDim.x - 2, tileDim.y - 2));
                                                wall->setPosition(sf::Vector2f(j * TILE_SIZE + 1, i * TILE_SIZE + 1));
                                                wall->setFillColor(Pallette::wall);
                                                tiles.push_back(std::move(wall));
                                        }
                                        break;
                                case '.':
                                        {
                                                auto sky = std::make_unique<sf::RectangleShape>(sf::Vector2f(tileDim.x - 2, tileDim.y - 2));
                                                sky->setPosition(sf::Vector2f(j * TILE_SIZE + 1, i * TILE_SIZE + 1));
                                                sky->setFillColor(Pallette::sky);
                                                tiles.push_back(std::move(sky));
                                        }
                                        break;
                                case 'o':
                                        {
                                                auto coin = std::make_unique<sf::CircleShape>(TILE_SIZE / 2 - 4);
                                                auto sky = std::make_unique<sf::RectangleShape>(sf::Vector2f(tileDim.x - 2, tileDim.y - 2));
                                                coin->setPosition(sf::Vector2f(j * TILE_SIZE + 4, i * TILE_SIZE + 4));
                                                sky->setPosition(sf::Vector2f(j * TILE_SIZE + 1, i * TILE_SIZE + 1));
                                                coin->setFillColor(Pallette::coin);
                                                sky->setFillColor(Pallette::sky);

                                                tiles.push_back(std::move(sky));
                                                tiles.push_back(std::move(coin));
                                        }
                                        break;
                                default:
                                        break;
                        }
                }
        }
}



int main(void){
        sf::Vector2f acceleration(0, 0);


        /* INITIALIZATION */

        loadMap(map, tiles);

        sf::RectangleShape& player = makePlayer(tiles, sf::Vector2f(32, 256), Pallette::player);

        // Create the main window
        sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "My Game");

        auto previousTime = std::chrono::system_clock::now();
        //auto nowTime = std::chrono::system_clock::now(); //might help with performance by not constantly creating and destorying struct
        

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
                                sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                                window.setView(sf::View(visibleArea));
                        }
                }
                
                /* UPDATE */ 

                sf::Vector2f moveDir(0, 1);

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                        //player.move(0.0f, -speed * elapsedTime);
                        moveDir.y = -1;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && false){
                        //player.move(0, speed * elapsedTime);
                        moveDir.y = 1;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                        //player.move(-speed * elapsedTime, 0);
                        moveDir.x = -1;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                        //player.move(speed * elapsedTime, 0);
                        moveDir.x = 1;
                }

                acceleration = (moveDir * speed + gravity) * scale * elapsedTime;
                sf::Vector2f dragAppl = -sign(velocity.x) * drag * scale * elapsedTime;
                velocity += acceleration;
                if (sign(velocity.x) == sign((velocity + dragAppl).x)) velocity += dragAppl;
                else velocity.x = 0;

                if (fabs(velocity.x) > 500 * elapsedTime) velocity.x = 500 * elapsedTime * sign(velocity.x);
                if (fabsf(velocity.y) > 500 * elapsedTime) velocity.y = 500 * elapsedTime * sign(velocity.y);

                if (fabs(velocity.x) < 0.001) velocity.x = 0;
                if (fabs(velocity.y) < 0.001) velocity.y = 0;

                //Collision Detection
                sf::Vector2f newPos = player.getPosition() + velocity;
                sf::Vector2f oldPos = player.getPosition();

                //Handle x direction
                if (moveDir.x > 0){
                        if (
                                map[(int)(oldPos.y / TILE_SIZE + 0.1)][(int)(newPos.x / TILE_SIZE + 1)] != '.' ||
                                map[(int)(oldPos.y / TILE_SIZE + 0.9)][(int)(newPos.x / TILE_SIZE + 1)] != '.'
                           ){
                                velocity.x = 0;
                        }
                }else{
                        if(
                                map[(int)(oldPos.y / TILE_SIZE + 0.1)][(int)(newPos.x / TILE_SIZE)] != '.' ||
                                map[(int)(oldPos.y / TILE_SIZE + 0.9)][(int)(newPos.x / TILE_SIZE)] != '.'
                          ){
                                velocity.x = 0;
                          }
                }

                //Handle y direction
                if (moveDir.y > 0){
                        if(
                                map[(int)(newPos.y / TILE_SIZE + 1)][(int)(newPos.x / TILE_SIZE + 0.1)] != '.' ||
                                map[(int)(newPos.y / TILE_SIZE + 1)][(int)(newPos.x / TILE_SIZE + 0.9)] != '.'
                          ){
                                velocity.y = 0;
                        }
                } else{
                        if(
                                map[(int)(newPos.y / TILE_SIZE)][(int)(newPos.x / TILE_SIZE + 0.1)] != '.' ||
                                map[(int)(newPos.y / TILE_SIZE)][(int)(newPos.x / TILE_SIZE + 0.9)] != '.'
                          ){
                                velocity.y = 0;
                        }
                }

                player.move(velocity);

                /*DRAW*/

                // Clear screen
                window.clear();
        
                for (auto& tile : tiles){
                        window.draw(*tile);
                }

                // Update the window
                window.display();
        }

        return EXIT_SUCCESS;
}
