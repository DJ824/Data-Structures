// Filename: Queue.cpp
// Compile command: g++ Queue.cpp -o Queue.exe

#include <iostream>
// #include <list>

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

// Queue Empty Exception
class QueueEmpty : public RuntimeException
{
public:
    QueueEmpty(const string &err) : RuntimeException(err) {}
};

// Queue Full Exception
class QueueFull : public RuntimeException
{
public:
    QueueFull(const string &err) : RuntimeException(err) {}
};

template <typename E>
class CArrayQueue
{
public:
    // constructor given capacity
    CArrayQueue(int c) : Q(new E[c]), cap(c), f(0), r(0), n(0){};

    int size() const { return n; };
    bool empty() const { return (n == 0); };

    const E &front() const throw(QueueEmpty)
    {
        if (empty())
            throw QueueEmpty("Empty Queue");
        return Q[f];
    };

    void dequeue() throw(QueueEmpty)
    {
        if (empty())
            throw QueueEmpty("Empty Queue");
        f = (f + 1) % cap;
        n--;
    };

    void enqueue(const E &e) throw(QueueFull)
    {
        if (size() == cap)
            throw QueueFull("Full Queue");
        Q[r] = e;
        r = (r + 1) % cap;
        n++;
    };

private:
    E *Q;     // array holding the queue
    int cap;  // array capacity
    int f, r; // index of front and rear
    int n;    // number of queue elements
};

template <typename E>
class CircleList
{ // a circularly linked list

protected:
    template <typename F>
    class CNode
    { // circularly linked list node
    private:
        E elem;         // linked list element value
        CNode<F> *next; // next item in the list

        friend class CircleList<E>;
    };

public:
    CircleList() : cursor(NULL){}; // constructor

    ~CircleList()
    {
        while (!empty())
            remove();
    }; // destructor

    bool empty() const { return cursor == NULL; }; // is list empty?

    const E &front() const { return cursor->next->elem; }; // element following cursor

    const E &back() const { return cursor->elem; }; // element at cursor

    void advance() { cursor = cursor->next; }; // advance cursor

    void add(const E &e)
    { // add after cursor

        CNode<E> *v = new CNode<E>; // create  new node
        v->elem = e;
        if (cursor == NULL)
        {                // list is empty?
            v->next = v; // v points to itself
            cursor = v;  // cursor points to v
        }
        else
        {                           // list is nonempty?
            v->next = cursor->next; // link in v after cursor
            cursor->next = v;
        }
    };

    void remove()
    {                                 // remove node after cursor
        CNode<E> *old = cursor->next; // the node being removed
        if (old == cursor)            // removing the only node?
            cursor = NULL;            // list is now empty
        else
            cursor->next = old->next; // link out the old node
        delete old;                   // delete the old node
    };

    int countNodes() const
    {
        if (empty())
            return 0;
        else if (cursor == cursor->next)
            return 1;
        else
        {
            int count = 2;
            CNode<E> *temp = cursor->next;
            while (temp->next != cursor)
            {
                ++count;
                temp = temp->next;
            }
            return count;
        }
    };

private:
    CircleList::CNode<E> *cursor; // the cursor
};

template <typename Elem>
class LinkedQueue
{ // queue as circularly linked list
public:
    LinkedQueue() : C(), n(0){};                     // constructor
    int size() const { return n; };                  // number of items in the queue
    int sizeList() const { return C.countNodes(); }; // Count of Nodes in List is same as size()
    bool empty() const { return n == 0; };           // is the queue empty?

    const Elem &front()
        const throw(QueueEmpty) // the front element
    {
        if (empty())
            throw QueueEmpty("front of empty queue");
        return C.front(); // list front is queue front
    };

    void enqueue(const Elem &e) // enqueuee at rear
    {
        C.add(e);    // insert after cursor
        C.advance(); // ...and advance
        n++;
    };

    void dequeue() throw(QueueEmpty) // dequeue at front
    {
        if (empty())
            throw QueueEmpty("dequeue of empty queue");
        C.remove(); // remove from list front
        n--;
    };

private:                // member data
    CircleList<Elem> C; // circular list of elements
    int n;              // number of elements
};

int main(int argc, const char *argv[])
{

    cout << "Using CArray Queue..." << endl;
    CArrayQueue<int> A(10);

    A.enqueue(5);
    A.enqueue(3);
    cout << "front is " << A.front() << endl;
    A.dequeue();
    cout << "front is " << A.front() << endl;
    A.enqueue(7);
    cout << "front is " << A.front() << endl;
    A.dequeue();
    cout << "front is " << A.front() << endl;
    A.dequeue();
    cout << "empty is " << A.empty() << endl;
    A.enqueue(9);
    A.enqueue(7);
    cout << "size is " << A.size() << endl;
    A.enqueue(3);
    cout << "front is " << A.front() << endl;
    A.enqueue(5);
    A.dequeue();
    cout << "front is " << A.front() << endl;
    cout << "size is " << A.size() << endl;

    cout << "Using Linked Queue..." << endl;
    LinkedQueue<int> B;

    B.enqueue(5);
    B.enqueue(3);
    cout << "front is " << B.front() << endl;
    B.dequeue();
    cout << "front is " << B.front() << endl;
    B.enqueue(7);
    cout << "front is " << B.front() << endl;
    B.dequeue();
    cout << "front is " << B.front() << endl;
    B.dequeue();
    cout << "empty is " << B.empty() << endl;
    B.enqueue(9);
    B.enqueue(7);
    cout << "size is " << B.size() << endl;
    cout << "sizeList is " << B.sizeList() << endl;
    B.enqueue(3);
    cout << "front is " << B.front() << endl;
    B.enqueue(5);
    B.dequeue();
    cout << "front is " << B.front() << endl;
    cout << "size is " << B.size() << endl;
    cout << "sizeList is " << B.sizeList() << endl;
    return 0;
}