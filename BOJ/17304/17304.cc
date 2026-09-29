#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M; std::cin >> N >> M;

  std::vector<std::vector<int>> graph(N + 1);

  for (int i{0}; i < M; ++i) {
    int A, B;
    std::cin >> A >> B;
    graph[A].push_back(B);
  }

  std::vector<int> discover(N + 1);
  std::vector<int> finished(N + 1);
  std::vector<int> low_link(N + 1);
  std::vector<bool> visited(N + 1);
  std::vector<std::vector<int>> SCCs;

  auto GetSCCs = [&]() -> void {
    std::function<void(int)> dfs;
    dfs = [&, cnt = (int)0](int now) mutable -> void {
      vistied[now] = true;
      discover[now] = ++cnt;
      low_link[now] = cnt;

      for (const auto& next : graph[now]) {
        if (discover[next] == 0) {
          dfs(next);
          low_link[now] = std::min(low_link[now], low_link[next]);
        }
        else if (visited[next] == true) {
          // 일반적으로는, finished => visited[next] := false
          // 문제는 u <-> v의 간선을 가지고 있을 때의 처리
          // 만약 u -> v가  back edge라면,
          if ()
          // 만약 u -> v가 cross edge라면, 
        }
      }

      finished[now] = cnt;
    }
  };
}