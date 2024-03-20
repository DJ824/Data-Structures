#include <vector>

class heap
{
private:
    std::vector<int> v;

public:
    void siftup(int i);
    void siftdown(int i);
    void insert(int x);
    int getmin();
    int extract_min();
    void swap(int i, int j);
};

/*
tree like data structure where each node is smaller or equal to its chldren if min-heap, or greater than or equal if max-heap
node = i;
left child = 2i + 1;
right child = 2i + 2;
parent = (i - 1) / 2;
*/

void heap::swap(int i, int j)
{
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void heap::siftup(int i)
{
    int parent = (i - 1) / 2;
    while (i != 0 && v[i] < v[parent])
    {
        swap(v[i], v[parent]);
        i = parent;
        parent = (i - 1) / 2;
    }
}

void heap::siftdown(int i)
{
    int left_child = 2 * i + 1;
    int right_child = 2 * i + 2;
    int smallest = 0;
    while ((left_child < v.size() && v[i] > v[left_child]) || (right_child < v.size() && v[i] > v[right_child]))
    {
        if (right_child >= v.size() || v[left_child] < v[right_child])
        {
            smallest = left_child;
        }
        else
            smallest = right_child;

        swap(v[i], v[smallest]);
        i = smallest;
        left_child = 2 * i + 1;
        right_child = 2 * i + 2;
    }
}

void heap::insert(int x)
{
    v.push_back(x);
    siftup(v[x]);
}

int heap::getmin()
{
    return v[0];
}
