#ifndef __GLOBAL_HPP__
#define __GLOBAL_HPP__

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <cmath>

namespace global{
    // window size
    unsigned int width_window = 1920;
    unsigned int height_window = 1080;

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

    // generate random coordinate outside the screen
    sf::Vector2f generate_position(char c){  // 'i' for inside the screen, 'o' for outside the screen
        float pos_x, pos_y;
        if(c == 'i'){
            pos_x = rand()%global::width_window + 1;
            pos_y = rand()%global::height_window + 1;

            return sf::Vector2f(pos_x, pos_y);

        }else if(c == 'o'){
            pos_x = rand()%(global::width_window + 500) - 250;
            pos_y = rand()%(global::height_window + 500) - 250;
            if(pos_x > (global::width_window + 250)) pos_x = global::width_window + 250;  // pencegahan aja, entah kenapa kadang-kadang besar banget
            if(pos_y > (global::width_window + 250)) pos_y = global::width_window + 250;  // pencegahan aja, entah kenapa kadang-kadang besar banget
            // printf("pos_x:%f\n", pos_x);

            if((pos_x >= 0 && pos_x <= global::width_window) && (pos_y >= 0 && pos_y <= global::height_window)){
                int R = rand()%2;
                int r = rand()%2;
                switch(R){
                    case 0:{
                        if(r == 0) pos_x = global::width_window + 250;
                        else if(r == 1) pos_x = -250;
                        // printf("pos_x:%f\n", pos_x);
                        break;
                    }
                    case 1:{
                        if(r == 0) pos_y = global::height_window + 250;
                        else if(r == 1) pos_y = -250;
                        // printf("pos_x:%f\n", pos_x);
                        break;
                    }
                }
            }
            // printf("pos_x:%f\n", pos_x);

            return sf::Vector2f(pos_x, pos_y);

        }else{
            return sf::Vector2f(0.f, 0.f);
        }
    }
}

#endif