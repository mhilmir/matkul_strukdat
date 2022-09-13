/////////////
for linux,
//////////////
if you want to compile src file that contains graphics.h inside,
you have to add -lgraph when compiling
example : g++ filename.cpp -lgraph

remember!!! winbgim.h only for windows



/////////////
for windows,
//////////////
if you want to compile src file that contains graphics.h inside,
you have to add this following arguments when compiling :
    -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
example : g++ filename.cpp -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
