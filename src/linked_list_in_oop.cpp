#include <iostream>
#include <unistd.h>
// #include <windows.h>

struct TNode{
    float data;
    TNode* next;
};

class TNode_manager{
private:
    TNode* head;
    TNode* tail;
    int length;
public:
    TNode_manager(){
        head = new TNode;
        tail = new TNode;
        length = 0;
    }

    int getLength(){
        return length;
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
        length++;
    }
    
    void display(){
        TNode* temp = head;
        while(temp){
            std::cout << temp << " ==> " <<  temp->data << " -- " << temp->next << std::endl;
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    void insert(int index, float input){
        int i = 0;
        TNode* tempIter = head;
        TNode* newNode = new TNode;
        newNode->data = input;

        while(tempIter){
            if(i == index-1){
                newNode->next = tempIter->next;
                tempIter->next = newNode;
                break;
            }
            tempIter = tempIter->next;
            i++;
        }
        length++;
    }

    void remove(int index){
        int i = 0;
        TNode* tempIter = head;

        while(tempIter){
            if(i == index-1){
                tempIter->next = (tempIter->next)->next;
                break;
            }
            tempIter = tempIter->next;
            i++;
        }
        length--;
    }

    int search(float target){
        int result = -1;
        int i = 0;
        TNode* tempIter = head;

        while(tempIter){
            if(tempIter->data == target){
                result = i;
                break;
            }
            tempIter = tempIter->next;
            i++;
        }
        return result;
    }

    float get(int index){
        int i = 0;
        TNode* tempIter = head;

        while(tempIter){
            if(i == index){
                return tempIter->data;
            }
            tempIter = tempIter->next;
            i++;
        }
    }

    void set(int index, float newValue){
        int i = 0;
        TNode* tempIter = head;

        while(tempIter){
            if(i == index){
                tempIter->data = newValue;
                break;
            }
            tempIter = tempIter->next;
            i++;
        }
    }

    float max(){
        float maxVAl;
        TNode* tempIter = head;

        maxVAl = tempIter->data;
        while(tempIter){
            if(maxVAl < tempIter->data){
                maxVAl = tempIter->data;
            }
            tempIter = tempIter->next;
        }

        return maxVAl;
    }

    float min(){
        float minVAl;
        TNode* tempIter = head;

        minVAl = tempIter->data;
        while(tempIter){
            if(minVAl > tempIter->data){
                minVAl = tempIter->data;
            }
            tempIter = tempIter->next;
        }

        return minVAl;
    }

    void reverse(){
        // TNode* tempIter_1 = head;  // for the beginning, tempIter_1 store 1st node
        // TNode* tempIter_2 = tempIter_1->next;  // for the beginning, tempIter_2 store 2nd node
        
        // for(tempIter_1 = head)
    }
};

int main(){
    unsigned int sec_to_microsec = 1000000;
    // unsigned int sec_to_milisec = 1000;
    TNode_manager myLinkedList;

    std::cout << "Add 5 elements" << std::endl;
    // Sleep(1*sec_to_milisec);
    usleep(1*sec_to_microsec);
    std::cout << "please wait..." << std::endl;
    // Sleep(2*sec_to_milisec);
    usleep(2*sec_to_microsec);
    myLinkedList.append(5);
    myLinkedList.append(6);
    myLinkedList.append(7);
    myLinkedList.append(8);
    myLinkedList.append(9);
    std::cout << "adding process completed" << std::endl << std::endl;
    // Sleep(1*sec_to_milisec);
    usleep(1*sec_to_microsec);

    // displaying linked list
    std::cout << "length : " << myLinkedList.getLength() << std::endl;
    myLinkedList.display();
    // Sleep(2*sec_to_milisec);
    usleep(2*sec_to_microsec);

    // insertion
    std::cout << "inserting 11 at index no-2" << std::endl;
    // Sleep(1*sec_to_milisec);
    usleep(1*sec_to_microsec);
    myLinkedList.insert(2, 11);
    std::cout << "insertion completed" << std::endl;
    // Sleep(1*sec_to_milisec);
    usleep(1*sec_to_microsec);
    std::cout << std::endl;

    // displaying linked list
    std::cout << "length : " << myLinkedList.getLength() << std::endl;
    myLinkedList.display();
    // Sleep(2*sec_to_milisec);
    usleep(2*sec_to_microsec);

    // insertion
    std::cout << "inserting 31.3 at index no-4" << std::endl;
    // Sleep(1*sec_to_milisec);
    usleep(1*sec_to_microsec);
    myLinkedList.insert(4, 31.3);
    std::cout << "insertion completed" << std::endl;
    // Sleep(1*sec_to_milisec);
    usleep(1*sec_to_microsec);
    std::cout << std::endl;

    // displaying linked list
    std::cout << "length : " << myLinkedList.getLength() << std::endl;
    myLinkedList.display();
    // Sleep(2*sec_to_milisec);
    usleep(2*sec_to_microsec);

    // remove
    std::cout << "deleting element at index no-3" << std::endl;
    // Sleep(1*sec_to_milisec);
    usleep(1*sec_to_microsec);
    myLinkedList.remove(3);
    std::cout << "delete process completed" << std::endl;
    // Sleep(1*sec_to_milisec);
    usleep(1*sec_to_microsec);
    std::cout << std::endl;

    // displaying linked list
    std::cout << "length : " << myLinkedList.getLength() << std::endl;
    myLinkedList.display();
    // Sleep(2*sec_to_milisec);
    usleep(2*sec_to_microsec);

    // searching
    std::cout << "searching 31.3 in linked list" << std::endl;
    std::cout << "please wait..." << std::endl;
    // Sleep(2*sec_to_milisec);
    usleep(2*sec_to_microsec);
    int x = myLinkedList.search(31.3);
    if(x == -1){
        std::cout << "unfortunately, the searched value was not found" << std::endl;
    } else{
        std::cout << "founded at index no. " << x << std::endl; 
    }
    std::cout << "\n";
    // Sleep(2*sec_to_milisec);
    usleep(2*sec_to_microsec);

    // get
    std::cout << "get element with index no. 4" << std::endl;
    // Sleep(1*sec_to_milisec);
    usleep(1*sec_to_microsec);
    int temp = myLinkedList.get(4);
    std::cout << "myLinkedList index no-4 : " << temp << std::endl;
    // Sleep(2*sec_to_milisec);
    usleep(2*sec_to_microsec);
    std::cout << "\n";

    // search and set
    std::cout << "length : " << myLinkedList.getLength() << std::endl;
    myLinkedList.display();
    std::cout << "search value 8 and set it to 77.7" << std::endl;
    // Sleep(1*sec_to_milisec);
    usleep(1*sec_to_microsec);
    std::cout << "please wait..." << std::endl;
    // Sleep(2*sec_to_milisec);
    usleep(2*sec_to_microsec);
    myLinkedList.set(myLinkedList.search(8), 77.7);
    std::cout << "done" << std::endl;
    // Sleep(0.5*sec_to_milisec);
    usleep(0.5*sec_to_microsec);
    std::cout << "\n";
    std::cout << "length : " << myLinkedList.getLength() << std::endl;
    myLinkedList.display();
    // Sleep(2*sec_to_milisec);
    usleep(2*sec_to_microsec);

    // get max and min
    std::cout << "maximum value : " << myLinkedList.max() << std::endl;
    // Sleep(1.5*sec_to_milisec);
    usleep(1.5 * sec_to_microsec);
    std::cout << "minimum value : " << myLinkedList.min() << std::endl;
    // Sleep(1.5*sec_to_milisec);
    usleep(1.5 * sec_to_microsec);
    std::cout << "\n";

    return 0;
}