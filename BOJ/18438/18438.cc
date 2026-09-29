#include <iostream>
#include <vector>

template <typename InputIt>
std::vector<int> AlgB(InputIt a_first, InputIt a_last, InputIt b_first, InputIt b_last) {
  auto a_size = std::distance(a_first, a_last);
  auto b_size = std::distance(b_first, b_last);

  auto rolled = std::vector(2, std::vector<int>(b_size + 1));
  int prev{0}, curr{1};

  for (int i{1}; i <= a_size; ++i) {
    std::swap(prev, curr);
    for (int j{1}; j <= b_size; ++j) {
      if (*(a_first + i - 1) == *(b_first + j - 1))
        rolled[curr][j] = rolled[prev][j - 1] + 1;
      else
        rolled[curr][j] = std::max(rolled[prev][j], rolled[curr][j - 1]);
    }
  }
  return rolled[curr];
}

template <typename InputIt>
std::string AlgC(InputIt a_first, InputIt a_last, InputIt b_first, InputIt b_last) {
  if (a_first == a_last || b_first == b_last) return "";
  if (a_first == std::prev(a_last)) {
    while (b_first != b_last) {
      if (*a_first == *b_first) return std::string(1, *a_first);
      ++b_first;
    }
    return "";
  }

  auto b_size = std::distance(b_first, b_last);
  auto a_mid = a_first + std::distance(a_first, a_last) / 2;
  auto L1 = AlgB(a_first, a_mid, b_first, b_last);
  auto L2 = AlgB(std::make_reverse_iterator(a_last),
                 std::make_reverse_iterator(a_mid),
                 std::make_reverse_iterator(b_last),
                 std::make_reverse_iterator(b_first));

  std::pair<int, int> max{-1, -1}; // {val, idx}
  for (int i{0}; i <= b_size; ++i) {
    if (max.first < L1[i] + L2[b_size - i]) {
      max = {L1[i] + L2[b_size - i], i};
    }
  }

  auto b_mid = b_first + max.second;
  return AlgC(a_first, a_mid, b_first, b_mid) + AlgC(a_mid, a_last, b_mid, b_last);
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  std::string S, V;
  std::cin >> S >> V;

  if (S.length() > V.length()) std::swap(S, V);
  auto LCS = AlgC(S.begin(), S.end(), V.begin(), V.end());
  std::cout << LCS.size() << '\n' << LCS << '\n';
}