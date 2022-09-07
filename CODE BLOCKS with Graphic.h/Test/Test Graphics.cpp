 #include<graphics.h>

 main()
 {
     int x,y;
     int f,xp,yp;
     f=0;
     initwindow(300,300);//Inisialisasi Layar Grafik

   while (!kbhit())

   {
       cleardevice();
       x=mousex();
       y=mousey();
       setcolor(WHITE);
       circle(x,y,20);
       if (f==1)
       {
           yp=yp-2;
           setcolor(WHITE);
       circle(xp,yp,5);

       }
       if (ismouseclick(WM_LBUTTONDOWN))
       {
           f=1;
           xp=x;
           yp=y;
           clearmouseclick(WM_LBUTTONDOWN);
       }

     delay(50);
   }

   closegraph();//Menutup Grafik
 }
