// Data Structures and Algorithms in C++ by Goodrich  Chapter 6 Vector source code.
// Filename: Vector.cpp
// Compile command: g++ Vector.cpp -o Vector.exe

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

// Vector IndexOutOfBounds
class IndexOutOfBounds : public RuntimeException
{
public:
    IndexOutOfBounds(const string &err) : RuntimeException(err) {}
};

template <typename E>
class ArrayVector
{
public:
    ArrayVector() : capacity(0), n(0), A(NULL){}; // constructor
    ~ArrayVector()
    {
        if (A != NULL)
            delete[] A;
    }; // destructor

    int size() const { return n; };             // number of elems
    bool empty() const { return size() == 0; }; // is vector empty?

    E &operator[](int i) { return A[i]; }; // elem at index

    E &at(int i) throw(IndexOutOfBounds)
    {
        if (i < 0 || i >= n)
            throw IndexOutOfBounds("illegal index in function at()");
        return A[i];
    };

    void set(int i, const E &e) throw(IndexOutOfBounds)
    {
        if (i < 0 || i >= n)
            throw IndexOutOfBounds("illegal index in function at()");
        A[i] = e;
    };

    void erase(int i)
    {                                   // remove elem at index
        for (int j = i + 1; j < n; j++) // shift elems down
            A[j - 1] = A[j];
        n--; // one fewer elem
    };

    void insert(int i, const E &e)
    {                                      // insert elem at index
        if (n >= capacity)                 // overflow?
            reserve(max(1, 2 * capacity)); // double array size
        for (int j = n - 1; j >= i; j--)   // shift elems up
            A[j + 1] = A[j];
        A[i] = e; // put in empty slot
        n++;      // one more element
    };

    void reserve(int N)
    { // reserve at least N spots
        if (capacity >= N)
            return;                 // already big enough
        E *B = new E[N];            // allocate bigger array
        for (int j = 0; j < n; j++) // copy contents
            B[j] = A[j];
        if (A != NULL)
            delete[] A; // discard old array
        A = B;          // make B the new array
        capacity = N;   // set new capacity
    };

private:
    int capacity; // current array size
    int n;        // number of elems in vector
    E *A;         // array storing the elems
};

int main(int argc, const char *argv[])
{

    cout << "Using ArrayVector..." << endl;
    ArrayVector<int> A;

    A.insert(0, 7);
    A.insert(0, 4);

    cout << "A.at(1) is " << A.at(1) << endl;

    A.insert(2, 2);

    cout << "A.at(2) is " << A.at(2) << endl;

    try
    {
        A.at(3);
        cout << "A.at(2) is " << A.at(2) << endl;
    }
    catch (RuntimeException &e)
    {
        cout << "A.at(2) failed " << e.getMessage() << endl;
    }

    A.erase(1);
    A.insert(1, 5);
    A.insert(1, 3);
    A.insert(4, 9);

    cout << "A.at(2) is " << A.at(2) << endl;
    cout << "A.at(3) is " << A.at(3) << endl;
    cout << "A.at(4) is " << A.at(4) << endl;

    A.set(3, 8);

    cout << "A.at(3) is " << A.at(3) << endl;

    cout << "A.at(4) is " << A.at(4) << endl;

    return 0;
}