#include <cstdlib>
#include <ctime>

#include <iostream>
#include <string>
#include <utility>

using std::cout;
using std::endl;

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////// Node //
////////////////////////////////////////////////////////////////////////////////

struct Node
{

  Node() = delete;
  Node(std::string const& K): _lPtr(nullptr), _rPtr(nullptr), _key(K) {}

  friend std::ostream& operator<<(std::ostream&, const Node* const);
  friend std::pair<Node**, bool> Find(std::string const&, Node** const);
  friend void Erase(Node** const);
  friend void Clear(const Node* const);

private:

  friend Node** FindMin(Node** const);
  friend Node** FindMax(Node** const);

  Node* _lPtr;
  Node* _rPtr;
  std::string _key;

};

std::ostream& operator<<(std::ostream& S, const Node* const N)
// ------ in the subtree with the root N:
// ------ recursively traverse this subtree with inorder keys output
{
  if (N != nullptr) S << '(' << N->_lPtr << N->_key << N->_rPtr << ')';
  return S;
}

std::pair<Node**, bool> Find(std::string const& K, Node** const P)
// ------ in the subtree with the root *P:
// ------ if the node with the key K exists, return pointer to pointer to it and the flag 'true',
// ------ otherwise return pointer to pointer, where the new node should be linked, and the flag 'false'
{
  const auto nodePtr = *P;
  if (nodePtr != nullptr)
  {
    if (K < nodePtr->_key)
    {
      // ------ search in the left subtree
      return Find(K, &nodePtr->_lPtr);
    }
    else if (K > nodePtr->_key)
    {
      // ------ search in the right subtree
      return Find(K, &nodePtr->_rPtr);
    }
    else
    {
      // ------ the node is found: return pointer to it
      return std::make_pair(P, true);
    }
  }
  else
  {
    // ------ the node isn't found
    return std::make_pair(P, false);
  }
}

void Erase(Node** const P)
// ------ in the subtree with the root *P:
// ------ recursively erase its root
{
  const auto nodePtr = *P;
  if (nodePtr->_lPtr != nullptr && nodePtr->_rPtr != nullptr)
  {
    // ------ the node has two children: find the closest node, copy its key and erase it
    // ------ closest left or right nodes are chosen randomly for symmetry
    const auto closestPtr = (std::rand() % 2 == 0) ? FindMax(&nodePtr->_lPtr) : FindMin(&nodePtr->_rPtr);
    nodePtr->_key = (*closestPtr)->_key;
    Erase(closestPtr);
  }
  else if (nodePtr->_lPtr != nullptr)
  {
    // ------ the node has only the left child
    *P = nodePtr->_lPtr;
    delete nodePtr;
  }
  else if (nodePtr->_rPtr != nullptr)
  {
    // ------ the node has only the right child
    *P = nodePtr->_rPtr;
    delete nodePtr;
  }
  else
  {
    // ------ the node doesn't have children
    *P = nullptr;
    delete nodePtr;
  }
}

void Clear(const Node* const N)
// ------ in the subtree with the root N:
// ------ recursively erase all this subtree
{
  if (N != nullptr)
  {
    Clear(N->_lPtr);
    Clear(N->_rPtr);
    delete N;
  }
}

Node** FindMin(Node** const P)
// ------ in the subtree with the root *P:
// ------ return pointer to pointer to the node with a minimal key
{
  const auto nodePtr = *P;
  return (nodePtr->_lPtr != nullptr) ? FindMin(&nodePtr->_lPtr) : P;
}

Node** FindMax(Node** const P)
// ------ in the subtree with the root *P:
// ------ return pointer to pointer to the node with a maximal key
{
  const auto nodePtr = *P;
  return (nodePtr->_rPtr != nullptr) ? FindMax(&nodePtr->_rPtr) : P;
}

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////// BST //
////////////////////////////////////////////////////////////////////////////////

struct BST
{

  BST(): _rootPtr(nullptr) {std::srand(std::time(nullptr));}
  virtual ~BST() {this->clear();}

  friend std::ostream& operator<<(std::ostream&, BST const&);

  bool contains(std::string const&) const noexcept;
  void insert(std::string const&);
  void erase(std::string const&) noexcept;
  void clear() noexcept;

private:

  Node* _rootPtr;

};

std::ostream& operator<<(std::ostream& S, BST const& T)
{
  S << T._rootPtr;
  return S;
}

bool BST::contains(std::string const& K) const noexcept
{
  return Find(K, const_cast<Node**>(&_rootPtr)).second;
}

void BST::insert(std::string const& K)
{
  const auto res = Find(K, &_rootPtr);
  if (not res.second) *res.first = new Node(K);
}

void BST::erase(std::string const& K) noexcept
{
  const auto res = Find(K, &_rootPtr);
  if (res.second) Erase(res.first);
}

void BST::clear() noexcept
{
  Clear(_rootPtr);
  _rootPtr = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////// main //
////////////////////////////////////////////////////////////////////////////////

int main()
{
  BST t;
  t.insert("50");
  t.insert("60");
  t.insert("40");
  t.insert("45");
  t.insert("43");
  t.insert("30");
  t.insert("35");
  // ---------------------------- traverse original tree
  cout << t << endl;
  // ------------------------------------------------ erase
  t.erase("50");
  // ------------------------ traverse after erasure
  cout << t << endl;
}