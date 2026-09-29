#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <vector>

#define debug(rem) if (local) std::cout << rem

#ifdef DEBUG
constexpr bool local = true;
#else
constexpr bool local = false;
#endif

constexpr int MAX = 90909;

long long prefix_sum[MAX];

class suffix_array {
 public:
  suffix_array(const std::string& str);
  void calc_lcp();
  void print();

  std::vector<int> sfx;
  std::vector<int> inv;
  std::vector<int> lcp;

 private:
  std::string str;
};

suffix_array::suffix_array(const std::string& str)
: str(str) {
  int size = static_cast<int>(str.size());
  sfx.resize(size); inv.resize(size); lcp.resize(size);
  std::vector<int> ord(256), nord(256), cnt(size + 1), aux(size + 1);

  int p = 1;
  for (int i{ 0 }; i < size; ++i) {
      sfx[i] = i;
      ord[i] = static_cast<int>(str[i]);
  }

  int pnt = 1;
  while (true) {
    for (int i{ 0 }; i <= size; ++i) cnt[i] = 0;
    for (int i{ 0 }; i < size; ++i) ++cnt[ord[std::min(i + p, size)]];
    for (int i{ 1 }; i <= size; ++i) cnt[i] += cnt[i - 1];
    for (int i{ size - 1 }; i >= 0; --i) aux[--cnt[ord[std::min(i + p, size)]]] = i;

    for (int i{ 0 }; i <= size; ++i) cnt[i] = 0;
    for (int i{ 0 }; i < size; ++i) cnt[ord[i]]++;
    for (int i{ 1 }; i < size; ++i) cnt[i] += cnt[i - 1];
    for (int i{ size - 1 }; i >= 0; --i) sfx[--cnt[ord[aux[i]]]] = aux[i];
    if (pnt == size) break;
    pnt = 1;
    nord[sfx[0]] = 1;
    for (int i{1}; i < size; ++i) {
      if (ord[sfx[i - 1]] != ord[sfx[i]] || ord[sfx[i - 1] + p] != ord[sfx[i] + p]) {
        ++pnt;
      }
      nord[sfx[i]] = pnt;
    }

    for (int i{0}; i < size; ++i) ord[i] = nord[i];
    p <<= 1;
  }

  for (int i{0}; i < size; i++) inv[sfx[i]] = i;

  calc_lcp();
}

void suffix_array::calc_lcp() {
  int h{0};
  int size = static_cast<int>(str.size());
  for (int i{0}; i < size; i++) {
    if (inv[i]) {
      int prev = sfx[inv[i] - 1];
      while (str[prev + h] == str[i + h]) h++;
      lcp[inv[i]] = h;
    }
    h = std::max(h - 1, 0);
  }
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  std::string S;
  std::cin >> S;

  int Q; std::cin >> Q;

  int size{static_cast<int>(S.size())};
  assert(1 <= size && size <= 90'000);
  suffix_array SA(S);
  for (int i{1}; i <= size; i++) {
    prefix_sum[i] = prefix_sum[i - 1] + size - SA.sfx[i - 1] - SA.lcp[i - 1];
  }

  debug("DEBUG> prefix_sum : ") << "[";
  for (int i{0}; i <= size; i++) {
    debug("") << prefix_sum[i] << ((i == size) ? "]\n" : ", ");
  }

  while (Q-- != 0) {
    int K; std::cin >> K;
    auto distance = std::distance(prefix_sum + 1, 
        std::lower_bound(prefix_sum, prefix_sum + size + 1, K));
    debug("DEBUG> distance : ") << distance << '\n';
    if (distance < 0 || distance >= size) {
      std::cout << "-1\n";
      continue;
    }
    std::cout << S.substr(SA.sfx[distance], K - prefix_sum[distance] + SA.lcp[distance]) << '\n';
  }
}