#include <iostream>
#include <vector>

class Tree {
 private:
  struct node {
    int value;
    bool visit;
    node* parent;
    node* child[2];

    node() : visit(false), parent(nullptr) {
      child[0] = child[1] = nullptr;
    }
  }; 
 public:
  Tree(const std::vector<int>& preorder_traversal);
  void postorder_traversal() const;
  void postorder_traversal(node*) const;

 private:
  node* root;
};

Tree::Tree(const std::vector<int>& preorder_traversal) {
  root = new node;
  root->value = preorder_traversal[0];
  node* view = root;
  size_t size = preorder_traversal.size();
  for (size_t i{1}; i < size; i++) {
    auto now = preorder_traversal[i];
    node* new_node = new node;
    new_node->value = now;
    if (now < view->value) {
      new_node->parent = view;
      view->child[0] = new_node;
    } else {
      
      while (view->parent != nullptr && now > view->parent->value)
        view = view->parent;
      new_node->parent = view;
      view->child[1] = new_node;
    }
    view = new_node;
  }
}

void Tree::postorder_traversal() const { 
  std::vector<node*> stack;
  stack.push_back(root);

  while (stack.empty() != true) {
    auto now = stack.back();

    if (now->visit == false) {
      now->visit = true;
      if (nullptr != now->child[1]) stack.push_back(now->child[1]);
      if (nullptr != now->child[0]) stack.push_back(now->child[0]);
    }
    else {
      stack.pop_back();
      std::cout << now->value << '\n';
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  std::vector<int> preorder_traversal;
  int num;
  while (std::cin >> num) {
    preorder_traversal.push_back(num);
  }

  Tree T(preorder_traversal);
  T.postorder_traversal();
}