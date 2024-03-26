#include <iostream>

template <typename T>
class Vector
{
private:
    T *data;
    int size;
    int capacity;
    int front;
    int back;

public:
    Vector(int initialCapacity = 10) : size(0), capacity(initialCapacity), front(0), back(0)
    {
        data = new T[capacity];
    }

    ~Vector()
    {
        delete[] data;
    }

    void insertAtBeginning(const T &element)
    {
        if (size == capacity)
        {
            resizeArray();
        }
        front = (front - 1 + capacity) % capacity;
        data[front] = element;
        size++;
    }

    void insertAtEnd(const T &element)
    {
        if (size == capacity)
        {
            resizeArray();
        }
        back = (back + 1) % capacity;
        data[back] = element;
        size++;
    }

    T removeFromBeginning()
    {
        if (size == 0)
        {
            throw std::out_of_range("Vector is empty");
        }
        T element = data[front];
        front = (front + 1) % capacity;
        size--;
        return element;
    }

    T removeFromEnd()
    {
        if (size == 0)
        {
            throw std::out_of_range("Vector is empty");
        }
        T element = data[back];
        back = (back - 1 + capacity) % capacity;
        size--;
        return element;
    }

private:
    void resizeArray()
    {
        int newCapacity = capacity * 2;
        T *newData = new T[newCapacity];
        for (int i = 0; i < size; i++)
        {
            newData[i] = data[(front + i) % capacity];
        }
        delete[] data;
        data = newData;
        front = 0;
        back = size - 1;
        capacity = newCapacity;
    }
};

int main()
{
    Vector<int> vec;
    vec.insertAtBeginning(1);
    vec.insertAtEnd(2);
    vec.insertAtBeginning(0);
    vec.insertAtEnd(3);

 

    std::cout << "Removed from beginning: " << vec.removeFromBeginning() << std::endl;
    std::cout << "Removed from end: " << vec.removeFromEnd() << std::endl;

    return 0;
}
