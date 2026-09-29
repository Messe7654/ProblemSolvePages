#include <iostream>
#include <list>

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int T; std::cin >> T;
  for (int testcase{1}; testcase <= T; ++testcase) {
    std::list<std::pair<char, int>> line;
    line.push_back({'-', 0});
    int N; std::cin >> N;
    for (int i{0}; i < N; ++i) {
      char c; int n;
      std::cin >> c >> n;
      line.push_back({c, n});
    }

    auto now{line.begin()}; ++now;
    auto prev{line.begin()};

    while (now != line.end()) {
      auto& [meterial, count] = *now;
      if (count >= 3) {
        int new_count = count / 3;
        if (line.back().first == meterial) line.back().second += new_count;
        else line.push_back({meterial, new_count});
        count -= 3 * new_count;

        if (count == 0) {
          now = line.erase(now);
          if (now->first == prev->first) {
            prev->second += now->second;
            now = line.erase(now);
            --now; --prev;
          }
        }
      }
      else {
        ++prev;
        ++now;
      }
    }

    int ret{0};
    for (auto it{line.begin()}; it != line.end(); ++it) {
      auto [meterial, count] = *it;
      ret += count;
    }
    std::cout << ret << '\n';
  }
}