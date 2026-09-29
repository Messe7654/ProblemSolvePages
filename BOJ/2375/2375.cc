#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <tuple>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int n;
  std::cin >> n;

  std::vector<std::tuple<int, int, int>> countries(n);
  for (auto& [x, y, p] : countries) {
    std::cin >> x >> y >> p;
  }

  std::sort(countries.begin(), countries.end(),
    [](auto& lhs, auto& rhs) { return std::get<1>(lhs) < std::get<1>(rhs); });
  std::pair<int, int> pos;
  std::vector<int> sum(n + 1);
  for (int i{1}; i <= n; ++i) {
    sum[i] = sum[i - 1] + std::get<1>(countries[i]) * std::get<2>(countries[i]);
  }

  int left{0}, right{n};
  while (left < right) {
    int mid = (left + right) / 2;
    if (sum[n] >= sum[mid] * 2 && sum[n] < sum[mid + 1] * 2) {
      pos.first = mid;
      break;
    }
    if (sum[n] >= sum[mid] * 2) left = mid + 1;
    else right = mid - 1;
  }
  std::cout << std::get<1>(countries[pos.first]) << std::get<1>(countries[pos.first + 1]) << '\n';
}