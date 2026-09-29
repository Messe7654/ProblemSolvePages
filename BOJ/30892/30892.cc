#include <algorithm>
#include <iostream>
#include <vector>
#include <list>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  long long N, K, T;
  std::cin >> N >> K >> T;
  std::vector<long long> raw(N);
  for (int i{0}; i < N; ++i) std::cin >> raw[i];
  std::sort(raw.begin(), raw.end(), std::greater<>());
  std::list<long long> A(raw.begin(), raw.end());

  auto cursor = A.begin();

  while (!A.empty() && K--) {
    while (cursor != A.end() && *cursor >= T) ++cursor;
    if (cursor == A.end()) break;
    T += *cursor; cursor = A.erase(cursor);
    if (cursor == A.end()) --cursor;
    while (cursor != A.begin() && *cursor < T) --cursor;    
  }
  std::cout << T << '\n';
}