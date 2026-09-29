#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

constexpr int dr[4] = {1, 0, -1, 0};
constexpr int dc[4] = {0, 1, 0, -1};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N;

  std::vector<std::vector<int>> board(N + 2, std::vector<int>(N + 2));

  for (int row{1}; row <= N; ++row) {
    for (int col{1}; col <= N; ++col) {
      std::cin >> board[row][col];
    }
  }

  auto IsIn = [N](int row, int col) {
    return 1 <= row && row <= N && 1 <= col && col <= N;
  };

  auto flatten = [N](int row, int col) -> int {
    --row; --col;
    return N * row + col;
  };


  std::vector<std::vector<int>> adjacecny_list(N * N);
  std::vector<int> indegree(N * N);

  for (int row{1}; row <= N; ++row) {
    for (int col{1}; col <= N; ++col) {
      for (int d{0}; d < 4; ++d) {
        int next_row{row + dr[d]}, next_col{col + dc[d]};
        if (IsIn(next_row, next_col) && board[row][col] < board[next_row][next_col]) {
          adjacecny_list[flatten(row, col)].push_back(flatten(next_row, next_col));
          ++indegree[flatten(next_row, next_col)];
        }
      }
    }
  }

  std::queue<int> queue;
  std::vector<int> maximal_length(N * N);

  for (int row{1}; row <= N; ++row) {
    for (int col{1}; col <= N; ++col) {
      if (indegree[flatten(row, col)] == 0) {
        queue.push(flatten(row, col));
        maximal_length[flatten(row, col)] = 1;
      }
    }
  }

  while (queue.empty() != true) {
    auto now = queue.front();
    queue.pop();

    for (const auto& next : adjacecny_list[now]) {
      if (--indegree[next] == 0) queue.push(next);
      maximal_length[next] = std::max(maximal_length[next], maximal_length[now] + 1);
    }
  }

  std::cout << *std::max_element(maximal_length.begin(), maximal_length.end());
}
