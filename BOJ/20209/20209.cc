#include <cassert>
#include <iostream>
#include <tuple>
#include <vector>
#include <queue>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, K; std::cin >> N >> K;

  std::vector<int> cube_number(N);
  
  for (int i{0}; i < N; ++i) {
    std::cin >> cube_number[i];
  }

  std::vector<unsigned> switch_connection(K);
  
  for (int i{0}; i < K; ++i) {
    int B; std::cin >> B;
    unsigned connection{0U};
    for (int j{0}; j < B; ++j) {
      int b; std::cin >> b;
      connection |= (1 << --b);
    }
    switch_connection[i] = connection;
  }

  auto encode = [&](const std::vector<int>& state) -> unsigned {
    unsigned ret{0U};
    for (int i{0}, mul{1}; i < N; ++i, mul = mul * 5) {
      ret += state[i] * mul;
    }
    return ret;
  };

  auto decode = [](unsigned code, int element_idx) -> unsigned {
    for (; element_idx > 0; --element_idx) code /= 5U;
    return code % 5U;
  };

  auto update = [](unsigned code, int element_idx, int val) -> unsigned {
    unsigned temp{code};
    for (int i{0}; i < element_idx; ++i) temp /= 5U;
    temp = temp % 5U;
    for (int i{0}; i < element_idx; ++i) { temp *= 5U; val *= 5;}
    return code + val - temp;
  };

  auto BFS = [&]() {
    int size = 1;
    for (int i{0}; i < K; ++i) size *= 5;
    std::vector<bool> visited(size);
    visited[0] = true;
    std::queue<std::tuple<unsigned, unsigned, int>> queue;
    queue.push({0U, encode(cube_number), 0});

    while (queue.empty() != true) {
      auto [visit, state, count] = queue.front();
      queue.pop();

      auto state_check = [&](unsigned state) {
        auto first = decode(state, 0);
        for (int j{1}; j < N; ++j) if (first != decode(state, j)) return false;
        return true;
      };

      if (state_check(state)) return count;

      for (int i{0}; i < K; ++i) {
        auto ith_switch_count = decode(visit, i);
        if (ith_switch_count >= 4U) continue;
        unsigned next_state = state;
        unsigned next_visit = update(visit, i, ith_switch_count + 1);
        if (visited[next_visit] == true) continue;

        for (int j{0}; j < N; ++j) {
          if (~switch_connection[i] & (1U << j)) continue;
          auto jth_switch_display = decode(state, j);
          next_state = update(next_state, j, (jth_switch_display + (i + 1)) % 5U);
        }

        visited[next_visit] = true;
        queue.push({next_visit, next_state, count + 1});
      }
    }
    return -1;
  };

  std::cout << BFS();
}