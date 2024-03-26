// Data Structures and Algorithms in C++ by Goodrich  Chapter 6 List source code.
// Filename: List.cpp
// Compile command: g++ List.cpp -o List.exe

#include <iostream>

using namespace std;

// Runtime Exception
class RuntimeException
{
private:
    string errorMsg;

public:
    RuntimeException(const string &err) { errorMsg = err; }
    string getMessage() const { return errorMsg; }
};

// List Empty Exception
class ListEmpty : public RuntimeException
{
public:
    ListEmpty(const string &err) : RuntimeException(err) {}
};

template <typename E>
class NodeList
{ // node-based list

protected:
    template <typename F>

    class Node
    {                          // a node of the list
        E elem;                // Element value
        Node<F> *prev;         // previous in list
        Node<F> *next;         // next in list
        friend class NodeList; // give NodeList access
    };

public: // insert Iterator declaration here...
    class Iterator
    { // an iterator for the list
    public:
        E &operator*() { return v->elem; };                            // reference to the element
        bool operator==(const Iterator &p) const { return v == p.v; }; // compare positions
        bool operator!=(const Iterator &p) const { return v != p.v; };
        Iterator &operator++()
        {
            v = v->next;
            return *this;
        }; // move to next position
        Iterator &operator--()
        {
            v = v->prev;
            return *this;
        };                     // move to previous position
        friend class NodeList; // give NodeList access
    private:
        Node<E> *v;                      // pointer to the node
        Iterator(Node<E> *u) { v = u; }; // create from node
    };

public:
    NodeList()
    {          // constructor
        n = 0; // initially empty

        header = new Node<E>; // create sentinels
        trailer = new Node<E>;

        header->next = trailer; // have them point to each other
        trailer->prev = header;
    }; // default constructor

    int size() const { return n; }; // list size

    bool empty() const { return (n == 0); }; // is the list empty?

    Iterator begin() const { return Iterator(header->next); }; // beginning position

    Iterator end() const { return Iterator(trailer); }; // (just beyond) last position

    void insertFront(const E &e) { insert(begin(), e); }; // insert at front

    void insertBack(const E &e) { insert(end(), e); }; // insert at rear

    void insert(const Iterator &p,
                const E &e) // insert e before p
    {
        Node<E> *w = p.v;         // p's node
        Node<E> *u = w->prev;     // p's predecessor
        Node<E> *v = new Node<E>; // new node to insert
        v->elem = e;
        v->next = w;
        w->prev = v; // link in v before w
        v->prev = u;
        u->next = v; // link in v after u
        n++;
    };

    void eraseFront() throw(ListEmpty)
    {
        if (empty())
            throw ListEmpty("front of empty list");
        erase(begin());
    }; // remove first

    void eraseBack() throw(ListEmpty)
    {
        if (empty())
            throw ListEmpty("front of empty list");
        erase(--end());
    }; // remove last

    void erase(const Iterator &p) throw(ListEmpty)
    {
        // remove p
        if (empty())
            throw ListEmpty("front of empty list");

        Node<E> *v = p.v;     // node to remove
        Node<E> *w = v->next; // successor
        Node<E> *u = v->prev; // predecessor
        u->next = w;
        w->prev = u; // unlink p
        delete v;    // delete this node
        n--;         // one fewer element
    };

    // housekeeping functions omitted...

private:              // data members
    int n;            // number of items
    Node<E> *header;  // head-of-list sentinel
    Node<E> *trailer; // tail-of-list sentinel
};

int main(int argc, const char *argv[])
{

    cout << "Using NodeList..." << endl;

    NodeList<int> A;

    A.insertFront(8);

    NodeList<int>::Iterator p = A.begin();

    cout << "Front element is : " << *p << endl;

    A.insertBack(5);

    NodeList<int>::Iterator q = p;
    ++q;
    cout << "Back element is : " << *q << endl;

    p == A.begin();

    A.insert(q, 3);

    *q = 7;

    cout << "q element is : " << *q << endl;

    A.insertFront(9);

    cout << "p element is : " << *p << endl;

    A.eraseBack();

    NodeList<int>::Iterator r = A.begin();
    cout << "Front element is : " << *r << endl;
    ++r;
    cout << "Next element is : " << *r << endl;
    ++r;
    cout << "Next element is : " << *r << endl;

    A.erase(p);

    r = A.begin();
    cout << "Front element is : " << *r << endl;

    A.eraseFront();

    r = A.begin();
    cout << "Front element is : " << *r << endl;

    return 0;
}