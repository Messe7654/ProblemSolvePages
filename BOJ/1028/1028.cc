#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int R, C; std::cin >> R >> C;
  auto IsIn = [R, C](int row, int col) -> bool {
    return 0 <= row && row < R && 0 <= col && col < C;
  };

  std::vector<std::vector<char>> board(R, std::vector<char>(C));
  for (int row{0}; row < R; ++row) {
    for (int col{0}; col < C; ++col) {
      std::cin >> board[row][col];
    }
  }

  std::vector<std::vector<int>> DL(R, std::vector<int>(C));
  std::vector<std::vector<int>> DR(R, std::vector<int>(C));

  for (int l{0}; l < R + C - 1; ++l) {
    int row = std::clamp(l, 0, R - 1);
    int col = std::clamp(-R + 1 + l, 0, C - 1);
    while (IsIn(row, col)) {
      DL[row][col] = (board[row][col] == '1') ? (IsIn(row + 1, col - 1) ? DL[row + 1][col - 1] + 1 : 1) : 0;
      --row; ++col;
    }
  }

  for (int l{0}; l < R + C - 1; ++l) {
    int row = std::clamp(R + C - l - 2, 0, R - 1);
    int col = std::clamp(l, 0, C - 1);
    while (IsIn(row, col)) {
      DR[row][col] = (board[row][col] == '1') ? (IsIn(row + 1, col + 1) ? DR[row + 1][col + 1] + 1 : 1) : 0;
      --row; --col;
    }
  }

  for (int l{std::min(R, C) >> 1}; l >= 0; --l) {
    for (int cr{l}; cr + l < R; ++cr) {
      for (int cc{l}; cc + l < C; ++cc) {
        if (DL[cr - l][cc] > l && DR[cr - l][cc] > l && DL[cr][cc + l] > l && DR[cr][cc - l] > l) {
          std::cout << l + 1; exit(0);
        }
      }
    }
  }
  std::cout << 0;
}