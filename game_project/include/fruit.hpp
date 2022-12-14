#ifndef __FRUIT_HPP__
#define __FRUIT_HPP__

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "global.hpp"
#include <vector>

class Fruit : public sf::Sprite{
private:
    bool fruit_move;
    float speed;
    sf::Clock clk;
    sf::Vector2f vel;
    sf::Vector2i spriteSize;
    sf::Texture texture;
public:
    Fruit(float spd = 15){
        Fruit::fruit_move = true;
        Fruit::speed = spd;
        Fruit::vel = sf::Vector2f(0.f, 0.f);
        Fruit::texture.loadFromFile("assets/images/pisang.png");
        Fruit::setTexture(texture);
        Fruit::spriteSize = sf::Vector2i(20, 32);
        // Fruit::setPosition(sf::Vector2f(lakon_pos));
        Fruit::setOrigin(spriteSize.x / 2, spriteSize.y / 2);
        Fruit::setScale(sf::Vector2f(2.f, 2.f));
    }

    void determine_vel(sf::Vector2f lakon_pos, sf::Vector2i mouse_pos){
        float vel_x_raw, vel_y_raw, vel_raw;

        vel_x_raw = mouse_pos.x - lakon_pos.x;
        vel_y_raw = mouse_pos.y - lakon_pos.y;

        vel_raw = sqrt(pow(vel_x_raw, 2) + pow(vel_y_raw, 2));
        Fruit::vel.x = vel_x_raw / vel_raw;
        Fruit::vel.y = vel_y_raw / vel_raw;

        Fruit::vel.x = Fruit::vel.x * Fruit::speed;
        Fruit::vel.y = Fruit::vel.y * Fruit::speed;

        // printf("vel_x: %f\nvel_y: %f", Fruit::vel.x, Fruit::vel.y);
    }

    void movement(){
        if(Fruit::fruit_move){
            Fruit::move(Fruit::vel);
            Fruit::movement_animation();
        }
    }

    void movement_animation(){
        if(clk.getElapsedTime().asSeconds() > 0.1f){
            Fruit::rotate(45.f);
            clk.restart();
        }
    }

    bool isInFrame(){
        if(Fruit::getPosition().x <= global::width_window
            && Fruit::getPosition().y <= global::height_window){
                return true;
        } return false;
    }
};


#endif