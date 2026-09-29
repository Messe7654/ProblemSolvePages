#include <cassert>
#include <cstdlib>
#include <iostream>
#include <tuple>

// A: r -> (r + 2) % 4, c -> c
// B: r -> r ^ 1, c -> c ^ 1
// C: r -> r ^ 3, c -> c ^ 1
constexpr int N = 4;
constexpr int M = 2;
constexpr int D[] = {1, 3, 0, 5, 2, 7, 4, 6};
inline int flatten(int row, int col) { return row * M + col; }
inline std::pair<int, int> unflatten(int index) { return {index / M, index % M}; }

int main() {
  int row, col;
  std::cin >> row >> col;
  --row; --col;
  
  int K; std::cin >> K;
  std::string ops;
  std::cin >> ops;
  for (const auto& c : ops) {
    switch (c) {
    case 'A':
      row = (row + 2) & 3;
      break;
    case 'B':
      row ^= 1;
      col ^= 1;
      break;
    case 'C':
      row ^= 3;
      col ^= 1;
      break;
    case 'D':
      std::tie(row, col) = unflatten(D[flatten(row, col)]);
      break;
    default:
      assert(false && "이외의 입력이 입력됐을지두");     
    }
  }

  std::cout << row + 1 << ' ' << col + 1 << '\n';
}