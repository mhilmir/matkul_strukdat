#include <iostream>

class nodaSaia{
private:
    TNode* head;
    TNode* tail;
public:
    void 
};

struct TNode{
    int data;
    TNode* next;
};

int main(){
    TNode* tempNode;  // node sementara sebagai sarana membuat node baru
    TNode* curNode;  // current node untuk menentukan di node mana kita sekarang berada

    TNode* Head;
    TNode* lastNode;
    // kita akan membuat linked list dengan urutan Head -> ............... -> lastNode

    /*
    new TNode ----> statement tersebut mereturn address yang memiliki kapasitas sebesar struct TNode
    */
    
    // membuat head node
    tempNode = new TNode;
    Head = tempNode;
    tempNode->data = 10;
    tempNode->next = NULL;
    lastNode = tempNode;
    /*
        | 10 |
         head
    */
    

    // nambah node
    tempNode = new TNode;
    tempNode->data = 5;
    tempNode->next = NULL;
    lastNode->next = tempNode;
    lastNode = tempNode;
    /*
        |   10   |   5   |
           head   lastNode
    */


    // nambah node
    tempNode = new TNode;
    tempNode->data = 6;
    tempNode->next = NULL;
    lastNode->next = tempNode;
    lastNode = tempNode;
    /*
        |   10   |   5   |   6   |
           head           lastNode
    */


    // inisialisasi curNode
    curNode = Head;
    
    // display linked list
    while(curNode){
        printf("%d ", curNode->data);
        curNode = curNode->next;
    }
    printf("\n");

    return 0;
}