#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

constexpr int dr[] = {0, 1, 0, -1};
constexpr int dc[] = {1, 0, -1, 0};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M, K;
  std::cin >> N >> M >> K;

  std::vector<std::string> board(N);
  auto visited = std::vector(N, std::vector<int>(M, 0x7FFFFFFF));

  for (auto& s : board) std::cin >> s;

  int x1, y1, x2, y2;
  std::cin >> x1 >> y1 >> x2 >> y2;
  --x1; --y1; --x2; --y2;

  std::queue<std::tuple<int, int, int>> queue;
  visited[x1][y1] = 0;
  queue.push({x1, y1, 0});

  int ans{-1};

  while (queue.empty() != true) {
    auto [curr_row, curr_col, dist] = queue.front(); queue.pop();

    if (curr_row == x2 && curr_col == y2) { ans = dist; break; }

    for (int d{0}; d < 4; ++d) {
      for (int i{1}; i <= K; ++i) {
        int next_row = curr_row + dr[d] * i;
        int next_col = curr_col + dc[d] * i;
        if (next_row < 0 || N <= next_row || next_col < 0 || M <= next_col) continue;
        if (visited[next_row][next_col] < dist + 1 || board[next_row][next_col] == '#') break;
        if (visited[next_row][next_col] > dist + 1) {
          visited[next_row][next_col] = dist + 1;
          queue.push({next_row, next_col, dist + 1});
        }
      }
    }
  }

  std::cout << ans << '\n';
}