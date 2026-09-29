#include <iostream>
#include <vector>

int main() {
  unsigned long long N, M; std::cin >> N >> M;
  unsigned long long sum{0}, min{1'000'000'000'001};
  std::vector<unsigned long long> A(N);
  std::vector<bool> can(N, true);
  for (int i{0}; i < N; ++i) {
    std::cin >> A[i];
    sum += A[i];
    min = std::min(min, A[i]);
  }


  while (M >= min) {
    M %= sum;
    for (int i{0}; i < N; ++i) {
      if (can[i] == true) {
        if (M >= A[i]) M -= A[i];
        else {
          can[i] = false;
          sum -= A[i];
        }
      }
    }
  }
  std::cout << M;
}