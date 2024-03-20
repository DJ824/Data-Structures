// g++ -o stack hybrid_stack.cpp    
// ./stack > JAISWAL_23309392.out 

#include <iostream>

// basic node struct, pointer to array in mem, pointer to next node, and int value corresponding block #
template <typename E>
struct node
{
  E *a;
  node *next;
  int number;

  node()
  {
    a = new E[8];
    next = nullptr;
  }

  ~node() { delete[] a; }
};


template <typename E>
class hybrid_stack
{
private:
  node<E> *head;
  int node_count;
  int top_of_stack;

// set top of stack to -1 so top() will point to last inserted element 
public:
  hybrid_stack()
  {
    node<E> *new_node = new node<E>();
    head = new_node;
    top_of_stack = -1;
    node_count = 1;
    head->number = 0;
  }

// traverse through nodes deleting each one 
  ~hybrid_stack()
  {
    while (head != nullptr)
    {
      node<E> *prev = head;
      head = head->next;
      delete prev;
    }
  }

// array has 8 elements, thus if we are at index 8 it should correspond to a new block
  void push(const E &data)
  {
    ++top_of_stack;
    if (top_of_stack % 8 == 0 && top_of_stack != 0)
    {
      node<E> *new_node = new node<E>();
      new_node->number = node_count;
      ++node_count;
      std::cout << "new node has been created with block number: " << new_node->number << std::endl;
      node<E> *curr = head;
      while (curr->next)
      {
        curr = curr->next;
      }
      curr->next = new_node;
      new_node->a[top_of_stack % 8] = data;
      std::cout << "block number: " << new_node->number << " "
                << "array element number: " << top_of_stack % 8 << " "
                << "stack size: " << top_of_stack + 1 << std::endl;
    }
    else
    {
      node<E> *curr = head;
      while (curr->next)
      {
        curr = curr->next;
      }
      curr->a[top_of_stack % 8] = data;
      std::cout << "block number: " << curr->number << " "
                << "array element number: " << top_of_stack % 8 << " "
                << "stack size: " << top_of_stack + 1 << std::endl;
    }
  }

// to remove, just remove access to the current element by decrementing top_of_stack 
// after decrementing, if we are at index 7, the next block should be deleted as it is "empty" 
  void pop()
  {
    if (top_of_stack == -1)
    {
      throw std::out_of_range("error, stack is empty");
    }
    --top_of_stack;
    node<E> *curr = head;
    node<E> *prev = nullptr;
    while (curr->next)
    {
      prev = curr;
      curr = curr->next;
    }

    if (top_of_stack % 8 == 7 || top_of_stack == -1)
    {
      if (prev != nullptr)
      {
        prev->next = nullptr;
      }
      else
      {
        head = nullptr;
      }
      std::cout << "block number: " << curr->number << " has been deleted" << std::endl;
      delete curr;
    }
  }

// traverse through list to latest block, then call mod operator to access index 
  E top() const
  {
    if (top_of_stack == -1)
    {
      throw std::out_of_range("error, stack is empty");
    }
    node<E> *curr = head;
    while (curr->next)
    {
      curr = curr->next;
    }
    return curr->a[top_of_stack % 8];
  }

  int size() { return top_of_stack + 1; }
 

  bool empty() { return top_of_stack == -1; }

};

int main()
{
  hybrid_stack<int> int_stack;

  std::cout << "pushing elements onto the stack:  " << std::endl;
  for (int i = 1; i <= 20; ++i)
  {
    int_stack.push(i);
    std::cout << "pushed: " << i << std::endl;
  }

  std::cout << std::endl
            << "current top element: " << int_stack.top() << std::endl
            << std::endl;

  std::cout << "popping elements from the stack " << std::endl;
  for (int i = 0; i < 5; ++i)
  {
    int_stack.pop();
    std::cout << "new top after pop: " << int_stack.top() << std::endl;
  }

  hybrid_stack<std::string> string_stack;

  std::cout << std::endl
            << "pushing strings onto the stack: " << std::endl;
  string_stack.push("jamie");
  string_stack.push("dimon");
  string_stack.push("ken");
  string_stack.push("griffin");

  std::cout << "top string: " << string_stack.top() << std::endl;

  std::cout << "popping a string from the stack..." << std::endl;
  string_stack.pop();
  std::cout << "new top string: " << string_stack.top() << std::endl;

  return 0;
}
