#include <iostream> 
using namespace std; 

struct Node{
    int data; 
    Node* next; 
};

class LinkedList{
    private: 
        Node* head; 

    public: 
        LinkedList(){
            head = nullptr; 
        }

        void addToHead(Node* &head, int newData){
            Node* newNode = new Node;   // create a new node 
            newNode->data = newData;    // assign data to insert into new node 
            newNode->next = head;       // assign pointer of new node to current head node
            head = newNode;             // assign the head ptr to the newly created node 
        }

        void printList(Node* head){
            Node* current = head;       // create node ptr to access head 
            // if the list is not empty, use the node ptr to print the data inside the node and update the node ptr to point to the next node
            while(current != nullptr){  
                cout << current->data << " ";
                current = current->next; 
            }
        }
         void printRecursive(Node* head){
             Node* current = head; 
             if (current == nullptr){
                return;
             } 
             printRecursive(current->next);

        }
        
        void deleteTarget(Node* &head, int value){
            if (head->data == value){    
                Node* temp = head;      // create temp variable to hold ptr to head node
                head = head->next;      // assign head ptr to the next node of prev head ptr 
                delete temp;            // delete temp ptr to prev head node 
                return;
            }

           Node* current = head; 
           Node* prev = nullptr; 

           while(current != nullptr && current->data != value){     // loop checking if we are at target node to delete
            prev = current;             // update prev pointer to current node
            current = current->next;    // update current pointer to next node 
           }

           if (current == nullptr){      // if we reached last node return 
            return; 
           }

           Node* temp = current;        // once at target node, create temp pointer to store node to delete
           prev->next = current->next;  // update next pointer of the prev node to the node pointed after target node  
           delete current;              // delete pointer to target node 
        }

        void insertTarget(Node*& head,int value, int target){   
            Node* current = head; 

            while(current != nullptr && current->data != target){
                current = current->next; 
            }

            Node* newNode = new Node;    // create new node to be added 
            newNode->data = value;       
            newNode->next = current->next;      // update next pointer of newnode to node after target 
            current->next = newNode;            // update next pointer of target to newly created node 
        }

        void reverse(Node* &head){
            Node* current = head; 
            Node* prev = nullptr; 
            Node* temp; 

            while(current != nullptr){
                temp = current->next; // temp variable to hold address of next node 
                current->next = prev; // reverse pointer of current node to prev node 
                prev = current;       // store current node as prev node 
                current = temp;       // update current node from the temp node 
            }
            head = prev; // after looping, current will be null and prev will be at the head  
        }
};



int main(){
    LinkedList l1; 
    LinkedList l2; 

    Node* head1 = nullptr;
    Node* head2 = nullptr; 

    l1.addToHead(head1, 8); 
    l1.addToHead(head1, 7); 
    l1.addToHead(head1, 6); 
    l1.addToHead(head1, 5); 

    cout << "l1:" << endl; 
    l1.printList(head1); 
    cout << endl; 

    l2.addToHead(head2, 4);
    l2.addToHead(head2, 3);
    l2.addToHead(head2, 2);
    l2.addToHead(head2, 1);
    
    cout << "l2:" << endl; 

    l2.printList(head2); 

    
            
 }