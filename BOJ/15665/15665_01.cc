#include <algorithm>
#include <iostream>
#include <vector>

template <typename FIt>
void println(FIt first, FIt last) {
  while (first != last) {
    std::cout << *first++ << ' ';
  }
  std::cout << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M;
  std::cin >> N >> M;
  std::vector<int> pool(N);
  for (int& i : pool) std::cin >> i;
  std::sort(pool.begin(), pool.end());

  std::vector<int> indices(M);
  std::vector<std::vector<int>> res;
  do {
    std::vector<int> now(M);
    for (int i{0}; i < M; ++i) now[i] = pool[indices[i]];
    res.push_back(now);

    auto it = std::find_if(indices.rbegin(), indices.rend(), [N](const int& i) { return i != N - 1; });
    if (it == indices.rend()) break;
    (*it)++;
    std::fill(indices.rbegin(), it, 0);
  } while (true);

  std::sort(res.begin(), res.end());
  res.erase(std::unique(res.begin(), res.end()), res.end());

  for (const auto& v : res) {
    println(v.begin(), v.end());
  }
}