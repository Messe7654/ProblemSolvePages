#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M; std::cin >> N >> M;

  // 0 : source, N + M + 1 : sink, 1 ~ N : 직원, N + 1 ~ N + M : 일
  std::vector<std::vector<int>> flow(N + M + 2, std::vector<int>(N + M + 2));
  std::vector<std::vector<int>> capacity(N + M + 2, std::vector<int>(N + M + 2));
  std::vector<std::vector<int>> weight(N + M + 2, std::vector<int>(N + M + 2));
  std::vector<std::vector<int>> graph(N + M + 2);
  std::vector<int> prev(N + M + 2);
  std::vector<bool> is_in_queue(N + M + 2);
  std::vector<int> distance(N + M + 2);

  for (int i{1}; i <= N; ++i) {
    capacity[0][i] = 1;
    graph[0].push_back(i);
    graph[i].push_back(0);
  }
  for (int i{1}; i <= M; ++i) {
    capacity[N + i][N + M + 1] = 1;
    graph[N + i].push_back(N + M + 1);
    graph[N + M + 1].push_back(N + i);
  }

  for (int i{1}; i <= N; ++i) {
    int K; std::cin >> K;
    for (int j{0}; j < K; ++j) {
      int job, salary; std::cin >> job >> salary;
      capacity[i][N + job] = 1;
      graph[i].push_back(N + job);
      graph[N + job].push_back(i);
      weight[i][N + job] = salary;
      weight[N + job][i] = -salary;
    }
  }
  
  int minimum_cost{0}, maximum_flow{0};
  while (true) {
    std::fill(prev.begin(), prev.end(), -1);
    std::fill(distance.begin(), distance.end(), 0x7FFFFFFF);
    std::queue<int> queue;

    queue.push(0);
    is_in_queue[0] = true;
    prev[0] = 0;
    distance[0] = 0;

    while (queue.empty() != true) {
      int now = queue.front(); queue.pop();

      is_in_queue[now] = false;

      for (const auto& next : graph[now]) {
        if (distance[next] > distance[now] + weight[now][next] &&
            capacity[now][next] - flow[now][next] > 0) {
          distance[next] = distance[now] + weight[now][next];
          prev[next] = now;
          if (is_in_queue[next] != true) {
            queue.push(next);
            is_in_queue[next] = true;
          }
        }
      }
    }

    if (prev[N + M + 1] == -1) break;

    for (int i{N + M + 1}; i != 0; i = prev[i]) {
      minimum_cost += weight[prev[i]][i];
      ++flow[prev[i]][i];
      --flow[i][prev[i]];
    }
    ++maximum_flow;
  }

  std::cout << maximum_flow << '\n' << minimum_cost;
}

