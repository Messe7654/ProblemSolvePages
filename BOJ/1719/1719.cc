#include <iostream>
#include <vector>

constexpr int INF = 987654321;

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int n, m; std::cin >> n >> m;
  std::vector<std::vector<int>> wgt(n, std::vector<int>(n, INF));
  std::vector<std::vector<int>> prv(n, std::vector<int>(n));
  
  for (int i{0}; i < n; ++i) wgt[i][i] = 0;

  for (int i{0}; i < m; ++i) {
    int a, b, w;
    std::cin >> a >> b >> w;
    --a; --b;
    wgt[a][b] = std::min(wgt[a][b], w);
    wgt[b][a] = std::min(wgt[b][a], w);
    prv[a][b] = a;
    prv[b][a] = b;
  }

  for (int mid{0}; mid < n; ++mid) {
    for (int src{0}; src < n; ++src) {
      for (int dst{0}; dst < n; ++dst) {
        if (src == dst) continue;
        if (wgt[src][mid] == INF || wgt[mid][dst] == INF) continue;
        if (wgt[src][dst] > wgt[src][mid] + wgt[mid][dst]) {
          wgt[src][dst] = wgt[src][mid] + wgt[mid][dst];
          prv[src][dst] = prv[mid][dst];
        }
      }
    }
  }

  for (int src{0}; src < n; ++src) {
    for (int dst{0}; dst < n; ++dst) {
      if (src == dst) std::cout << '-';
      else std::cout << prv[dst][src] + 1;
      std::cout << ((dst + 1 == n) ? '\n' : ' '); 
    }
  }
}