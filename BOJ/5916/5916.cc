#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

struct HLD {
  std::vector<int> head;
  std::vector<int> chain;
  std::vector<int> chain_size;
  std::vector<int> discover;
  std::vector<int> depth;
  std::vector<int> parent;

  HLD(std::vector<std::vector<int>>& graph) {
    int size = static_cast<int>(graph.size()) - 1;
    head.resize(size + 1);
    chain.resize(size + 1);
    chain_size.resize(size + 1);
    discover.resize(size + 1);
    depth.resize(size + 1);
    parent.resize(size + 1);

    std::vector<int> weight(size + 1);
    
    auto DFS = [&]() {
      std::vector<bool> visited(size + 1);
      std::function<void(int)> __imple__;
      __imple__ = [&](int now) -> void {
        visited[now] = true;
        weight[now] = 1;
        for (const auto& next : graph[now]) {
          if (visited[next] == true) continue;
          depth[next] = depth[now] + 1;
          parent[next] = now;
          __imple__(next);
          weight[now] += weight[next];
        }
      };

      __imple__(1);
    };

    DFS();

    for (auto& adjacency_list : graph) {
      std::sort(adjacency_list.begin(), adjacency_list.end(), [&weight](const auto& lhs, const auto& rhs) {
        return weight[lhs] > weight[rhs];
      });
    }

    std::vector<bool> visited(size + 1);
    std::function<void(int)> MakeHLD;
    MakeHLD = [&, order1 = (int)1, order2 = (int)1](int now) mutable -> void {
      visited[now] = true;
      // Heavy-Chain
      for (const auto& next : graph[now]) {
        if (visited[next] == true) continue;
        chain[next] = chain[now];
        discover[next] = ++order1;
        MakeHLD(next);
        break;
      }
      // Other Chain
      for (const auto& next : graph[now]) {
        if (visited[next] == true) continue;
        chain[next] = ++order2;
        head[order2] = next;
        discover[next] = ++order1;
        MakeHLD(next);
      } 
    };

    chain[1] = 1;
    head[1] = 1;
    discover[1] = 1;
    MakeHLD(1);
    for (int i{1}; i <= size; ++i) {
      ++chain_size[chain[i]];
    }
  }
};

class segment_tree {
 public:
  segment_tree(int size) : capacity(size) {
    T.resize(capacity << 2);
    L.resize(capacity << 2);
  }

  int Get(int u, int v) {
    return __get__(1, 1, capacity, u, v);
  }

  void Update(int u, int v) {
    __update__(1, 1, capacity, u, v);
  }

 private:
  long long __get__(int Tidx, int start, int end, int left, int right) {
    if (L[Tidx] != 0) {
      T[Tidx] += (end - start + 1) * L[Tidx];
      if (start != end) {
        L[Tidx << 1    ] += L[Tidx];
        L[Tidx << 1 | 1] += L[Tidx];
      }
      L[Tidx] = 0;
    }
    if (end < left || right < start) return 0;
    if (start == end) return T[Tidx];
    auto mid = start + ((end - start) >> 1);
    auto lhs = __get__(Tidx << 1    , start  , mid, left, right);
    auto rhs = __get__(Tidx << 1 | 1, mid + 1, end, left, right);
    return lhs + rhs;
  }

  long long __update__(int Tidx, int start, int end, int left, int right) {
    if (L[Tidx] != 0) {
      T[Tidx] += (end - start + 1) * L[Tidx];
      if (start != end) {
        L[Tidx << 1    ] += L[Tidx];
        L[Tidx << 1 | 1] += L[Tidx];
      }
      L[Tidx] = 0;
    }

    if (right < start || end < left) return T[Tidx];
    if (left <= start && end <= right) {
      T[Tidx] += (end - start + 1);
      if (start != end) {
        ++L[Tidx << 1    ];
        ++L[Tidx << 1 | 1];
      }
      return T[Tidx];
    }

    auto mid = start + ((end - start) >> 1);
    auto lhs = __update__(Tidx << 1    , start  , mid, left, right);
    auto rhs = __update__(Tidx << 1 | 1, mid + 1, end, left, right);
    return T[Tidx] = lhs + rhs;
  }

  int capacity;
  std::vector<long long> T;
  std::vector<long long> L;
};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M; std::cin >> N >> M;
  std::vector<std::vector<int>> graph(N + 1);
  for (int i{1}; i < N; ++i) {
    int a, b; std::cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  HLD hld(graph);
  segment_tree seg(N);

  // 심기
  auto query01 = [&](int u, int v) -> void {
    if (u == v) return;
    while (hld.chain[u] != hld.chain[v]) {
      if (hld.depth[hld.head[hld.chain[u]]] < hld.depth[hld.head[hld.chain[v]]]) std::swap(u, v);
      int H = hld.head[hld.chain[u]];
      seg.Update(hld.discover[H], hld.discover[u]);
      u = hld.parent[H];
    }

    if (hld.depth[u] > hld.depth[v]) std::swap(u, v);
    seg.Update(hld.discover[u] + 1, hld.discover[v]);
  };

  // 구하기
  auto query02 = [&](int u, int v) -> long long {
    if (u == v) return 0;
    long long ret{0};
    while (hld.chain[u] != hld.chain[v]) {
      if (hld.depth[hld.head[hld.chain[u]]] < hld.depth[hld.head[hld.chain[v]]]) std::swap(u, v);
      int H = hld.head[hld.chain[u]];
      ret += seg.Get(hld.discover[H], hld.discover[u]);
      u = hld.parent[H];
    }

    if (hld.depth[u] > hld.depth[v]) std::swap(u, v);
    ret += seg.Get(hld.discover[u] + 1, hld.discover[v]);
    return ret;
  };

  for (int i{0}; i < M; ++i) {
    char op; int u, v;
    std::cin >> op >> u >> v;
    if (op == 'P') query01(u, v);
    else std::cout << query02(u, v) << '\n';
  }
}