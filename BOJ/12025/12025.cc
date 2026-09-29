#include <algorithm>
#include <iostream>
#include <numeric>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  std::string password; unsigned long long k;
  std::cin >> password >> k;

  int cnt = std::accumulate(password.begin(), password.end(), 0,
     [](int T, const char& c){ return T + (c == '1' || c == '2' || c == '6' || c == '7'); });
  if ((1ULL << cnt) < k) { std::cout << -1; return 0; }
  --k;
  for (auto& c : password) {
    if (c == '1' || c == '6') c = ((1ULL << --cnt) & k) ? '6' : '1';
    if (c == '2' || c == '7') c = ((1ULL << --cnt) & k) ? '7' : '2';
  }
  std::cout << password;
}