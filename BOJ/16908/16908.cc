#include <algorithm>
#include <cassert>
#include <iostream>
#include <string_view>
#include <vector>
#include <map>

constexpr std::size_t kBukkitMax = 256ULL;

auto println = [](const std::string& rem, auto& list) -> void {
  if (list.empty()) { std::cout << rem << '\n'; return; }
  std::cout << rem;
  std::size_t size = list.size();
  for (std::size_t i{0}; i < size; ++i) {
    std::cout << list[i] << ((i + 1 == size) ? '\n' : ' ');
  }
};

class suffix_array {
 public:
  explicit suffix_array(const std::string& str) {
    std::size_t size = str.size();
    original_string = str;
    sfx.resize(size);
    lcp.resize(size);
    inv.resize(size);

    std::vector<int> ord(size + 1);
    std::vector<int> nord(size + 1);
    std::vector<int> count(std::max(size + 1, kBukkitMax));
    std::vector<int> temp(size + 1);

    int bukkit_idx{0};

    for (std::size_t i{0}; i < size; ++i) {
       sfx[i] = i;
       ord[i] = original_string[i];
    }

    for (std::size_t H = 1;; H <<= 1) {
      // ord[i + H], ord[i] 순으로 count sort 2회 -> Radix Sort
      std::fill(count.begin(), count.end(), 0);
      for (std::size_t i{0}; i < size; ++i) ++count[ord[std::min(i + H, size)]];
      for (std::size_t i{1}; i < std::max(size + 1, kBukkitMax); ++i) count[i] += count[i - 1];
      for (std::size_t i{size - 1}; i < size; --i) temp[--count[ord[std::min(i + H, size)]]] = i;

      std::fill(count.begin(), count.end(), 0);
      for (std::size_t i{0}; i < size; ++i) ++count[ord[i]];
      for (std::size_t i{1}; i < std::max(size + 1, kBukkitMax); ++i) count[i] += count[i - 1];
      for (std::size_t i{size - 1}; i < size; --i) sfx[--count[ord[temp[i]]]] = temp[i];
      
      // 순위 재정의
      bukkit_idx = 1;
      nord[sfx[0]] = 1;
      for (std::size_t i{1}; i < size; ++i) {
        auto prev = sfx[i - 1]; auto curr = sfx[i];

        if (ord[prev] != ord[curr] || ord[std::min(prev + H, size)] != ord[std::min(curr + H, size)])
          ++bukkit_idx;
        nord[curr] = bukkit_idx;
      }
      std::swap(ord, nord);

      if (bukkit_idx == size) break;
    }
    
    for (std::size_t i{0}; i < size; ++i) inv[sfx[i]] = i;

    int h{0};
    for (std::size_t i{0}; i < size; ++i) {
      if (inv[i] == 0) continue;

      auto prev = sfx[inv[i] - 1];
      while (i + h < size && prev + h < size &&
             original_string[i + h] == original_string[prev + h]) ++h;
      lcp[inv[i]] = h;
      h = std::max(h - 1, 0);
    }
  }

  std::pair<std::size_t, std::size_t> search_range(const std::string& P) const {
    std::size_t size = sfx.size();
    std::string_view text_view = original_string;
  
    // lower_bound
    std::size_t lhs{0}, rhs{size};
    while (lhs < rhs) {
      std::size_t mid = lhs + ((rhs - lhs) >> 1);
      std::string_view suffix = text_view.substr(sfx[mid]);
      if (suffix.compare(0, P.size(), P) < 0)
        lhs = mid + 1;
      else
        rhs = mid;
    }
    std::size_t begin = lhs;
  
    // upper_bound
    rhs = size;
    while (lhs < rhs) {
      std::size_t mid = (lhs + rhs) / 2;
      std::string_view suffix = text_view.substr(sfx[mid]);
      if (suffix.compare(0, P.size(), P) <= 0)
        lhs = mid + 1;
      else
        rhs = mid;
    }
    std::size_t end = lhs;
  
    return {begin, end};
  }

  bool contains(const std::string& pattern) const {
    auto [begin, end] = search_range(pattern);
    return begin < end;
  }  

  std::string original_string;
  std::vector<std::size_t> sfx;
  std::vector<std::size_t> inv;
  std::vector<std::size_t> lcp;
};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N;

  std::string S;
  std::cin >> S;

  std::vector<std::size_t> length(N);
  
  for (int i{1}; i < N; ++i) {
    S += (char)(i + 36);
    length[i] = S.size();
    std::string X;
    std::cin >> X;
    S += X;
  }

  auto DD = [&](std::size_t x) {
    return std::distance(length.begin(), std::upper_bound(length.begin(), length.end(), x));
  };

  suffix_array SA(S);

  std::map<std::ptrdiff_t, std::size_t> count;
  int unique{0};
  std::size_t l = 0;
  std::size_t r = 0;
  std::size_t max = 0;

  while (r < SA.lcp.size()) {
    if (++count[DD(SA.sfx[r])] == 1) ++unique;
    while (unique == N) {
      if (r > l) {
        auto range_min = *std::min_element(SA.lcp.begin() + l + 1, SA.lcp.begin() + r + 1);
        max = std::max(max, range_min);
      }

      if (--count[DD(SA.sfx[l++])] == 0) --unique;
    }
    ++r;
  }
  std::cout << max << '\n';
}