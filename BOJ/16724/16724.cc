#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <vector>
#include <unordered_set>

// R, U, L, D
int dr[4] = {0, -1, 0, 1};
int dc[4] = {1, 0, -1, 0};

int GetDirection(char di) {
  if (di == 'R') return 0;
  if (di == 'U') return 1;
  if (di == 'L') return 2;
  if (di == 'D') return 3;
  assert(false);
  return -1;
}

class DisjointSet {
 public:
  DisjointSet(std::size_t size = 1) : capacity(size) {
    parent.resize(capacity);
    std::generate(parent.begin(), parent.end(), [idx = (int)-1]() mutable { return ++idx; });
    rank.resize(capacity);
  }

  int Find(int idx) {
    return parent[idx] == idx ? idx : parent[idx] = Find(parent[idx]);
  }

  void Union(int a, int b) {
    a = Find(a); b = Find(b);
    if (rank[a] < rank[b]) parent[a] = b;
    else if (rank[a] > rank[b]) parent[b] = a;
    else { // rank[a] == rank[b]
      ++rank[b];
      parent[a] = b;
    }
  }
  
 private:
  std::size_t capacity;
  std::vector<int> parent;
  std::vector<int> rank;
};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M; std::cin >> N >> M;
  std::vector<std::vector<char>> board(N, std::vector<char>(M));
  for (int r{0}; r < N; ++r) {
    for (int c{0}; c < M; ++c) {
      std::cin >> board[r][c];
    }
  }

  auto flatten = [M](int row, int col) -> int {
    return row * M + col;
  };

  DisjointSet DS(N * M);

  std::function<void(int, int)> Walk;
  Walk = [&](int row, int col) -> void {
    int next_row = row + dr[GetDirection(board[row][col])];
    int next_col = col + dc[GetDirection(board[row][col])];

    if (0 <= next_row && next_row < N &&
        0 <= next_col && next_col < M &&
        DS.Find(flatten(next_row, next_col)) != DS.Find(flatten(row, col))) {
      DS.Union(flatten(next_row, next_col), flatten(row, col));
      Walk(next_row, next_col);
    }
  };

  for (int r{0}; r < N; ++r) {
    for (int c{0}; c < M; ++c) {
      if (DS.Find(flatten(r, c)) == flatten(r, c)) Walk(r, c);
    }
  }

  std::unordered_set<int> groups;

  for (int r{0}; r < N; ++r) {
    for (int c{0}; c < M; ++c) {
      auto now_idx = DS.Find(flatten(r, c));
      if (!groups.contains(now_idx)) groups.insert(now_idx);
    }
  }

  std::cout << groups.size();
}