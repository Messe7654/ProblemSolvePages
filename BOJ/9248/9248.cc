#include <algorithm>
#include <iostream>
#include <vector>

class suffix_array {
 public:
  suffix_array(const std::string& str);
  
  std::vector<int> sfx;
  std::vector<int> lcp;
  std::vector<int> inv;

 private:
  std::string origin;
};

suffix_array::suffix_array(const std::string& str) {
  origin = str;
  int size = static_cast<int>(str.size());
  sfx.resize(size); inv.resize(size); lcp.resize(size);
  std::vector<int> ord(size + 1);
  std::vector<int> nord(size + 1);

  for (int i{0}; i < size; ++i) {
    sfx[i] = i;
    ord[i] = static_cast<int>(str[i]);
  }

  int p{1}, pnt{1};
  while (true) {
    std::sort(sfx.begin(), sfx.end(), [&](auto& lhs, auto& rhs) {
      if (ord[lhs] == ord[rhs]) return ord[lhs + p] < ord[rhs + p];
      return ord[lhs] < ord[rhs];
    });

    if (pnt == size) break;
    
    pnt = 1;
    nord[sfx[0]] = 1;
    for (int i{1}; i < size; ++i) {
      if (ord[sfx[i - 1]] != ord[sfx[i]] || ord[sfx[i - 1] + p] != ord[sfx[i] + p]) ++pnt;
      nord[sfx[i]] = pnt;
    }

    ord = nord;
    p <<= 1;
  }

  for (int i{0}; i < size; ++i) inv[sfx[i]] = i;

  int h{0};
  for (int i{0}; i < size; ++i) {
    if (inv[i]) {
      int prev = sfx[inv[i] - 1];
      while (str[prev + h] == str[i + h]) ++h;
      lcp[inv[i]] = h;
    }
    h = std::max(h - 1, 0);
  }
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  std::string input;
  std::cin >> input;
  suffix_array sa(input);


  int size = static_cast<int>(input.size());
  for (int i{0}; i < size; ++i) std::cout << sa.sfx[i] + 1 << ((i + 1 == size) ? '\n' : ' ');
  std::cout << "x ";
  for (int i{1}; i < size; ++i) std::cout << sa.lcp[i] << ((i + 1 == size) ? '\n' : ' ');
}