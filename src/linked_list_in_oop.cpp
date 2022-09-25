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
            // std::cout << "masuk ke head" << std::endl;
            head->data = tempNode->data;
            head->next = tempNode;

            tail = head;  // in the first assignment, head == tail
        } else{
            // std::cout << "masuk ke tail" << std::endl;
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
};

int main(){
    TNode_manager linkedList;
    linkedList.append(5);
    linkedList.append(6);
    linkedList.append(7);

    linkedList.display();

    return 0;
}