#include "testlib.h"

#include <algorithm>

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);

  int N = rnd.next(1, 8);
  int K = rnd.next(1, 8);

  std::vector<int> a(N);
  std::generate(a.begin(), a.end(), []() { return rnd.next(0, 4); });

  println(N, K);
  println(a);
  
  for (int i{0}; i < K; ++i) {
    int B = rnd.next(1, N);
    auto b = rnd.distinct(B, N);
    println(B, b);
  }
}