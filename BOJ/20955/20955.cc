#include <algorithm>
#include <iostream>
#include <vector>

class DisjointSet {
 public:
  using size_type = std::size_t;
 public:
  explicit DisjointSet(size_type size)
  : size_(size), disjoint_count_(size), surplus_(0) {
    parent_.resize(size);
    std::generate(parent_.begin(), parent_.end(), [i = (size_type)0]() mutable { return i++; });
    rank_.resize(size);
  }
  ~DisjointSet() = default;

  inline size_type size() const { return size_; }
  inline size_type surplus() const { return surplus_; }
  inline size_type disjoint_count() const { return disjoint_count_; }

  size_type Find(size_type i) {
    return (i == parent_[i]) ? i : parent_[i] = Find(parent_[i]);
  }

  void Union(size_type i, size_type j) {
    i = Find(i), j = Find(j);
    if (i == j) {
      ++surplus_;
      return;
    }

    --disjoint_count_;

    if (rank_[i] < rank_[j]) parent_[i] = j;
    else if (rank_[i] > rank_[j]) parent_[j] = i;
    else {
      ++rank_[i];
      parent_[j] = i;
    }
  }

 private:
 size_type disjoint_count_;
 size_type size_;
 size_type surplus_;
  std::vector<size_type> parent_;
  std::vector<size_type> rank_;
};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M; std::cin >> N >> M;

  DisjointSet DSU(N);
  for (int i{0}; i < M; ++i) {
    int u, v;
    std::cin >> u >> v;
    --u; --v;
    DSU.Union(u, v);
  }
  
  std::cout << DSU.disjoint_count() + DSU.surplus() - 1 << '\n';
}