#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <vector>

struct HLD {
  std::vector<int> head;
  std::vector<int> chain;
  std::vector<int> discover;
  std::vector<int> depth;
  std::vector<int> parent;

  HLD(std::vector<std::vector<int>>& graph) {
    std::size_t size = graph.size();
    head.resize(size);
    chain.resize(size);
    discover.resize(size);
    depth.resize(size);
    parent.resize(size);
    
    std::vector<int> weight(size);

    auto DFS = [&](int start) {
      std::vector<bool> visited(size);
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

      __imple__(start);
    };

    parent[0] = -1;
    DFS(0);
    assert(parent[0] == -1);

    for (auto& adjacecy_list : graph) {
      std::sort(adjacecy_list.begin(), adjacecy_list.end(),
        [&weight](const auto& lhs, const auto& rhs) {
          return weight[lhs] > weight[rhs];
        }
      );
    }

    std::vector<bool> visited(size);
    std::function<void(int)> Construct;
    Construct = [&, order1 = (int)0, order2 = (int)0](int now) mutable -> void {
      visited[now] = true;

      // Heavy-Chain
      for (const auto& next : graph[now]) {
        if (visited[next] == true) continue;
        chain[next] = chain[now];
        discover[next] = ++order1;
        Construct(next);
        break;
      }

      // Otherwise
      for (const auto& next : graph[now]) {
        if (visited[next] == true) continue;
        chain[next] = ++order2; // new chain
        head[order2] = next;
        discover[next] = ++order1;
        Construct(next);
      }
    };

    chain[0] = 0;
    head[0] = 0;
    discover[0] = 0;
    Construct(0);
  }
};

class SegmentTree {
 public:
  typedef std::size_t                  size_type;
  typedef std::size_t                      index;
  typedef long long                   value_type;

 public:
  SegmentTree(size_type N) {
    for (int i{1}; i < 64; i <<= 1) {
      N |= N >> i;
    }
    bias = capacity = N + 1;
    T.resize(capacity << 1);
  }

  void push(index i, value_type value) {
    i |= bias;
    T[i] = value;
    while (i >>= 1) {
      T[i] = T[i << 1] + T[i << 1 | 1];
    }
  }

  value_type query(index left, index right) {
    left |= bias; right |= bias;
    value_type ret{0LL};
    while (left <= right) {
      if (left & 1)   ret += T[left++];
      if (~right & 1) ret += T[right--];
      left >>= 1; right >>= 1;
    }
    return ret;
  }

 private:
  size_type capacity;
  size_type bias;

  std::vector<value_type> T;  
};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N;

  std::vector<std::vector<int>> graph(N);
  for (int i{1}; i < N; ++i) {
    int p; std::cin >> p;
    graph[--p].push_back(i);
  }

  HLD hld(graph);
  SegmentTree seg(N);

  for (int i{1}; i < N; ++i) seg.push(hld.discover[i], 1);

  auto Query01 = [&](int u, int v) -> long long {
    if (u == v) return 0LL;
    long long ret{0LL};
    while (hld.chain[u] != hld.chain[v]) {
      if (hld.depth[hld.head[hld.chain[u]]] < hld.depth[hld.head[hld.chain[v]]])
        std::swap(u, v);
      int H = hld.head[hld.chain[u]];
      ret += seg.query(hld.discover[H], hld.discover[u]);
      u = hld.parent[H];
      assert(u != -1);
    }

    if (hld.depth[u] > hld.depth[v]) std::swap(u, v);
    ret += seg.query(hld.discover[u] + 1, hld.discover[v]);
    return ret;
  };

  auto Query02 = [&](int x) -> void {
    seg.push(hld.discover[x], 0);
  };

  int Q; std::cin >> Q;
  for (int query_idx{1}; query_idx <= Q; ++query_idx) {
    int op; std::cin >> op;

    if (1 == op) {
      int u, v;
      std::cin >> u >> v;
      std::cout << Query01(--u, --v) << '\n';
      continue;
    }
    if (2 == op) {
      int x; std::cin >> x;
      Query02(--x);
      continue;
    }
  }
}