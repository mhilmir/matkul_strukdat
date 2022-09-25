#include <iostream>

struct TNode{
    int data;
    TNode* next;
};

class TNode_manager{
private:
    TNode* head;
    TNode* tail;
public:
    TNode_manager(){
        head = new TNode;
        tail = new TNode;
    }

    void append(float input){
        TNode* tempNode = new TNode;
        tempNode->data = input;
        tempNode->next = NULL;

        if(head->next == NULL){  // first assignment
            head->data = tempNode->data;
            head->next = tempNode;

            tail = head;  // in the first assignment, head == tail
        } else{
            tail->next = tempNode;
            tail = tempNode;
        }
    }
    
    void display(){
        TNode* temp = head;
        while(temp){
            std::cout << temp << " - " <<  temp->data << " - " << temp->next << std::endl;
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    void insert(int index, float input){

    }
};

int main(){
    TNode_manager myLinkedList;
    myLinkedList.append(5);
    myLinkedList.append(6);
    myLinkedList.append(7);
    myLinkedList.append(8);
    myLinkedList.append(9);

    myLinkedList.display();

    myLinkedList.insert(2, 11);

    return 0;
}