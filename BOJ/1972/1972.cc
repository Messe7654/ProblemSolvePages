#include <iostream>
#include <string_view>
#include <unordered_set>

using namespace std::string_view_literals;
std::string_view surprised_prompt = " is surprising.\n"sv;
std::string_view unsurprised_prompt = " is NOT surprising.\n"sv;

bool IsSurprising(std::string_view str) {
  int n = static_cast<int>(str.size());

  for (int D{0}; D <= n - 2; ++D) {
    std::unordered_set<int> set;
    auto left_iterator = str.begin();
    auto right_iterator = str.begin();
    for (int i{0}; i <= D; ++i) ++right_iterator;

    while (right_iterator != str.end()) {
      int now = ((*left_iterator) - 'A') * 26 + *right_iterator;
      if (set.insert(now).second == false) return false;
      ++left_iterator; ++right_iterator;
    }
  }
  return true;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  std::string input;
  
  while (std::cin >> input) {
    if ("*" == input) break;
    std::cout << input << ((IsSurprising(input)) ? surprised_prompt : unsurprised_prompt);
  }
}