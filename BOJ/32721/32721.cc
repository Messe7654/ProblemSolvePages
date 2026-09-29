#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
#include <stack>

struct ReducedInfo {
  int original_size;
  int reduced_size;
  std::vector<int> SCC_id;        // SCC_id[vertex_id] : return group_id of vertex[vertex_id]
  std::vector<int> SCC_size;      // SCC_size[group_id] : return size of SCC[group_id]
  std::vector<int> SCC_indegree;  // SCC_indegree[group_id] : return indegree of SCC[group_id]
};

ReducedInfo GetSCC(const std::vector<int>& go) {
  int N = static_cast<int>(go.size());
  std::stack<int> stack;

  std::vector<int> discover(N);
  std::vector<int> low_link(N);
  std::vector<bool> visited(N);

  ReducedInfo ret;
  ret.original_size = N;
  ret.SCC_id.resize(N);

  std::function<void(int)> dfs;
  dfs = [&, cnt = (int)-1, group_id = (int)-1](int now) mutable -> void {
    visited[now] = true;
    discover[now] = ++cnt;
    low_link[now] = cnt;

    stack.push(now);

    const int& next = go[now];
    if (discover[next] == 0) {
      dfs(next);
      low_link[now] = std::min(low_link[now], low_link[next]);
    }
    else if (visited[next] == true) {
      low_link[now] = std::min(low_link[now], discover[next]);
    }

    if (low_link[now] == discover[now]) {
      ++group_id;
      ret.SCC_size.push_back(0);
      ret.SCC_indegree.push_back(0);

      std::vector<int> SCC;
      while (stack.empty() != true) {
        int top = stack.top(); stack.pop();

        SCC.emplace_back(top);
        visited[top] = false;
        ret.SCC_id[top] = group_id;
        if (now == top) {
          ret.SCC_size[group_id] = static_cast<int>(SCC.size());
          break;
        }
      }
      
      for (const auto& id : SCC) {
        if (ret.SCC_id[id] != ret.SCC_id[go[id]])
          ++ret.SCC_indegree[ret.SCC_id[go[id]]];
      }
    }
  };

  for (int i{0}; i < N; ++i) if (discover[i] == 0) dfs(i);
  ret.reduced_size = static_cast<int>(ret.SCC_size.size());
  return ret;
};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N;
  std::vector<int> go(N);

  for (int i{0}; i < N; ++i) {
    std::cin >> go[i];
    --go[i];
  }

  auto info = GetSCC(go);

  int ans{0};
  if (info.reduced_size == 1) ans = 0;
  else {
    for (int group_id{0}; group_id < info.reduced_size; ++group_id) {
      if (info.SCC_size[group_id] == 1) continue;
      ans += (info.SCC_indegree[group_id] == 0) ? 1 : info.SCC_indegree[group_id];
    }
  }

  std::cout << ans << '\n';
}