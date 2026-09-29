#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int N, M;
  std::cin >> N >> M;

  // DP[u, 0] := u가 dominient set에 속함
  // DP[u, 1] := u는 dominient set에 속하지 않지만, u의 자식중 하나가 속함
  // DP[u, 2] := u는 dominient set에 속하지 않지만, u의 부모 노드가 속함
  std::vector<std::array<int, 3>> DP(N);
  std::vector<std::vector<int>> adj(N);
  std::vector<bool> visited(N);

  for (int i{0}; i < M; ++i) {
    int a, b;
    std::cin >> a >> b;
    --a; --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  auto MDS = [&](auto&& self, int prev, int curr) -> void {
    visited[curr] = true;

    if (adj[curr].empty()) {
      DP[curr] = {1, 0x7FFFFFFF, 0};
      return;
    }

    for (int next : adj[curr]) if (visited[next] == false) self(self, curr, next);
    
    DP[curr][0] = 1;
    for (int next : adj[curr]) {
      if (prev == next) continue;
      DP[curr][0] += std::min({DP[next][0], DP[next][1], DP[next][2]});
    }

    bool use_extra = true;
    int min_extra = 0x7FFFFFFF;
    for (int next : adj[curr]) {
      if (prev == next) continue;
      const int d0 = DP[next][0];
      const int d1 = DP[next][1];

      if (d0 <= d1) {
        DP[curr][1] += d0;
        use_extra = false;
      }
      else {
        DP[curr][1] += d1;
        min_extra = std::min(min_extra, d0 - d1);
      }
    }
    if (use_extra) DP[curr][1] += min_extra; 

    for (int next : adj[curr]) {
      if (prev == next) continue;
      DP[curr][2] += std::min(DP[next][0], DP[next][1]);
    }
  };

  int ans{0};
  for (int i{0}; i < N; ++i) {
    if (visited[i] == false) {
      MDS(MDS, -1, i);
      ans += std::min({DP[i][0], DP[i][1]});
    }
  }
  std::cout << ans << '\n';
}