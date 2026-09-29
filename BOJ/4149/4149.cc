#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>

const std::vector<uint64_t> a_list{2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 23ULL, 29ULL, 31ULL, 37ULL, 41ULL};

namespace rnd {
  std::random_device rd;

  template<typename T>
  T next(T min, T max) {
    std::uniform_int_distribution<T> dist(min, max);
    return dist(rd);
  }

  template<typename T>
  T next(T n) {
    return next(static_cast<T>(0), n);
  }
}; // namespace rnd

// return (a * b) % m
uint64_t multiply(uint64_t a, uint64_t b, uint64_t m) {
  uint64_t ret{0};
  a = a % m;
  b = b % m;

  while (b) {
    if (b & 1ULL) ret = (ret + a) % m;
    b >>= 1;
    a = (a << 1) % m;
  }
  return ret;
}

// return (a ^ b) m
uint64_t pow(uint64_t a, uint64_t b, uint64_t m) {
  uint64_t ret = 1;
  a = a % m;
  while (b) {
    if (b & 1ULL) ret = multiply(ret, a, m);
    b >>= 1;
    a = multiply(a, a, m);
  }
  return ret;
}

uint64_t GCD(uint64_t a, uint64_t b) {
  if (a < b) std::swap(a, b);
  while (b > 0) {
    uint64_t r = a % b;
    a = b;
    b = r;
  }
  return a;
}

bool miller_rabin(uint64_t n) {
  if (n < 2) return false;
  if (n < 4) return true;
  if (n % 2 == 0) return false;

  uint64_t k = n - 1; // n - 1 = 2^m * d
  int m{0};
  uint64_t d = k;
  while (d % 2 == 0) {
    d >>= 1;
    ++m;
  }

  bool composite{true};

  for (const auto& a : a_list) {
    if (a > k) break;
    uint64_t x = pow(a, d, n);
    if (x == 1 || x == n - 1) continue;
    bool composite{true};
    for (int r{1}; r < m; ++r) {
      x = multiply(x, x, n);
      if (x == n - 1) {
        composite = false;
        break;
      }
    }
    if (composite) return false;
  }
  return true;
}

uint64_t pollad_rho(uint64_t n) {
  if (n % 2 == 0) return 2;

  // x : slow pointer, y : fast pointer
  uint64_t x = rnd::next((uint64_t)2, n - 1);
  uint64_t y = x;
  uint64_t c = rnd::next((uint64_t)1, n - 1);
  uint64_t d = 1;

  auto g = [&](uint64_t x) {
    return (multiply(x, x, n) + c) % n;
  };

  while (d == 1ULL) {
    x = g(x);
    y = g(g(y));
    d = GCD(std::abs(static_cast<int64_t>(x - y)), n);
    if (d == n) return 0;
  }

  return d;
}

std::vector<uint64_t> prime_factorization(uint64_t n) {
  std::vector<uint64_t> ret;

  for (uint64_t i{2}; i <= 1'000; ++i) {
    while (n % i == 0) { ret.push_back(i); n = n / i; }
  }

  while (n > 1) {
    if (miller_rabin(n)) {
      ret.push_back(n);
      break;
    }
    auto factor = pollad_rho(n);
    if (factor == 0ULL) {
      ret.push_back(n);
      break;
    }
    while (n % factor == 0ULL) {
      ret.push_back(factor);
      n = n / factor;
    }
  }

  std::sort(ret.begin(), ret.end());
  return ret;
}

int main() {
  uint64_t n; std::cin >> n;
  auto factors = prime_factorization(n);
  for (const auto& factor : factors) {
    std::cout << factor << '\n';
  }
}