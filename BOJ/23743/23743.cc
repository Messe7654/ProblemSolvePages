#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

class DisjointSet {
 public:
  DisjointSet(int size) {
    parent.resize(size + 1);
    rank.resize(size + 1);
    for (int i{1}; i <= size; ++i) {
      parent[i] = i;
      rank[i] = 1;
    }
  }
  ~DisjointSet() = default;

  int Find(int x) { return (x == parent[x]) ? x : parent[x] = Find(parent[x]); }

  void Union(int a, int b) {
    a = Find(a); b = Find(b);
    if (rank[a] > rank[b]) std::swap(a, b);
    parent[a] = b;
    rank[b] += rank[a];
  }

  bool IsEqualSet(int a, int b) { return Find(a) == Find(b); }

 private:
  std::vector<int> parent;
  std::vector<int> rank;
};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M;
  std::cin >> N >> M;

  std::vector<std::tuple<int, int, int>> edges;
  edges.reserve(N + M);
  DisjointSet set(N);
  for (int i{0}; i < M; ++i) {
    int a, b, c;
    std::cin >> a >> b >> c;
    edges.push_back({c, a, b});
  }
  for (int i{1}; i <= N; ++i) {
    int t;
    std::cin >> t;
    edges.push_back({t, 0, i});
  }

  std::priority_queue<std::tuple<int, int, int>,
                     std::vector<std::tuple<int, int, int>>,
                     std::greater<std::tuple<int, int, int>>> pq(edges.begin(), edges.end());
  int ans{0};
  while (pq.empty() != true) {
    auto [weight, a, b] = pq.top();
    pq.pop();

    if (set.IsEqualSet(a, b) == true) continue;
    ans += weight;
    set.Union(a, b);
  }

  std::cout << ans;
}