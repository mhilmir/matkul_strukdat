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
    int iter_anim;
    bool lakon_move;
    char whereToMove;
    float speed;
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
        Lakon::iter_anim = 0;
        Lakon::lakon_move = false;
        Lakon::speed = spd;
        Lakon::vel = sf::Vector2f(0.f,0.f);
        Lakon::texture.loadFromFile("assets/images/lakon.png");
        Lakon::setTexture(texture);
        Lakon::spriteSize = sf::Vector2i(64, 64);
        Lakon::setTextureRect(sf::IntRect(4*spriteSize.x, 2*spriteSize.y, spriteSize.x, spriteSize.y));
        Lakon::setPosition(global::width_window/2, global::height_window/2);
        Lakon::setOrigin(spriteSize.x / 2, spriteSize.y / 2);
        Lakon::setScale(sf::Vector2f(1.f, 1.f));

        moveUpAnim.reserve(9);
        moveLeftAnim.reserve(9);
        moveDownAnim.reserve(9);
        moveRightAnim.reserve(9);
        for(int i=0; i<9; i++){
            moveUpAnim[i] = sf::IntRect(i*spriteSize.x, 8*spriteSize.y, spriteSize.x, spriteSize.y);
            moveLeftAnim[i] = sf::IntRect(i*spriteSize.x, 9*spriteSize.y, spriteSize.x, spriteSize.y);
            moveDownAnim[i] = sf::IntRect(i*spriteSize.x, 10*spriteSize.y, spriteSize.x, spriteSize.y);
            moveRightAnim[i] = sf::IntRect(i*spriteSize.x, 11*spriteSize.y, spriteSize.x, spriteSize.y);
        }
    }

    void movement(){
        Lakon::lakon_move = false;
        Lakon::whereToMove = NULL;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            Lakon::vel.y = -1;
            Lakon::lakon_move = true;
            Lakon::whereToMove = 'w';
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            Lakon::vel.y = 1;
            Lakon::lakon_move = true;
            Lakon::whereToMove = 's';
        }
        else Lakon::vel.y = 0;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            Lakon::vel.x = -1;
            Lakon::lakon_move = true;
            Lakon::whereToMove = 'a';
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            Lakon::vel.x = 1;
            Lakon::lakon_move = true;
            Lakon::whereToMove = 'd';
        }
        else Lakon::vel.x = 0;

        if(Lakon::lakon_move){
            Lakon::vel = global::normalize(Lakon::vel);
            Lakon::vel.x = Lakon::vel.x * Lakon::speed;
            Lakon::vel.y = Lakon::vel.y * Lakon::speed;
            Lakon::move(Lakon::vel);
            Lakon::movement_animation();
        }
    }

    void movement_animation(){
        if(clk.getElapsedTime().asSeconds() > 0.1f){
            if(Lakon::iter_anim == 8) iter_anim = -1;
            iter_anim++;
            // printf("%d\n", iter_anim);

            switch(Lakon::whereToMove){
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