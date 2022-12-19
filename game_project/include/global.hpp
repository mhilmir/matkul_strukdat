#ifndef __GLOBAL_HPP__
#define __GLOBAL_HPP__

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <cmath>

namespace global{
    // window size
    unsigned int width_window = 1280;
    unsigned int height_window = 720;

    // normalize function for vel
    sf::Vector2f normalize(sf::Vector2f vector)
    {
        constexpr auto units_in_last_place = 2;
        auto norm = std::sqrt((vector.x * vector.x) + (vector.y * vector.y));
        // Prevent division by zero
        if (norm <= std::numeric_limits<float>::epsilon() * norm * units_in_last_place
            || norm < std::numeric_limits<float>::min())
        {
            return sf::Vector2f{};
        }
        return vector / norm;
    }
}

#endif