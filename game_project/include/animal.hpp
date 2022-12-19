#ifndef __ANIMAL_HPP__
#define __ANIMAL_HPP__

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "global.hpp"
#include <vector>

class Animal : public sf::Sprite{
private:
    int iter_anim;
    bool lakon_move;
    char orientation;  // for determine wolf orientation, 'h' for horizontal, 'v' for vertical
    char command;
    char last_command;
    float speed;
    sf::Clock clk;
    sf::Vector2f vel;
    sf::Vector2i spriteSize_ver;
    sf::Texture texture;
    std::vector<sf::IntRect> moveUpAnim;
    std::vector<sf::IntRect> moveLeftAnim;
    std::vector<sf::IntRect> moveDownAnim;
    std::vector<sf::IntRect> moveRightAnim;

public:
    Animal(float spd, sf::Vector2f init_pos){
        Animal::iter_anim = 0;
        Animal::lakon_move = false;
        Animal::speed = spd;
        Animal::setPosition(init_pos);
        Animal::vel = sf::Vector2f(0.f,0.f);
        Animal::texture.loadFromFile("assets/images/wolf.png");
        Animal::setTexture(texture);
        Animal::orientation = 'v';
        Animal::spriteSize_ver = sf::Vector2i(32, 64);  // for vertical orientation
        Animal::setTextureRect(sf::IntRect(0*spriteSize_ver.x, 0*spriteSize_ver.y, spriteSize_ver.x, spriteSize_ver.y));
        Animal::setOrigin(spriteSize_ver.x / 2, spriteSize_ver.y / 2);  // for vertical orientation
        Animal::setScale(sf::Vector2f(1.f, 1.f));

        moveUpAnim.reserve(4);
        moveDownAnim.reserve(4);
        moveLeftAnim.reserve(5);
        moveRightAnim.reserve(5);
        for(int i=0; i<4; i++){
            moveDownAnim[i] = sf::IntRect(i*spriteSize_ver.x, 2*spriteSize_ver.y, spriteSize_ver.x, spriteSize_ver.y);
            moveUpAnim[i] = sf::IntRect((i+5)*spriteSize_ver.x, 2*spriteSize_ver.y, spriteSize_ver.x, spriteSize_ver.y);
        }
        for(int i=0; i<5; i++){
            moveRightAnim[i] = sf::IntRect((i+5)*spriteSize_ver.y, 3*spriteSize_ver.x, spriteSize_ver.y, spriteSize_ver.x);
            moveLeftAnim[i] = sf::IntRect((i+5)*spriteSize_ver.y, 9*spriteSize_ver.x, spriteSize_ver.y, spriteSize_ver.x);
        }
        // // check
        // for(int i=0; i<5; i++){
        //     printf("left:%d, top:%d, width:%d, height:%d\n", moveLeftAnim[i].left, moveLeftAnim[i].top, moveLeftAnim[i].width, moveLeftAnim[i].height);
        // }

    }

    void movement(sf::Vector2f lakon_pos){
        Animal::lakon_move = false;
        Animal::command = NULL;
        if((lakon_pos.y - Animal::getPosition().y) < -40){
            Animal::vel.y = -1;
            Animal::lakon_move = true;
            Animal::command = 'w';
            Animal::last_command = 'w';
            Animal::orientation = 'v';
        }
        else if((lakon_pos.y - Animal::getPosition().y) > 40){
            Animal::vel.y = 1;
            Animal::lakon_move = true;
            Animal::command = 's';
            Animal::last_command = 's';
            Animal::orientation = 'v';
        }
        else Animal::vel.y = 0;
        if((lakon_pos.x - Animal::getPosition().x) < -40){
            Animal::vel.x = -1;
            Animal::lakon_move = true;
            Animal::command = 'a';
            Animal::last_command = 'a';
            Animal::orientation = 'h';
        }
        else if((lakon_pos.x - Animal::getPosition().x) > 40){
            Animal::vel.x = 1;
            Animal::lakon_move = true;
            Animal::command = 'd';
            Animal::last_command = 'd';
            Animal::orientation = 'h';
        }
        else Animal::vel.x = 0;

        // add on conditional, for fixing orientation never 'v'
        // if(abs(lakon_pos.x - Animal::getPosition().x) < 10 ) Animal::orientation = 'v';
        // printf("lakon: %f,   animal: %f\n%d\n", lakon_pos.x, Animal::getPosition().x, abs(lakon_pos.x - Animal::getPosition().x));

        if(Animal::lakon_move){
            Animal::vel = global::normalize(Animal::vel);
            Animal::vel.x = Animal::vel.x * Animal::speed;
            Animal::vel.y = Animal::vel.y * Animal::speed;
            Animal::move(Animal::vel);
            Animal::movement_animation();
        }else{
            switch(Animal::last_command){
                case 'w':
                    Animal::setTextureRect(moveUpAnim[3]);
                    Animal::setOrigin(spriteSize_ver.x / 2, spriteSize_ver.y / 2);
                    break;
                case 's':
                    Animal::setTextureRect(moveDownAnim[3]);
                    Animal::setOrigin(spriteSize_ver.x / 2, spriteSize_ver.y / 2);
                    break;
                case 'a':
                    Animal::setTextureRect(moveLeftAnim[0]);
                    Animal::setOrigin(spriteSize_ver.y / 2, spriteSize_ver.x / 2);
                    break;
                case 'd':
                    Animal::setTextureRect(moveRightAnim[0]);
                    Animal::setOrigin(spriteSize_ver.y / 2, spriteSize_ver.x / 2);
                    break;
                default:
                    Animal::setTextureRect(moveDownAnim[3]);
            }
        }
    }

    void movement_animation(){
        if(clk.getElapsedTime().asSeconds() > 0.1f){
            if(Animal::orientation == 'v'){
                if(Animal::iter_anim >= 3) iter_anim = -1;  // 0 - 3
                iter_anim++;

                switch(Animal::command){
                    case 'w':
                        Animal::setTextureRect(moveUpAnim[iter_anim]);
                        Animal::setOrigin(spriteSize_ver.x / 2, spriteSize_ver.y / 2);
                        break;
                    case 's':
                        Animal::setTextureRect(moveDownAnim[iter_anim]);
                        Animal::setOrigin(spriteSize_ver.x / 2, spriteSize_ver.y / 2);
                        break;
                }
            } else if(Animal::orientation == 'h'){
                if(Animal::iter_anim >= 4) iter_anim = -1;  // 0 - 4
                iter_anim++;

                switch(Animal::command){
                    case 'a':
                        Animal::setTextureRect(moveLeftAnim[iter_anim]);
                        Animal::setOrigin(spriteSize_ver.y / 2, spriteSize_ver.x / 2);
                        break;
                    case 'd':
                        Animal::setTextureRect(moveRightAnim[iter_anim]);
                        Animal::setOrigin(spriteSize_ver.y / 2, spriteSize_ver.x / 2);
                        break;
                }
            }
            clk.restart();

            // check
            printf("iter: %d, command : %c, orientation: %c\n", Animal::iter_anim, Animal::command, Animal::orientation);
        }
    } 
};

#endif