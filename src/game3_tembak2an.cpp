#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<stdio.h>
#include<cmath>

#define PI 3.14159265359

class Pesawat{
private :
    float x;
    float y;
    float sc;  // scale
    int Xmax ;  // screen x max
    int Ymax;  // screen y max
    int sty;  // determine plane speed y
    int stx;  // determine plane speed x
    float body[9][2] = {{0.5,0}, {0.5,-1.25}, {0,-1.5}, {-0.5,-1.25}, {-0.5,0}, {-0.25,2.75}, {-1,3}, {1,3}, {0.25,2.75}};  // for drawing body plane
    float wing[6][2] = {{2.5,0.5}, {3,1.75}, {2.5,-0.5}, {-2.5,-0.5}, {-3,1.75}, {-2.5,0.5}};  // for drawing wing plane

    // for bullet
    float xbullet;
    float ybullet;
    float radbullet = 5;
    int stybullet = 15;

public:
    Pesawat(){
        sc = rand()%15 + 5;
        Xmax = getmaxx();
        Ymax = getmaxy() / 2.75;
        sty = rand()%20 + 4;
        stx = rand()%20 + 4;
        x = rand()%Xmax + 10;
        y = rand()%Ymax + 10;
    }

    void Posisi(float xi, float yi){
        x = xi;
        y = yi;
    }

    void Skala(float scli){
        sc = scli;
    }

    void MoveUp(){
        y = y - sty;
        if (y < 0){
            y = y + Ymax;
        }
    }

    void MoveRight(){
        x = x + stx;
        if (x > Xmax){
            x = x - Xmax;
        }
    }

    void RotatePesawat(float degree){
        int num_bpoints = 9;
        int num_wpoints = 6; 
        // convert degree to radian
        float rad = degree * (PI/180);

        // rotating body
        for(int i=0; i<num_bpoints; i++){
            float temp[2];  // for storing one-point coordinate
            // assign to temp
            for(int j=0; j<2; j++){
                temp[j] = body[i][j];
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
                body[i][j] = temp[j];
            }
        }

        // rotating wing
        for(int i=0; i<num_wpoints; i++){
            float temp[2];  // for storing one-point coordinate
            // assign to temp
            for(int j=0; j<2; j++){
                temp[j] = wing[i][j];
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
                wing[i][j] = temp[j];
            }
        }
    }

    void DrawPesawat(){
        // drawing body of plane
        line((body[0][0]*sc + x), (body[0][1]*sc + y), (body[1][0]*sc + x), (body[1][1]*sc + y));
        line((body[1][0]*sc + x), (body[1][1]*sc + y), (body[2][0]*sc + x), (body[2][1]*sc + y));
        line((body[2][0]*sc + x), (body[2][1]*sc + y), (body[3][0]*sc + x), (body[3][1]*sc + y));
        line((body[3][0]*sc + x), (body[3][1]*sc + y), (body[4][0]*sc + x), (body[4][1]*sc + y));
        line((body[4][0]*sc + x), (body[4][1]*sc + y), (body[5][0]*sc + x), (body[5][1]*sc + y));
        line((body[5][0]*sc + x), (body[5][1]*sc + y), (body[6][0]*sc + x), (body[6][1]*sc + y));
        line((body[6][0]*sc + x), (body[6][1]*sc + y), (body[7][0]*sc + x), (body[7][1]*sc + y));
        line((body[7][0]*sc + x), (body[7][1]*sc + y), (body[8][0]*sc + x), (body[8][1]*sc + y));
        line((body[8][0]*sc + x), (body[8][1]*sc + y), (body[0][0]*sc + x), (body[0][1]*sc + y));

        // drawing wing of plane
        line((wing[0][0]*sc + x), (wing[0][1]*sc + y), (wing[1][0]*sc + x), (wing[1][1]*sc + y));
        line((wing[1][0]*sc + x), (wing[1][1]*sc + y), (wing[2][0]*sc + x), (wing[2][1]*sc + y));
        line((wing[2][0]*sc + x), (wing[2][1]*sc + y), (wing[3][0]*sc + x), (wing[3][1]*sc + y));
        line((wing[3][0]*sc + x), (wing[3][1]*sc + y), (wing[4][0]*sc + x), (wing[4][1]*sc + y));
        line((wing[4][0]*sc + x), (wing[4][1]*sc + y), (wing[5][0]*sc + x), (wing[5][1]*sc + y));
        line((wing[5][0]*sc + x), (wing[5][1]*sc + y), (wing[0][0]*sc + x), (wing[0][1]*sc + y));
    }

    void saveBulletPos(){
        xbullet = x;
        ybullet = y;
    }

    void DrawBullet(){
        circle(xbullet, ybullet, radbullet);
    }

    void moveBullet(){
        ybullet = ybullet + stybullet;
    }

    // tambahan
    int getYBullet(){
        return ybullet;
    }
};

class PesawatLakon{
private :
    float x;
    float y;
    float sc;  // scale
    int Xmax ;  // screen x max
    int Ymax;  // screen y max
    int sty;  // determine plane speed y
    int stx;  // determine plane speed x
    float body[13][2] = {{1,-3}, {0.25,-3}, {0.25,-4.5}, {0,-5}, {-0.25,-4.5}, {-0.25,-3}, {-1,-3}, {-1,1.5}, {-1.5,1.75}, {-1.25,2}, {1.25,2}, {1.5,1.75}, {1,1.5}};  // for drawing body plane
    float wing[6][2] = {{1,-2}, {5,0}, {4,1}, {-4,1}, {-5,0}, {-1,-2}};  // for drawing wing plane

    // for bullet
    float xbullet;
    float ybullet;
    float radbullet = 5;
    int stybullet = 30;

public:
    PesawatLakon(){
        sc = rand()%20 + 5;
        Xmax = getmaxx();
        Ymax = getmaxy();
        sty = rand()%20 + 4;
        stx = rand()%20 + 4;
        x = rand()%Xmax + 10;
        y = rand()%Ymax + 10;
    }

    void Posisi(float xi, float yi){
        x = xi;
        y = yi;
    }

    void Skala(float scli){
        sc = scli;
    }

    void MoveUp(){
        y = y - sty;
        if (y < 0){
            y = y + Ymax;
        }
    }

    void MoveRight(){
        x = x + stx;
        if (x > Xmax){
            x = x - Xmax;
        }
    }

    void RotatePesawat(float degree){
        int num_bpoints = 13;
        int num_wpoints = 6;
        // convert degree to radian
        float rad = degree * (PI/180);

        // rotating body
        for(int i=0; i<num_bpoints; i++){
            float temp[2];  // for storing one-point coordinate
            // assign to temp
            for(int j=0; j<2; j++){
                temp[j] = body[i][j];
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
                body[i][j] = temp[j];
            }
        }

        // rotating wing
        for(int i=0; i<num_wpoints; i++){
            float temp[2];  // for storing one-point coordinate
            // assign to temp
            for(int j=0; j<2; j++){
                temp[j] = wing[i][j];
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
                wing[i][j] = temp[j];
            }
        }
    }

    void DrawPesawat(){
        // drawing body of plane
        line((body[0][0]*sc + x), (body[0][1]*sc + y), (body[1][0]*sc + x), (body[1][1]*sc + y));
        line((body[1][0]*sc + x), (body[1][1]*sc + y), (body[2][0]*sc + x), (body[2][1]*sc + y));
        line((body[2][0]*sc + x), (body[2][1]*sc + y), (body[3][0]*sc + x), (body[3][1]*sc + y));
        line((body[3][0]*sc + x), (body[3][1]*sc + y), (body[4][0]*sc + x), (body[4][1]*sc + y));
        line((body[4][0]*sc + x), (body[4][1]*sc + y), (body[5][0]*sc + x), (body[5][1]*sc + y));
        line((body[5][0]*sc + x), (body[5][1]*sc + y), (body[6][0]*sc + x), (body[6][1]*sc + y));
        line((body[6][0]*sc + x), (body[6][1]*sc + y), (body[7][0]*sc + x), (body[7][1]*sc + y));
        line((body[7][0]*sc + x), (body[7][1]*sc + y), (body[8][0]*sc + x), (body[8][1]*sc + y));
        line((body[8][0]*sc + x), (body[8][1]*sc + y), (body[9][0]*sc + x), (body[9][1]*sc + y));
        line((body[9][0]*sc + x), (body[9][1]*sc + y), (body[10][0]*sc + x), (body[10][1]*sc + y));
        line((body[10][0]*sc + x), (body[10][1]*sc + y), (body[11][0]*sc + x), (body[11][1]*sc + y));
        line((body[11][0]*sc + x), (body[11][1]*sc + y), (body[12][0]*sc + x), (body[12][1]*sc + y));
        line((body[12][0]*sc + x), (body[12][1]*sc + y), (body[0][0]*sc + x), (body[0][1]*sc + y));

        // drawing wing of plane
        line((wing[0][0]*sc + x), (wing[0][1]*sc + y), (wing[1][0]*sc + x), (wing[1][1]*sc + y));
        line((wing[1][0]*sc + x), (wing[1][1]*sc + y), (wing[2][0]*sc + x), (wing[2][1]*sc + y));
        line((wing[2][0]*sc + x), (wing[2][1]*sc + y), (wing[3][0]*sc + x), (wing[3][1]*sc + y));
        line((wing[3][0]*sc + x), (wing[3][1]*sc + y), (wing[4][0]*sc + x), (wing[4][1]*sc + y));
        line((wing[4][0]*sc + x), (wing[4][1]*sc + y), (wing[5][0]*sc + x), (wing[5][1]*sc + y));
        line((wing[5][0]*sc + x), (wing[5][1]*sc + y), (wing[0][0]*sc + x), (wing[0][1]*sc + y));
    }

    void saveBulletPos(){
        xbullet = mousex();
        ybullet = mousey();
    }

    void DrawBullet(){
        circle(xbullet, ybullet, radbullet);
    }

    void moveBullet(){
        ybullet = ybullet - stybullet;
    }


};

class Bullet{
private:
    float x;
    float y;
    float radius;
    int Xmax ;  // screen x max
    int Ymax;  // screen y max
    int sty;  // determine bullet speed y
public:
    Bullet(){
        // x = mousex();
        // y = mousey();
        radius = 5;
        Ymax = getmaxy();
        Xmax = getmaxx();
        sty = 30;
    }

    void saveBulletPos(){
        x = mousex();
        y = mousey();
    }

    void DrawBullet(){
        circle(x, y, radius);
    }

    void moveBullet(){
        y = y - sty;
    }
};

int main(){
    initwindow(500,500);
    PesawatLakon PesawatKuh;
    PesawatKuh.Skala(10);
    Pesawat M[20];
    // Bullet myBullet;
    float xh,yh;
    char c;
    bool adaPeluru = false;

    // harus dijalankan cuma sekali
    // PesawatKuh.RotatePesawat(90);
    for(int i=0; i<20; i++){
        M[i].RotatePesawat(90);
    }

    do{
        cleardevice();
        if(kbhit()){  // keyboard hit
            c = getch();  // get button of pressed keyboard
            if (c == 27) break;
        }

        xh = mousex();
        yh = mousey() ;
        PesawatKuh.Posisi(xh, yh);
        PesawatKuh.DrawPesawat();

        // if(ismouseclick(WM_LBUTTONDOWN)){
        //     printf("clicked once");
        //     clearmouseclick(WM_LBUTTONDOWN);
        // }

        // nembak
        if(ismouseclick(WM_LBUTTONDOWN)){
            PesawatKuh.saveBulletPos();
            clearmouseclick(WM_LBUTTONDOWN);
        }
        PesawatKuh.DrawBullet();
        PesawatKuh.moveBullet();

        // move pesawat ke kanan
        for(int i=0; i<7; i++){
            M[i].MoveRight();
            M[i].DrawPesawat();

            // for bullet
            if(!adaPeluru){
                printf("save bullet pos");
                M[i].saveBulletPos();
                adaPeluru = true;
            }
            M[i].DrawBullet();
            M[i].moveBullet();
            if(M[i].getYBullet() > getmaxy()){
                M[i].saveBulletPos();
            }
        }

        delay(50);  // delay 50ms each iteration
    } while(1);

    getch();
    closegraph();
    return 0;
}
