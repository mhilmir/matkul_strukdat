 #include<graphics.h>

 main()
 {

  int x1,x2,x3,x4;
  int y1,y2,y3,y4;
  int xh,yh,xp,yp;
  int f;

   initwindow(600,400);//Inisialisasi Layar Grafik
   x1=0;
   y1 = 30;
   x2=0;
   y2=60;
   x3=0;
   y3= 90;
   f = 0;

   while (!kbhit())
   {   cleardevice();
       x1=x1+5;
       circle(x1,y1,10);
       if (x1>getmaxx())
       {x1 = x1 -getmaxx();
       }
       x2=x2+1;
       circle(x2,y2,20);
       if (x2>getmaxx())
       {x2 = x2 -getmaxx();
       }

       x3=x3+7;
       circle(x3,y3,5);
       if (x3>getmaxx())
       {x3 = x3 -getmaxx();
       }
       xh = mousex();
       yh = mousey();
       circle(xh,yh,15);
       if (ismouseclick(WM_LBUTTONDOWN))
       {
        f =1;
        xp =xh;
        yp = yh;
        clearmouseclick(WM_LBUTTONDOWN);
       }
       if (f==1)
        {
            yp = yp-4;
            circle(xp,yp,2);
        }
       if (yp<0)
       {
           f =0;
       }






       delay(50);
   }

   closegraph();//Menutup Grafik
 }
