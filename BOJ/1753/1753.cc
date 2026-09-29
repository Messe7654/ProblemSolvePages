#include <iostream>
#include <vector>

namespace user_defined {
template <typename T>
class priority_queue {
 public:
  bool empty();
  const T& top();
  void push(const T& elem);
  void pop();
 private:
  std::vector<T> data;
};

template <typename T>
bool priority_queue<T>::empty() {
  return data.empty();
}

template <typename T>
const T& priority_queue<T>::top() {
  return data.back();
}

template <typename T>
void priority_queue<T>::push(const T& elem) {
  int index{0}, size{static_cast<int>(data.size())};
  for (; index < size; ++index) {
    if (std::less<T>()(data[index], elem)) break;
  }
  data.insert(data.begin() + index, elem);
}

template <typename T>
void priority_queue<T>::pop() {
  data.pop_back();
};
};

std::vector<int> dijkstra(const std::vector<std::vector<std::pair<int, int>>>& G, int src) {
  int N = static_cast<int>(G.size()) - 1;
  std::vector<int> distance(N + 1, 0x7FFFFFFF);
  distance[src] = 0;

  user_defined::priority_queue<std::pair<int, int>> pq;
  pq.push({0, src});

  while (pq.empty() != true) {
    auto [now_weight, now_idx] = pq.top();
    pq.pop();
    if (distance[now_idx] < now_weight) continue;

    for (auto [next_idx, next_weight] : G[now_idx]) {
      if (next_weight + now_weight < distance[next_idx]) {
        distance[next_idx] = next_weight + now_weight;
        pq.push({distance[next_idx], next_idx});
      }
    }
  }

  return distance;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int V, E; std::cin >> V >> E;
  int K; std::cin >> K;

  std::vector<std::vector<std::pair<int, int>>> adj(V + 1);

  for (int i{0}; i < E; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;
    adj[u].push_back({v, w});
  }

  auto distance = dijkstra(adj, K);

  for (int i{1}; i <= V; ++i) {
    if (i == K) std::cout << "0\n";
    else if (distance[i] == 0x7FFFFFFF) std::cout << "INF\n";
    else std::cout << distance[i] << '\n';
  }
}