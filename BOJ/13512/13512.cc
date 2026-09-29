#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <vector>

constexpr int kMax = 0x7FFFFFFF;

struct HLD {
  std::vector<int> chain;
  std::vector<int> depth;
  std::vector<int> discover;
  std::vector<int> inverse;
  std::vector<int> head;
  std::vector<int> parent;

  HLD(std::vector<std::vector<int>>& graph) {
    int size = static_cast<int>(graph.size()) - 1;

    chain.resize(size + 1);
    depth.resize(size + 1);
    discover.resize(size + 1);
    inverse.resize(size + 1);
    head.resize(size + 1);
    parent.resize(size + 1);
      
    std::vector<int> weight(size + 1);

    std::function<void(int)> DFS;
    DFS = [&, visited = std::vector<bool>(size + 1)](int now) mutable -> void {
      visited[now] = true;
      weight[now] = 1;

      for (const auto& next : graph[now]) {
        if (visited[next] == true) continue;
        parent[next] = now;
        depth[next] = depth[now] + 1;
        DFS(next);
        weight[now] += weight[next];
      }
    };

    DFS(1);
    for (auto& adjacency_list : graph) {
      std::sort(adjacency_list.begin(), adjacency_list.end(),
        [&weight](const auto& lhs, const auto& rhs) { return weight[lhs] > weight[rhs]; });
    }

    std::function<void(int)> Construct;
    Construct = [&, visited = std::vector<bool>(size + 1),
                 order1 = (int)0, order2 = (int)0](int now) mutable -> void {
      visited[now] = true;
      discover[now] = ++order1;

      for (const auto& next : graph[now]) {
        if (visited[next] == true) continue;
        chain[next] = chain[now];
        Construct(next);
        break;
      }

      for (const auto& next : graph[now]) {
        if (visited[next] == true) continue;
        chain[next] = ++order2;
        head[order2] = next;
        Construct(next);
      }
    };

    head[0] = 1;
    Construct(1);

    for (int i{1}; i <= size; ++i) {
      inverse[discover[i]] = i;
    }
  }
};

class segment_tree {
 public:
  segment_tree(int size) : capacity(size) { T.resize(capacity << 2, kMax); }

  void Update(int idx, int val) {
    __update__(1, 1, capacity, idx, val);
  }

  int Get(int left, int right) {
    return __get__(1, 1, capacity, left, right);
  }

 private:
  void __update__(int Tidx, int start, int end, int idx, int val) {
    if (idx < start || end < idx) return;
    if (start == end) { T[Tidx] = val; return; }
    int mid = start + ((end - start) >> 1);
    __update__(Tidx << 1    , start  , mid, idx, val);
    __update__(Tidx << 1 | 1, mid + 1, end, idx, val);
    T[Tidx] = std::min(T[Tidx << 1], T[Tidx << 1 | 1]);
  }

  int __get__(int Tidx, int start, int end, int left, int right) {
    if (right < start || end < left) return kMax;
    if (left <= start && end <= right) return T[Tidx];
    int mid = start + ((end - start) >> 1);
    auto lhs = __get__(Tidx << 1    , start  , mid, left, right);
    auto rhs = __get__(Tidx << 1 | 1, mid + 1, end, left, right);
    return std::min(lhs, rhs);
  }

  int capacity;
  std::vector<int> T;
};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N;
  std::vector<std::vector<int>> graph(N + 1);
  
  for (int i{1}; i < N; ++i) {
    int a, b; std::cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  HLD hld(graph);
  segment_tree seg(N);
  std::vector<bool> is_black(N + 1);

  // update
  auto query01 = [&](int idx) {
    is_black[idx] = !is_black[idx];
    seg.Update(hld.discover[idx], is_black[idx] ? hld.discover[idx] : kMax);
  };

  // get
  auto query02 = [&](int idx) {
    auto min = kMax;
    while (idx != 0) {
      int H = hld.head[hld.chain[idx]];
      min = std::min(min, seg.Get(hld.discover[H], hld.discover[idx]));
      idx = hld.parent[H];
    }
    return (min == kMax) ? -1 : hld.inverse[min];
  };

  int M; std::cin >> M;
  for (int i{0}; i < M; ++i) {
    int a, b; std::cin >> a >> b;
    if (a == 1) {
      query01(b);
    }
    else {
      std::cout << query02(b) << '\n';
    }
  }
}