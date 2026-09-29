#include <algorithm>
#include <iostream>
#include <vector>

class disjoint_set {
 public:
  disjoint_set(int N) : N(N), disjoint_count_(N) {
    parent.resize(N);
    std::generate(parent.begin(), parent.end(), [i = (int)0]() mutable { return i++; });
    rank.resize(N);
  }

  int Find(int x) {
    return (x == parent[x]) ? x : parent[x] = Find(parent[x]);
  }

  void Union(int a, int b) {
    a = Find(a); b = Find(b);
    if (a == b) return;
    --disjoint_count_;
    if (rank[a] < rank[b]) parent[a] = b;
    else {
      parent[b] = a;
      if (rank[a] == rank[b]) ++rank[a];
    }
  }

  inline int disjoint_count() { return disjoint_count_; }

 private:
  int N;
  int disjoint_count_;
  std::vector<int> parent;
  std::vector<int> rank;
};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int n, m, k;
  while (std::cin >> n >> m >> k) {
    if (n == 0 && m == 0 && k == 0) break;
    std::vector<std::pair<int, int>> red_edges, blue_edges;
    red_edges.reserve(m);
    blue_edges.reserve(m);

    for (int i{0}; i < m; ++i) {
      char c; int f, t;
      std::cin >> c >> f >> t;
      --f; --t;
      if (f > t) std::swap(f, t);
      if (c == 'R') red_edges.emplace_back(f, t);
      else blue_edges.emplace_back(f, t);
    }
    disjoint_set spanning_tree(n);
    disjoint_set blue_edge_ds(n);
    for (const auto& [u, v] : blue_edges) {
      blue_edge_ds.Union(u, v);
    }
    if (k > n - blue_edge_ds.disjoint_count()) { std::cout << "0\n"; continue; }

    for (const auto& [u, v] : red_edges) {
      spanning_tree.Union(u, v);
    }
    if (spanning_tree.disjoint_count() > k + 1) { std::cout << "0\n"; continue; }
    for (const auto& [u, v] : blue_edges) {
      spanning_tree.Union(u, v);
    }
    std::cout << ((spanning_tree.disjoint_count() == 1) ? "1\n" : "0\n");
  }
}