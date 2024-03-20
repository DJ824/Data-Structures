#include <iostream>
#include <queue>
#include <stack>
#include <climits>

struct node {
  int data;
  node *left;
  node *right;
  node(int data) {
    this->data = data;
    left = nullptr;
    right = nullptr;
  }
};

class btree {
private:
  node *root;
public:

  void add_node(int data, node *&root) {
    if (root == nullptr) {
      root = new node(data);
    } else {
      node* curr = root;
      if (data < curr->data) {
        if (curr->left == nullptr) {
          curr->left = new node(data);
        } else {
          add_node(data, curr->left);
        }
      } else {
        if (curr->right == nullptr) {
          curr->right = new node(data);
        } else {
          add_node(data, curr->right);
        }
      }
    }
  }

  int get_data(int data, node *&root) {
    if (root == nullptr){
      return INT_MAX; 
    }     
    if (root->data == data){
      return root->data; 
    }
    node *curr = root;
      if (data < curr->data) {
      return get_data(data, curr->left);
      } else {
      return get_data(data, curr->right);
      }
    }
  

  void pre_order(node *root) {
    if (root == nullptr) {
      return;
    }
    std::cout << root->data;
    pre_order(root->left);
    pre_order(root->right);
  }

  void in_order(node *root) {
    if (root == nullptr) {
      return;
    } else {
      in_order(root->left);
      std::cout << root->data;
      in_order(root->right);
    }
  }

  void post_order(node *root) {
    if (root == nullptr) {
      return;
    } else {
      post_order(root->left);
      post_order(root->right);
      std::cout << root->data;
    }
  }

  void iterative_pre_order(node *root) {
    std::stack<node *> s;
    node *curr = root;
    while (curr != nullptr || !s.empty()) {
      if (curr != nullptr) {
        std::cout << curr->data;
        s.push(curr);
        curr = curr->left;
      } else {
        node *prev = s.top();
        s.pop();
        curr = prev->right;
      }
    }
  }

  void iterative_in_order(node *root) {
    std::stack<node *> s;
    node *curr = root;
    while (curr != nullptr || !s.empty()) {
      if (curr != nullptr) {
        s.push(curr);
        curr = curr->left;
      } else {
        curr = s.top();
        s.pop();
        std::cout << curr->data;
        curr = curr->right;
      }
    }
  }

  void bfs(node *root) {
    std::queue<node *> q;
    node *curr = root;
    q.push(curr);
    while (!q.empty()) {
      node *curr = q.front();
      if (curr->left != nullptr) {
        q.push(curr->left);
      }
      if (curr->right != nullptr) {
        q.push(curr->right);
      }
      q.pop();
    }
  }
};
