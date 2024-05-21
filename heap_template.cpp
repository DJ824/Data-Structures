// Data Structures and Algorithms in C++ by Goodrich  Chapter 8 HeapPriorityQueue source code
// Filename: HeapPriorityQueue.cpp
// Compile command: g++ HeapPriorityQueue.cpp -o HeapPriorityQueue.exe

#include <iostream>
#include <vector>

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

// HeapPriorityQueue Empty Exception
class HeapPriorityQueueEmpty : public RuntimeException
{
public:
    HeapPriorityQueueEmpty(const string &err) : RuntimeException(err) {}
};

class isLess
{ // IsLess comparator
public:
    bool operator()(const int &p, const int &q) const
    {
        return p < q;
    }
};

template <typename E>
class VectorCompleteTree
{

public:                                            // publicly accessible types
    typedef typename vector<E>::iterator Position; // a position in the tree

protected:                                         // protected utility functions
    Position pos(int i) { return V.begin() + i; }; // map an index to a position

    int idx(const Position &p) const { return p - V.begin(); }; // map a position to an index

public:
    VectorCompleteTree() : V(1) {} // constructor
    int size() const { return V.size() - 1; };
    Position left(const Position &p) { return pos(2 * idx(p)); };
    Position right(const Position &p) { return pos(2 * idx(p) + 1); };
    Position parent(const Position &p) { return pos(idx(p) / 2); };
    bool hasLeft(const Position &p) const { return 2 * idx(p) <= size(); };
    bool hasRight(const Position &p) const { return 2 * idx(p) + 1 <= size(); };
    bool isRoot(const Position &p) const { return idx(p) == 1; };
    Position root() { return pos(1); };
    Position last() { return pos(size()); };
    void addLast(const E &e) { V.push_back(e); };
    void removeLast() { V.pop_back(); };
    void swap(const Position &p, const Position &q)
    {
        E e = *q;
        *q = *p;
        *p = e;
    };

private:         // member data
    vector<E> V; // tree contents
};

template <typename E, typename C>
class HeapPriorityQueue
{
public:
    int size() const { return T.size(); };      // number of elements
    bool empty() const { return size() == 0; }; // is the queue empty?

    void insert(const E &e) // insert element
    {
        T.addLast(e);          // add e to heap
        Position v = T.last(); // e's position
        while (!T.isRoot(v))
        { // up-heap bubbling
            Position u = T.parent(v);
            if (!isLess(*v, *u))
                break;    // if v in order, we're done
            T.swap(v, u); // ...else swap with parent
            v = u;
        }
    };

    const E &min() // minimum element
    {
        return *(T.root());
    };

    void removeMin() throw(HeapPriorityQueueEmpty) // remove minimum
    {
        try
        {
            if (empty())
                throw HeapPriorityQueueEmpty("removeMin: empty HeapPriorityQueue");
        }
        catch (HeapPriorityQueueEmpty &e)
        {
            cout << e.getMessage();
            return;
        }

        if (size() == 1)    // only one node?
            T.removeLast(); // ...remove it
        else
        {
            Position u = T.root(); // root position
            T.swap(u, T.last());   // swap last with root
            T.removeLast();        // ...and remove last
            while (T.hasLeft(u))
            { // down-heap bubbling
                Position v = T.left(u);
                if (T.hasRight(u) && isLess(*(T.right(u)), *v))
                    v = T.right(u); // v is u's smaller child
                if (isLess(*v, *u))
                {                 // is u out of order?
                    T.swap(u, v); // ...then swap
                    u = v;
                }
                else
                    break; // else we're done
            }
        }
    };

private:
    VectorCompleteTree<E> T; // priority queue contents
    C isLess;                // less-than comparator

    // shortcut for tree position
    typedef typename VectorCompleteTree<E>::Position Position;
};

int main(int argc, const char *argv[])
{

    HeapPriorityQueue<int, isLess> h;

    // Ch 8.1.3 Example 8.4
    h.insert(5);
    h.insert(9);
    h.insert(2);
    h.insert(7);

    cout << "size is " << h.size() << endl; // size is 4
    cout << "min is " << h.min() << endl;   // min is 2

    h.removeMin();

    cout << "size is " << h.size() << endl; // size is 3
    cout << "min is " << h.min() << endl;   // min is 5

    h.removeMin();
    h.removeMin();
    h.removeMin();

    cout << "size is " << h.size() << endl;   // size is 0
    cout << "empty is " << h.empty() << endl; // empty is 1

    h.removeMin(); // throw an error

    return 0;
}