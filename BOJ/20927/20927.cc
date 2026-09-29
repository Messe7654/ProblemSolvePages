#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include <tuple>

class DisjointSet {
 public:
  DisjointSet(int x) : capacity(x) {
    parent.resize(x);
    rank.resize(x);
    std::generate(parent.begin(), parent.end(), [i = 0]() mutable { return i++; });
  }

  ~DisjointSet() = default;

  int Find(int idx) {
    return (parent[idx] == idx) ? idx : parent[idx] = Find(parent[idx]);
  }

  void Union(int a, int b) {
    assert(0 <= a && a < capacity);
    assert(0 <= b && b < capacity);
    a = Find(a); b = Find(b);
    if (rank[a] < rank[b]) parent[a] = b;
    else {
      if (rank[a] == rank[b]) ++rank[a];
      parent[b] = a;
    }
  }

 private:
  int capacity;
  std::vector<int> parent;
  std::vector<int> rank;
};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M;
  std::cin >> N >> M;
  if (N != 1 && M < N - 1) { std::cout << "NO\n"; exit(0); }
  std::vector<int> b(N);
  std::vector<std::tuple<int, int, int>> edges(M);
  std::vector<bool> used(M);

  std::generate_n(used.begin(), N - 1, [](){ return true; });

  for (int i{0}; i < N; ++i) std::cin >> b[i];
  for (auto& [A, B, C] : edges) {
    std::cin >> A >> B >> C;
    assert(1 <= A && A <= N);
    assert(1 <= B && B <= N);
    --A; --B;
    if (A > B) std::swap(A, B);
  }

  std::sort(edges.begin(), edges.end(), [](auto& lhs, auto& rhs) {
    return std::get<2>(lhs) < std::get<2>(rhs);
  });

  std::vector<bool> ans(M);
  int min = 0x7FFFFFFF;
  do {
    DisjointSet ds(N);
    std::vector<int> degree(N);
    bool valid{true};
    int now{0};

    for (int i{0}; i < M; ++i) {
      if (used[i] == false) continue;
      const auto& [src, dst, weight] = edges[i];
      assert(0 <= src && src <= static_cast<int>(degree.size()));
      assert(0 <= dst && dst <= static_cast<int>(degree.size()));
      
      if (degree[src] >= b[src] || degree[dst] >= b[dst]) { valid = false; break; }
      if (ds.Find(src) == ds.Find(dst)) { valid = false; break; }
      ++degree[src];
      ++degree[dst];
      ds.Union(src, dst);
      now += weight;
    }

    if (valid && now < min) {
      assert(valid == true);
      min = now;
      std::copy(used.begin(), used.end(), ans.begin());
    }
  } while (std::prev_permutation(used.begin(), used.end()));

  if (min != 0x7FFFFFFF) {
    std::cout << "YES\n";
    for (int i{0}; i < M; ++i)
      if (ans[i] == true)
        std::cout << std::get<0>(edges[i]) + 1 << ' ' << std::get<1>(edges[i]) + 1 << '\n';
  }
  else {
    std::cout << "NO\n";
  }
}