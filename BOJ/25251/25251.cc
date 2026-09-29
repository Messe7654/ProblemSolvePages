#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int H, W; std::cin >> H >> W;
  std::vector<std::string> grid(H);
  std::vector<std::vector<bool>> visit(H, std::vector<bool>(W));
  for (auto& s : grid) std::cin >> s;
  
  int K{0};
  for (int row{0}; row < H; ++row) {
    for (int col{0}; col < W; ++col) {
      if (grid[row][col] == 'C') ++K;
    }
  }

  auto hire = [&]() -> void {
    int rightmost{0};
    for (int row{0}; row < H; ++row) {
      for (int col{rightmost}; col < W; ++col) {
        if (visit[row][col] == true) break;
        visit[row][col] == true;
        if (grid[row][col] == 'C') {
          rightmost = col;
          --K;
        }
      }
    }
  };

  int ans{0};
  while (K > 0) {
    ++ans;
    hire();
  }

  std::cout << ans;
}