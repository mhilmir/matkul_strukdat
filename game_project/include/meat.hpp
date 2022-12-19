#ifndef __FRUIT_HPP__
#define __FRUIT_HPP__

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "global.hpp"
#include <vector>

class Meat : public sf::Sprite{
private:
    bool fruit_move;
    float speed;
    sf::Clock clk;
    sf::Vector2f vel;
    sf::Vector2i spriteSize;
    sf::Texture texture;
public:
    Meat(float spd = 10){
        Meat::fruit_move = true;
        Meat::speed = spd;
        Meat::vel = sf::Vector2f(0.f, 0.f);
        Meat::texture.loadFromFile("assets/images/MeatnOthers.png");
        Meat::setTexture(texture);
        Meat::spriteSize = sf::Vector2i(16, 16);
        // Meat::setPosition(sf::Vector2f(lakon_pos));
        Meat::setTextureRect(sf::IntRect(0*spriteSize.x, 0*spriteSize.y, spriteSize.x, spriteSize.y));
        Meat::setOrigin(spriteSize.x / 2, spriteSize.y / 2);
        Meat::setScale(sf::Vector2f(1.5f, 1.5f));
    }

    void determine_vel(sf::Vector2f lakon_pos, sf::Vector2i mouse_pos){
        float vel_x_raw, vel_y_raw, vel_raw;

        vel_x_raw = mouse_pos.x - lakon_pos.x;
        vel_y_raw = mouse_pos.y - lakon_pos.y;

        vel_raw = sqrt(pow(vel_x_raw, 2) + pow(vel_y_raw, 2));
        Meat::vel.x = vel_x_raw / vel_raw;
        Meat::vel.y = vel_y_raw / vel_raw;

        Meat::vel.x = Meat::vel.x * Meat::speed;
        Meat::vel.y = Meat::vel.y * Meat::speed;

        printf("vel_x: %f\nvel_y: %f", Meat::vel.x, Meat::vel.y);
    }

    void movement(){
        if(Meat::fruit_move){
            Meat::move(Meat::vel);
            Meat::movement_animation();
        }
    }

    void movement_animation(){
        if(clk.getElapsedTime().asSeconds() > 0.05f){
            Meat::rotate(45.f);
            clk.restart();
        }
    }

    bool isInFrame(){
        if(Meat::getPosition().x <= global::width_window
            && Meat::getPosition().y <= global::height_window){
                return true;
        } return false;
    }
};


#endif