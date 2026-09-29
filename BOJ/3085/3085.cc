#include <iostream>
#include <vector>

int Count(int N, const std::vector<std::vector<char>>& board) {
  int max{0};

  for (int r{0}; r < N; ++r) {
    int now{1}; char last{'e'};
    for (int c{0}; c < N; ++c) {
      if (last == board[r][c]) ++now;
      else {
        max = std::max(now, max);
        now = 1;
        last = board[r][c];
      }
    }
    max = std::max(now, max);
  }

  for (int c{0}; c < N; ++c) {
    int now{1}; char last{'e'};
    for (int r{0}; r < N; ++r) {
      if (last == board[r][c]) ++now;
      else {
        max = std::max(now, max);
        now = 1;
        last = board[r][c];
      }
    }
    max = std::max(now, max);
  }

  return max;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N;
  std::cin >> N;
  std::vector<std::vector<char>> board(N, std::vector<char>(N));
  
  for (int r{0}; r < N; ++r) {
    for (int c{0}; c < N; ++c) {
      std::cin >> board[r][c];
    }
  }

  int max{0};
  for (int r{0}; r < N; ++r) {
    for (int c{0}; c < N - 1; ++c) {
      if (board[r][c] == board[r][c + 1]) continue;
      std::swap(board[r][c], board[r][c + 1]);
      max = std::max(max, Count(N, board));
      std::swap(board[r][c], board[r][c + 1]);
    }
  }

  for (int c{0}; c < N; ++c) {
    for (int r{0}; r < N - 1; ++r) {
      if (board[r][c] == board[r + 1][c]) continue;
      std::swap(board[r + 1][c], board[r][c]);
      max = std::max(max, Count(N, board));
      std::swap(board[r + 1][c], board[r][c]);
    }
  }

  std::cout << max;
}