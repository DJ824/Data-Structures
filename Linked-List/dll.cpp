#include <iostream>
using namespace std;

template <typename T> struct Node {
  T val;
  Node *prev;
  Node *next;
};

template <typename T> class DLL {
private:
  Node<T> *header;
  Node<T> *trailer;

public:
  DLL() {
    header = new Node<T>;
    trailer = new Node<T>;
    header->next = trailer;
    trailer->prev = header;
  }

  ~DLL() {
    while (!empty()) {
      removeFront();
    }
    delete header;
    delete trailer;
  }

  bool empty() const { return (header->next == trailer); }

  const T &front() const { return (header->next->val); }

  const T &back() const { return (trailer->prev->val); }

  void addFront(const T &data) { add(data, header->next); }

  void addBack(const T &data) { add(data, trailer); }

  // adds a new node before the target node
  void add(const T &data, Node<T> *target) {
    Node<T> *newNode = new Node<T>;
    newNode->val = data;
    newNode->next = target;
    newNode->prev = target->prev;
    target->prev->next = newNode;
    target->prev = newNode;
  }

  void remove(Node<T> *target) {
    Node<T> *pred = target->prev;
    Node<T> *succ = target->next;
    pred->next = succ;
    succ->prev = pred;
    delete target;
  }

  void removeFront() { remove(header->next); }

  void removeBack() { remove(trailer->prev); }

  void reverse() {
    Node<T> *temp = nullptr;
    Node<T> *current = header;
    while (current != nullptr) {
      temp = current->prev;
      current->prev = current->next;
      current->next = temp;
      current = current->prev;
    }
    temp = header;
    header = trailer;
    trailer = temp;
    header->prev = nullptr;
    trailer->next = nullptr;
  }
};

int main() {}
