#include <iostream>
#include <tuple>

constexpr long long kMod = 1'000'000'007LL;

std::tuple<long long, long long, long long> EXGCD(long long a, long long b) {
  if (b == 0) return {a, 1, 0};
  auto [g, x, y] = EXGCD(b, a % b);
  return {g, y, x - (a / b) * y};
}

long long ModInversion(long long num) {
  auto [g, x, y] = EXGCD(num, kMod);
  return (x % kMod + kMod) % kMod;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N;
  long long sum{0}, pow{0};

  for (int i{0}; i < N; ++i) {
    int A; std::cin >> A;
    sum = (sum + A) % kMod;
    pow = (pow + (A * A) % kMod) % kMod;
  }

  long long diff = ((sum * sum) % kMod - pow + kMod) % kMod;
  long long result = (diff * ModInversion(2)) % kMod;
  std::cout << result << '\n';
}