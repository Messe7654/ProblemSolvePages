#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include <random>

typedef std::pair<int, int> pii;

std::vector<pii> SMT(const std::vector<pii>& list) {
  std::vector<pii> G(list.begin(), list.end());
  std::sort(G.begin(), G.end(), [](const pii &l, const pii &r){ return l.first * r.second < l.second * r.first; });
  return std::move(G);
};

std::vector<pii> solution(const std::vector<pii>& list) {
  std::vector<pii> G(list.begin(), list.end());
  std::sort(G.begin(), G.end(), [](const pii &l, const pii &r){ return 1LL * l.first * r.second <= 1LL * l.second * r.first; });
  return std::move(G);
}

int main(int argc, char* argv[]) {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N = std::stoi(argv[1]);

  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<int> coord_dist(0, 1000);
  
  std::vector<pii> v(N);

  while (true) {
    for (int i{0}; i < N; ++i) {
      v[i] = {coord_dist(mt), coord_dist(mt)};
    }
    if (solution(v) != SMT(v)) break;
  }

  std::cout << N << '\n';
  for (int i{0}; i < N; ++i) {
    std::cout << v[i].first << ' ' << v[i].second << '\n';
  }
}