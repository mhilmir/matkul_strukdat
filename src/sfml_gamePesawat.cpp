#include <SFML/Graphics.hpp>
#include <cmath>
#include <unistd.h>

#define PI 3.14159265359

// global var//////////////////////////
unsigned int width_screen = 1000;
unsigned int height_screen = 1000;
///////////////////////////////////////////////////

class PesawatLakon{
private :
    float pos_x = width_screen * 0.5;
    float pos_y = height_screen * 0.75;
    float scale = 15;
    float body_points[13][2] = {{1,-3}, {0.25,-3}, {0.25,-4.5}, {0,-5}, {-0.25,-4.5}, {-0.25,-3}, {-1,-3}, {-1,1.5}, {-1.5,1.75}, {-1.25,2}, {1.25,2}, {1.5,1.75}, {1,1.5}};  // for drawing body_points plane
    float wing_points[6][2] = {{1,-2}, {5,0}, {4,1}, {-4,1}, {-5,0}, {-1,-2}};  // for drawing wing_points plane

public:
    PesawatLakon(){}

    void moveHor(int speed){
        pos_x = pos_x + speed;
    }

    void moveVer(int speed){
        pos_y = pos_y + speed;
    }

    void drawPesawat(sf::RenderWindow& window){
        sf::Vertex draw_body[] = {
            sf::Vertex(sf::Vector2f(pos_x + body_points[0][0]*scale, pos_y + body_points[0][1]*scale)),
            sf::Vertex(sf::Vector2f(pos_x + body_points[1][0]*scale, pos_y + body_points[1][1]*scale)),
            sf::Vertex(sf::Vector2f(pos_x + body_points[2][0]*scale, pos_y + body_points[2][1]*scale)),
            sf::Vertex(sf::Vector2f(pos_x + body_points[3][0]*scale, pos_y + body_points[3][1]*scale)),
            sf::Vertex(sf::Vector2f(pos_x + body_points[4][0]*scale, pos_y + body_points[4][1]*scale)),
            sf::Vertex(sf::Vector2f(pos_x + body_points[5][0]*scale, pos_y + body_points[5][1]*scale)),
            sf::Vertex(sf::Vector2f(pos_x + body_points[6][0]*scale, pos_y + body_points[6][1]*scale)),
            sf::Vertex(sf::Vector2f(pos_x + body_points[7][0]*scale, pos_y + body_points[7][1]*scale)),
            sf::Vertex(sf::Vector2f(pos_x + body_points[8][0]*scale, pos_y + body_points[8][1]*scale)),
            sf::Vertex(sf::Vector2f(pos_x + body_points[9][0]*scale, pos_y + body_points[9][1]*scale)),
            sf::Vertex(sf::Vector2f(pos_x + body_points[10][0]*scale, pos_y + body_points[10][1]*scale)),
            sf::Vertex(sf::Vector2f(pos_x + body_points[11][0]*scale, pos_y + body_points[11][1]*scale)),
            sf::Vertex(sf::Vector2f(pos_x + body_points[12][0]*scale, pos_y + body_points[12][1]*scale)),
            sf::Vertex(sf::Vector2f(pos_x + body_points[0][0]*scale, pos_y + body_points[0][1]*scale))
        };
        sf::Vertex draw_wing[] = {
            sf::Vertex(sf::Vector2f(pos_x + wing_points[0][0]*scale, pos_y + wing_points[0][1]*scale)),
            sf::Vertex(sf::Vector2f(pos_x + wing_points[1][0]*scale, pos_y + wing_points[1][1]*scale)),
            sf::Vertex(sf::Vector2f(pos_x + wing_points[2][0]*scale, pos_y + wing_points[2][1]*scale)),
            sf::Vertex(sf::Vector2f(pos_x + wing_points[3][0]*scale, pos_y + wing_points[3][1]*scale)),
            sf::Vertex(sf::Vector2f(pos_x + wing_points[4][0]*scale, pos_y + wing_points[4][1]*scale)),
            sf::Vertex(sf::Vector2f(pos_x + wing_points[5][0]*scale, pos_y + wing_points[5][1]*scale)),
            sf::Vertex(sf::Vector2f(pos_x + wing_points[0][0]*scale, pos_y + wing_points[0][1]*scale))
        };

        window.draw(draw_body, 13+1, sf::LineStrip);
        window.draw(draw_wing, 6+1, sf::LineStrip);
    }
};

class PesawatMusuh{
private :
    float pos_x;
    float pos_y;
    float scale;
    int speed_y;  // determine plane speed y
    int speed_x;  // determine plane speed x
    float body_points[9][2] = {{0.5,0}, {0.5,-1.25}, {0,-1.5}, {-0.5,-1.25}, {-0.5,0}, {-0.25,2.75}, {-1,3}, {1,3}, {0.25,2.75}};  // for drawing body_points plane
    float wing_points[6][2] = {{2.5,0.5}, {3,1.75}, {2.5,-0.5}, {-2.5,-0.5}, {-3,1.75}, {-2.5,0.5}};  // for drawing wing_points plane

public:
    PesawatMusuh(){
        scale = rand()%15 + 5;
        speed_y = rand()%5 + 1;
        speed_x = rand()%5 + 1;
        pos_x = rand() % width_screen + 10;
        pos_y = rand() % int(height_screen*0.25) + 10;
    }

    void MoveRight(){
        pos_x = pos_x + speed_x;
        if(pos_x > width_screen){
            pos_x = pos_x - width_screen;
        }
    }

    void MoveLeft(){
        pos_x = pos_x - speed_x;
        if(pos_x < 0){
            pos_x = pos_x + width_screen;
        }
    }

    void rotatePesawat(float degree){
        int num_bpoints = 9;
        int num_wpoints = 6; 
        // convert degree to radian
        float rad = degree * (PI/180);

        // rotating body
        for(int i=0; i<num_bpoints; i++){
            float temp[2];  // for storing one-point coordinate
            // assign to temp
            for(int j=0; j<2; j++){
                temp[j] = body_points[i][j];
            }
            // convert cartesian to polar (r, theta)
            float r = sqrt( pow(temp[0],2) + pow(temp[1],2) );
            float theta = atan2(temp[1], temp[0]);

            // adding theta by degree(radian) inputted
            theta = theta + rad;

            // convert polar to cartesian again and store it to temp
            temp[0] = r * cos(theta);  // as x
            temp[1] = r * sin(theta);  // as y

            // return temp to body_array
            for(int j=0; j<2; j++){
                body_points[i][j] = temp[j];
            }
        }

        // rotating wing
        for(int i=0; i<num_wpoints; i++){
            float temp[2];  // for storing one-point coordinate
            // assign to temp
            for(int j=0; j<2; j++){
                temp[j] = wing_points[i][j];
            }
            // convert cartesian to polar (r, theta)
            float r = sqrt( pow(temp[0],2) + pow(temp[1],2) );
            float theta = atan2(temp[1], temp[0]);

            // adding theta by degree(radian) inputted
            theta = theta + rad;

            // convert polar to cartesian again and store it to temp
            temp[0] = r * cos(theta);  // as x
            temp[1] = r * sin(theta);  // as y

            // return temp to wing_array
            for(int j=0; j<2; j++){
                wing_points[i][j] = temp[j];
            }
        }
    }

    void drawPesawat(sf::RenderWindow& window){
        sf::Vertex draw_body[] = {
            sf::Vertex(sf::Vector2f(pos_x + body_points[0][0]*scale, pos_y + body_points[0][1]*scale)),
            sf::Vertex(sf::Vector2f(pos_x + body_points[1][0]*scale, pos_y + body_points[1][1]*scale)),
            sf::Vertex(sf::Vector2f(pos_x + body_points[2][0]*scale, pos_y + body_points[2][1]*scale)),
            sf::Vertex(sf::Vector2f(pos_x + body_points[3][0]*scale, pos_y + body_points[3][1]*scale)),
            sf::Vertex(sf::Vector2f(pos_x + body_points[4][0]*scale, pos_y + body_points[4][1]*scale)),
            sf::Vertex(sf::Vector2f(pos_x + body_points[5][0]*scale, pos_y + body_points[5][1]*scale)),
            sf::Vertex(sf::Vector2f(pos_x + body_points[6][0]*scale, pos_y + body_points[6][1]*scale)),
            sf::Vertex(sf::Vector2f(pos_x + body_points[7][0]*scale, pos_y + body_points[7][1]*scale)),
            sf::Vertex(sf::Vector2f(pos_x + body_points[8][0]*scale, pos_y + body_points[8][1]*scale)),
            sf::Vertex(sf::Vector2f(pos_x + body_points[0][0]*scale, pos_y + body_points[0][1]*scale))
        };
        sf::Vertex draw_wing[] = {
            sf::Vertex(sf::Vector2f(pos_x + wing_points[0][0]*scale, pos_y + wing_points[0][1]*scale)),
            sf::Vertex(sf::Vector2f(pos_x + wing_points[1][0]*scale, pos_y + wing_points[1][1]*scale)),
            sf::Vertex(sf::Vector2f(pos_x + wing_points[2][0]*scale, pos_y + wing_points[2][1]*scale)),
            sf::Vertex(sf::Vector2f(pos_x + wing_points[3][0]*scale, pos_y + wing_points[3][1]*scale)),
            sf::Vertex(sf::Vector2f(pos_x + wing_points[4][0]*scale, pos_y + wing_points[4][1]*scale)),
            sf::Vertex(sf::Vector2f(pos_x + wing_points[5][0]*scale, pos_y + wing_points[5][1]*scale)),
            sf::Vertex(sf::Vector2f(pos_x + wing_points[0][0]*scale, pos_y + wing_points[0][1]*scale))
        };

        window.draw(draw_body, 9+1, sf::LineStrip);
        window.draw(draw_wing, 6+1, sf::LineStrip);
    }
};


int main(){
    sf::RenderWindow window(sf::VideoMode(width_screen, height_screen), "Pesawat-Pesawatan");

    // create pesawat lakon
    PesawatLakon jatayu;

    // create pesawat musuh
    int num_opponents = 5;
    PesawatMusuh opponents_toRight[num_opponents];
    PesawatMusuh opponents_toLeft[num_opponents];
    for(int i=0; i<num_opponents; i++){
        opponents_toRight[i].rotatePesawat(90);
    }
    for(int i=0; i<num_opponents; i++){
        opponents_toLeft[i].rotatePesawat(-90);
    }

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
            else if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::W){
                    // printf("W\n");
                    jatayu.moveVer(-10);
                } if(event.key.code == sf::Keyboard::S){
                    // printf("S\n");
                    jatayu.moveVer(10);
                } if(event.key.code == sf::Keyboard::A){
                    // printf("A\n");
                    jatayu.moveHor(-10);
                } if(event.key.code == sf::Keyboard::D){
                    // printf("D\n");
                    jatayu.moveHor(10);
                }
            }
            else if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left){
                    // printf("klik kiri\n");
                }
            }
        }


        window.clear();

        jatayu.drawPesawat(window);
        
        for(int i=0; i<num_opponents; i++){
            opponents_toRight[i].MoveRight();
            opponents_toRight[i].drawPesawat(window);
        }
        for(int i=0; i<num_opponents; i++){
            opponents_toLeft[i].MoveLeft();
            opponents_toLeft[i].drawPesawat(window);
        }

        window.display();
        usleep(20*1000);
    }

    return 0;
}