#include <iostream>

int board[1001][1001][3];

void query(int a, int b, int c, int d) {
  for (int i{0}; i < 3; ++i) {
    std::cout << board[c][d][i] - board[a - 1][d][i] -
                 board[c][b -1][i] + board[a - 1][b - 1][i]
              << ((i + 1 == 3) ? "\n" : " ");
  }
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M, K;
  std::cin >> N >> M >> K;
  int map[26];
  map['J' - 'A'] = 0;
  map['O' - 'A'] = 1;
  map['I' - 'A'] = 2;

  for (int r{1}; r <= N; ++r) {
    std::string line;
    std::cin >> line;
    for (int c{1}; c <= M; ++c) {
      char input = line[c - 1];
      ++board[r][c][map[input - 'A']];
    }
  }

  for (int r{1}; r <= N; ++r) {
    for (int c{2}; c <= M; ++c) {
      board[r][c][0] += board[r][c - 1][0];
      board[r][c][1] += board[r][c - 1][1];
      board[r][c][2] += board[r][c - 1][2];
    }
  }

  for (int c{1}; c <= M; ++c) {
    for (int r{2}; r <= N; ++r) {
      board[r][c][0] += board[r - 1][c][0];
      board[r][c][1] += board[r - 1][c][1];
      board[r][c][2] += board[r - 1][c][2];
    }
  }

  for (int i{0}; i < K; ++i) {
    int a, b, c, d;
    std::cin >> a >> b >> c >> d;
    query(a, b, c, d);
  }
}