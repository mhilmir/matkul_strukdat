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
    float body[5][2] = {{0,0}, {1,1}, {0.5,5}, {-0.5,5}, {-1,1}};  // for drawing body plane
    float wing[4][2] = {{3,1}, {3,2}, {-3,2}, {-3,1}};  // for drawing wing plane

public:
    Pesawat(){
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
        // convert degree to radian
        float rad = degree * (PI/180);

        // rotating body
        for(int i=0; i<5; i++){
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
        for(int i=0; i<4; i++){
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
        line((body[4][0]*sc + x), (body[4][1]*sc + y), (body[0][0]*sc + x), (body[0][1]*sc + y));

        // drawing wing of plane
        line((wing[0][0]*sc + x), (wing[0][1]*sc + y), (wing[1][0]*sc + x), (wing[1][1]*sc + y));
        line((wing[1][0]*sc + x), (wing[1][1]*sc + y), (wing[2][0]*sc + x), (wing[2][1]*sc + y));
        line((wing[2][0]*sc + x), (wing[2][1]*sc + y), (wing[3][0]*sc + x), (wing[3][1]*sc + y));
        line((wing[3][0]*sc + x), (wing[3][1]*sc + y), (wing[0][0]*sc + x), (wing[0][1]*sc + y));
    }
};

int main(){
    initwindow(500,500);
    Pesawat P;
    P.Skala(20);
    Pesawat M[20];
    float xh,yh;
    char c;

    // harus dijalankan cuma sekali
    P.RotatePesawat(90);
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
        P.Posisi(xh, yh);
        P.DrawPesawat();

        // move pesawat ke atas
        // for(int i=0; i<20; i++){
        //     M[i].MoveUp();
        //     M[i].DrawPesawat();
        // }

        // move pesawat ke kanan
        for(int i=0; i<20; i++){
            M[i].MoveRight();
            M[i].DrawPesawat();
        }

        delay(50);  // delay 50ms each iteration
    } while(1);

    getch();
    closegraph();
    return 0;
}
