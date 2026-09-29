#include <bits/stdc++.h>

constexpr int kInf = 0x7FFFFFFF;

using numeric_string = std::vector<int>;

class SplayTree {
 public:
  using size_type = std::size_t;

  SplayTree() = default;
  ~SplayTree() = default;

  template <typename InputIt>
  SplayTree(InputIt first, InputIt last) {
    for (; first != last; ++first) insert(*first);
  }

  void insert(int key) {
    root = insert(root, key);
    root->parent = nullptr;
  }

  void erase(int key) {
    root = erase(root, key);
    if (root) root->parent = nullptr;
  }

  int rank(int key) { return rank(root, key); }

  bool exist(int key) {
    node_ptr n = find(root, key);
    return n != nullptr;
  }

  void clear() { root = nullptr; }

 private:
  struct Node {
    int key, size, count;
    Node *left, *right, *parent;
    Node(int key)
        : key(key),
          size(1),
          count(1),
          left(nullptr),
          right(nullptr),
          parent(nullptr) {}
  };

  using node_ptr = Node*;
  node_ptr root = nullptr;

  int size(node_ptr n) const { return n ? n->size : 0; }

  void update(node_ptr n) {
    if (n) {
      n->size = n->count + size(n->left) + size(n->right);
    }
  }

  void rotate(node_ptr x) {
    node_ptr p = x->parent, g = p->parent;
    if (p->left == x) {
      p->left = x->right;
      if (x->right) x->right->parent = p;
      x->right = p;
    } else {
      p->right = x->left;
      if (x->left) x->left->parent = p;
      x->left = p;
    }
    p->parent = x;
    x->parent = g;

    if (g) {
      if (g->left == p)
        g->left = x;
      else
        g->right = x;
    } else {
      root = x;
    }

    update(p);
    update(x);
  }

  void splay(node_ptr x) {
    if (!x) return;
    while (x->parent) {
      node_ptr p = x->parent, g = p->parent;
      if (!g)
        rotate(x);
      else if ((g->left == p) == (p->left == x)) {
        rotate(p);
        rotate(x);
      } else {
        rotate(x);
        rotate(x);
      }
    }
  }

  node_ptr find(node_ptr n, int key) {
    node_ptr cur = n;
    while (cur) {
      if (key < cur->key)
        cur = cur->left;
      else if (key > cur->key)
        cur = cur->right;
      else {
        splay(cur);
        return cur;
      }
    }
    return nullptr;
  }

  node_ptr insert(node_ptr n, int key) {
    if (!n) return new Node(key);

    node_ptr cur = n, parent = nullptr;
    while (cur) {
      parent = cur;
      if (key < cur->key)
        cur = cur->left;
      else if (key > cur->key)
        cur = cur->right;
      else {
        cur->count++;
        splay(cur);
        update(cur);
        return cur;
      }
    }

    node_ptr new_node = new Node(key);
    new_node->parent = parent;
    if (key < parent->key)
      parent->left = new_node;
    else
      parent->right = new_node;

    splay(new_node);
    return new_node;
  }

  node_ptr erase(node_ptr n, int key) {
    node_ptr t = find(n, key);
    if (!t) return n;

    if (t->count > 1) {
      t->count--;
      update(t);
      return t;
    }

    splay(t);
    node_ptr L = t->left;
    node_ptr R = t->right;
    delete t;

    if (!L) return R;
    L->parent = nullptr;

    node_ptr maxL = L;
    while (maxL->right) maxL = maxL->right;
    splay(maxL);
    maxL->right = R;
    if (R) R->parent = maxL;
    update(maxL);
    return maxL;
  }

  int rank(node_ptr n, int key) {
    int res = 0;
    node_ptr cur = n;
    while (cur) {
      if (key < cur->key) {
        cur = cur->left;
      } else {
        res += size(cur->left);
        if (key > cur->key) res += cur->count;
        cur = cur->right;
      }
    }
    return res;
  }
};

namespace std {
template <>
struct hash<std::pair<int, bool>> {
    std::size_t operator()(const std::pair<int, bool>& p) const {
        std::size_t h1 = std::hash<int>{}(p.first);
        std::size_t h2 = std::hash<bool>{}(p.second);
        return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
    }
};
}

class OAC {
 public:
  using string_type     = std::vector<int>;
  using key_type        = std::pair<int, bool>;
  using prefix_rep_type = std::vector<key_type>;

 private:
  struct node {
    using key_type = std::pair<int, bool>;
    using pointer  = node*;

    int d;
    int P;
    pointer pi;
    std::unordered_map<key_type, pointer> go;
    std::set<int> out;
  };
  using pointer = node*;

 public:
  OAC() {
    root_ = new node;
    root_->d = 0;
    root_->pi = root_;
    root_->P = 0;
  }
  ~OAC() = default;

  template <typename RelativeOrderedSet>
  void build_automaton(const std::vector<string_type>& patterns) {
    auto tau = RelativeOrderedSet();

    for (std::size_t i{0}; i < patterns.size(); ++i) {
      const auto& P = patterns[i];
      prefix_rep_type prefix_representation;
      prefix_representation.resize(P.size());

      for (std::size_t j{0}; j < P.size(); ++j) {
        prefix_representation[j] = {tau.rank(P[j]), tau.exist(P[j])};
        tau.insert(P[j]);
      }
      
      tau.clear();
      __add_pattern(prefix_representation, root_, 0, i);
    }    
  }

  template <typename RelativeOrderedSet>
  void compute_AC_failure_function(const std::vector<string_type>& patterns) {
    std::queue<pointer> queue;

    std::vector<RelativeOrderedSet> tau(patterns.size());

    for (const auto& [_, next] : root_->go) {
      queue.push(next);
      next->pi = root_;
    }

    while (queue.empty() != true) {
      auto curr = queue.front(); queue.pop();

      for (auto& [_, next] : curr->go) {
        const auto& character = patterns[next->P][next->d - 1];
        if (curr->P != next->P) {
          for (int k{0}; k < curr->pi->d; ++k) {
            tau[next->P].insert(patterns[next->P][curr->d - curr->pi->d + k]);
          }
        }
        auto r = tau[next->P].rank(character);
        auto e = tau[next->P].exist(character);

        auto q_pi = curr->pi;
        while (q_pi->go.find({r, e}) == q_pi->go.end()) {
          for (int k = curr->d - q_pi->d; k < curr->d - q_pi->pi->d; ++k) {
            tau[next->P].erase(patterns[next->P][k]);
          }
          r = tau[next->P].rank(character);
          e = tau[next->P].exist(character);
          q_pi = q_pi->pi;
        }

        tau[next->P].insert(character);
        next->pi = q_pi->go[{r, e}];
        queue.push(next);

        next->out.insert(next->pi->out.begin(), next->pi->out.end());
      }
    }
  }

  template <typename RelativeOrderedSet>
  int search(const string_type& T) const {
    auto tau = RelativeOrderedSet();
    pointer curr = root_;

    int N = static_cast<int>(T.size());
    for (int i{0}; i < N; ++i) {
      auto r = tau.rank(T[i]);
      auto e = tau.exist(T[i]);

      while (curr->go.find({r, e}) == curr->go.end()) {
        int kl = i - curr->d;
        int ku = i - curr->pi->d;
        
        for (int k = std::max(0, kl); k < ku; ++k) {
          tau.erase(T[k]);
        }

        curr = curr->pi;
        r = tau.rank(T[i]); e = tau.exist(T[i]);
      }

      curr = curr->go[{r, e}];
      tau.insert(T[i]);
      if (!curr->out.empty()) {
        for (const auto& P : curr->out) {
          return P;
        }
      }
    }

    return -1;
  }

 private:
  void __add_pattern(const std::vector<key_type>& pattern, pointer parent, int index, int p_no) {
    if (!parent || pattern.size() == 0) return;

    const auto& c = pattern[index];
    auto it = parent->go.find(c);

    pointer new_node;
    if (it == parent->go.end()) {
      new_node = new node;
      new_node->d = parent->d + 1;
      new_node->P = p_no;
      parent->go.insert({c, new_node});
    }
    else new_node = it->second;

    if (index + 1 == static_cast<int>(pattern.size())) {
      new_node->out.insert(p_no);
      return;
    }
    __add_pattern(pattern, new_node, index + 1, p_no);
  }

  pointer root_;
};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int K, M, N;
  std::cin >> K >> M >> N;

  using string_type = std::vector<int>;
  std::vector<string_type> patterns(M, string_type(K));
  string_type T(N);

  for (auto& pattern : patterns) {
    for (auto& x : pattern) std::cin >> x;
  }
  for (auto& x : T) std::cin >> x;

  auto ah = OAC();
  ah.build_automaton<SplayTree>(patterns);
  ah.compute_AC_failure_function<SplayTree>(patterns);
  auto ret = ah.search<SplayTree>(T);

  if (ret == -1) std::cout << "0\n";
  else {
    for (int i{0}; i < K; ++i) {
      std::cout << patterns[ret][i] << ((i + 1 == K) ? '\n' : ' ');
    }
  }
}