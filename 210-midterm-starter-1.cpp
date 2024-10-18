// COMSC-210 | Midterm #1 | Yukun Zhang
// IDE used: Visual Studio Code

#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    //The node structure, containing an int data, a pointer to the front node and a pointer to the back node.
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) {//Constructors with default initial values can either complete the default initialization with just int val, or add the required prev or next pointers.
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    //Good default constructor to create empty DLLs
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    //Input value and position, generate a new node with the data and insert it into the current DLL with the input position
    void insert_after(int value, int position) {
        if (position < 0) {//Check that the position is positive
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {//Check if the current DLL is empty
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)//Loop to find the position, 
            temp = temp->next;

        if (!temp) {//position is too large
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;//Insert node
        newNode->prev = temp;
        if (temp->next)//If it's not the last one
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    //Delete the a node in DLL by search data
    void delete_val(int value) {
        if (!head) return; //If it is empty

        Node* temp = head;
        
        while (temp && temp->data != value)//Find the node that contains the target data
            temp = temp->next;

        if (!temp) return; //didn't find it

        if (temp->prev)
            temp->prev->next = temp->next;
        else// if it is head, change the head
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else// if it is head, change the tail
            tail = temp->prev; 

        delete temp;
    }

    //Delete the a node in DLL by position
    void delete_pos(int pos) {
        if (!head) {// if DLL is empty
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {//Delete the head
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){//find position
            if (!temp) {//position too large
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {//position too large
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {//is tail, delete tail
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;//delete a non-tail, non-head node
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    //Accept an int, generate a new node to add to the tail
    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)//if DLL is empty
            head = tail = newNode;//insert as the first and last node
        else {
            tail->next = newNode;//insert to tail, and update tail only
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    //Accept an int, generate a new node to add to the head
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)//if DLL is empty
            head = tail = newNode;//insert as the first and last node
        else {
            newNode->next = head;//insert to head, and update head only
            head->prev = newNode;
            head = newNode;
        }
    }
    
    //delete the node pointed to by head
    void pop_front() {

        if (!head) {//if DLL is empty
            cout << "List is empty." << endl;
            return;//do nothing
        }

        Node * temp = head;

        if (head->next) {//if this is not the last node in the DLL
            head = head->next;//update head to next one
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;//update head and tail, now the DLL is empty
        delete temp;//delete node
    }

    //delete the node pointed to by tail
    void pop_back() {
        if (!tail) {//if DLL is empty
            cout << "List is empty." << endl;
            return;//do nothing
        }
        Node * temp = tail;

        if (tail->prev) {//if this is not the last node in the DLL
            tail = tail->prev;//update tail to the previous one
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;//update head and tail, now the DLL is empty
        delete temp;//delete node
    }

    //destructor, completely deletes the node within each DLL, freeing up memory
    ~DoublyLinkedList() {
        while (head) {//traverse and delete all nodes
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    //output data in DLL, fron head to tail
    void print() {
        Node* current = head;
        if (!current) {//nothing in the DLL
            cout << "List is empty." << endl;
            return;
        }
        while (current) {//traverse all nodes from head, output all data
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    //output data in DLL, fron head to tail
    void print_reverse() {
        Node* current = tail;
        if (!current) { //nothing in the DLL
            cout << "List is empty." << endl;
            return;
        }
        while (current) {//traverse all nodes from tail, output all data
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    //My output function
    //Ignores all elements in even positions, and outputs only those in odd positions.
    void every_other_element() {
        Node* current = head;
        int count = 1;
        if (!current) {//nothing in the DLL
            cout << "List is empty." << endl;
            return;
        }
        while (current) {//traverse all nodes from head
            if (count % 2 == 1) //If the element is in an odd position, output
                cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}