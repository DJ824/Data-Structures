// Filename: binarytree.cpp
// Compile command: g++ binarytree.cpp -o binarytree.exe

#include <iostream>
#include <list>

using namespace std;

template <typename Elem>
class LinkedBinaryTree
{ // Linked List Binary Tree

protected:
    template <typename F>
    class Node
    { // a node of the tree

    public:
        Node() : elt(), par(NULL), left(NULL), right(NULL) {} // constructor

    private:
        Elem elt;       // element value
        Node<F> *par;   // parent
        Node<F> *left;  // left child
        Node<F> *right; // right child

        friend class LinkedBinaryTree;
    };

public:
    class Position
    { // position in the tree

    public:
        Position(Node<Elem> *_v = NULL) : v(_v) {} // constructor

        Elem &operator*() { return v->elt; } // get element

        const Elem &value() const { return v->elt; } // get element

        Position left() const { return Position(v->left); } // get left child

        Position right() const { return Position(v->right); } // get right child

        Position parent() const { return Position(v->par); } // get parent

        bool isRoot() const { return v->par == NULL; } // root of the tree?

        bool isExternal() const // an external node?
        {
            return v->left == NULL && v->right == NULL;
        }

    private:
        Node<Elem> *v; // pointer to the node

        friend class LinkedBinaryTree; // give tree access
    };

    typedef std::list<Position> PositionList; // list of positions

public:
    LinkedBinaryTree() : _root(NULL), n(0) {} // constructor

    int size() const { return n; } // number of nodes

    bool empty() const { return size() == 0; } // is tree empty?

    Position root() const { return Position(_root); } // get the root

    PositionList positions() const
    { // list of nodes
        PositionList pl;
        preorder(_root, pl);
        //      return PositionList(pl);
        return pl;
    };

    void addRoot()
    {
        _root = new Node<Elem>;
        n = 1;
    }; // add root to empty tree

    void expandExternal(const Position &p); // expand external node
    void expandExternal(const Position &p,
                        const Elem &l, const Elem &r);

    Position removeAboveExternal(const Position &p)
    { // remove p and parent

        Node<Elem> *w = p.v;
        Node<Elem> *v = w->par; // get p's node and parent
        Node<Elem> *sib = (w == v->left ? v->right : v->left);
        if (v == _root)
        {                // child of root?
            _root = sib; // ...make sibling root
            sib->par = NULL;
        }
        else
        {
            Node<Elem> *gpar = v->par; // w's grandparent
            if (v == gpar->left)
                gpar->left = sib; // replace parent by sib
            else
                gpar->right = sib;
            sib->par = gpar;
        }
        delete w;
        delete v; // delete removed nodes
        n -= 2;   // two fewer nodes
        return Position(sib);
    };

    // Tree traversal methods in which "visiting a position (node)" means printing its element.

    // I have put two versions of each of inOrder, postOrder, and inOrder binary tree traversal.

    void preorderPrint(const Position &p) const
    { // preorder print utility
        if (p.v)
        {

            cout << p.value() << " "; // Visit the position

            preorderPrint(p.left()); // Traverse Position's Left Subtree

            preorderPrint(p.right()); // Traverse Position's Right Subtree
        }
    };

    void preorderPrintv2(const Position &p) const
    { // preorder print utility
        if (p.v)
        {

            cout << p.value() << " "; // Visit the position

            if (!(p.isExternal()))
            {
                preorderPrintv2(p.left());  // Traverse Position's Left Subtre
                preorderPrintv2(p.right()); // Traverse Position's Right Subtree
            }
        }
    };

    void postorderPrint(const Position &p) const
    { // postorder print utility
        if (p.v)
        {

            postorderPrint(p.left()); // Traverse Position's Left Subtree

            postorderPrint(p.right()); // Traverse Position's Right Subtree

            cout << p.value() << " "; // Visit the position
        }
    };

    void postorderPrintv2(const Position &p) const
    { // postorder print utility
        if (p.v)
        {

            if (!(p.isExternal()))
            {
                postorderPrintv2(p.left());  // Traverse Position's Left Subtre
                postorderPrintv2(p.right()); // Traverse Position's Right Subtree
            }

            cout << p.value() << " "; // Visit the position
        }
    };

    void inorderPrint(const Position &p) const
    { // preorder print utility
        if (p.v)
        {

            inorderPrint(p.left()); // Traverse Position's Left Subtree

            cout << p.value() << " "; // Visit the position

            inorderPrint(p.right()); // Traverse Position's Right Subtree
        }
    };

    void inorderPrintv2(const Position &p) const
    { // preorder print utility
        if (p.v)
        {

            if (!(p.isExternal()))
                inorderPrintv2(p.left()); // Traverse Position's Left Subtree

            cout << p.value() << " "; // Visit the position
            if (!(p.isExternal()))
                inorderPrintv2(p.right()); // Traverse Position's Right Subtree
        }
    };

    // housekeeping functions omitted...

protected:                                                // local utilities
    void preorder(Node<Elem> *v, PositionList &pl) const; // preorder utility

private:
    Node<Elem> *_root; // pointer to the root
    int n;             // number of nodes
};

template <typename Elem> // expand external node
void LinkedBinaryTree<Elem>::expandExternal(const Position &p)
{
    Node<Elem> *v = p.v;       // p's node
    v->left = new Node<Elem>;  // add a new left child
    v->left->par = v;          // v is its parent
    v->right = new Node<Elem>; // and a new right child
    v->right->par = v;         // v is its parent
    n += 2;                    // two more nodes
}

template <typename Elem> // expand external node
void LinkedBinaryTree<Elem>::expandExternal(const Position &p,
                                            const Elem &l, const Elem &r)
{
    Node<Elem> *v = p.v;      // p's node
    v->left = new Node<Elem>; // add a new left child
    v->left->par = v;         // v is its parent
    v->left->elt = l;         // set left child element

    v->right = new Node<Elem>; // and a new right child
    v->right->par = v;         // v is its parent
    n += 2;                    // two more nodes
    v->right->elt = r;         // set right child element
}

template <typename Elem>
void LinkedBinaryTree<Elem>::preorder(Node<Elem> *v, PositionList &pl) const
{
    pl.push_back(Position(v));

    if (v->left != NULL)
        preorder(v->left, pl);

    if (v->right != NULL)
        preorder(v->right, pl);
}

int main(int argc, const char *argv[])
{

    LinkedBinaryTree<int> t;

    t.addRoot();

    LinkedBinaryTree<int>::Position r = t.root(); // Add root and set its value
    *r = 978;

    t.expandExternal(r, 10, 20); // Add left child and right child

    cout << "Root elem is " << *r << endl;
    cout << "Left elem is " << (r.left()).value() << endl;
    cout << "Right elem is " << (r.right()).value() << endl;

    cout << "PreorderPrint:" << endl;
    t.preorderPrint(t.root());
    cout << endl;

    cout << "PreorderPrint version 2:" << endl;
    t.preorderPrintv2(t.root());
    cout << endl;

    cout << "PostorderPrint:" << endl;
    t.postorderPrint(t.root());
    cout << endl;

    cout << "PostorderPrint version 2:" << endl;
    t.postorderPrintv2(t.root());
    cout << endl;

    cout << "InorderPrint:" << endl;
    t.inorderPrint(t.root());
    cout << endl;

    cout << "InorderPrint version 2:" << endl;
    t.inorderPrintv2(t.root());
    cout << endl;

    cout << "Adding nodes 30, 40, 50, 60..." << endl;
    t.expandExternal(r.left(), 30, 40);  // Add to left subtree
    t.expandExternal(r.right(), 50, 60); // Add to right subtree

    cout << "PreorderPrint:" << endl;
    t.preorderPrint(t.root());
    cout << endl;

    cout << "PreorderPrint version 2:" << endl;
    t.preorderPrintv2(t.root());
    cout << endl;

    cout << "PostorderPrint:" << endl;
    t.postorderPrint(t.root());
    cout << endl;

    cout << "PostorderPrint version 2:" << endl;
    t.postorderPrintv2(t.root());
    cout << endl;

    cout << "InorderPrint:" << endl;
    t.inorderPrint(t.root());
    cout << endl;

    cout << "InorderPrint version 2:" << endl;
    t.inorderPrintv2(t.root());
    cout << endl;

    return 0;
}