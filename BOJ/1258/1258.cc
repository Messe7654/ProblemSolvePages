#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
#include <list>
#include <queue>

class Graph {
 public:
  Graph(int size) : capacity(size) {
    map.resize(capacity, std::vector<std::list<int>::iterator>(capacity));
    adjacency_list.resize(capacity);
  }

  void InsertEdge(int a, int b) {
    if (map[a][b] != std::list<int>::iterator()) return;
    adjacency_list[a].push_back(b);
    map[a][b] = adjacency_list[a].end();
    map[a][b]--;
  }

  void EraseEdge(int a, int b) {
    if (map[a][b] == std::list<int>::iterator()) return;
    adjacency_list[a].erase(map[a][b]);
    map[a][b] = std::list<int>::iterator();
  }

  std::pair<std::vector<int>, bool> match() {
    std::vector<int> left(capacity, -1);
    std::vector<bool> visited(capacity);
    auto Clear = [&visited]() { std::fill(visited.begin(), visited.end(), false); };
    std::function<int(int)> DFS;
    DFS = [&](int now) -> int {
      visited[now] = true;
      for (auto next : adjacency_list[now]) {
        if (left[next] == -1 || visited[left[next]] != true && DFS(left[next])) {
          left[next] = now;
          return 1;
        }
      }
      return 0;
    };

    int cnt{0};
    for (int i{0}; i < capacity; ++i) {
      Clear();
      if (DFS(i)) ++cnt;
    }

    return {left, (cnt == capacity)};
  }

 private:
  int capacity;
  std::vector<std::vector<std::list<int>::iterator>> map;
  std::vector<std::list<int>> adjacency_list;
};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int n; std::cin >> n;
  Graph G(n);
  
  std::vector<std::vector<int>> cost(n, std::vector<int>(n));
  std::vector<int> row_potential(n), col_potential(n);

  for (int row{0}; row < n; ++row) {
    for (int col{0}; col < n; ++col) {
      std::cin >> cost[row][col];
    }
  }

  for (int row{0}; row < n; ++row) {
    int row_min = 0x7FFFFFFF;
    for (int col{0}; col < n; ++col) row_min = std::min(row_min, cost[row][col]);
    row_potential[row] += row_min;
    for (int col{0}; col < n; ++col) {
      cost[row][col] -= row_min;
      if (cost[row][col] == 0) G.InsertEdge(row, col);
    }
  }

  for (int col{0}; col < n; ++col) {
    int col_min = 0x7FFFFFFF;
    for (int row{0}; row < n; ++row) col_min = std::min(col_min, cost[row][col]);
    col_potential[col] += col_min;
    for (int row{0}; row < n; ++row) {
      cost[row][col] -= col_min;
      if (cost[row][col] == 0) G.InsertEdge(row, col);
    }
  }

  while (true) {
    auto [left, is_matched] = G.match();
    if (is_matched) {
      int ans{0};
      for (int i{0}; i < n; ++i)
        ans += row_potential[i] + col_potential[i];
      std::cout << ans;
      break;
    }

    int min = 0x7FFFFFFF;
    for (int col{0}; col < n; ++col) {
      if (left[col] != -1) continue;
      for (int row{0}; row < n; ++row) {
        if (cost[row][col] != 0) min = std::min(min, cost[row][col]);
      }
    }

    std::vector<int> row_addition(n);
    for (int col{0}; col < n; ++col) {
      if (left[col] != -1) continue;
      col_potential[col] += min;
      for (int row{0}; row < n; ++row) {
        if (cost[row][col] == 0) G.EraseEdge(row, col);
        cost[row][col] -= min;
        if (cost[row][col] == 0) G.InsertEdge(row, col);
        else if (cost[row][col] < 0) row_addition[row] = std::max(row_addition[row], -cost[row][col]);
      }
    }

    for (int row{0}; row < n; ++row) {
      if (row_addition[row] == 0) continue;
      row_potential[row] -= row_addition[row];
      for (int col{0}; col < n; ++col) {
        if (cost[row][col] == 0) G.EraseEdge(row, col);
        cost[row][col] += row_addition[row];
        if (cost[row][col] == 0) G.InsertEdge(row, col);
      }
    }
  }
}