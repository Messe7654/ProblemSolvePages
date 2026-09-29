#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::string A, B;
  std::cin >> A >> B;
  int N{static_cast<int>(A.size())}, M{static_cast<int>(B.size())};
  std::vector<std::vector<int>> ED(N + 1, std::vector<int>(M + 1));

  for (int a{1}; a <= N; ++a) {
    for (int b{1}; b <= M; ++b) {
      ED[a][b] = std::max({ED[a - 1][b], ED[a][b - 1], ED[a - 1][b - 1] + (A[a - 1] == B[b - 1])});
    }
  }

  std::cout << N + M - ED[N][M];
}