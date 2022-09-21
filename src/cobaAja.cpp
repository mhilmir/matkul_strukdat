#include <iostream>
#include <dos.h>

int main(){
    float body[5][2] = {{0,0}, {1,1}, {0.5,5}, {-0.5,5}, {-1,1}};
    std::cout << sizeof(body)/sizeof(float) << std::endl;
    return 0;
}