#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <tuple>

int ans{0};
std::string board[5];
bool visited[1U << 25];

int dr[4] = {0, 1, 0, -1};
int dc[4] = {1, 0, -1, 0};

inline unsigned Flatten(int row, int col) { return 5 * row + col; }
inline std::pair<int, int> Unflatten(int flatted) { return {flatted / 5, flatted % 5}; }
inline bool IsIn(int row, int col) { return 0 <= row && row < 5 && 0 <= col && col < 5; }

void BFS(int row, int col) {
  std::queue<std::tuple<int, int, unsigned, unsigned, int>> queue;
  queue.push({row, col, 1U << (Flatten(row, col)), 0U, board[row][col] == 'S'});
  visited[1U << (Flatten(row, col))] = true;

  while (queue.empty() != true) {
    auto [now_row, now_col, now_state, candidate, now_S_count] = queue.front();
    queue.pop();

    if (7 - __builtin_popcount(now_state) + now_S_count < 4) continue;
    if (__builtin_popcount(now_state) == 7) {
      if (now_S_count >= 4) ++ans;
      continue;
    }

    for (int i{0}; i < 4; ++i) {
      int next_row = now_row + dr[i];
      int next_col = now_col + dc[i];

      if (IsIn(next_row, next_col)) candidate |= 1U << Flatten(next_row, next_col);
    }

    unsigned copy = candidate;
    while (copy) {
      unsigned next = copy & -copy;
      auto [next_row, next_col] = Unflatten(__builtin_ctz(next));
      unsigned next_state = now_state | next;
      if (visited[next_state] != true) {
        visited[next_state] =  true;
        queue.push({next_row, next_col, next_state, candidate ^ next, now_S_count + (board[next_row][next_col] == 'S')});
      }
      copy ^= next;
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  std::cin >> board[0] >> board[1] >> board[2] >> board[3] >> board[4];

  for (int r{0}; r < 5; ++r)
    for (int c{0}; c < 5; ++c) 
      if (board[r][c] == 'S') BFS(r, c);

  std::cout << ans;
}