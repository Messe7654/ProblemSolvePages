#include <functional>
#include <iostream>
#include <vector>

constexpr int dr[] = {-2, -2, -1, -1,  1,  1,  2,  2};
constexpr int dc[] = {-1,  1, -2,  2, -2,  2, -1,  1};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N;
  auto A = std::vector(N, std::vector<int>(N));
  auto board = std::vector(N, std::vector<bool>(N));

  for (int row{0}; row < N; ++row) {
    for (int col{0}; col < N; ++col) {
      std::cin >> A[row][col];
    }
  }

  int max{0};
  std::function<void(int, int, int)> backtrack;
  backtrack = [&](int row, int col, int score) -> void {
    if (row == N) {
      max = std::max(max, score);
      return;
    }

    int next_row = row + (col + 1 == N);
    int next_col = (col + 1) % N;

    auto is_safe = [&](int row, int col) -> bool {
      for (int i{0}; i < 8; ++i) {
        int next_row = row + dr[i];
        int next_col = col + dc[i];
        if ((0 <= next_row && next_row < N && 0 <= next_col && next_col < N) &&
            board[next_row][next_col] == true) return false;
      }
      return true;
    };

    if (is_safe(row, col)) {
      board[row][col] = true;
      backtrack(next_row, next_col, A[row][col] + score);
      board[row][col] = false;
    }
    backtrack(next_row, next_col, score);
  };

  backtrack(0, 0, 0);
  std::cout << max << '\n';
}