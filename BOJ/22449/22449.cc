#include <algorithm>
#include <iostream>
#include <vector>

template <typename InputIt>
std::vector<int> ZFunction(InputIt first, InputIt last) {
  int size = std::distance(first, last);
  if (size == 0) return {};

  std::vector<int> Z(size);
  int l{0}, r{0};
  for (int i{1}; i < size; ++i) {
    if (i <= r) Z[i] = std::min(r - i + 1, Z[i - l]);
    while (i + Z[i] < size && *(first + Z[i]) == *(first + i + Z[i])) ++Z[i];
    if (i + Z[i] - 1 > r) {
      l = i;
      r = i + Z[i] - 1;
    }
  }
  return Z;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  std::string S, V;
  std::cin >> S >> V;

  int N = static_cast<int>(S.size());
  int M = static_cast<int>(V.size());

  std::string concat = V + '$' + S;
  auto forward_z = ZFunction(concat.begin(), concat.end());

  std::reverse(S.begin(), S.end());
  std::reverse(V.begin(), V.end());
  std::string reverse_concat = V + '$' + S;
  auto reverse_z = ZFunction(reverse_concat.begin(), reverse_concat.end());

  int match{0};
  for (int i{0}; i <= N - M; ++i) {
    int pref = forward_z[i + M + 1];
    int suff = reverse_z[N - i + 1];
    if (pref + suff == M - 1) ++match;
  }
  std::cout << match << '\n';
}