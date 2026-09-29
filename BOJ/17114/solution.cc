#include <array>
#include <iostream>
#include <vector>
#include <queue>

constexpr int kMaxDimension = 11;
using hypher_dimension = std::array<int, kMaxDimension>;

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  hypher_dimension bounds;
  hypher_dimension acc_mul; acc_mul[0] = 1;

  for (int i{0}; i < kMaxDimension; ++i) std::cin >> bounds[i];
  for (int i{1}; i < kMaxDimension; ++i) acc_mul[i] = acc_mul[i - 1] * bounds[i - 1];

  auto IsIn = [bounds](hypher_dimension curr) -> bool {
    for (int i{0}; i < kMaxDimension; ++i) {
      if (!(0 <= curr[i] && curr[i] < bounds[i])) return false;
    }
    return true;
  };

  auto Flatten = [acc_mul](hypher_dimension curr) -> int {
    int ret{0};
    for (int i{0}; i < kMaxDimension; ++i) ret += curr[i] * acc_mul[i];
    return ret;
  };

  auto Unflatten = [bounds](int idx) -> hypher_dimension {
    hypher_dimension ret;
    for (int i{0}; i < kMaxDimension; ++i) {
      ret[i] = idx % bounds[i];
      idx /= bounds[i];
    }
    return ret;
  };

  std::queue<hypher_dimension> queue;
  int max_size = acc_mul[kMaxDimension - 1] * bounds[kMaxDimension - 1];
  std::vector<int> tomato(max_size);

  for (int i{0}; i < max_size; ++i) {
    std::cin >> tomato[i];
    if (tomato[i] == 1) queue.push(Unflatten(i));
  }

  auto Checking = [&]() -> bool {
    std::vector<bool> visited(max_size);
    auto BFS = [&](hypher_dimension start) {
      std::queue<hypher_dimension> queue;
      visited[Flatten(start)] = true;
      queue.push(start);

      bool IsThereOne = false;

      while (queue.empty() != true) {
        auto curr = queue.front(); queue.pop();

        if (tomato[Flatten(curr)] == 1) IsThereOne = true;

        for (int i{0}; i < kMaxDimension; ++i) {
          hypher_dimension next{curr};
          ++next[i];
          auto next_idx = Flatten(next);

          if (!IsIn(next)) continue;
          if (visited[next_idx] || tomato[next_idx] == -1) continue;
          visited[next_idx] = true;
          queue.push(next);
        }

        for (int i{0}; i < kMaxDimension; ++i) {
          hypher_dimension next{curr};
          --next[i];
          auto next_idx = Flatten(next);

          if (!IsIn(next)) continue;
          if (visited[next_idx] || tomato[next_idx] == -1) continue;
          visited[next_idx] = true;
          queue.push(next);
        }
      }

      return IsThereOne;
    };

    for (int i{0}; i < max_size; ++i) {
      if (visited[i] || tomato[i] == -1) continue;
      if (!BFS(Unflatten(i))) return false;
    }

    return true;
  };

  if (Checking() == false) { std::cout << "-1\n"; exit(0); }

  int ans{0};
  while (true) {
    int step_size = static_cast<int>(queue.size());

    while (step_size--) {
      auto curr = queue.front(); queue.pop();

      for (int i{0}; i < kMaxDimension; ++i) {
        hypher_dimension next{curr};
        ++next[i];
        auto next_idx = Flatten(next);

        if (!IsIn(next)) continue;
        if (tomato[next_idx] == 0) {
          tomato[next_idx] = 1;
          queue.push(next);
        }
      }

      for (int i{0}; i < kMaxDimension; ++i) {
        hypher_dimension next{curr};
        --next[i];
        auto next_idx = Flatten(next);

        if (!IsIn(next)) continue;
        if (tomato[next_idx] == 0) {
          tomato[next_idx] = 1;
          queue.push(next);
        }
      }
    }

    if (queue.empty()) break;
    ++ans;
  }

  std::cout << ans << '\n';
}