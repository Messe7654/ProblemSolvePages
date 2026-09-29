#include <iostream>
#include <string>
#include <tuple>

std::string transform_string(const std::string& origin, int start, int end) {
  std::string ret = origin;
  while (start <= end) {
    std::swap(ret[start], ret[end]);
    ++start; --end;
  }
  return ret;
}

std::pair<int, int> solution(const std::string& origin, const std::string& change) {
  int N = static_cast<int>(origin.size());

  int left{0}, right{N - 1};
  while (left < N && origin[left] == change[left]) ++left;
  while (right >= 0 && origin[right] == change[right]) --right;
  while (left - 1 >= 0 && right + 1 < N && origin[left - 1] == change[right + 1]) {
    --left; ++right;
  }
  return {left, right};
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N;

  std::string origin, change;
  std::cin >> origin >> change;

  auto [start, end] = solution(origin, change);
  std::cout << start + 1 << ' ' << end + 1 << '\n';
}
