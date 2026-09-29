#include <bits/stdc++.h>

#include "testlib.h"

constexpr std::pair<int, int> n_dist = {1, 500'000};
constexpr std::pair<int, int> m_dist = {1, 500'000};

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);

  int n = rnd.next(n_dist.first, n_dist.second);
  int m = rnd.next(m_dist.first, m_dist.second);
  int w = rnd.next(-10, 10);

  println(n, m, w);
}