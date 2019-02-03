#include <Utility.hpp>
#include <Tile.hpp>
#include <Coin.hpp>

namespace Violet{
        namespace Util{
                void loadMap(const std::array<std::string, Violet::Constants::TILES_PER_LINE>& map, std::vector<std::unique_ptr<Violet::Renderable>>& renderables)
                {
                        for (int i = 0; i < map.size(); i++){
                                for (int j = 0; j < map[i].size(); j++){
                                        switch (map[i][j]){
                                                case '#':
                                                        renderables.push_back(
                                                                std::make_unique<Violet::Tile>(
                                                                        Violet::Pallette::wall,
                                                                        sf::Vector2f(
                                                                                j * Violet::Constants::TILE_SIZE + 1,
                                                                                i * Violet::Constants::TILE_SIZE + 1)));
                                                        break;
                                                case '.':
                                                        renderables.push_back(
                                                                std::make_unique<Violet::Tile>(
                                                                        Violet::Pallette::sky,
                                                                        sf::Vector2f(
                                                                                j * Violet::Constants::TILE_SIZE + 1,
                                                                                i * Violet::Constants::TILE_SIZE + 1)));
                                                        break;
                                                case 'o':
                                                        renderables.push_back(
                                                                std::make_unique<Violet::Coin>(
                                                                        sf::Vector2f(
                                                                                j * Violet::Constants::TILE_SIZE + 1,
                                                                                i * Violet::Constants::TILE_SIZE + 1)));
                                                        break;
                                                default:
                                                        break;
                                        }
                                }
                        }
                }
        }
}
