#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

int N, M, K;
int S, D;
int tax;

struct edge {
  int dst;
  int weight;
};
std::vector<std::vector<edge>> adj;
std::vector<std::pair<int, int>> distance;
std::vector<std::pair<int, int>> path;

void dijkstra() {
  struct info {
    int id;
    int weight;
  };

  struct comp {
    bool operator()(const info& lhs, const info& rhs) const {
      return lhs.weight > rhs.weight;
    }
  };

  std::priority_queue<info, std::vector<info>, comp> pq;
  distance[S] = {0, 0};

  pq.push({S, 0});
  while (pq.empty() != true) {
    auto [now, now_weight] = pq.top();
    pq.pop();

    for (auto [next, next_weight] : adj[now]) {
      if (distance[next].first > next_weight + now_weight ||
          distance[next].second > distance[now].second + 1) {
        distance[next].first = next_weight + now_weight;
        distance[next].second = distance[now].second + 1;
        if (next == D)
          path.push_back({distance[next].first, distance[next].second});
        pq.push({next, distance[next].first});
      }
    }
  }
}

int min() {
  int ret{0x7FFFFFFF};
  for (auto [weight, count] : path) {
    ret = std::min(ret, weight + count * tax);
  }
  return ret;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  std::cin >> N >> M >> K;
  std::cin >> S >> D;
  adj.resize(N + 1);
  distance.resize(N + 1, {0x7FFFFFFF, 0x7FFFFFFF});

  for (int i{0}; i < M; ++i) {
    int a, b, w;
    std::cin >> a >> b >> w;
    adj[a].push_back({b, w});
    adj[b].push_back({a, w});
  }

  dijkstra();

  std::cout << min() << '\n';
  for (int i{0}; i < K; ++i) {
    int p;
    std::cin >> p;
    tax += p;
    std::cout << min() << '\n';
  }
}