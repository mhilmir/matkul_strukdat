#include <SFML/Graphics.hpp>
#include <cmath>

// global var
unsigned int width_window = 1280;
unsigned int height_window = 720;

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
    sf::RenderWindow window(sf::VideoMode(width_window, height_window), "windowOpened");
    window.setFramerateLimit(60);

    sf::Vector2f vel;
    float speed = 3;

    sf::Texture texture;
    texture.loadFromFile("game_project/assets/images/stickman.png");
    
    sf::Sprite player;
    player.setTexture(texture);
    player.setPosition(width_window/2, height_window/2);
    player.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    player.setScale(0.1, 0.1);
    // player.rotate(90);
    // rotate, use scale to -1,1

    while(window.isOpen()){
        sf::Event e;
        while(window.pollEvent(e)){
            if(e.type == sf::Event::Closed){
                window.close();
            }
            if(e.type == sf::Event::KeyPressed){
                if(e.key.code == sf::Keyboard::W)
                    vel.y = -1;
                else if(e.key.code == sf::Keyboard::S)
                    vel.y = 1;
                if(e.key.code == sf::Keyboard::A){
                    vel.x = -1;
                    player.setScale(-0.1,0.1);
                }
                else if(e.key.code == sf::Keyboard::D){
                    vel.x = 1;
                    player.setScale(0.1,0.1);
                }
                
                vel = normalize(vel) * speed;
            }
            if(e.type == sf::Event::KeyReleased){
                vel = sf::Vector2f(0,0);
            }
        }

        window.clear(sf::Color::White);
        player.move(vel);
        window.draw(player);
        window.display();
    }
    return 0;
}