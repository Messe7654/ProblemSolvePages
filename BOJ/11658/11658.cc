#include <algorithm>
#include <iostream>
#include <vector>

class BIT {
 public:
  BIT(const std::pair<int, int>& dimension) {
    auto [row_dim, col_dim] = dimension;
    dimension_ = {GetMsb(row_dim) << 1, GetMsb(col_dim) << 1};
    T_.resize(dimension_.first, std::vector<int>(dimension_.second));
  }

  void Push(const std::pair<int, int>& pos, int value) {
    int origin = static_cast<int>(Query(pos, pos));
    int diff = value - origin;
    auto [row, col] = pos;
    for (int r{row}; r < dimension_.first; r += r & (~r + 1)) {
      for (int c{col}; c < dimension_.second; c += c & (~c + 1)) {
        T_[r][c] += diff;
      }
    }
  }

  long long Query(const std::pair<int, int>& left, const std::pair<int, int>& right) {
    long long ret{0};
    ret += Sum(right);
    ret -= Sum({left.first - 1, right.second});
    ret -= Sum({right.first, left.second - 1});
    ret += Sum({left.first - 1, left.second - 1});
    return ret;
  }

 private:
  /// @brief (1, 1), pos를 꼭짓점으로 하는 사각형 범위의 합을 구한다.
  long long Sum(const std::pair<int, int>& pos) {
    long long ret{0};
    auto [row, col] = pos;
    while (row > 0) {
      for (int c{col}; c > 0; c &= ~c | (c - 1)) {
        ret += T_[row][c];
      }
      row &= ~row | (row - 1);
    }
    return ret;
  }

  unsigned GetMsb(unsigned x) {
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return (x + 1) >> 1;
  }

  std::pair<int, int> dimension_;
  std::vector<std::vector<int>> T_;
};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M;
  std::cin >> N >> M;

  BIT bit({N, N});

  for (int row{1}; row <= N; ++row) {
    for (int col{1}; col <= N; ++col) {
      int number; std::cin >> number;
      bit.Push({row, col}, number);
    }
  }

  for (int i{0}; i < M; ++i) {
    int op; std::cin >> op;
    if (op == 0) {
      int x, y, c;
      std::cin >> x >> y >> c;
      bit.Push({x, y}, c);
    }
    else if (op == 1) {
      int x1, y1, x2, y2;
      std::cin >> x1 >> y1 >> x2 >> y2;
      std::cout << bit.Query({x1, y1}, {x2, y2}) << '\n';
    }
    // assert(false);
  }
}