#ifndef UTILITY__H__
#define UTILITY__H__

//STD
#include <array>
#include <string>
#include <vector>
#include <memory>

//Violet
#include <Constants.hpp>
#include <Renderable.hpp>


namespace Violet{
        namespace Util{
                /*
                 * Gets the sign of a numeric value
                 */
                template <typename T>
                T sign(T x){
                        if (x > 0) return 1;
                        if (x == 0) return 0;
                        if (x < 0) return -1;

                        return 0;
                }

                /*
                 * Loads a map into a container of renderables. Helpful for
                 * getting things going
                 */
                void loadMap(
                        const std::array<std::string, Violet::Constants::TILES_PER_LINE>& map,
                        std::vector<std::unique_ptr<Violet::Renderable>>& renderables);
        };
};

#endif
