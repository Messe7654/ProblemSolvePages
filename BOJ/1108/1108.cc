#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <stack>
#include <string_view>
#include <unordered_map>
#include <vector>

std::vector<std::vector<int>> graph;
std::unordered_map<std::string, int> map;

std::vector<long long> tarjan() {
  int size = static_cast<int>(map.size());

  std::vector<long long> ret(size, 1);

  std::vector<int> scc_id(size);
  std::vector<int> low_link(size);
  std::vector<int> discover(size);
  std::vector<bool> visited(size);
  std::stack<int> stack;

  std::function<void(int)> dfs;
  dfs = [&, euler_count = (int)0, max_id = (int)0](int now) mutable -> void {
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
      ++max_id;
      std::vector<int> scc;
      while (stack.empty() != true) {
        int top = stack.top(); stack.pop();
        scc.push_back(top);
        scc_id[top] = max_id;
        visited[top] = false;
        if (now == top) break;
      }

      for (const auto& ele : scc) {
        for (const auto& next : graph[ele]) {
          if (scc_id[ele] == scc_id[next]) continue;
          assert(ret[ele] + ret[next] > 0 && "오버플로 발생 가능?");
          ret[ele] += ret[next];
        }
      }
    }
  };

  for (int i{0}; i < size; ++i) {
    if (discover[i] == 0) dfs(i);
  }

  return ret;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N;

  for (int i{0}; i < N; ++i) {
    std::string now;
    std::cin >> now;
    if (map.find(now) == map.end()) {
      map[now] = map.size();
      graph.push_back(std::vector<int>());
    }

    int k; std::cin >> k;
    for (int j{0}; j < k; ++j) {
      std::string prev;
      std::cin >> prev;
      if (map.find(prev) == map.end()) {
        map[prev] = map.size();
        graph.push_back(std::vector<int>());
      }

      graph[map[now]].push_back(map[prev]);
    }
  }

  auto score = tarjan();

  std::string probe;
  std::cin >> probe;

  std::cout << score[map[probe]];
}