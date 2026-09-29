#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N;
  std::vector<int> A(N);
  for (int& i : A) std::cin >> i;

  std::vector<int> B;
  B.reserve(N);

  B.push_back(A[0]);
  for (int i{1}; i < N; ++i) {
    if (A[i] > B.back()) B.push_back(A[i]);
    else {
      auto it = std::lower_bound(B.begin(), B.end(), A[i]);
      *it = A[i];
    }
  }

  std::cout << N - B.size() << '\n';
}