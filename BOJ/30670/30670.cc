#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using coord_list = std::unordered_map<int, std::vector<int>>;

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int n, m; std::cin >> n >> m;
  std::vector<std::vector<int>> board(n + 1, std::vector<int>(m + 1));
  coord_list row_list, col_list;
  long long sum{0};
  for (int row{1}; row <= n; ++row) {
    for (int col{1}; col <= m; ++col) {
      std::cin >> board[row][col];
      const auto& color = board[row][col];
      row_list[color].push_back(row);
      col_list[color].push_back(col);
    }
  }

  auto GetTotalDistance = [](const auto& list) -> long long {
    long long ret{0};

    for (const auto& [k, v] : list) {
      auto sorted = v;
      std::sort(sorted.begin(), sorted.end(), std::greater<>());

      int n = static_cast<int>(sorted.size());
      for (int i{0}; i < n; ++i) {
        ret += 1LL * (n - 2 * (i + 1) + 1) * sorted[i];
      }
    }

    return ret;
  };

  sum += GetTotalDistance(row_list);
  sum += GetTotalDistance(col_list);

  std::cout << sum;
}