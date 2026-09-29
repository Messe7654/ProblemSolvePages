#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

class SegmentTree {
 public:
  SegmentTree(std::size_t size) {
    capacity = size;
    L.resize(capacity << 2);
    T.resize(capacity << 2);
  }

  void push(int left, int right, int weight) {
    __insert(1, 1, capacity, left, right, weight);
  }

  int get(int left, int right) {
    return __get(1, 1, capacity, left, right);
  }

 private:
  void __lazy_propagate(int Tidx, int start, int end) {
    T[Tidx] += (end - start + 1) * L[Tidx];
    if (start != end) {
      L[Tidx << 1    ] += L[Tidx];
      L[Tidx << 1 | 1] += L[Tidx];
    }
    L[Tidx] = 0;
  }

  void __insert(int Tidx, int start, int end, int left, int right, int weight) {
    if (L[Tidx] != 0) __lazy_propagate(Tidx, start, end);
    if (right < start || end < left) return;
    if (left <= start && end <= right) {
      T[Tidx] += (end - start + 1) * weight;
      if (start != end) {
        L[Tidx << 1    ] += weight;
        L[Tidx << 1 | 1] += weight;
      }
      return;
    }
    int mid = start + ((end - start) >> 1);
    __insert(Tidx << 1    ,   start, mid, left, right, weight);
    __insert(Tidx << 1 | 1, mid + 1, end, left, right, weight);
    T[Tidx] = T[Tidx << 1] + T[Tidx << 1 | 1];
  }

  int __get(int Tidx, int start, int end, int left, int right) {
    if (L[Tidx] != 0) __lazy_propagate(Tidx, start, end);
    if (right < start || end < left) return 0;
    if (left <= start && end <= right) return T[Tidx];
    int mid = start + ((end - start) >> 1);
    auto lhs = __get(Tidx << 1    ,   start, mid, left, right);
    auto rhs = __get(Tidx << 1 | 1, mid + 1, end, left, right);
    return lhs + rhs;
  }

  std::size_t capacity;
  std::vector<int> L;
  std::vector<int> T;
};

struct HLD {
  std::vector<int> head;
  std::vector<int> chain;
  std::vector<int> discover;
  std::vector<int> depth;
  std::size_t capacity;

  HLD(std::vector<std::vector<int>>& children, std::vector<int>& parent) {
    capacity = parent.size();

    head.resize(capacity);
    chain.resize(capacity);
    discover.resize(capacity);
    depth.resize(capacity);

    std::vector<int> weight(capacity);

    auto DFS = [&]() -> void {
      std::function<void(int)> __dfs;
      __dfs = [&](int now) -> void {
        weight[now] = 1;
        for (const auto& next : children[now]) {
          depth[next] += depth[now] + 1;
          __dfs(next);
          weight[now] += weight[next];
        }
      };
      __dfs(1);
    };

    DFS();

    for (auto& list : children) {
      std::sort(list.begin(), list.end(),
          [&weight](const auto& lhs, const auto& rhs) {
        return weight[lhs] > weight[rhs];   
      });
    }

    std::vector<bool> visited(capacity);
    std::function<void(int)> ConstructHLD;
    ConstructHLD = [&, discover_count = (int)1, chain_count = (int)1](int now) mutable -> void {
      visited[now] = true;

      // Heavy Chain
      for (const auto& next : children[now]) {
        if (visited[next] == true) continue;
        chain[next] = chain[now];
        discover[next] = ++discover_count;
        ConstructHLD(next);
        break;
      }

      // Light Chain
      for (const auto& next : children[now]) {
        if (visited[next] == true) continue;
        chain[next] = ++chain_count;
        head[chain_count] = next;
        discover[next] = ++discover_count;
        ConstructHLD(next);
      }
    };

    chain[1] = 1;
    head[1] = 1;
    discover[1] = 1;
    ConstructHLD(1);
  };
};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M; std::cin >> N >> M;
  std::vector<int> parent(N + 1);
  std::vector<std::vector<int>> children(N + 1);

  for (int i{1}; i <= N; ++i) {
    int c; std::cin >> c;
    if (c == -1) continue;
    parent[i] = c;
    children[c].push_back(i);
  }

  HLD hld(children, parent);
  SegmentTree seg(N);

  auto query01 = [&](int i, int w) -> void {
    while (hld.chain[i] != hld.chain[1]) {
      int H = hld.head[hld.chain[i]];
      seg.push(hld.discover[H], hld.discover[i], w);
      i = parent[H];
    }
    seg.push(hld.discover[1], hld.discover[i], w);
  };

  auto query02 = [&](int i) -> int {
    return seg.get(hld.discover[i], hld.discover[i]);
  };

  for (int i{0}; i < M; ++i) {
    int op; std::cin >> op;
    if (op == 1)  {
      int i, w; std::cin >> i >> w;
      query01(i, w);
      continue;
    }
    if (op == 2) {
      int i; std::cin >> i;
      std::cout << query02(i) << '\n';
      continue;
    }
  }
}