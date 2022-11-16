#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <vector>

// global var
unsigned int width_window = 1920;
unsigned int height_window = 1080;

sf::Vector2f normalize(sf::Vector2f vector)
{
    constexpr auto units_in_last_place = 2;
    auto norm = std::sqrt((vector.x * vector.x) + (vector.y * vector.y));
    // Prevent division by zero
    if (norm <= std::numeric_limits<float>::epsilon() * norm * units_in_last_place
        || norm < std::numeric_limits<float>::min())
    {
        return sf::Vector2f{};
    }
    return vector / norm;
}

class Lakon{
private:

public:
};

int main(){
    sf::RenderWindow window(sf::VideoMode(width_window, height_window), "Escape From The Zoo");
    window.setFramerateLimit(60);

    sf::Texture texture;
    texture.loadFromFile("assets/images/stickman.png");

    // player
    sf::Sprite player;
    sf::Vector2f velP;
    float speedP = 5;  // player movement speed
    player.setTexture(texture);
    player.setPosition(width_window/2, height_window/2);
    player.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    player.setScale(0.1, 0.1);
    bool isMoveP;  // is WASD pressed

    // projectiles
    

    // enemies
    const int num_enemy = 12;
    // std::vector <sf::Sprite> enemy;
    // std::vector <sf::Vector2f> velEn;
    // std::vector <float> speedEn;
    sf::Sprite enemy[num_enemy];
    sf::Vector2f velEn[num_enemy];
    float speedEn[num_enemy];  // enemy movement speed
    for(int i=0; i<num_enemy; i++){
        enemy[i].setTexture(texture);
        enemy[i].setPosition(rand()%100+1180, rand()%720);
        enemy[i].setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
        enemy[i].setScale(-0.1, 0.1);
        speedEn[i] = float(rand()%5 + 1) / 2;
    }

    // MAIN LOOP
    while(window.isOpen()){
        sf::Event e;
        while(window.pollEvent(e)){
            if(e.type == sf::Event::Closed) window.close();
        }

        // player movement
        isMoveP = false;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            velP.y = -1;
            isMoveP = true;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            velP.y = 1;
            isMoveP = true;
        }
        else velP.y = 0;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            velP.x = -1;
            isMoveP = true;
            player.setScale(sf::Vector2f(-0.1f, 0.1f));
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            velP.x = 1;
            isMoveP = true;
            player.setScale(sf::Vector2f(0.1f, 0.1f));
        }
        else velP.x = 0;

        if(isMoveP){
            velP = normalize(velP);
            velP.x = velP.x * speedP;
            velP.y = velP.y * speedP;
            player.move(velP);
        }

        // enemies follow always follow player
        float xP = player.getPosition().x;
        float yP = player.getPosition().y;
        for(int i=0; i<num_enemy; i++){
            float xEn = enemy[i].getPosition().x;
            float yEn = enemy[i].getPosition().y;

            if(yEn - yP > 0) enemy[i].move(sf::Vector2f(0.f, -speedEn[i]));
            if(yEn - yP < 0) enemy[i].move(sf::Vector2f(0.f, speedEn[i]));
            if(xEn - xP > 0) {enemy[i].move(sf::Vector2f(-speedEn[i], 0.f)); enemy[i].setScale(-0.1, 0.1);}
            if(xEn - xP < 0) {enemy[i].move(sf::Vector2f(speedEn[i], 0.f)); enemy[i].setScale(0.1, 0.1);}
        }

        window.clear(sf::Color::White);
        // draw player
        window.draw(player);
        // draw enemies
        for(int i=0; i<num_enemy; i++){
            window.draw(enemy[i]);
        }
        window.display();
    }
    return 0;
}