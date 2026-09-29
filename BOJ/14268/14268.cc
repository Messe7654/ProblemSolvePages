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

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M; std::cin >> N >> M;

  std::vector<std::vector<int>> children(N + 1);
  for (int i{1}; i <= N; ++i) {
    int c; std::cin >> c;
    if (c == -1) continue;
    children[c].push_back(i);
  }

  std::function<void(int)> DFS;
  std::vector<int> discover(N + 1);
  std::vector<int> finished(N + 1);
  DFS = [&, cnt = (int)0](int now) mutable -> void {
    discover[now] = ++cnt;
    for (const auto& next : children[now]) {
      DFS(next);
    }
    finished[now] = cnt;
  };
  DFS(1);

  SegmentTree seg(N);

  for (int i{0}; i < M; ++i) {
    int op; std::cin >> op;
    if (op == 1) {
      int i, w; std::cin >> i >> w;
      seg.push(discover[i], finished[i], w);
      continue;
    }
    if (op == 2) {
      int i; std::cin >> i;
      std::cout << seg.get(discover[i], discover[i]) << '\n';
      continue;
    }
  }
}