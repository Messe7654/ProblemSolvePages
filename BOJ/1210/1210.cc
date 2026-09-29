#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

constexpr int kMax = 10'000'000;

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M;
  int begin, finish;

  std::cin >> N >> M;
  std::cin >> begin >> finish;

  const int source{0}, sync{N << 1 | 1}, bias{N};

  std::vector<std::vector<int>> cost((N + 1) << 1, std::vector<int>((N + 1) << 1));
  std::vector<std::vector<int>> flow((N + 1) << 1, std::vector<int>((N + 1) << 1));
  std::vector<std::vector<int>> capacity((N + 1) << 1, std::vector<int>((N + 1) << 1));

  std::vector<std::vector<int>> graph((N + 1) << 1);

  auto InsertEdge = [&](int src, int dst) -> void {
    graph[src].push_back(dst + bias);
    graph[dst + bias].push_back(src);
    capacity[src][dst + bias] = kMax;
  };

  graph[source].push_back(begin + bias);
  graph[begin + bias].push_back(source);
  capacity[source][begin + bias] = kMax;

  graph[finish].push_back(sync);
  graph[sync].push_back(finish);
  capacity[finish][sync] = kMax;

  for (int i{1}; i <= N; ++i) {
    int temp; std::cin >> temp;
    graph[i + bias].push_back(i);
    graph[i].push_back(i + bias);
    capacity[i + bias][i] = temp; 
  }

  for (int i{0}; i < M; ++i) {
    int a, b;
    std::cin >> a >> b;
    InsertEdge(a, b);
    InsertEdge(b, a);
  }

  auto MaxFlow = [&]() -> long long {
    std::vector<int> parent((N + 1) << 1, -1);
    long long ret{0};

    auto BFS = [&]() -> bool {
      std::fill(parent.begin(), parent.end(), -1);
      std::vector<bool> visited((N + 1) << 1);
      std::queue<int> queue;
      queue.push(source);
      visited[source] = true;

      while (queue.empty() != true) {
        auto now = queue.front();
        queue.pop();

        for (const auto next : graph[now]) {
          if (capacity[now][next] - flow[now][next] <= 0 || visited[next] == true) continue;
          visited[next] = true;
          queue.push(next);
          parent[next] = now;
          if (next == sync) return true;
        }
      }
      return false;
    };
    
    while (BFS() == true) {
      int now_flow = kMax;
      for (int i{sync}; i != source; i = parent[i]) {
        now_flow = std::min(now_flow, capacity[parent[i]][i] - flow[parent[i]][i]);
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

  auto Solution = [&]() -> std::vector<int> {
    std::vector<int> ret;
    std::vector<bool> cut((N + 1) << 1);

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

    for (int i{1}; i <= N; ++i) {
      if (cut[i + bias] == true && cut[i] == false) {
        ret.push_back(i);
      }
    }    

    return ret;
  };

  MaxFlow();

  auto ret = Solution();
  for (auto i : ret) {
    std::cout << i << ' ';
  }
  std::cout << '\n';
}