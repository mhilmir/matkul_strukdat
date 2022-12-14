#ifndef __LAKON_HPP__
#define __LAKON_HPP__

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "global.hpp"
#include <vector>

class Lakon : public sf::Sprite{
private:
    float health;
    int iter_anim;
    bool lakon_move;
    char command;
    char last_command;
    float speed;
    float clk_threshold;
    sf::Clock clk;
    sf::Vector2f vel;
    sf::Vector2i spriteSize;
    sf::Texture texture;
    std::vector<sf::IntRect> moveUpAnim;
    std::vector<sf::IntRect> moveLeftAnim;
    std::vector<sf::IntRect> moveDownAnim;
    std::vector<sf::IntRect> moveRightAnim;

public:
    Lakon(float spd = 5){
        Lakon::health = 100.f;
        Lakon::clk_threshold = 0.05f;
        Lakon::iter_anim = 0;
        Lakon::lakon_move = false;
        Lakon::speed = spd;
        Lakon::vel = sf::Vector2f(0.f,0.f);
        Lakon::texture.loadFromFile("assets/images/lakon.png");
        Lakon::setTexture(texture);
        Lakon::spriteSize = sf::Vector2i(32, 64);
        Lakon::setTextureRect(sf::IntRect(0*spriteSize.x, 0*spriteSize.y, spriteSize.x, spriteSize.y));
        Lakon::setPosition(global::width_window/2, global::height_window/2);
        Lakon::setOrigin(spriteSize.x / 2, spriteSize.y / 2);
        Lakon::setScale(sf::Vector2f(1.1f, 1.1f));

        moveUpAnim.reserve(8);
        moveLeftAnim.reserve(8);
        moveDownAnim.reserve(8);
        moveRightAnim.reserve(8);
        for(int i=0; i<8; i++){
            moveDownAnim[i] = sf::IntRect(i*spriteSize.x, 0*spriteSize.y, spriteSize.x, spriteSize.y);
            moveUpAnim[i] = sf::IntRect(i*spriteSize.x, 1*spriteSize.y, spriteSize.x, spriteSize.y);
            moveRightAnim[i] = sf::IntRect(i*spriteSize.x, 2*spriteSize.y, spriteSize.x, spriteSize.y);
            moveLeftAnim[i] = sf::IntRect(i*spriteSize.x, 3*spriteSize.y, spriteSize.x, spriteSize.y);
        }
    }

    float get_health(){
        return Lakon::health;
    }

    void reduceHealth(float damage){
        if(Lakon::health <= 0){
            Lakon::health = 0;
        } else{
            Lakon::health = Lakon::health + damage;
        }
    }

    void displayHealth(sf::RenderWindow& window){
        sf::RectangleShape rectangle(sf::Vector2f((Lakon::health/100) * 220.f, 30.f));
        rectangle.setPosition(sf::Vector2f(1600.f, 40.f));
        
        window.draw(rectangle);
    }

    void movement(){
        Lakon::lakon_move = false;
        Lakon::command = '\0';
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            Lakon::vel.y = -1;
            Lakon::lakon_move = true;
            Lakon::command = 'w';
            Lakon::last_command = 'w';
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            Lakon::vel.y = 1;
            Lakon::lakon_move = true;
            Lakon::command = 's';
            Lakon::last_command = 's';
        }
        else Lakon::vel.y = 0;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            Lakon::vel.x = -1;
            Lakon::lakon_move = true;
            Lakon::command = 'a';
            Lakon::last_command = 'a';
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            Lakon::vel.x = 1;
            Lakon::lakon_move = true;
            Lakon::command = 'd';
            Lakon::last_command = 'd';
        }
        else Lakon::vel.x = 0;

        if(Lakon::lakon_move){
            Lakon::vel = global::normalize(Lakon::vel);
            Lakon::vel.x = Lakon::vel.x * Lakon::speed;
            Lakon::vel.y = Lakon::vel.y * Lakon::speed;
            Lakon::move(Lakon::vel);
            Lakon::movement_animation();
        }else{  // if there is no command yet, set animation to "standing" mode
            switch(Lakon::last_command){
                case 'w':
                    Lakon::setTextureRect(moveUpAnim[0]);
                    break;
                case 's':
                    Lakon::setTextureRect(moveDownAnim[0]);
                    break;
                case 'a':
                    Lakon::setTextureRect(moveLeftAnim[0]);
                    break;
                case 'd':
                    Lakon::setTextureRect(moveRightAnim[0]);
                    break;
                default:
                    Lakon::setTextureRect(moveDownAnim[0]);
            }
        }
    }

    void movement_animation(){
        if(clk.getElapsedTime().asSeconds() > Lakon::clk_threshold){
            if(Lakon::iter_anim == 7) iter_anim = -1;  // 0 to 7
            iter_anim++;
            // printf("%d\n", iter_anim);

            switch(Lakon::command){
                case 'w':
                    Lakon::setTextureRect(moveUpAnim[iter_anim]);
                    break;
                case 's':
                    Lakon::setTextureRect(moveDownAnim[iter_anim]);
                    break;
                case 'a':
                    Lakon::setTextureRect(moveLeftAnim[iter_anim]);
                    break;
                case 'd':
                    Lakon::setTextureRect(moveRightAnim[iter_anim]);
                    break;
            }
            clk.restart();
        }
    } 
};

#endif