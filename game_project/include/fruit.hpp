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
    bool isMove;
    float speed;
    sf::Vector2f vel;
    
public:
};


#endif __FRUIT_HPP__