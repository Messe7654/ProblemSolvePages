#include <iostream>
#include <vector>
#include <set>

int fibbo[33] = {0, 1, };
int g[3'000'001] = {0, 1, 2, 3, };

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  for (int i{2}; i < 33; ++i) {
    fibbo[i] = fibbo[i - 1] + fibbo[i - 2];
  }


  int N;
  std::cin >> N;

  std::vector<int> inputs(N);
  int max{0};
  for (int i{0}; i < N; ++i) {
    std::cin >> inputs[i];
    max = std::max(max, inputs[i]);
  }
  
  // for (int i{4}; i <= 3'000'000; ++i) {
  for (int i{4}; i <= max; ++i) {
    std::vector<bool> checker(16);
    for (int j{1}; j < 33 && fibbo[j] <= i; ++j) {
      checker[g[i - fibbo[j]]] = true;
    }
    int k{0};
    while (checker[k] != 0) ++k;
    g[i] = k;
  }
  int r{0};
  for (auto input : inputs) {
    r ^= g[input];
  }
  std::cout << ((r) ? "koosaga" : "cubelover");
}