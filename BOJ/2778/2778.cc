#include <iostream>
#include <tuple>

int GCD(int a, int b) {
  if (a < b) return GCD(b, a);
  return b ? a : GCD(b, a % b);
}

// ax + by + c = 0
struct line {
  int a;
  int b;
  int c;

  friend std::istream& operator>>(std::istream& IN, line& o) {
    IN >> o.a >> o.b >> o.c;
    return IN;
  }

  friend bool IsParallel(const line& l1, const line& l2) {
    return (1LL * l1.a * l2.b - 1LL * l1.b * l2.a)
  }
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int T; std::cin >> T;
  for (int testcase{1}; testcase <= T; ++testcase) {
    
  }
}