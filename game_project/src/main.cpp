#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <vector>
#include "../include/global.hpp"
#include "../include/lakon.hpp"
#include "../include/food.hpp"
#include "../include/animal.hpp"
#include <iostream>

int main(){
    // load fonts
    sf::Font font_African, font_LovaNature;
    if(!font_African.loadFromFile("assets/fonts/African-l6d.ttf")){
        std::cerr << ".Error while loading font" << std::endl;
        return -1;
    }
    if(!font_LovaNature.loadFromFile("assets/fonts/LoveNature-nRmEP.ttf")){
        std::cerr << ".Error while loading font" << std::endl;
        return -1;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////// MENU GAME ///////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::RenderWindow menu_window(sf::VideoMode(global::width_window, global::height_window), "Main Menu");

    sf::Texture menu_texture;
    menu_texture.loadFromFile("assets/images/menu.png");
    sf::Sprite menu_sprite;
    menu_sprite.setTexture(menu_texture);
    menu_sprite.setScale(sf::Vector2f(1/1.667, 1/2.222));
    sf::Text text1, text2;
    text1.setFont(font_African);
    text1.setString("Bruh, RUN...!!!");
    text1.setCharacterSize(70);
    text1.setFillColor(sf::Color::Green);
    text1.setStyle(sf::Text::Bold);
    text1.setPosition(sf::Vector2f(global::width_window/2, global::height_window/2 - 100));
    text1.setOrigin(text1.getLocalBounds().width/2, text1.getLocalBounds().height/1);
    text2.setFont(font_LovaNature);
    text2.setString("press enter....");
    text2.setCharacterSize(50);
    text2.setFillColor(sf::Color::White);
    text2.setPosition(sf::Vector2f(global::width_window/2, global::height_window/2 + 50));
    text2.setOrigin(text2.getLocalBounds().width/2, text2.getLocalBounds().height/1);

    // MENU LOOP
    while(menu_window.isOpen()){
        sf::Event e;

        // close window conditional
        while(menu_window.pollEvent(e))
            if(e.type == sf::Event::Closed) menu_window.close();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) break;;

        menu_window.clear(sf::Color::White);
        menu_window.draw(menu_sprite);
        menu_window.draw(text1);
        menu_window.draw(text2);
        menu_window.display();
    }


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////// GAME //////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool ulang = 1;
    while(ulang == 1){

    sf::RenderWindow window(sf::VideoMode(global::width_window, global::height_window), "Bruh, RUN...!!!");
    window.setFramerateLimit(60);

    // load map and environment
    sf::Texture map_texture;
    map_texture.loadFromFile("assets/images/grass.png");
    sf::Sprite map_sprite[6];
    map_sprite[0].setTexture(map_texture);
    map_sprite[1].setTexture(map_texture);
    map_sprite[2].setTexture(map_texture);
    map_sprite[3].setTexture(map_texture);
    map_sprite[4].setTexture(map_texture);
    map_sprite[5].setTexture(map_texture);
    map_sprite[0].setPosition(sf::Vector2f(0.f, 0.f));
    map_sprite[1].setPosition(sf::Vector2f(640.f, 0.f));
    map_sprite[2].setPosition(sf::Vector2f(1280.f, 0.f));
    map_sprite[3].setPosition(sf::Vector2f(0.f, 440.f));
    map_sprite[4].setPosition(sf::Vector2f(640.f, 440.f));
    map_sprite[5].setPosition(sf::Vector2f(1280.f, 440.f));
    // tree
    sf::Texture tree_texture;
    tree_texture.loadFromFile("assets/images/48x48_trees.png");
    sf::Sprite tree1, tree2, tree3, tree4;
    tree1.setTexture(tree_texture);
    tree1.setTextureRect(sf::IntRect(0*48, 0, 48, 48));
    tree2.setTexture(tree_texture);
    tree2.setTextureRect(sf::IntRect(1*48, 0, 48, 48));
    tree3.setTexture(tree_texture);
    tree3.setTextureRect(sf::IntRect(2*48, 0, 48, 48));
    tree4.setTexture(tree_texture);
    tree4.setTextureRect(sf::IntRect(3*48, 0, 48, 48));

    tree1.setScale(sf::Vector2f(5.f, 5.f));
    tree1.setPosition(sf::Vector2f(1550.f, 850.f));
    tree2.setScale(sf::Vector2f(5.f, 5.f));
    tree2.setPosition(sf::Vector2f(1690.f, 780.f));
    tree3.setScale(sf::Vector2f(5.f, 5.f));
    tree3.setPosition(sf::Vector2f(45.f, 780.f));
    tree4.setScale(sf::Vector2f(5.f, 5.f));
    tree4.setPosition(sf::Vector2f(-40.f, 810.f));

    // music and sfx
    sf::Music backsound;
    if (!backsound.openFromFile("assets/sounds/musics/avatar_backsound.wav"))
        return -1; // error
    backsound.setLoop(true);
    backsound.play();

    sf::SoundBuffer throw_buffersfx;
    sf::SoundBuffer damaged_buffersfx;
    sf::SoundBuffer onTarget_buffersfx;
    if(!throw_buffersfx.loadFromFile("assets/sounds/sfx/throw_sounds_effect.wav"))
        return -1;
    if(!damaged_buffersfx.loadFromFile("assets/sounds/sfx/damaged_sound_effect.wav"))
        return -1;
    if(!onTarget_buffersfx.loadFromFile("assets/sounds/sfx/eating_sound_effect.wav"))
        return -1;
    sf::Sound throw_sfx;
    throw_sfx.setBuffer(throw_buffersfx);
    sf::Sound damaged_sfx;
    damaged_sfx.setBuffer(damaged_buffersfx);
    sf::Sound onTarget_sfx;
    onTarget_sfx.setBuffer(onTarget_buffersfx);

    // throw_sfx.setPlayingOffset(sf::seconds(-0.5f));
    // onTarget_sfx.setPlayingOffset(sf::seconds(-1.5f));

    // player
    Lakon Kratosss;

    // projectiles meat
    Food meat;
    std::vector<Food> meat_vect;

    // enemy
    int num_wolf = 12;
    std::vector <Animal> wolf_vect(num_wolf);
    for(int i=0; i<wolf_vect.size(); i++){
        wolf_vect[i].setPosition(global::generate_position('o'));
        wolf_vect[i].set_speed(float(rand()%3+2) / 2);
    }

    // clock for mouse click
    sf::Clock clk_lm;
    float clk_lm_threshold = 0.5f;
    // clock for collision
    std::vector <sf::Clock> clk_coll_kw(num_wolf);
    float clk_coll_kw_threshold = 1.f;
    


    // GAME LOOP
    while(window.isOpen()){
        sf::Event e;

        // close window conditional
        while(window.pollEvent(e))
            if(e.type == sf::Event::Closed) window.close();


        /////////////////////////////////////////////////////////////////////
        //////////////////// MECHANISM MOVEMENTS ////////////////////////////
        ////////////////////////////////////////////////////////////////////
        

        // player movement
        Kratosss.movement();
        // printf("x:%f   , y:%f\n", Kratosss.getPosition().x, Kratosss.getPosition().y);

        // enemies movement
        for(int i=0; i<wolf_vect.size(); i++){
            wolf_vect[i].movement(Kratosss.getPosition());
        }

        // add projectiles
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if(clk_lm.getElapsedTime().asSeconds() > clk_lm_threshold){
                throw_sfx.play();  // play sound
                meat.setPosition(Kratosss.getPosition());
                meat.determine_vel(Kratosss.getPosition(), sf::Mouse::getPosition(window));
                meat_vect.push_back(meat);
                clk_lm.restart();
            }
        }
        // projectiles movement
        for(int i=0; i<meat_vect.size(); i++){
            meat_vect[i].movement();
        }
        // destroy projectiles
        if(!meat_vect.empty() && (meat_vect[0].getPosition().x < 0 || meat_vect[0].getPosition().x > global::width_window
            || meat_vect[0].getPosition().y < 0 || meat_vect[0].getPosition().y > global::height_window))
                meat_vect.erase(meat_vect.begin());


        //////////////////////////////////////////////////////////////////
        //////////////////////// COLLISION CHECK /////////////////////////
        //////////////////////////////////////////////////////////////////
        if(Kratosss.get_health() <= 0.f) window.close();
        for(int i=0; i<wolf_vect.size(); i++){
            if(wolf_vect[i].get_health() <= 0){
                wolf_vect.erase(wolf_vect.begin() + i);
            }
        }
        
        // kw == kratosss collision to wolf
        for(int i=0; i< wolf_vect.size(); i++){
            if(Kratosss.getGlobalBounds().intersects(wolf_vect[i].getGlobalBounds())
                && clk_coll_kw[i].getElapsedTime().asSeconds() > clk_coll_kw_threshold){
                    damaged_sfx.play();  // play sound
                    Kratosss.reduceHealth(-2.5);
                    clk_coll_kw[i].restart();
            }
        }

        // wm == wolf collision to meat
        for(int i=0; i<wolf_vect.size(); i++){
            for(int j=0; j<meat_vect.size(); j++){
                if(wolf_vect[i].getGlobalBounds().intersects(meat_vect[j].getGlobalBounds())){
                    onTarget_sfx.play();  // play sound
                    wolf_vect[i].reduceHealth(-20);
                    meat_vect.erase(meat_vect.begin() + j);
                }
            }
        }

        //////////////////////////////////////////////////////////////////
        /////////////////////// DRAWING SESSION //////////////////////////
        //////////////////////////////////////////////////////////////////

        window.clear(sf::Color::White);

        // map
        for(int i=0; i<6; i++){
            window.draw(map_sprite[i]);
        }
        // player
        window.draw(Kratosss);
        Kratosss.displayHealth(window);
        // projectiles
        // printf("%d\n", meat_vect.size());
        for(int i=0; i<meat_vect.size(); i++){
            window.draw(meat_vect[i]);
        }
        // wolves
        // printf("%d\n", wolf_vect.size());
        for(int i=0; i<wolf_vect.size(); i++){
            window.draw(wolf_vect[i]);
            wolf_vect[i].displayHealth(window);
        }
        // Trees
        window.draw(tree2);
        window.draw(tree1);
        window.draw(tree3);
        window.draw(tree4);

        window.display();
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////// GAME OVER //////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::RenderWindow gameOver_window(sf::VideoMode(global::width_window, global::height_window), "GAME OVER");

    sf::Texture gameOver_texture;
    gameOver_texture.loadFromFile("assets/images/game_over.png");
    sf::Sprite gameOver_sprite;
    gameOver_sprite.setTexture(gameOver_texture);
    gameOver_sprite.setScale(1.408f, 1.406f);
    sf::Text text3, text4;
    text3.setFont(font_LovaNature);
    text3.setString("press enter to restart");
    text3.setCharacterSize(50);
    text3.setFillColor(sf::Color::Black);
    text3.setPosition(sf::Vector2f(global::width_window/2, global::height_window/2 - 100));
    text3.setOrigin(text3.getLocalBounds().width/2, text3.getLocalBounds().height/1);
    text4.setFont(font_LovaNature);
    text4.setString("press esc to quit the game");
    text4.setCharacterSize(50);
    text4.setFillColor(sf::Color::Black);
    text4.setPosition(sf::Vector2f(global::width_window/2, global::height_window/2 - 50));
    text4.setOrigin(text4.getLocalBounds().width/2, text4.getLocalBounds().height/1);
    // GAME OVER LOOP
    ulang = 0;
    while(gameOver_window.isOpen()){
        sf::Event e;

        // close window conditional
        while(gameOver_window.pollEvent(e))
            if(e.type == sf::Event::Closed) gameOver_window.close();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) gameOver_window.close();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {ulang = 1; break;}

        gameOver_window.clear(sf::Color::White);
        gameOver_window.draw(gameOver_sprite);
        gameOver_window.draw(text3);
        gameOver_window.draw(text4);
        gameOver_window.display();
    }

    }

    return 0;
}