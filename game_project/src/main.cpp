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

    // projectiles pisang
    Fruit pisang;
    std::vector<Fruit> pisang_vect;

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

    // add on variable
    // bool lm_clicked;
    sf::Clock clk;
    float clk_threshold = 0.5f;

    // MAIN LOOP
    while(window.isOpen()){
        sf::Event e;

        // close window conditional
        while(window.pollEvent(e))
            if(e.type == sf::Event::Closed) window.close();

        // player movement
        Kratosss.movement();

        // add projectiles
        // lm_clicked = false;
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if(clk.getElapsedTime().asSeconds() > clk_threshold){
                pisang.setPosition(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
                pisang.determine_vel(Kratosss.getPosition(), sf::Mouse::getPosition());
                pisang_vect.push_back(pisang);
                clk.restart();
            }
            // lm_clicked = true;
        }
        // projectiles movement
        for(int i=0; i<pisang_vect.size(); i++){
            pisang_vect[i].movement();
        }
        // destroy projectiles
        if(!pisang_vect.empty() && (pisang_vect[0].getPosition().x < 0 || pisang_vect[0].getPosition().x > global::width_window
            || pisang_vect[0].getPosition().y < 0 || pisang_vect[0].getPosition().y > global::height_window))
                pisang_vect.erase(pisang_vect.begin());
        // printf("%d\n", pisang_vect.size());

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

        // DRAWING SESSION
        window.clear(sf::Color::White);

        // draw player
        window.draw(Kratosss);
        // draw projectiles
        for(int i=0; i<pisang_vect.size(); i++){
            window.draw(pisang_vect[i]);
        }
        // draw enemies
        for(int i=0; i<enemies.size(); i++){
            window.draw(enemies[i]);
        }

        window.display();
    }
    return 0;
}