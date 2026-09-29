#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

class DisjointSet {
 public:
  DisjointSet(std::size_t size)
  : capacity(size), components_count(size) {
    parent.resize(capacity);
    rank.resize(capacity);

    std::generate(parent.begin(), parent.end(),
                  [i = (int)0]() mutable { return i++; });
    std::generate(rank.begin(), rank.end(), []() { return 1; });
  }

  std::size_t Find(std::size_t idx) {
    return parent[idx] == idx ? idx : parent[idx] = Find(parent[idx]);
  }

  void Union(std::size_t x, std::size_t y) {
    x = Find(x);
    y = Find(y);
    if (x == y) return;
    --components_count;
    if (rank[x] > rank[y]) std::swap(x, y);
    parent[x] = y;
    if (rank[x] == rank[y]) ++rank[y];
  }

  const std::size_t& count() const { return components_count; };

 private:
  std::size_t components_count;
  std::size_t capacity;
  std::vector<int> parent;
  std::vector<int> rank;
};

struct vectex {
  double x;
  double y;
  int id;
};

struct edge {
  int src_id;
  int dst_id;
  double distance;
};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N;
  std::vector<vectex> star(N);
  std::vector<edge> edges;
  edges.reserve(N * (N - 1) / 2);

  for (int i{0}; i < N; ++i) {
    std::cin >> star[i].x >> star[i].y;
    star[i].id = i;
  }

  for (int src_id{0}; src_id < N - 1; ++src_id) {
    for (int dst_id{src_id + 1}; dst_id < N; ++dst_id) {
      const auto& src = star[src_id];
      const auto& dst = star[dst_id];
      double distance =
        std::sqrt((src.x - dst.x) * (src.x - dst.x) + (src.y - dst.y) * (src.y - dst.y));
      edges.push_back({src_id, dst_id, distance});
    }
  }

  std::sort(edges.begin(), edges.end(), [](const auto& lhs, const auto& rhs) {
    return lhs.distance < rhs.distance;
  });

  DisjointSet ds(N);
  double ans{0};
  for (auto [src_id, dst_id, distance] : edges) {
    if (ds.count() <= 1) break;

    if (ds.Find(src_id) == ds.Find(dst_id)) continue;
    ds.Union(src_id, dst_id);
    ans += distance;
  }

  std::cout << ans;
}