#include <algorithm>
#include <iostream>
#include <vector>

int V, E;
std::vector<int> adj[10'001][2];      // {정방향, 역방향}

std::vector<int> substep1() {
  std::vector<bool> discover(V + 1, false);
  std::vector<bool> finished(V + 1, false); 
  std::vector<int> scc_stack;

  auto DFS = [&discover, &finished, &scc_stack](int start) -> void {
    if (discover[start] == true) return;
    std::vector<int> stack;
    stack.push_back(start);

    while (stack.empty() != true) {
      auto now = stack.back();
      if (discover[now] != true) {
        discover[now] = true;

        for (auto rit{adj[now][0].rbegin()}; rit != adj[now][0].rend(); ++rit) {
          auto next = *rit;
          if (discover[next] != true) stack.push_back(next);
        }
      }
      if (now == stack.back()) {
        if (finished[now] != true) {
          finished[now] = true;
          scc_stack.push_back(now);
        }
        stack.pop_back();
      }
    }
  };

  for (int i{1}; i <= V; ++i) DFS(i);
  return scc_stack;
}

std::vector<std::vector<int>> substep2(std::vector<int>& scc_stack) {
  std::vector<bool> visited(V + 1, false);
  std::vector<int> leaders(V + 1);

  auto DFS = [&visited, &leaders](int start) -> void {
    if (visited[start] == true) return;
    std::vector<int> stack;
    stack.push_back(start);

    while (stack.empty() != true) {
      auto now = stack.back();
      stack.pop_back();
      leaders[now] = start;
      visited[now] = true;

      for (auto rit{adj[now][1].rbegin()}; rit != adj[now][1].rend(); ++rit) {
        auto next = *rit;
        if (visited[next] != true) {
          visited[next] = true;
          stack.push_back(next);
        }
      }
    }
  };

  while (scc_stack.empty() != true) {
    auto start = scc_stack.back();
    scc_stack.pop_back();

    DFS(start);
  }

  std::vector<std::vector<int>> ret(V + 1);
  for (int i{1}; i <= V; ++i) {
    ret[leaders[i]].push_back(i);
  }

  ret.erase(std::remove_if(ret.begin(), ret.end(), [](auto& list) { return list.empty(); }), ret.end());
  std::sort(ret.begin(), ret.end());

  return ret;
}

void kosaraju() {
  auto scc_stack = substep1();
  auto scc_list = substep2(scc_stack);

  auto println = [](const auto& list) {
    int size = static_cast<int>(list.size());
    for (int i{0}; i < size; ++i)
      std::cout << list[i] << ((i + 1 == size) ? " -1\n" : " ");
  };

  std::cout << scc_list.size() << '\n';
  for (auto sccs : scc_list) println(sccs);
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  std::cin >> V >> E;

  for (int i{0}; i < E; ++i) {
    int a, b;
    std::cin >> a >> b;
    adj[a][0].push_back(b);
    adj[b][1].push_back(a);
  }

  for (int i{1}; i <= V; ++i) {
    std::sort(adj[i][0].begin(), adj[i][0].end());
    std::sort(adj[i][1].begin(), adj[i][1].end());
  }

  kosaraju();
}