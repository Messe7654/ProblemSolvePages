#include <algorithm>
#include <iostream>
#include <vector>
#include <bitset>

// 20이면 충분
constexpr int kMaxBit = 20;

class binary_trie {
 protected:
  struct node {
    int base;
    int subtree_size;
    node* go[2];

    node(int base) : base(base) {
      go[0] = go[1] = nullptr;
      subtree_size = 0;
    }
  };

 public:
  binary_trie() {
    acc_xor = 0;
    root = new node(kMaxBit + 1);
  }

  void insert(int number) {
    if (contains(number)) return;
    node* curr = root;
    for (int base{kMaxBit}; base >= 0; --base) {
      bool di = (number & (1 << base)) > 0;
      if (curr->go[di] == nullptr) curr->go[di] = new node(base);
      ++curr->subtree_size;
      curr = curr->go[di];
    }
    ++curr->subtree_size;
  }

  bool contains(int number) const {
    node* curr = root;
    for (int base = kMaxBit; base >= 0; --base) {
      bool di = (number & (1 << base)) > 0;
      if (curr->go[di] == nullptr) return false;
      curr = curr->go[di];
    }
    return true;
  }

  inline void XOR(int x) { acc_xor ^= x; }

  int mex() const {
    node* curr = root;
    int ret{0};
    for (int base{kMaxBit}; base >= 0; --base) {
      bool di = (acc_xor & (1 << base)) > 0;
      if (curr->go[di] == nullptr) return ret;
      if (curr->go[di]->subtree_size < (1 << (base))) {
        curr = curr->go[di];
      } else {
        ret |= (1 << base);
        if (curr->go[di ^ 1] == nullptr) return ret;
        curr = curr->go[di ^ 1];
      }
    }
    return ret;
  }

 private:
  int acc_xor;
  node* root;
};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  binary_trie T;
  int N, M; std::cin >> N >> M;
  for (int i{0}; i < N; ++i) {
    int x; std::cin >> x;
    T.insert(x);
  }

  for (int query_idx{1}; query_idx <= M; ++query_idx) {
    int x; std::cin >> x;
    T.XOR(x);
    std::cout << T.mex() << '\n';
  }
}