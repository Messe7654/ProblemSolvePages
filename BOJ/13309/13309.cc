#include <algorithm>
#include <cassert>
#include <iostream>
#include <stack>
#include <vector>

int N, Q;
std::vector<int> T;
std::vector<int> L;
std::vector<int> parent;
std::vector<std::vector<int>> children;
std::vector<int> discover;
std::vector<int> finished;

auto println = [](std::vector<int>& list) -> void {
  if (list.empty()) {
    std::cout << "[]\n";
    return;
  }
  size_t size = list.size();
  std::cout << '[';
  for (size_t idx{1}; idx < size; ++idx) {
    std::cout << list[idx] << ((idx + 1 == size) ? "]\n" : ", ");
  }
};

void dfs() {
  std::vector<int> visited(N + 1);
  std::stack<int> stack;
  stack.push(1);
  int count{0};
  while (stack.empty() != true) {
    auto now = stack.top();
    if (visited[now] != true) {
      visited[now] = true;
      discover[now] = ++count;
      for (auto next : children[now]) {
        if (visited[next] != true) stack.push(next);
      }
    } else {
      stack.pop();
      finished[now] = count;
    }
  }
}

void Update(int Tidx, int start, int end, int left, int right, int value) {
  if (L[Tidx] != 0) {
    if (discover[T[Tidx]] <= discover[L[Tidx]]) {
      T[Tidx] = L[Tidx];
      L[Tidx << 1] = L[Tidx];
      L[Tidx << 1 | 1] = L[Tidx];
    }
    L[Tidx] = 0;
  }

  if (end < left || right < start) return;
  if (left <= start && end <= right) {
    if (discover[T[Tidx]] > discover[value]) return;
    T[Tidx] = value;
    L[Tidx << 1] = value;
    L[Tidx << 1 | 1] = value;
    return;
  }

  int mid = start + ((end - start) >> 1);
  Update(Tidx << 1, start, mid, left, right, value);
  Update(Tidx << 1 | 1, mid + 1, end, left, right, value);
}

int Get(int Tidx, int start, int end, int idx) {
  if (L[Tidx] != 0) {
    if (discover[T[Tidx]] <= discover[L[Tidx]]) {
      T[Tidx] = L[Tidx];
      L[Tidx << 1] = L[Tidx];
      L[Tidx << 1 | 1] = L[Tidx];
    }
    L[Tidx] = 0;
  }
  if (idx < start || end < idx) return -1;
  if (start == end) return T[Tidx];

  int mid = start + ((end - start) >> 1);
  int lhs = Get(Tidx << 1, start, mid, idx);
  int rhs = Get(Tidx << 1 | 1, mid + 1, end, idx);
  return (lhs == -1) ? rhs : lhs;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  std::cin >> N >> Q;
  T.resize(N << 3);
  L.resize(N << 3);
  parent.resize(N + 1);
  children.resize(N + 1);
  discover.resize(N + 1);
  finished.resize(N + 1);

  for (int i{2}; i <= N; ++i) {
    std::cin >> parent[i];
    children[parent[i]].push_back(i);
  }

  for (int i{1}; i <= N; ++i)
    std::sort(children[i].rbegin(), children[i].rend());

  dfs();

  Update(1, 1, N, 1, N, 1);

  while (Q-- != 0) {
    int b, c, d;
    std::cin >> b >> c >> d;

    // b와 c를 연결하는 경로가 존재하는지 묻는 질의만 수행
    if (d == 0) {
      auto lhs = Get(1, 1, N, discover[b]);
      auto rhs = Get(1, 1, N, discover[c]);
      std::cout << ((lhs == rhs) ? "YES\n" : "NO\n");
    }
    // b와 c를 연결하는 경로가 존재하는지 묻고,
    // "YES"면 b와 parent[b]를 연결 끊기, "NO"면 c와 parent[c]를 연결 끊기
    else {
      auto lhs = Get(1, 1, N, discover[b]);
      auto rhs = Get(1, 1, N, discover[c]);
      if (lhs == rhs) {
        std::cout << "YES\n";
        if (b != 1) Update(1, 1, N, discover[b], finished[b], b);
      } else {
        std::cout << "NO\n";
        if (c != 1) Update(1, 1, N, discover[c], finished[c], c);
      }
    }
  }
}