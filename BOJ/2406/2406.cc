#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>
#include <queue>

class disjoint_set {
 public:
  disjoint_set(std::size_t N) : capacity_(N), disjoint_size_(N) {
    parent_.resize(N);
    for (std::size_t i{0}; i < N; ++i) parent_[i] = i;
    rank_.resize(N);
  }
  ~disjoint_set() = default;

  std::size_t Find(std::size_t x) {
    return (x == parent_[x]) ? x : parent_[x] = Find(parent_[x]);
  }

  void Union(std::size_t x, std::size_t y) {
    x = Find(x); y = Find(y);
    if (x == y) return;
    --disjoint_size_;
    if (rank_[x] == rank_[y]) {
      ++rank_[x];
      parent_[y] = x;
    }
    else if (rank_[x] < rank_[y]) parent_[x] = y;
    else parent_[y] = x;
  }

  std::size_t disjoint_size() const { return disjoint_size_; }

 private:
  std::size_t disjoint_size_;
  std::size_t capacity_;
  std::vector<std::size_t> parent_;
  std::vector<std::size_t> rank_;
};


int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M;
  std::cin >> N >> M;
  disjoint_set DS(N);

  for (int i{0}; i < M; ++i) {
    int X, Y;
    std::cin >> X >> Y;
    if (X == 1 || Y == 1) continue;
    DS.Union(--X, --Y);
  }

  std::vector<std::tuple<int, int, int>> edges; // {weight, src, dst(sorted)};
  edges.reserve(N * N / 2);
  for (int row{0}; row < N; ++row) {
    for (int col{0}; col < N; ++col) {
      int weight; std::cin >> weight;
      if (col <= row) continue;
      if (row == 0) continue;
      edges.push_back({weight, row, col});
    }
  }

  std::sort(edges.begin(), edges.end());
  int X{0}, K{0};
  std::vector<std::pair<int, int>> result_edges;
  for (const auto& [weight, src, dst] : edges) {
    if (DS.disjoint_size() == 2) break;
    if (DS.Find(src) == DS.Find(dst)) continue;
    DS.Union(src, dst);
    X += weight;
    ++K;
    result_edges.push_back({src, dst});
  }

  std::cout << X << ' ' << K << '\n';
  for (const auto& [src, dst] : result_edges) {
    std::cout << src + 1 << ' ' << dst + 1 << '\n';
  }
}