#include <stdio.h>

struct TNode{
    int data;
    TNode* next;
};

void X(int* d){
    *d = 10;
}

int main(){
    TNode* Head;
    TNode* newNode;
    TNode* prevNode;
    TNode* curNode;

    newNode = new TNode;  // newNode = 3
    Head = newNode;  // Head =3
    newNode->data = 10;
    newNode->next = NULL;
    prevNode = newNode;  // 3
    // ---------
    // |3 |
    // |10 |Null|
    // ---------
    newNode = new TNode;// newNode = 10
    newNode->data=5;
    newNode->next=NULL;
    prevNode->next = newNode;
    prevNode = newNode;
    // --------- ---------
    // |3 | |10 |
    // |10 |10 | |5 |NULL|
    // --------- ---------


    newNode = new TNode;// newNode = 1
    newNode->data=6;
    newNode->next=NULL;
    prevNode->next = newNode;
    prevNode = newNode;
    curNode =Head;
    while(curNode)
    {
    printf("%d ",curNode->data);
    curNode = curNode->next;
    }



    int c;
    c = 1;
    X(&c);




    return 0;
}