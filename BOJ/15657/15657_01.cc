#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);
 
  int N, M;
  std::cin >> N >> M;
  std::vector<int> pool(N);
  for (int& i : pool) std::cin >> i;
  std::sort(pool.begin(), pool.end());

  std::vector<int> indices(M);

  do {
    for (int i{0}; i < M; ++i) std::cout << pool[indices[i]] << ' ';
    std::cout << '\n';

    auto it = std::find_if(indices.rbegin(), indices.rend(), [N](const int& i) { return i != N - 1; });
    if (it == indices.rend()) break;
    (*it)++;
    std::fill(indices.rbegin(), it, *it);
  } while (true);
}