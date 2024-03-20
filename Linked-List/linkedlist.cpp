#include <iostream>

// Define the structure for a singly linked list node
struct Node {
    int data;       // Data stored in the node
    Node* next;     // Pointer to the next node in the list
};

// Define the LinkedList class to manage linked list operations
class LinkedList {
private:
    Node* head;      // Pointer to the first node in the list

public:
    // Constructor to initialize an empty linked list
    LinkedList() {
        head = nullptr; // Initialize the head to nullptr
    }

    // Method to insert a new node at the beginning of the list
    void insertAtBeginning(int newData) {
        Node* newNode = new Node;   // Create a new node
        newNode->data = newData;    // Assign the data
        newNode->next = head;       // Point the new node to the current head
        head = newNode;             // Update the head to the new node
    }

    // Method to print the elements of the linked list
    void printList() {
        Node* current = head;       // Start at the head
        while (current != nullptr) {
            std::cout << current->data << " ";   // Print the data
            current = current->next;             // Move to the next node
        }
        std::cout << std::endl;
    }

    
};

int main() {
    LinkedList list;

    list.insertAtBeginning(5);
    list.insertAtBeginning(10);
    list.insertAtBeginning(15);
    list.insertAtBeginning(20);

    std::cout << "Linked List: ";
    list.printList();


    return 0;
}
