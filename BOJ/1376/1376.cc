#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <vector>

int msb(int i) {
  i |= i >> 1;
  i |= i >> 2;
  i |= i >> 4;
  i |= i >> 8;
  i |= i >> 16;
  return ++i;
}

class BIT {
 public:
  BIT(int size) : capacity(size) { tree.resize(msb(capacity)); }
  void push(int idx) {
    while (idx <= capacity) {
      ++tree[idx];
      idx += idx & (~idx + 1);
    }
  }

  void pop(int idx) {
    while (idx <= capacity) {
      --tree[idx];
      idx += idx & (~idx + 1);
    }
  }

  int get(int idx) {
    int ret{0};
    while (idx > 0) {
      ret += tree[idx];
      idx ^= idx & (~idx + 1);
    }
    return ret;
  }

  int kthElement(int k) {
    int left{1}, right{static_cast<int>(capacity)};
    while (right - left > 0) {
      int mid = left + ((right - left) >> 1);
      if (get(mid) < k) left = mid + 1;
      else right = mid;
    }
    return left;
  }

 private:
  int capacity;
  std::vector<int> tree;
};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M; std::cin >> N >> M;
  std::vector<std::vector<int>> graph(N + 1);
  std::vector<BIT> adjacent_info(N + 1, BIT(0));
  for (int i{0}; i < M; ++i) {
    int a, b; std::cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  for (int i{1}; i <= N; ++i) {
    std::sort(graph[i].begin(), graph[i].end());
    graph[i].erase(std::unique(graph[i].begin(), graph[i].end()), graph[i].end());
  }

  for (int now{1}; now <= N; ++now) {
    adjacent_info[now] = BIT(graph[now].size());
    for (int j{1}; j <= graph[now].size(); ++j) adjacent_info[now].push(j);
  }

  std::vector<bool> visited(N + 1);

  std::function<void(int)> MFS;
  MFS = [&](int now) -> void {
    std::cout << now << ' ';
    assert(visited[now] == false);
    visited[now] = true;
    auto GetIdx = [](int target, const auto& list) {
      return std::distance(list.begin(), std::lower_bound(list.begin(), list.end(), target)) + 1;
    };

    for (const auto& next : graph[now]) {
      adjacent_info[next].pop(GetIdx(now, graph[next]));
    }

    while (true) {
      auto count = adjacent_info[now].get(graph[now].size());
      if (count == 0) break;
      auto next = ((count & 1) ? adjacent_info[now].kthElement(count - (count >> 1)) : adjacent_info[now].kthElement(1));
      MFS(graph[now][next - 1]);
    }
  };
  MFS(1);
}