#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M;
  std::cin >> N >> M;

  std::vector<int> arr(N);
  for (int i{0}; i < N; ++i) std::cin >> arr[i];

  while (M > 0) {
    int lsb = (M & (~M + 1));
    std::vector<int> tmp(N);
    for (int i{0}; i < N; ++i) tmp[i] = arr[i] ^ arr[(i + lsb) % N];
    std::swap(tmp, arr);
    M &= ~lsb;
  }

  for (int i{0}; i < N; ++i) std::cout << arr[i] << '\n';
}