#include <iostream>
#include <vector>

unsigned next_perm(unsigned i) {
  unsigned t = i | (i - 1);
  return (t + 1) | ((~t & -~t) - 1) >> (__builtin_ctz(i) + 1);
}

int L1_norm(const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
  return std::abs(p1.first - p2.first) + std::abs(p1.second - p2.second);
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M; std::cin >> N >> M;
  std::vector<std::pair<int, int>> chicken_coords;
  std::vector<std::pair<int, int>> house_coords;

  for (int r{0}; r < N; ++r) {
    for (int c{0}; c < N; ++c) {
      int x; std::cin >> x;
      if (x == 1) house_coords.push_back({r, c});
      if (x == 2) chicken_coords.push_back({r, c});
    }
  }

  int chicken_coords_size = static_cast<int>(chicken_coords.size());
  auto ChickenDistance = [&](const std::pair<int, int>& house, unsigned state) {
    int min = 0x7FFFFFFF;
    for (int i{0}; i < chicken_coords_size; ++i) {
      if (state & (1U << i)) min = std::min(min, L1_norm(house, chicken_coords[i]));
    }
    return min;
  };

  unsigned mask = 0;
  for (int i{0}; i < M; ++i) mask |= 1U << i;
  int min{0x7FFFFFFF};
  while (mask < (1U << chicken_coords_size)) {
    int sum{0};
    for (const auto& house : house_coords) sum += ChickenDistance(house, mask);
    min = std::min(min, sum);
    mask = next_perm(mask);
  }

  std::cout << min;
}