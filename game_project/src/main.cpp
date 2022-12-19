#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <vector>
#include "../include/global.hpp"
#include "../include/lakon.hpp"
#include "../include/meat.hpp"
#include "../include/animal.hpp"

int main(){
    sf::RenderWindow window(sf::VideoMode(global::width_window, global::height_window), "Escape From The Zoo");
    window.setFramerateLimit(60);

    // sf::Texture texture;
    // texture.loadFromFile("assets/images/stickman.png");
    // load map and environment
    sf::Texture map_texture;
    map_texture.loadFromFile("assets/images/grass.png");
    sf::Sprite map_sprite[4];
    map_sprite[0].setTexture(map_texture);
    map_sprite[1].setTexture(map_texture);
    map_sprite[2].setTexture(map_texture);
    map_sprite[3].setTexture(map_texture);
    map_sprite[0].setPosition(sf::Vector2f(0.f, 0.f));
    map_sprite[1].setPosition(sf::Vector2f(640.f, 0.f));
    map_sprite[2].setPosition(sf::Vector2f(0.f, 80.f));
    map_sprite[3].setPosition(sf::Vector2f(640.f, 80.f));
    // sf::Texture tree1_texture;
    // tree1_texture.loadFromFile("")

    // player
    Lakon Kratosss;

    // projectiles daging
    Meat daging;
    std::vector<Meat> daging_vect;

    // // enemy
    // std::vector <sf::Sprite> enemies(12);
    // std::vector <sf::Vector2f> velEn(12);
    // std::vector <float> speedEn(12);  // enemies movement speed
    // for(int i=0; i<enemies.size(); i++){
    //     enemies[i].setTexture(texture);
    //     enemies[i].setPosition(rand()%100+1180, rand()%720);
    //     enemies[i].setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    //     enemies[i].setScale(-0.1, 0.1);
    //     speedEn[i] = float(rand()%5 + 1) / 2;
    // }
    // enemy
    Animal wolf(3.5f, sf::Vector2f(0.5*global::width_window, 1*global::height_window));
    // std::vector <Animal> wolf_vect;


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

        // enemies movement
        wolf.movement(Kratosss.getPosition());

        // add projectiles
        // lm_clicked = false;
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if(clk.getElapsedTime().asSeconds() > clk_threshold){
                daging.setPosition(Kratosss.getPosition());
                daging.determine_vel(Kratosss.getPosition(), sf::Mouse::getPosition(window));
                daging_vect.push_back(daging);
                clk.restart();
            }
            // lm_clicked = true;
        }
        // projectiles movement
        for(int i=0; i<daging_vect.size(); i++){
            daging_vect[i].movement();
        }
        // destroy projectiles
        if(!daging_vect.empty() && (daging_vect[0].getPosition().x < 0 || daging_vect[0].getPosition().x > global::width_window
            || daging_vect[0].getPosition().y < 0 || daging_vect[0].getPosition().y > global::height_window))
                daging_vect.erase(daging_vect.begin());
        // printf("%d\n", daging_vect.size());

        // // enemies movement
        // float xP = Kratosss.getPosition().x;
        // float yP = Kratosss.getPosition().y;
        // for(int i=0; i<enemies.size(); i++){
        //     float xEn = enemies[i].getPosition().x;
        //     float yEn = enemies[i].getPosition().y;

        //     if(yEn - yP > 0) enemies[i].move(sf::Vector2f(0.f, -speedEn[i]));
        //     if(yEn - yP < 0) enemies[i].move(sf::Vector2f(0.f, speedEn[i]));
        //     if(xEn - xP > 0) {enemies[i].move(sf::Vector2f(-speedEn[i], 0.f)); enemies[i].setScale(-0.1, 0.1);}
        //     if(xEn - xP < 0) {enemies[i].move(sf::Vector2f(speedEn[i], 0.f)); enemies[i].setScale(0.1, 0.1);}
        // }

        // DRAWING SESSION
        window.clear(sf::Color::White);

        // draw map
        for(int i=0; i<4; i++){
            window.draw(map_sprite[i]);
        }
        // draw player
        window.draw(Kratosss);
        // draw projectiles
        for(int i=0; i<daging_vect.size(); i++){
            window.draw(daging_vect[i]);
        }
        // draw enemies
        // for(int i=0; i<enemies.size(); i++){
        //     window.draw(enemies[i]);
        // }
        window.draw(wolf);


        window.display();
    }
    return 0;
}