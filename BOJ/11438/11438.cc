#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

struct HLD {
  std::vector<int> chain;
  std::vector<int> depth;
  std::vector<int> discover;
  std::vector<int> head;
  std::vector<int> parent;

  HLD(std::vector<std::vector<int>>& graph) {
    int size = static_cast<int>(graph.size()) - 1;

    chain.resize(size + 1);
    depth.resize(size + 1);
    discover.resize(size + 1);
    head.resize(size + 1);
    parent.resize(size + 1);

    std::vector<int> weight(size + 1);

    std::function<void(int)> DFS;
    DFS = [&, visited = std::vector<bool>(size + 1)](int now) mutable -> void {
      visited[now] = true;
      weight[now] = 1;
      for (const auto& next : graph[now]) {
        if (visited[next] == true) continue;
        depth[next] = depth[now] + 1;
        parent[next] = now;
        DFS(next);
        weight[now] += weight[next];
      }
    };

    DFS(1);

    for (auto& adjacency_list : graph) {
      std::sort(adjacency_list.begin(), adjacency_list.end(), [&weight](const auto& lhs, const auto& rhs) {
        return weight[lhs] > weight[rhs];
      });
    }

    std::function<void(int)> ConstructHLD;
    ConstructHLD = [&, visited = std::vector<bool>(size + 1), 
                    order1 = (int)1, order2 = (int)1](int now) mutable -> void {
      visited[now] = true;
      // Heavy-Chain
      for (const auto& next : graph[now]) {
        if (visited[next] == true) continue;
        chain[next] = chain[now];
        discover[next] = ++order1;
        ConstructHLD(next);
        break;
      }
      // New Chain
      for (const auto& next : graph[now]) {
        if (visited[next] == true) continue;
        chain[next] = ++order2;
        head[order2] = next;
        discover[next] = ++order1;
        ConstructHLD(next);
      }
    };

    chain[1] = head[1] = discover[1] = 1;
    ConstructHLD(1);
  }
};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N;
  std::vector<std::vector<int>> graph(N + 1);
  
  for (int i{1}; i < N; ++i) {
    int a, b; std::cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  HLD hld(graph);

  auto LCA = [&](int a, int b) -> int {
    if (a == b) return a;
    while (hld.chain[a] != hld.chain[b]) {
      if (hld.depth[hld.head[hld.chain[a]]] < hld.depth[hld.head[hld.chain[b]]]) std::swap(a, b);
      a = hld.parent[hld.head[hld.chain[a]]];
    }
    if (hld.depth[a] > hld.depth[b]) std::swap(a, b);
    return a;
  };

  int M; std::cin >> M;
  for (int i{0}; i < M; ++i) {
    int a, b; std::cin >> a >> b;
    std::cout << LCA(a, b) << '\n';
  }
}