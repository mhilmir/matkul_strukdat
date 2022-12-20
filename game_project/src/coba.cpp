#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include "../include/global.hpp"


int main(){
    sf::Vector2f pos_inside;
    sf::Vector2f pos_outside;
    while(1){
        // pos_inside = global::generate_position('i');
        pos_outside = global::generate_position('o');
        // printf("pos_x_in:%f, pos_y_in:%f\n\n", pos_inside.x, pos_inside.y);
        printf("pos_x_out:%f, pos_y_out:%f\n\n", pos_outside.x, pos_outside.y);
    }


}