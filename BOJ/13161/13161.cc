#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

constexpr int kMax = 1'000'000'007;

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N;
  std::cin >> N;

  const int source{0}, sync{N + 1};
  std::vector<std::vector<int>> graph(N + 2);
  std::vector<std::vector<int>> capacity(N + 2, std::vector<int>(N + 2));
  std::vector<std::vector<int>> flow(N + 2, std::vector<int>(N + 2));

  for (int i{1}; i <= N; ++i) {
    int op;
    std::cin >> op;
    if (op == 1) {
      graph[source].push_back(i);
      graph[i].push_back(source);
      capacity[source][i] = kMax;
    }
    else if (op == 2) {
      graph[sync].push_back(i);
      graph[i].push_back(sync);
      capacity[i][sync] = kMax;
    }
  }

  for (int i{1}; i <= N; ++i) {
    for (int j{1}; j <= N; ++j) {
      std::cin >> capacity[i][j];
      if (i != j) graph[i].push_back(j);
    }
  }

  auto MaxFlow = [&]() -> long long {
    long long ret{0};
    std::vector<int> parent(N + 2, -1);

    auto BFS = [&]() -> bool {
      std::fill(parent.begin(), parent.end(), -1);
      std::vector<bool> visited(N + 2);
      std::queue<int> queue;
      queue.push(source);

      while (queue.empty() != true) {
        auto now = queue.front();
        queue.pop();

        for (const auto& next : graph[now]) {
          if (visited[next] == true || capacity[now][next] - flow[now][next] <= 0) continue;
          queue.push(next);
          visited[next] = true;
          parent[next] = now;
          if (sync == next) return true;
        }
      }
      return false;
    };

    while (BFS()) {
      int now_flow = kMax;
      for (int i{sync}; i != source; i = parent[i]) {
        int p = parent[i];
        now_flow = std::min(now_flow, capacity[p][i] - flow[p][i]);
      }
      for (int i{sync}; i != source; i = parent[i]) {
        int p = parent[i];
        flow[p][i] += now_flow;
        flow[i][p] -= now_flow;
      }
      ret += now_flow;
    }
    return ret;
  };

  auto MinCut = [&]() -> std::pair<std::vector<int>, std::vector<int>> {
    std::vector<bool> cut(N + 2);
    std::queue<int> queue;

    queue.push(source);
    cut[source] = true;

    while (queue.empty() != true) {
      auto now = queue.front();
      queue.pop();

      for (const auto& next : graph[now]) {
        if (cut[next] != true && capacity[now][next] - flow[now][next] > 0) {
          cut[next] = true;
          queue.push(next);
        }
      }
    }

    std::vector<int> A, B;
    for (int i{1}; i <= N; ++i) {
      if (cut[i] == true) A.push_back(i);
      else B.push_back(i);
    }
    return {A, B};
  };

  auto Println = [](const auto& list) {
    if (list.empty()){ std::cout << '\n'; return; }
    for (std::size_t i{0}; i < list.size(); ++i) {
      std::cout << list[i] << ((i + 1 == list.size()) ? '\n' : ' ');
    }
  };

  std::cout << MaxFlow() << '\n';
  auto [A, B] = MinCut();
  Println(A);
  Println(B);
}