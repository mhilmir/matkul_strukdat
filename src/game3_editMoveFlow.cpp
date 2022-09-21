#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<stdio.h>

class Pesawat{
private :
    float x;
    float y;
    float sc;  // scale
    int Xmax ;  // screen x max
    int Ymax;  // screen y max
    int sty;  // determine plane speed y
    int stx;  // determine plane speed x

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

    void MoveRightBeta(){
        x = x + stx;
        if (x > Xmax){
            x = x - Xmax;
        }
    }

    void DrawPesawat(){
        line((0*sc + x), (0*sc + y), (1*sc + x), (1*sc + y));
        line((1*sc + x), (1*sc + y), (0.5*sc + x), (5*sc + y));
        line((0.5*sc + x), (5*sc + y), (0*sc + x), (5*sc + y));

        line((0*sc + x), (1*sc + y), (3*sc + x), (1*sc + y));
        line((3*sc + x), (1*sc + y), (3*sc + x), (2*sc + y));
        line((3*sc + x), (2*sc + y), (0*sc + x), (2*sc + y));

        line((0*sc + x), (0*sc + y), (-1*sc + x), (1*sc + y));
        line((-1*sc + x), (1*sc + y), (-0.5*sc + x), (5*sc + y));
        line((-0.5*sc + x), (5*sc + y), (0*sc + x), (5*sc + y));

        line((0*sc + x), (1*sc + y), (-3*sc + x), (1*sc + y));
        line((-3*sc + x), (1*sc + y), (-3*sc + x), (2*sc + y));
        line((-3*sc + x), (2*sc + y), (0*sc + x), (2*sc + y));
    }
};

int main()
{
    initwindow(500,500);
    Pesawat P;
    P.Skala(20);
    Pesawat M[20];
    float xh,yh;
    char c;

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

        // move pesawat ke kanan betaa
        for(int i=0; i<20; i++){
            M[i].MoveRightBeta();
            M[i].DrawPesawat();
        }

        delay(50);  // delay 50ms each iteration
    } while(1);

    getch();
    closegraph();
    return 0;
}
