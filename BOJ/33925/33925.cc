#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, J, S, H, K;
  std::cin >> N >> J >> S >> H >> K;

  std::vector<std::string> board(3);
  std::cin >> board[0] >> board[1] >> board[2];

  int need[] = {0, 0, 0};
  for (int i{1}; i < N - 1; ++i) {
    if (board[0][i] == 'v') ++need[2];
    if (board[2][i] == '^') ++need[board[1][i] == '^'];
  }

  if (J >= need[0] + (need[1] << 1)) J = 0;
  else if (J >= need[0]) J = need[1] - ((J - need[0]) / 2);
  else J = need[0] + need[1] - J;

  S = -std::min((S - need[2]), 0);
  
  if ((J + S) * K >= H) std::cout << "-1\n";
  else std::cout << H - (J + S) * K << '\n';
}