#include <algorithm>
#include <iostream>
#include <vector>

#define debug(rem) if (local) std::cout << rem

#ifdef DEBUG
constexpr bool local = true;
#else
constexpr bool local = false;
#endif

std::vector<long long> timer = {0, 1, 2, 4, 6, 9};

void update(long long to) {
  long long N{5};
  while (((N + 1) / 2 + 1) * (N / 2 + 1) < to) {
    timer.push_back(((N + 1) / 2 + 1) * (N / 2 + 1));
    N++;
  }
  timer.push_back(((N + 1) / 2 + 1) * (N / 2 + 1));
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int T; std::cin >> T;
  std::vector<int> queries(T);
  int max{0};
  for (int i{0}; i < T; i++) {
    int a, b;
    std::cin >> a >> b;
    queries[i] = b - a;
    max = std::max(max, b - a);
  }

  update(max);
  debug("DEBUG> [");
  int size = static_cast<int>(timer.size());
  for (int i{1}; i < size; i++) {
    debug("") << timer[i] << ((i + 1 == size) ? "]\n" : ", ");
  }
  for (auto query : queries) {
    std::cout << std::distance(
                     timer.begin(),
                     std::lower_bound(timer.begin(), timer.end(), query))
              << '\n';
  }
}