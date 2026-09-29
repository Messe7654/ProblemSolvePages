#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>
#include <string>

constexpr int dr[4] = {-1, 0, 1, 0};
constexpr int dc[4] = {0, 1, 0, -1};

int BFS(const std::vector<std::vector<int>>& board, std::pair<int, int> start, std::pair<int, int> end) {
  int N = static_cast<int>(board.size());
  int M = static_cast<int>(board[0].size());

  auto IsIn = [N, M](int r, int c) {
    return 0 <= r && r < N && 0 <= c && c < M;
  };

  std::vector<std::vector<bool>> visited(N, std::vector<bool>(M));
  std::queue<std::tuple<int, int, int>> queue; // {{coord}, dist}
  queue.emplace(start.first, start.second, 0);
  visited[start.first][start.second] = true;

  while (queue.empty() != true) {
    auto [row, col, dist] = queue.front(); queue.pop();
    if (row == end.first && col == end.second) return dist;
    for (int i{0}; i < 4; ++i) {
      int next_row = row + dr[i];
      int next_col = col + dc[i];
      if (IsIn(next_row, next_col) == true &&
          board[next_row][next_col] != 1 &&
          visited[next_row][next_col] != true) {
        visited[next_row][next_col] = true;
        queue.emplace(next_row, next_col, dist + 1);
      }
    }
  }
  return 0x7FFFFFFF;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M, T;
  std::cin >> N >> M >> T;

  std::vector<std::vector<int>> board(N, std::vector<int>(M));
  std::pair<int, int> gram_coord{-1, -1};
  for (int r{0}; r < N; ++r) {
    for (int c{0}; c < M; ++c) {
      std::cin >> board[r][c];
      if (board[r][c] == 2) gram_coord = {r, c};
    }
  }

  assert(gram_coord.first != -1 && gram_coord.second != -1);

  auto YtoP = BFS(board, {0, 0}, {N - 1, M - 1});
  auto YtoG = BFS(board, {0, 0}, gram_coord);
  auto GtoP = std::abs(N - gram_coord.first - 1) + std::abs(M - gram_coord.second - 1);

  int min = 0x7FFFFFFF;
  if (YtoP != 0x7FFFFFFF) min = std::min(min, YtoP);
  if (YtoG != 0x7FFFFFFF) min = std::min(min, YtoG + GtoP);
  if (min > T) std::cout << "Fail";
  else std::cout << min;
}