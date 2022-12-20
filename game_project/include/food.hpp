#ifndef __FRUIT_HPP__
#define __FRUIT_HPP__

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "global.hpp"
#include <vector>

class Food : public sf::Sprite{
private:
    bool fruit_move;
    float speed;
    float clk_threshold;
    sf::Clock clk;
    sf::Vector2f vel;
    sf::Vector2i spriteSize;
    sf::Texture food_texture;
    // sf::Texture 
    // sf::Sprite arrow;
public:
    Food(float spd = 10){
        Food::clk_threshold = 0.2f;
        Food::fruit_move = true;
        Food::speed = spd;
        Food::vel = sf::Vector2f(0.f, 0.f);
        Food::food_texture.loadFromFile("assets/images/MeatnOthers.png");
        Food::setTexture(food_texture);
        Food::spriteSize = sf::Vector2i(16, 16);
        // Food::setPosition(sf::Vector2f(lakon_pos));
        Food::setTextureRect(sf::IntRect(0*spriteSize.x, 0*spriteSize.y, spriteSize.x, spriteSize.y));
        Food::setOrigin(spriteSize.x / 2, spriteSize.y / 2);
        Food::setScale(sf::Vector2f(1.75f, 1.75f));
        // Food::arrow.
    }

    void determine_vel(sf::Vector2f lakon_pos, sf::Vector2i mouse_pos){
        float vel_x_raw, vel_y_raw, vel_raw;

        vel_x_raw = mouse_pos.x - lakon_pos.x;
        vel_y_raw = mouse_pos.y - lakon_pos.y;

        vel_raw = sqrt(pow(vel_x_raw, 2) + pow(vel_y_raw, 2));
        Food::vel.x = vel_x_raw / vel_raw;
        Food::vel.y = vel_y_raw / vel_raw;

        Food::vel.x = Food::vel.x * Food::speed;
        Food::vel.y = Food::vel.y * Food::speed;
    }

    void movement(){
        if(Food::fruit_move){
            Food::move(Food::vel);
            Food::movement_animation();
        }
    }

    void movement_animation(){
        if(clk.getElapsedTime().asSeconds() > Food::clk_threshold){
            Food::rotate(45.f);
            clk.restart();
        }
    }

    bool isInFrame(){
        if(Food::getPosition().x <= global::width_window
            && Food::getPosition().y <= global::height_window){
                return true;
        } return false;
    }
};


#endif