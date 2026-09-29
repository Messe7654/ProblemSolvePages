#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

class DisjointSet {
 public:
  DisjointSet(std::size_t N) : capacity_(N), disjoint_count_(N) {
    parent_.resize(N);
    for (auto i{0}; i < N; ++i) parent_[i] = i;
    rank_.resize(N);
  }
  ~DisjointSet() = default;

  std::size_t Find(std::size_t x) {
    return (x == parent_[x]) ? x : parent_[x] = Find(parent_[x]);
  }

  void Union(std::size_t a, std::size_t b) {
    a = Find(a); b = Find(b);
    if (a == b) return;
    --disjoint_count_;
    if (rank_[a] == rank_[b]) {
      ++rank_[a];
      parent_[b] = a;
    }
    else if (rank_[a] < rank_[b]) parent_[a] = b;
    else parent_[b] = a;
  }

  std::size_t disjoint_count() const { return disjoint_count_; }

 private:
  std::size_t capacity_;
  std::size_t disjoint_count_;
  std::vector<std::size_t> parent_;
  std::vector<std::size_t> rank_;
};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int m, n;
  while (std::cin >> m >> n) {
    if (m == 0 && n == 0) break;

    int sum{0};
    std::vector<std::tuple<int, int, int>> edges;
    edges.reserve(n);
    DisjointSet ds(m);

    for (int i{0}; i < n; ++i) {
      int x, y, z;
      std::cin >> x >> y >> z;
      if (x > y) std::swap(x, y);
      edges.push_back({x, y, z});
      sum += z;                  
    }

    int mst{0};
    std::sort(edges.begin(), edges.end(), [](const auto& lhs, const auto& rhs) {
      return std::get<2>(lhs) < std::get<2>(rhs);
    });

    for (const auto& [src, dst, weight] : edges) {
      if (ds.disjoint_count() == 1) break;
      if (ds.Find(src) == ds.Find(dst)) continue;

      mst += weight;
      ds.Union(src, dst);
    }

    std::cout << sum - mst << '\n';
  }
}