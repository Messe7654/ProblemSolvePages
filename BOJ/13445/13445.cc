#include <iostream>

int GetMsb(int x) {
  x |= x >> 1;
  x |= x >> 2;
  x |= x >> 4;
  x |= x >> 8;
  x |= x >> 16;
  return (x + 1) >> 1;
}

class Trie {
 private:
  struct node {
    int subtree_size;
    node* go[2];

    node() : subtree_size(0) { go[0] = go[1] = nullptr; }
  };

 public:
  Trie() { root_ = new node; }

  ///
  /// @brief Trie에 number를 삽입하는 함수.
  /// @param number Trie에 삽입할 수
  void Insert(int number) {
    __insert_imple(number, 21, root_);
  }

  /// @brief Trie에 저장된 수들에 number와 xor 했을 때, threshold보다 작은 수들의 개수를 반환하는 함수
  /// @param number xor할 수
  /// @param threshold 임계값
  /// @return Trie에 저장된 수들에 number와 xor 했을 때, threshold보다 작은 수들의 개수
  int Query(int number, int threshold) {
    return __query_imple(number, threshold, 21, root_);
  }

 private:
  void __insert_imple(int number, int digit, node* now) {
    ++now->subtree_size;
    if (digit < 0) return;
    int next_bit = ((number & (1 << digit)) != 0);
    if (now->go[next_bit] == nullptr) now->go[next_bit] = new node;
    __insert_imple(number, digit - 1, now->go[next_bit]);
  }

  int __query_imple(int number, int threshold, int digit, node* now) {
    if (digit < 0 || threshold == 0) return 0;
    int ret{0};
    int msb = GetMsb(threshold);

    bool set = !(number & (1 << digit));
    if (msb < (1 << digit)) {
      if (now->go[!set] != nullptr)
        ret += __query_imple(number, threshold, digit - 1, now->go[!set]);
    }
    else if (msb == (1 << digit)) {
      if (now->go[!set] != nullptr)
        ret += now->go[!set]->subtree_size;
      if (now->go[set] != nullptr)
        ret += __query_imple(number, threshold ^ msb, digit - 1, now->go[set]);
    }
    else ret += now->subtree_size;
    return ret;
  }

  node* root_;
};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  Trie trie;
  trie.Insert(0);

  int N, K;
  std::cin >> N >> K;

  int accumulated{0};
  long long ans{0};
  for (int i{0}; i < N; ++i) {
    int a;
    std::cin >> a;
    accumulated ^= a;
    ans += trie.Query(accumulated, K);
    trie.Insert(accumulated);
  }
  std::cout << ans;
}