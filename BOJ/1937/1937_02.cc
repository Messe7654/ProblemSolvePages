#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

constexpr int dr[4] = {1, 0, -1, 0};
constexpr int dc[4] = {0, 1, 0, -1};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N;

  std::vector<std::vector<int>> board(N + 2, std::vector<int>(N + 2));

  for (int row{1}; row <= N; ++row) {
    for (int col{1}; col <= N; ++col) {
      std::cin >> board[row][col];
    }
  }

  auto IsIn = [N](int row, int col) {
    return 1 <= row && row <= N && 1 <= col && col <= N;
  };

  std::function<int(int, int)> DFS1;
  std::function<int(int, int)> DFS2;
}
