#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>

int calc_lcp(const std::string& s1, const std::string& s2) {
  int max = static_cast<int>(std::min(s1.size(), s2.size()));
  for (int i{0}; i < max; ++i) {
    if (s1[i] != s2[i]) return i;
  }
  return max;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N;
  std::vector<std::pair<std::string, int>> list;
  list.reserve(N);
  std::unordered_set<std::string> dict;
  
  for (int i{0}; i < N; ++i) {
    std::string word;
    std::cin >> word;
    if (dict.insert(word).second) list.push_back({word, list.size()});
  }
  list.push_back({"{", list.size()});

  std::sort(list.begin(), list.end());

  std::pair<int, int> ans_idx{0x7FFFFFFF, 0x7FFFFFFF};
  int idx1, idx2;

  int max{0}, prev_lcp{-1};

  for (int i{1}; i <= N; ++i) {
    int now_lcp = calc_lcp(list[i - 1].first , list[i].first);
    if (prev_lcp < now_lcp) {
      idx1 = std::min(list[i - 1].second, list[i].second);
      idx2 = std::max(list[i - 1].second, list[i].second);
    }
    else if (prev_lcp == now_lcp) {
      if (idx1 > list[i].second) { idx2 = idx1; idx1 = list[i].second; }
      else if (idx2 > list[i].second) { idx2 = list[i].second; }
    }
    else { // prev_lcp > now_lcp
      if (max < prev_lcp) {
        max = prev_lcp;
        ans_idx = {idx1, idx2};
      }
      else if (max == prev_lcp && ans_idx.first > idx1) {
          ans_idx = {idx1, idx2};
      }
    }
    prev_lcp = now_lcp;
  }

  std::sort(list.begin(), list.end(),
    [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; });


  std::cout << list[ans_idx.first].first << '\n' << list[ans_idx.second].first;
}