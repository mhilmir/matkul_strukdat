#include <iostream>
#include <unistd.h>

struct iniNode{
    float data;
    iniNode* below;
};

class Stack{
private:
    iniNode* downNode;
    iniNode* topNode;
    int len;
public:
    Stack(){
        downNode = new iniNode;
        topNode = new iniNode;
        downNode->below = NULL;
        topNode->below = NULL;
        len = 0;
    }

    void push(float inp){
        iniNode* temp = new iniNode;
        if(!len){  // input saat stack kosong
            temp->data = inp;
            temp->below = NULL;

            downNode = temp;
            topNode = temp;
        } else{  // input saat stack ada isinya
            temp = topNode;

            topNode = new iniNode;
            topNode->data = inp;
            topNode->below = temp;
        }
        len++;
    }

    void display(){
        iniNode* temp = topNode;
        std::cout << "ini top ygy" << std::endl;
        while(temp){
            std::cout << temp << " ==> " <<  temp->data << " -- " << temp->below << std::endl;
            temp = temp->below;
        }
        std::cout << "ini down ygy" << std::endl;
    }

    void pop(){
        topNode = topNode->below;
        len--;
    }

    bool isEmpty(){
        if(!len){
            return 1;
        } return 0;
    }

    int getLength(){
        return len;
    }
};

int main(){
    Stack stackKuhh;
    unsigned int sec_to_microsec = 1000000;

    std::cout << "check dengan isEmpty() : ";
    if(stackKuhh.isEmpty()){
        std::cout << "ini stack khosong" << std::endl << std::endl;
    }

    std::cout << "Add 5 elements" << std::endl;
    usleep(1*sec_to_microsec);
    std::cout << "please wait..." << std::endl;
    usleep(2*sec_to_microsec);
    stackKuhh.push(5.0);
    stackKuhh.push(6.0);
    stackKuhh.push(7.0);
    stackKuhh.push(8.0);
    stackKuhh.push(9.0);
    std::cout << "adding process completed" << std::endl << std::endl;
    usleep(1*sec_to_microsec);

    // displaying linked list
    std::cout << "length : " << stackKuhh.getLength() << std::endl;
    stackKuhh.display();
    usleep(2*sec_to_microsec);

    // remove
    std::cout << "\nPOP OUT 1 element" << std::endl;
    usleep(1*sec_to_microsec);
    stackKuhh.pop();
    std::cout << "delete process completed" << std::endl;
    usleep(1*sec_to_microsec);
    std::cout << std::endl;

    // displaying linked list
    std::cout << "length : " << stackKuhh.getLength() << std::endl;
    stackKuhh.display();
    usleep(2*sec_to_microsec);

    std::cout << std::endl << "Add 7 elements" << std::endl;
    usleep(1*sec_to_microsec);
    std::cout << "please wait..." << std::endl;
    usleep(2*sec_to_microsec);
    stackKuhh.push(21);
    stackKuhh.push(22);
    stackKuhh.push(23);
    stackKuhh.push(24);
    stackKuhh.push(25);
    stackKuhh.push(26);
    stackKuhh.push(27);
    std::cout << "adding process completed" << std::endl << std::endl;
    usleep(1*sec_to_microsec);

    // displaying linked list
    std::cout << "length : " << stackKuhh.getLength() << std::endl;
    stackKuhh.display();
    usleep(2*sec_to_microsec);

    // remove
    std::cout << "\nPOP OUT 4 element" << std::endl;
    usleep(1*sec_to_microsec);
    stackKuhh.pop();
    stackKuhh.pop();
    stackKuhh.pop();
    stackKuhh.pop();
    std::cout << "delete process completed" << std::endl;
    usleep(1*sec_to_microsec);
    std::cout << std::endl;

    // displaying linked list
    std::cout << "length : " << stackKuhh.getLength() << std::endl;
    stackKuhh.display();
    usleep(2*sec_to_microsec);

    std::cout << std::endl << "check dengan isEmpty() : ";
    if(!stackKuhh.isEmpty()){
        std::cout << "sudah ada isinya" << std::endl;
    }

    return 0;
}