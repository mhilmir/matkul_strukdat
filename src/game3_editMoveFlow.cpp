#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<stdio.h>

class Pesawat{
private :
    float x;
    float y;
    float sc;  // scale
    int Xmax ;
    int Ymax;
    int sty;  // determine plane speed

public:
    Pesawat(){
        sc = rand()%20 + 5;
        Xmax = getmaxx();
        Ymax = getmaxy();
        sty = rand()%20 + 4;
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

    void DrawPesawat(){
        line(0*sc+x,0*sc+y,1*sc+x,1*sc+y);
        line(1*sc+x,1*sc+y,0.5*sc+x,5*sc+y);
        line(0.5*sc+x,5*sc+y,0*sc+x,5*sc+y);

        line(0*sc+x,1*sc+y,3*sc+x,1*sc+y);
        line(3*sc+x,1*sc+y,3*sc+x,2*sc+y);
        line(3*sc+x,2*sc+y,0*sc+x,2*sc+y);


        line(-0*sc+x,0*sc+y,-1*sc+x,1*sc+y);
        line(-1*sc+x,1*sc+y,-0.5*sc+x,5*sc+y);
        line(-0.5*sc+x,5*sc+y,-0*sc+x,5*sc+y);

        line(-0*sc+x,1*sc+y,-3*sc+x,1*sc+y);
        line(-3*sc+x,1*sc+y,-3*sc+x,2*sc+y);
        line(-3*sc+x,2*sc+y,-0*sc+x,2*sc+y);
    }
};

int main()
{
    initwindow(500,500);
    class Pesawat P;
    P.Skala(20);
    class Pesawat M[20];
    float xh,yh;
    char c;

    do{
        cleardevice();
        if(kbhit()){
            c = getch();
            if (c == 27) break;
        }

        xh = mousex();
        yh = mousey() ;
        P.Posisi(xh, yh);
        P.DrawPesawat();

        for(int i=0; i<20; i++){
            M[i].MoveUp();
            M[i].DrawPesawat();
        }

        delay(50);
    } while(1);

    getch();
    closegraph();
    return 0;
}
