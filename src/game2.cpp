#include <graphics.h>
#include <stdlib.h>

int  main()
 {
   int x[1000],y[1000],v[1000],r[1000],w[1000];
   int f[1000],xp[1000],yp[1000];
   int xh,yh;
   for (int  i=0;i<1000;i++)
   {
       f[i]=0;
       x[i] = rand()%100;
       y[i] = rand()%200;
       r[i] = rand()%18+2;
       v[i] = rand()%5+1;
       w[i]= rand()%10+1;
   }
   initwindow(600,400);
   while (!kbhit())
   {
       cleardevice();
       for (int i = 0;i<1000;i++)
      {
       x[i]=x[i]+v[i];
       if (x[i]>getmaxx())
       {
           x[i]=x[i]-getmaxx();
       }
       setcolor(w[i]);
       circle(x[i],y[i],r[i]);
      }
      xh =mousex();
      yh =mousey();
      setcolor(3);
      circle(xh,yh,20);
      if (ismouseclick(WM_LBUTTONDOWN))
       {
           for (int i = 0;i<1000;i++)
           {
               if (f[i]==0)
               {
                   f[i]=1;
                   xp[i]=xh;
                   yp[i]=yh;
                   break;
               }
           }
        clearmouseclick(WM_LBUTTONDOWN);
       }
       for (int i=0;i<1000;i++)
       {
           if (f[i]==1)
           {
               yp[i]=yp[i]-5;
               if (yp[i]<0)
               {
                   f[i]=0;
               }
               circle(xp[i],yp[i],2);
            }

        }
    delay(50);
   }
   closegraph();//Menutup Grafik
   return 0;
 }
