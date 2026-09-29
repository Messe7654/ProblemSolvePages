#include <iostream>
#include <set>
#include <map>
#include <queue>

constexpr int kAlive  = 1;
constexpr int kDead   = 2;
constexpr int kMirror = 3;

std::map<int, std::set<std::pair<int, int>>> row_map, col_map;
std::map<std::pair<int, int>, int> board;

void print_dead(std::pair<int, int> pii) {
  std::cout << "{" << pii.first + 1 << ", " << pii.second + 1
            << "} 에 있던 거울냥이가 죽었습니다. X를 눌러 조의를 표해주세요.\n";
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N; // \le 200'000

  std::vector<std::pair<int, int>> queue(N);

  for (int i{0}; i < N; ++i) {
    int R, C;
    std::cin >> R >> C;
    --R; --C;
    row_map[R].insert({R, C});
    row_map[R + 1].insert({R + 1, C});
    col_map[C].insert({R, C});
    col_map[C].insert({R + 1, C});
    queue[i] = {R, C};
    board[{R, C}] = kAlive;
    board[{R + 1, C}] = kMirror;
  }

  for (const auto [R, C] : queue) {
    if (board[{R, C}] == kDead) continue;
    std::set<std::pair<int, int>>::iterator it;

    it = row_map[R].find({R, C});
    while (++it != row_map[R].end()) {
      if (board[*it] == kMirror) break;
      if (board[*it] == kAlive) { board[*it] = kDead; --N; }
    }

    it = row_map[R].find({R, C});
    while (it-- != row_map[R].begin()) {
      if (board[*it] == kMirror) break;
      if (board[*it] == kAlive) { board[*it] = kDead; --N; }
    }

    it = col_map[C].find({R, C});
    while (it-- != col_map[C].begin()) {
      if (board[*it] == kMirror) break;
      if (board[*it] == kAlive) { board[*it] = kDead; --N; }
    }
  }

  std::cout << N << '\n';
}