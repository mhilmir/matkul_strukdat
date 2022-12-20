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
    float health;
    int iter_move_anim;
    int iter_bite_anim;
    bool lakon_move;
    char orientation;  // for determine wolf orientation, 'h' for horizontal, 'v' for vertical
    char command;
    char last_command;
    float speed;
    float clk_threshold;
    sf::Clock clk;
    sf::Vector2f vel;
    sf::Vector2i spriteSize_ver;
    sf::Texture texture;
    std::vector<sf::IntRect> moveUpAnim;
    std::vector<sf::IntRect> moveLeftAnim;
    std::vector<sf::IntRect> moveDownAnim;
    std::vector<sf::IntRect> moveRightAnim;
    std::vector<sf::IntRect> biteUpAnim;
    std::vector<sf::IntRect> biteDownAnim;
    std::vector<sf::IntRect> biteRightAnim;
    std::vector<sf::IntRect> biteLeftAnim;


public:
    Animal(){
        Animal::health = 100.f;
        Animal::clk_threshold = 0.15f;
        Animal::iter_move_anim = 0;
        Animal::iter_bite_anim = 0;
        Animal::lakon_move = false;
        Animal::vel = sf::Vector2f(0.f,0.f);
        Animal::texture.loadFromFile("assets/images/wolf.png");
        Animal::setTexture(texture);
        Animal::orientation = 'v';
        Animal::spriteSize_ver = sf::Vector2i(32, 64);  // for vertical orientation
        Animal::setTextureRect(sf::IntRect(0*spriteSize_ver.x, 0*spriteSize_ver.y, spriteSize_ver.x, spriteSize_ver.y));
        Animal::setOrigin(spriteSize_ver.x / 2, spriteSize_ver.y / 2);  // for vertical orientation
        Animal::setScale(sf::Vector2f(1.1f, 1.1f));

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
        biteUpAnim.reserve(5);
        biteDownAnim.reserve(5);
        biteRightAnim.reserve(5);
        biteLeftAnim.reserve(5);
        for(int i=0; i<5; i++){
            biteUpAnim[i] = sf::IntRect(i*spriteSize_ver.x, 4*spriteSize_ver.y, spriteSize_ver.x, spriteSize_ver.y);
            biteDownAnim[i] = sf::IntRect((i+5)*spriteSize_ver.x, 4*spriteSize_ver.y, spriteSize_ver.x, spriteSize_ver.y);
            biteRightAnim[i] = sf::IntRect((i+5)*spriteSize_ver.y, 5*spriteSize_ver.x, spriteSize_ver.y, spriteSize_ver.x);
            biteLeftAnim[i] = sf::IntRect((i+5)*spriteSize_ver.y, 11*spriteSize_ver.x, spriteSize_ver.y, spriteSize_ver.x);
        }
    }

    void set_speed(float inp_speed){
        Animal::speed = inp_speed;
    }

    float get_health(){
        return Animal::health;
    }

    void reduceHealth(float damage){
        if(Animal::health <= 0){
            Animal::health = 0;
        } else{
            Animal::health = Animal::health + damage;
        }
    }

    void displayHealth(sf::RenderWindow& window){
        sf::RectangleShape rectangle(sf::Vector2f((Animal::health/100) * 50.f, 10.f));
        rectangle.setPosition(sf::Vector2f(Animal::getPosition().x, Animal::getPosition().y - 40));
        
        window.draw(rectangle);
    }


    void movement(sf::Vector2f lakon_pos){
        Animal::lakon_move = false;
        Animal::command = '\0';
        if((lakon_pos.y - Animal::getPosition().y) < -10){
            Animal::vel.y = -1;
            Animal::lakon_move = true;
            Animal::command = 'w';
            Animal::last_command = 'w';
            Animal::orientation = 'v';
        }
        else if((lakon_pos.y - Animal::getPosition().y) > 10){
            Animal::vel.y = 1;
            Animal::lakon_move = true;
            Animal::command = 's';
            Animal::last_command = 's';
            Animal::orientation = 'v';
        }
        else Animal::vel.y = 0;
        if((lakon_pos.x - Animal::getPosition().x) < -10){
            Animal::vel.x = -1;
            Animal::lakon_move = true;
            Animal::command = 'a';
            Animal::last_command = 'a';
            Animal::orientation = 'h';
        }
        else if((lakon_pos.x - Animal::getPosition().x) > 10){
            Animal::vel.x = 1;
            Animal::lakon_move = true;
            Animal::command = 'd';
            Animal::last_command = 'd';
            Animal::orientation = 'h';
        }
        else Animal::vel.x = 0;

        if(Animal::lakon_move){
            Animal::vel = global::normalize(Animal::vel);
            Animal::vel.x = Animal::vel.x * Animal::speed;
            Animal::vel.y = Animal::vel.y * Animal::speed;
            Animal::move(Animal::vel);
            Animal::movement_animation();
        }else{
            Animal::bite_animation();

            //this is for quiet wolf animation
            // switch(Animal::last_command){
            //     case 'w':
            //         Animal::setTextureRect(moveUpAnim[3]);
            //         Animal::setOrigin(spriteSize_ver.x / 2, spriteSize_ver.y / 2);
            //         break;
            //     case 's':
            //         Animal::setTextureRect(moveDownAnim[3]);
            //         Animal::setOrigin(spriteSize_ver.x / 2, spriteSize_ver.y / 2);
            //         break;
            //     case 'a':
            //         Animal::setTextureRect(moveLeftAnim[0]);
            //         Animal::setOrigin(spriteSize_ver.y / 2, spriteSize_ver.x / 2);
            //         break;
            //     case 'd':
            //         Animal::setTextureRect(moveRightAnim[0]);
            //         Animal::setOrigin(spriteSize_ver.y / 2, spriteSize_ver.x / 2);
            //         break;
            //     default:
            //         Animal::setTextureRect(moveDownAnim[3]);
            // }
        }
    }

    void movement_animation(){
        if(clk.getElapsedTime().asSeconds() > Animal::clk_threshold){
            if(Animal::orientation == 'v'){
                if(Animal::iter_move_anim >= 3) iter_move_anim = -1;  // 0 - 3
                iter_move_anim++;

                switch(Animal::command){
                    case 'w':
                        Animal::setTextureRect(moveUpAnim[iter_move_anim]);
                        Animal::setOrigin(spriteSize_ver.x / 2, spriteSize_ver.y / 2);
                        break;
                    case 's':
                        Animal::setTextureRect(moveDownAnim[iter_move_anim]);
                        Animal::setOrigin(spriteSize_ver.x / 2, spriteSize_ver.y / 2);
                        break;
                    default:
                        printf("ini nih 111");
                }
            } else if(Animal::orientation == 'h'){
                if(Animal::iter_move_anim >= 4) iter_move_anim = -1;  // 0 - 4
                iter_move_anim++;

                switch(Animal::command){
                    case 'a':
                        Animal::setTextureRect(moveLeftAnim[iter_move_anim]);
                        Animal::setOrigin(spriteSize_ver.y / 2, spriteSize_ver.x / 2);
                        break;
                    case 'd':
                        Animal::setTextureRect(moveRightAnim[iter_move_anim]);
                        Animal::setOrigin(spriteSize_ver.y / 2, spriteSize_ver.x / 2);
                        break;
                    default:
                        printf("ini nih 222");
                }
            } else{
                printf("fjksdfd\n");
            }
            // printf("iter: %d\n", iter_move_anim);
            if(iter_move_anim > 4) printf("lah loh\n");
            clk.restart();

            // // check
            // printf("iter: %d, command : %c, orientation: %c\n", Animal::iter_move_anim, Animal::command, Animal::orientation);
        }
    }

    void bite_animation(){
        // printf("bite nih\n");
        if(clk.getElapsedTime().asSeconds() > Animal::clk_threshold){
            if(Animal::iter_bite_anim >= 4) iter_bite_anim = -1;  // 0 - 4
            iter_bite_anim++;
            // printf("iter bite: %d", iter_bite_anim);

            switch(Animal::last_command){
                case 'w':
                    Animal::setTextureRect(biteUpAnim[iter_bite_anim]);
                    Animal::setOrigin(spriteSize_ver.x / 2, spriteSize_ver.y / 2);
                    // printf("w nihh");
                    break;
                case 's':
                    Animal::setTextureRect(biteDownAnim[iter_bite_anim]);
                    Animal::setOrigin(spriteSize_ver.x / 2, spriteSize_ver.y / 2);
                    // printf("s nihh");
                    break;
                case 'a':
                    Animal::setTextureRect(biteLeftAnim[iter_bite_anim]);
                    Animal::setOrigin(spriteSize_ver.y / 2, spriteSize_ver.x / 2);
                    // printf("a nihh");
                    break;
                case 'd':
                    Animal::setTextureRect(biteRightAnim[iter_bite_anim]);
                    Animal::setOrigin(spriteSize_ver.y / 2, spriteSize_ver.x / 2);
                    // printf("d nihh");
                    break;
            }

            clk.restart();
        }
    }
};

#endif