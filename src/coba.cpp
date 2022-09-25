#include <iostream>

int main(){
    
    int* i = new int;

    *i = 78;

    std::cout << i << " " << *i << std::endl;
    return 0;
}