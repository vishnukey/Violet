//STD
#include <cmath>

//SFML
#include <SFML/Window/Keyboard.hpp>

//Violet
#include <Player.hpp>
#include <Utility.hpp>
#include <Constants.hpp>

namespace Violet{
                const sf::Vector2f Player::drag = {.1,0};
                const sf::Vector2f Player::gravity = {0, 2};

                Player::Player(sf::Vector2f init_pos)
                {
                        gfx = sf::RectangleShape(Constants::tileDim);
                        gfx.setPosition(init_pos);
                        gfx.setFillColor(Pallette::player);
                }

                Player::~Player()
                {

                }

                void Player::render(std::function<void(sf::Drawable&)> draw)
                {
                        draw(gfx);
                }

                void Player::update(float elapsedTime)
                {
                        sf::Vector2f moveDir(0, 1);

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                                //gfx.move(0.0f, -speed * elapsedTime);
                                moveDir.y = -1;
                        }
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                                //gfx.move(0, speed * elapsedTime);
                                moveDir.y = 1;
                        }
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                                //gfx.move(-speed * elapsedTime, 0);
                                moveDir.x = -1;
                        }
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                                //gfx.move(speed * elapsedTime, 0);
                                moveDir.x = 1;
                        }

                        //physics
                        sf::Vector2f acceleration =
                                (moveDir * speed + gravity) *
                                (SCALE * elapsedTime);
                        velocity += acceleration;

                        applyDrag(elapsedTime);
                        capSpeed(elapsedTime);

                        move(moveDir);
                }

                void Player::applyDrag(float elapsedTime)
                {
                        //drag
                        sf::Vector2f dragAppl =
                                -Util::sign(velocity.x) *
                                drag *
                                (Player::SCALE * elapsedTime);
                        if (Util::sign(velocity.x) == Util::sign((velocity + dragAppl).x)) velocity += dragAppl;
                        else velocity.x = 0;
                }

                void Player::capSpeed(float elapsedTime)
                {
                        // Bounds checking & value clamping
                        if (fabs(velocity.x) > maxSpeed * elapsedTime)
                                velocity.x = maxSpeed * elapsedTime * Util::sign(velocity.x);
                        if (fabs(velocity.y) > maxSpeed * elapsedTime)
                                velocity.y = maxSpeed * elapsedTime * Util::sign(velocity.y);

                        if (fabs(velocity.x) < 0.001) velocity.x = 0;
                        if (fabs(velocity.y) < 0.001) velocity.y = 0;
                }

                void Player::move(const sf::Vector2f& moveDir)
                {
                        //Collision Detection
                        sf::Vector2f newPos = gfx.getPosition() + velocity; // TODO: Don't use graphics for positioning
                        sf::Vector2f oldPos = gfx.getPosition();

                        //Handle x direction
                        if (moveDir.x > 0){
                                if (
                                        Constants::map[(int)(oldPos.y / Constants::TILE_SIZE + 0.1)][(int)(newPos.x / Constants::TILE_SIZE + 1)] != '.' ||
                                        Constants::map[(int)(oldPos.y / Constants::TILE_SIZE + 0.9)][(int)(newPos.x / Constants::TILE_SIZE + 1)] != '.'
                                   ){
                                        velocity.x = 0;
                                }
                        }else{
                                if(
                                        Constants::map[(int)(oldPos.y / Constants::TILE_SIZE + 0.1)][(int)(newPos.x / Constants::TILE_SIZE)] != '.' ||
                                        Constants::map[(int)(oldPos.y / Constants::TILE_SIZE + 0.9)][(int)(newPos.x / Constants::TILE_SIZE)] != '.'
                                  ){
                                        velocity.x = 0;
                                  }
                        }

                        //Handle y direction
                        if (moveDir.y > 0){
                                if(
                                        Constants::map[(int)(newPos.y / Constants::TILE_SIZE + 1)][(int)(newPos.x / Constants::TILE_SIZE + 0.1)] != '.' ||
                                        Constants::map[(int)(newPos.y / Constants::TILE_SIZE + 1)][(int)(newPos.x / Constants::TILE_SIZE + 0.9)] != '.'
                                  ){
                                        velocity.y = 0;
                                }
                        } else{
                                if(
                                        Constants::map[(int)(newPos.y / Constants::TILE_SIZE)][(int)(newPos.x / Constants::TILE_SIZE + 0.1)] != '.' ||
                                        Constants::map[(int)(newPos.y / Constants::TILE_SIZE)][(int)(newPos.x / Constants::TILE_SIZE + 0.9)] != '.'
                                  ){
                                        velocity.y = 0;
                                }
                        }

                        gfx.move(velocity);
                }
};
