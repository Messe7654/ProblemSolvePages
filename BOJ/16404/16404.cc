#include <iostream>
#include <vector>
#include <functional>

class segment_tree {
 public:
  segment_tree(int N) : capacity(N) {
    lazy.resize(N << 2);
    data.resize(N << 2);
  }

  void Update(int start, int end, int aug) { __update(1, 1, capacity, start, end, aug); }
  
  int Get(int start, int end) { return __get(1, 1, capacity, start, end); }

 private:
  void __update(int Tidx, int start, int end, int left, int right, int aug) {
    if (lazy[Tidx] != 0) {
      data[Tidx] += (end - start + 1) * lazy[Tidx];
      if (start != end) {
        lazy[Tidx << 1    ] += lazy[Tidx];
        lazy[Tidx << 1 | 1] += lazy[Tidx];
      }
      lazy[Tidx] = 0;
    }

    if (right < start || end < left) return;
    if (left <= start && end <= right) {
      data[Tidx] += (end - start + 1) * aug;
      if (start != end) {
        lazy[Tidx << 1    ] += aug;
        lazy[Tidx << 1 | 1] += aug;
      }
      return;
    }

    int mid = start + ((end - start) >> 1);
    __update(Tidx << 1    , start,   mid, left, right, aug);
    __update(Tidx << 1 | 1, mid + 1, end, left, right, aug);
    data[Tidx] = data[Tidx << 1] + data[Tidx << 1 | 1];
  }

  int __get(int Tidx, int start, int end, int left, int right) {
    if (lazy[Tidx] != 0) {
      data[Tidx] += (end - start + 1) * lazy[Tidx];
      if (start != end) {
        lazy[Tidx << 1    ] += lazy[Tidx];
        lazy[Tidx << 1 | 1] += lazy[Tidx];
      }
      lazy[Tidx] = 0;
    }

    if (right < start || end < left) return 0;
    if (left <= start && end <= right) return data[Tidx];

    int mid = start + ((end - start) >> 1);
    auto lhs = __get(Tidx << 1    , start,   mid, left, right);
    auto rhs = __get(Tidx << 1 | 1, mid + 1, end, left, right);
    return lhs + rhs;
  }

  int capacity;
  std::vector<int> lazy;
  std::vector<int> data;
};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M;
  std::cin >> N >> M;

  std::vector<std::vector<int>> graph(N + 1);
  for (int i{1}; i <= N; ++i) {
    int p; std::cin >> p;
    if (p == -1) continue;
    graph[p].push_back(i);
  }

  std::vector<int> discover(N + 1);
  std::vector<int> finished(N + 1);

  std::function<void(int)> dfs;
  dfs = [&, euler_count = (int)0](int now) mutable -> void {
    discover[now] = ++euler_count;

    for (const auto& next : graph[now]) {
      if (discover[now] != 0) dfs(next);
    }

    finished[now] = euler_count;
  };

  dfs(1);

  segment_tree seg(N + 1);

  while (M-- != 0) {
    int op; std::cin >> op;
    if (op == 1) {
      int i, w;
      std::cin >> i >> w;
      seg.Update(discover[i], finished[i], w);
    }
    else { // op == 2
      int i; std::cin >> i;
      std::cout << seg.Get(discover[i], discover[i]) << '\n';
    }
  }
}