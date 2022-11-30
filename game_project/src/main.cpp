#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <vector>
#include "../include/global.hpp"
#include "../include/lakon.hpp"
#include "../include/fruit.hpp"

int main(){
    sf::RenderWindow window(sf::VideoMode(global::width_window, global::height_window), "Escape From The Zoo");
    window.setFramerateLimit(60);

    sf::Texture texture;
    texture.loadFromFile("assets/images/stickman.png");

    // player
    Lakon Kratosss;

    // projectiles
    std::vector<Fruit> projectiles;

    // enemy
    std::vector <sf::Sprite> enemies(12);
    std::vector <sf::Vector2f> velEn(12);
    std::vector <float> speedEn(12);  // enemies movement speed
    for(int i=0; i<enemies.size(); i++){
        enemies[i].setTexture(texture);
        enemies[i].setPosition(rand()%100+1180, rand()%720);
        enemies[i].setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
        enemies[i].setScale(-0.1, 0.1);
        speedEn[i] = float(rand()%5 + 1) / 2;
    }

    // MAIN LOOP
    while(window.isOpen()){
        sf::Event e;

        // close window conditional
        while(window.pollEvent(e))
            if(e.type == sf::Event::Closed) window.close();

        // player movement
        Kratosss.movement();

        // add projectiles
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            Fruit Pisang(Kratosss.getPosition());
            Pisang.determine_vel(Kratosss.getPosition(), sf::Mouse::getPosition());
            projectiles.push_back(Pisang);
        }
        // projectiles movement
        for(int i=0; i<projectiles.size(); i++){
            projectiles[i].movement();
        }

        // enemies movement
        float xP = Kratosss.getPosition().x;
        float yP = Kratosss.getPosition().y;
        for(int i=0; i<enemies.size(); i++){
            float xEn = enemies[i].getPosition().x;
            float yEn = enemies[i].getPosition().y;

            if(yEn - yP > 0) enemies[i].move(sf::Vector2f(0.f, -speedEn[i]));
            if(yEn - yP < 0) enemies[i].move(sf::Vector2f(0.f, speedEn[i]));
            if(xEn - xP > 0) {enemies[i].move(sf::Vector2f(-speedEn[i], 0.f)); enemies[i].setScale(-0.1, 0.1);}
            if(xEn - xP < 0) {enemies[i].move(sf::Vector2f(speedEn[i], 0.f)); enemies[i].setScale(0.1, 0.1);}
        }

        window.clear(sf::Color::White);
        // draw player
        window.draw(Kratosss);
        // draw projectiles
        for(int i=0; i<projectiles.size(); i++){
            window.draw(projectiles[i]);
        }
        // draw enemies
        for(int i=0; i<enemies.size(); i++){
            window.draw(enemies[i]);
        }
        window.display();
    }
    return 0;
}