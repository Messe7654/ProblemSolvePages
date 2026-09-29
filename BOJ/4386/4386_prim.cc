#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

struct vertex {
  double x;
  double y;
  int id;
};

struct edge {
  int dst;
  double distance;
};

double GetDistance(const vertex& src, const vertex& dst)  {
  return std::sqrt(
    (src.x - dst.x) * (src.x - dst.x) + (src.y - dst.y) * (src.y - dst.y)
  );
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N;
  std::vector<vertex> star(N);
  std::vector<bool> tree(N);

  for (int i{0}; i < N; ++i) {
    std::cin >> star[i].x >> star[i].y;
    star[i].id = i;
  }

  
  auto comp = [](const edge& lhs, const edge& rhs) {
    return lhs.distance > rhs.distance;
  };
  std::priority_queue<edge, std::vector<edge>, decltype(comp)> pq(comp);
  
  double ans{0};
  pq.push({0, 0});
  int count{1};
  
  while (pq.empty() != true && count < N) {
    auto [now, now_distance] = pq.top(); pq.pop();
    if (tree[now] == true) continue;
    tree[now] = true;
    ans += now_distance;

    for (int next{0}; next < N; ++next) {
      if (tree[next] == true) continue;
      double next_distance = GetDistance(star[now], star[next]);
      pq.push({next, next_distance});
    }
  }

  std::cout << ans;
}