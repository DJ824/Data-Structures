#include <iostream>

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

public:
  hybrid_stack()
  {
    node<E> *new_node = new node<E>();
    head = new_node;
    top_of_stack = -1;
    node_count = 1;
    head->number = 0;
  }

  ~hybrid_stack()
  {
    while (head != nullptr)
    {
      node<E> *prev = head;
      head = head->next;
      delete prev;
    }
  }

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

  void pop()
  {
    if (top_of_stack == -1)
    {
      throw std::out_of_range("Error: Attempt to pop from an empty stack.");
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

  E top() const
  {
    if (top_of_stack == -1)
    {
      throw std::out_of_range("Error: Attempt to access the top of an empty stack.");
    }
    node<E> *curr = head;
    while (curr->next)
    {
      curr = curr->next;
    }
    return curr->a[top_of_stack % 8];
  }
};

int main()
{
  hybrid_stack<int> intStack;

  std::cout << "pushing elements onto the stack:  " << std::endl;
  for (int i = 1; i <= 20; ++i)
  {
    intStack.push(i);
    std::cout << "pushed: " << i << std::endl;
  }

  std::cout << std::endl
            << "current top element: " << intStack.top() << std::endl
            << std::endl;

  std::cout << "popping elements from the stack " << std::endl;
  for (int i = 0; i < 5; ++i)
  {
    intStack.pop();
    std::cout << "new top after pop: " << intStack.top() << std::endl;
  }

  hybrid_stack<std::string> stringStack;

  std::cout << std::endl
            << "pushing strings onto the stack: " << std::endl;
  stringStack.push("jamie");
  stringStack.push("dimon");
  stringStack.push("ken");
  stringStack.push("griffin");

  std::cout << "top string: " << stringStack.top() << std::endl;

  std::cout << "popping a string from the stack..." << std::endl;
  stringStack.pop();
  std::cout << "new top string: " << stringStack.top() << std::endl;

  return 0;
}
