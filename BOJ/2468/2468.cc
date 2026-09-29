#include <iostream>
#include <vector>
#include <queue>

int dr[4] = {1, 0, -1, 0};
int dc[4] = {0, 1, 0, -1};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N;
  std::cin >> N;

  std::vector<std::vector<int>> board(N, std::vector<int>(N));
  int max_height{0};
  for (int row{0}; row < N; ++row) {
    for (int col{0}; col < N; ++col) {
      std::cin >> board[row][col];
      max_height = std::max(max_height, board[row][col]);
    }
  }

  auto Count = [&](int H) -> int {
    std::vector<std::vector<bool>> visited(N, std::vector<bool>(N));
    int ret{0};
    auto BFS = [&](std::pair<int, int> start) {
      std::queue<std::pair<int, int>> queue;
      queue.push(start);
      visited[start.first][start.second] = true;

      while (queue.empty() != true) {
        auto [now_row, now_col] = queue.front();
        queue.pop();

        for (int i{0}; i < 4; ++i) {
          int next_row = now_row + dr[i];
          int next_col = now_col + dc[i];

          if (next_row < 0 || next_row >= N || next_col < 0 || next_col >= N) continue;
          if (visited[next_row][next_col] == true) continue;
          if (board[next_row][next_col] <= H) continue;

          queue.push({next_row, next_col});
          visited[next_row][next_col] = true;
        }
      }
    };

    for (int row{0}; row < N; ++row) {
      for (int col{0}; col < N; ++col) {
        if (visited[row][col] == true || board[row][col] <= H) continue;
        ++ret;
        BFS({row, col});
      }
    }
    return ret;
  };

  int ans{0};
  for (int H{1}; H < max_height; ++H) {
    ans = std::max(ans, Count(H));
  }
  std::cout << ans;
}