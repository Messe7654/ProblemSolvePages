#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>

int SCC(const std::vector<std::vector<int>>& graph) {
  int size = static_cast<int>(graph.size());

  std::vector<int> group_id(size, -1);
  std::vector<bool> visited(size);
  std::vector<int> discover(size);
  std::vector<int> low_link(size);
  std::stack<int> stack;
  --size;

  std::vector<int> indegree;
  indegree.reserve(size);

  std::function<void(int)> dfs;

  dfs = [&, euler_count = (int)0, id_count = (int)0](int now) mutable -> void {
    visited[now] = true;
    discover[now] = ++euler_count;
    low_link[now] = euler_count;

    stack.push(now);

    for (const auto& next : graph[now]) {
      if (discover[next] == 0) {
        dfs(next);
        low_link[now] = std::min(low_link[now], low_link[next]);
      }
      else if (visited[next] == true) {
        low_link[now] = std::min(low_link[now], discover[next]);
      }
    }

    if (low_link[now] == discover[now]) {
      std::vector<int> now_scc;
      while (stack.empty() != true) {
        int top = stack.top(); stack.pop();

        now_scc.push_back(top);
        visited[top] = false;

        if (now == top) break;
      }

      ++id_count;
      indegree.push_back(0);
      std::unordered_set<int> set;

      for (const int& member : now_scc) {
        group_id[member] = id_count;
      }

      for (const int& member : now_scc) {
        for (const int& next : graph[member]) {
          if (group_id[member] == group_id[next]) continue;
          set.insert(group_id[next]);
        }
      }

      for (const int& next_group_id : set) ++indegree[next_group_id];
    }
  };

  for (int i{1}; i <= size; ++i) {
    if (discover[i] == 0) dfs(i);
  }

  int ans{0};
  for (const auto& i : indegree) if (i == 0) ++ans;

  return ans;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M; std::cin >> N >> M;

  std::vector<std::vector<int>> graph(N + 1);

  for (int i{0}; i < M; ++i) {
    int x, y;
    std::cin >> x >> y;
    graph[x].push_back(y);
  }

  std::cout << SCC(graph);
}