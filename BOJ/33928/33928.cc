#include <functional>
#include <iostream>
#include <vector>

constexpr int dr[] = {-2, -2, -1, -1,  1,  1,  2,  2};
constexpr int dc[] = {-1,  1, -2,  2, -2,  2, -1,  1};
constexpr int kInf = 0x7FFFFFFF;

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N;
  if (N <= 4) {
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
    exit(0);
  }
  auto A = std::vector(N, std::vector<int>(N));

  auto flatten = [N](int row, int col) -> int {
    return row * N + col;
  };

  auto unflatten = [N](int index) -> std::pair<int, int> {
    return {index / N, index % N};
  };

  for (int row{0}; row < N; ++row) {
    for (int col{0}; col < N; ++col) {
      std::cin >> A[row][col];
    }
  }

  std::vector<std::size_t> pos(N * N);
  std::vector<int> L, R;

  for (int row{0}; row < N; ++row) {
    for (int col{0}; col < N; ++col) {
      auto curr = flatten(row, col);
      if ((row + col) & 1) { pos[curr] = L.size(); L.push_back(curr); }
      else                 { pos[curr] = R.size(); R.push_back(curr); }
    }
  }

  auto K = std::max(L.size(), R.size());
  std::vector<std::unordered_map<int, int>> cost(K);

  for (std::size_t li{0}; li < L.size(); ++li) {
    const auto [row, col] = unflatten(L[li]);
    for (int i{0}; i < 8; ++i) {
      int next_row = row + dr[i];
      int next_col = col + dc[i];

      if (!(0 <= next_row && next_row < N && 0 <= next_col && next_col < N)) continue;
      auto ri = pos[flatten(next_row, next_col)];
      
      cost[li][ri] = -A[next_row][next_col];
    }
  }

  auto hungarian = [&]() -> int {
    std::vector<int> U(K + 1), V(K + 1), left(K + 1), prev(K + 1);
    // prev: path track
    for (auto i{1}; i <= K; ++i) {
      left[0] = i;
      std::vector<int> min(K + 1, kInf);
      std::vector<bool> used(K + 1);

      int j0{0};

      do {
        used[j0] = true;
        int i0 = left[j0];
        int delta = kInf;
        int j1 = -1;

        for (int j{1}; j <= K; ++j) {
          if (!used[j]) {
            int curr = cost[i0 - 1][j - 1] - U[i0] - V[j];
            if (curr < min[j]) {
              min[j] = curr;
              prev[j] = j0;
            }
            if (min[j] < delta) {
              delta = min[j];
              j1 = j;
            }
          }
        }
        for (int j{0}; j <= K; ++j) {
          if (used[j]) {
            U[left[j]] += delta;
            V[j] -= delta;
          }
          else min[j] -= delta;
        }

        j0 = j1;
      } while (left[j0] != 0);

      do {
        int j1 = prev[j0];
        left[j0] = left[j1];
        j0 = j1;
      } while (j0);
    }

    return -V[0];
  };

  std::cout << -hungarian() << '\n';
}