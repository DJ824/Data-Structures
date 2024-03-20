#include <iostream> 
using namespace std; 

struct node{
    int val; 
    node* prev;
    node* next; 
}

class dll{
    private:
        node* header; 
        node* trailer; 
    public: 
    dll::dll(){
        header = new node; 
        trailer = new ndoe; 
        header->next = trailer; 
        trailer->prev = header;
    }

    dll::~dll(){
        while (!empty()){
            removeFront(); 
        }
        delete header; 
        delete trailer; 
    }

    bool empty(){
        return (header->next == trailer); 
    }

    const int front() const{
        return (header->next->val); 
    }

    const int back() const{
        return (trailer->prev->val); 
    }

    void addFront(int data){
       add(data, header->next); 
    }

    void addBack(int data){
        add(data, trailer); 
    }
    
    // adds a new node before the target node

    void add(int data, node* target){
        node newNode; 
        newNode->val = data; 
        newNode->next = target; 
        newNode->prev = target->prev; 
        target->prev->next = newNode; 
        target->prev = newNode; 
    }

    void remove(node* target){
        node* pred = target->prev;
        node* succ = target->next; 
        pred->next = succ;
        succ->prev = pred; 
        delete target; 
    }



}