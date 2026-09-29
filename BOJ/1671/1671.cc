#include <iostream>
#include <functional>
#include <vector>

struct shark {
  int a;
  int b;
  int c;

  shark() : a(0), b(0), c(0) {}

  bool operator<=(shark& o) {
    return (a <= o.a && b <= o.b && c <= o.c);
  }

  friend std::istream& operator>>(std::istream& IN, shark& o) {
    IN >> o.a >> o.b >> o.c;
    return IN;
  }
};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N;
  std::cin >> N;

  std::vector<shark> info(N);
  std::vector<std::vector<int>> graph(N);
  std::vector<int> left(N, -1);
  std::vector<bool> visited(N);
  auto clear = [&visited, N]() {
    for (int i{0}; i < N; ++i) visited[i] = false;
  };

  for (int i{0}; i < N; ++i) {
    std::cin >> info[i];
  }

  for (int i{0}; i < N; ++i) {
    for (int j{0}; j < N; ++j) {
      if (i == j) continue;
      if (info[i] <= info[j]) {
        if (info[j] <= info[i]) {
          if (i < j) graph[j].push_back(i);
          else graph[i].push_back(j);
        }
        else graph[j].push_back(i);
      }
    }
  }

  std::function<int(int)> dfs;
  dfs = [&](int now) -> int {
    visited[now] = true;
    for (auto next :  graph[now]) {
      if (left[next] == -1 || !visited[left[next]] && dfs(left[next])) {
        left[next] = now;
        return 1;
      }
    }
    return 0;
  };

  int count{0};
  for (int i{0}; i < N; ++i) {
    clear();
    if (dfs(i)) ++count;
    clear();
    if (dfs(i)) ++count;
  }

  std::cout << N - count;
}