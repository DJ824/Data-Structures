// g++ -o expressionTree JAISWAL_23309392.cpp 
// ./expressionTree > JAISWAL_23309392.out

#include <iostream>
#include <list>

using namespace std;

template <typename Elem>
class LinkedBinaryTree
{
protected:
    template <typename F>
    class Node
    {
    public:
        Node() : elt(), par(NULL), left(NULL), right(NULL) {}

    private:
        Elem elt;
        Node<F> *par;
        Node<F> *left;
        Node<F> *right;

        friend class LinkedBinaryTree;
    };

public:
    class Position
    {
    public:
        Position(Node<Elem> *_v = NULL) : v(_v) {}
        Elem &operator*() { return v->elt; }
        const Elem &value() const { return v->elt; }
        Position left() const { return Position(v->left); }
        Position right() const { return Position(v->right); }
        Position parent() const { return Position(v->par); }
        bool isRoot() const { return v->par == NULL; }
        bool isExternal() const { return v->left == NULL && v->right == NULL; }

    private:
        Node<Elem> *v;
        friend class LinkedBinaryTree;
    };

    typedef std::list<Position> PositionList;

public:
    LinkedBinaryTree() : _root(NULL), n(0) {}
    int size() const { return n; }
    bool empty() const { return size() == 0; }
    Position root() const { return Position(_root); }
    PositionList positions() const
    {
        PositionList pl;
        preorder(_root, pl);
        return pl;
    };

    void addRoot()
    {
        _root = new Node<Elem>;
        n = 1;
    }

    void expandExternal(const Position &p);
    void expandExternal(const Position &p, const Elem &l, const Elem &r);

    Position removeAboveExternal(const Position &p);

    std::string printExpression(const Position &p) const;

    float evaluateExpression(const Position &p) const;

protected:
    void preorder(Node<Elem> *v, PositionList &pl) const;

private:
    Node<Elem> *_root;
    int n;
};

template <typename Elem>
void LinkedBinaryTree<Elem>::expandExternal(const Position &p)
{
    Node<Elem> *v = p.v;
    v->left = new Node<Elem>;
    v->left->par = v;
    v->right = new Node<Elem>;
    v->right->par = v;
    n += 2;
}

template <typename Elem>
void LinkedBinaryTree<Elem>::expandExternal(const Position &p, const Elem &l, const Elem &r)
{
    Node<Elem> *v = p.v;
    v->left = new Node<Elem>;
    v->left->par = v;
    v->left->elt = l;
    v->right = new Node<Elem>;
    v->right->par = v;
    v->right->elt = r;
    n += 2;
}

// run a standard preOrder traversal to print the expression
// we can add the parenthesis by adding them to the string we are returning after every recursive call 
template <typename Elem>
std::string LinkedBinaryTree<Elem>::printExpression(const Position &p) const
{
    if (!p.v)
        return "";

    if (p.isExternal())
    {
        return std::string(1, p.value());
    }

    std::string leftExpr = printExpression(p.left());
    std::string rightExpr = printExpression(p.right());

    return "(" + leftExpr + " " + std::string(1, p.value()) + " " + rightExpr + ")";
}

// same methodology as printing, we run a preOrder traversal and return the value calculated inside each parenthesis 
template <typename Elem>
float LinkedBinaryTree<Elem>::evaluateExpression(const Position &p) const
{
    if (p.isExternal())
    {
        return std::atoi(std::string(1, p.value()).c_str());
    }

    float x = evaluateExpression(p.left());
    float y = evaluateExpression(p.right());

    switch (p.value())
    {
    case '+':
        return x + y;
    case '-':
        return x - y;
    case '*':
        return x * y;
    case '/':
        if (y == 0)
            throw std::runtime_error("Division by zero.");
        return x / y;
    default:
        throw std::invalid_argument("Unsupported operator.");
    }
}

int main(int argc, const char *argv[])
{
    LinkedBinaryTree<char> tree;

    tree.addRoot();
    LinkedBinaryTree<char>::Position root = tree.root();
    *root = '*';

    tree.expandExternal(root, '/', '8');

    LinkedBinaryTree<char>::Position pos2 = root.left();
    tree.expandExternal(pos2, '*', '+');

    LinkedBinaryTree<char>::Position pos3 = pos2.left();
    tree.expandExternal(pos3, '+', '-');

    LinkedBinaryTree<char>::Position pos4 = pos3.left();
    tree.expandExternal(pos4, '5', '2');

    LinkedBinaryTree<char>::Position pos5 = pos3.right();
    tree.expandExternal(pos5, '2', '1');

    LinkedBinaryTree<char>::Position pos6 = pos2.right();
    tree.expandExternal(pos6, '+', '-');

    LinkedBinaryTree<char>::Position pos7 = pos6.left();
    tree.expandExternal(pos7, '2', '9');

    LinkedBinaryTree<char>::Position pos8 = pos6.right();
    tree.expandExternal(pos8, '-', '1');

    LinkedBinaryTree<char>::Position pos9 = pos8.left();
    tree.expandExternal(pos9, '7', '2');

    std::string expression = tree.printExpression(root);
    std::cout << "The expression represented by the tree is:\n"
              << expression << std::endl;

    float ans = tree.evaluateExpression(root);
    std::cout << ans << std::endl;

    return 0;
}

// (((5+2) ∗ (2−1))/((2+9) + ((7−2)−1)) ∗ 8)