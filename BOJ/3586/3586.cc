/// [BOJ-3586] 방정식
/// acmpicpc.net/problem/3586
#include <iostream>
#include <stack>

class frac {
 public:
  frac(int n, int d = 1) : n(n), d(d) {
    int G = gcd(n, d);
    n /= G; d /= G;
  }

  frac operator*(const frac& f) const {
    return frac(n * f.n, d * f.d);
  }
  frac operator+(const frac& f) {
    return frac(f.d * n + d * f.n, d * f.d);
  }
  frac operator-(const frac& f) {
    return frac(f.d * n - d * f.n, d * f.d);
  }
  frac operator/(const frac& f) {
    return frac(n * f.d, d * f.n);
  }

  inline int get_n() { return n; }
  inline int get_d() { return d; }

 private:
  int gcd(int a, int b) {
    if (a < b) std::swap(a, b);
    while (b != 0) {
      int r = a % b;
      a = b;
      b = r;
    }
    return a;
  }

  int d;
  int n;
};

struct view {
  frac F;
  bool X;
};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  
}