#include <functional>
#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

constexpr int dr[4]{0, 1, 0, -1};
constexpr int dc[4]{1, 0, -1, 0};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M; std::cin >> M >> N;
  std::vector<std::vector<char>> board(N + 1, std::vector<char>(M + 1));
  std::vector<std::vector<int>> DP(N + 1, std::vector<int>(M + 1, 10'001));
  DP[1][1] = 0;

  for (int i{1}; i <= N; ++i)
    for (int j{1}; j <= M; ++j)
      std::cin >> board[i][j];

  std::queue<std::tuple<int, int, int>> queue;
  queue.push({1, 1, 0});

  auto IsIn = [&](int row, int col) -> bool {
    return 1 <= row && row <= N && 1 <= col && col <= M;
  };

  while (queue.empty() != true) {
    auto [now_row, now_col, now_cnt] = queue.front();
    queue.pop();

    if (now_cnt > DP[now_row][now_col]) continue;

    for (int i{0}; i < 4; ++i) {
      int next_row = now_row + dr[i];
      int next_col = now_col + dc[i];

      if (IsIn(next_row, next_col) != true) continue;
      int next_cnt = now_cnt + (board[next_row][next_col] == '1');
      if (next_cnt < DP[next_row][next_col]) {
        DP[next_row][next_col] = next_cnt;
        queue.push({next_row, next_col, next_cnt});
      }
    }
  }

  std::cout << DP[N][M];
}