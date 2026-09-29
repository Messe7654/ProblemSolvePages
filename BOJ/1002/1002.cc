#include <iostream>
#include <tuple>
#include <utility>

int DistanceDouble(const std::pair<int, int>& a, const std::pair<int, int>& b) {
  int x_dist = b.first - a.first;
  int y_dist = b.second - a.second;
  return x_dist * x_dist + y_dist * y_dist;
}

int Solve(const std::tuple<int, int, int>& a, const std::tuple<int, int, int>& b) {
  if (a == b) return -1;
  const auto& [ax, ay, ar] = a;
  const auto& [bx, by, br] = b;
  auto distance = DistanceDouble({ax, ay}, {bx, by});
  auto cond1 = (ar - br) * (ar - br);
  auto cond2 = (ar + br) * (ar + br);
  if (distance < cond1) return 0;
  if (distance == cond1) return 1;
  if (distance < cond2) return 2;
  if (distance == cond2) return 1;
  return 0;  
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int T;
  std::cin >> T;

  for (int testcase{1}; testcase <= T; ++testcase) {
    int x1, y1, r1, x2, y2, r2;
    std::cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
    std::cout << Solve({x1, y1, r1}, {x2, y2, r2}) << '\n';
  }
}