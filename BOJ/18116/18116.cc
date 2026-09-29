#include <algorithm>
#include <iostream>
#include <vector>

class DisjointSet {
 public:
  using size_type = std::size_t;
  
  DisjointSet(size_type capacity) : capacity_(capacity) {
    parent_.resize(capacity);
    std::generate(parent_.begin(), parent_.end(), [i = (size_type)(0)]() { return i++; });
    rank_.resize(capacity);
  }
  
  size_type Find(size_type i);
  void Union(size_type x, size_type y);

 private:
  size_type capacity;
  std::vector<size_type> parent_;
  std::vector<size_type> rank_;
};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N;

  for (int query{0}; query < N; ++query) {
    char op; std::cin >> op;

    if (op == 'I') {
      int a, b;
      std::cin >> a >> b;
      continue;
    }
    if (op == 'Q') {
      
      continue;
    }
  }
}