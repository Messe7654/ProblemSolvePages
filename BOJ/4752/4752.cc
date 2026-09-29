// [BOJ-4752] HTML 에디터
// https://www.acmicpc.net/problem/4752
#include <iostream>
#include <string>
#include <vector>

void query(int B, int E, std::string TEXT) {
  std::vector<std::string> tag_stack;

  int size{static_cast<int>(TEXT.size())};
  bool tag_read{false};
  std::string tag{""};
  int i{0};
  for (; i < B; ++i) {
    if (TEXT[i] == '<') tag_read = true;
    if (tag_read) tag += TEXT[i];
    if (tag_read && TEXT[i] == '>') {
      tag_read = false;
      if (tag[1] != '/') tag_stack.push_back(tag);
      else tag_stack.pop_back();
      tag = "";
    }
  }
  for (auto str : tag_stack) {
    std::cout << str;
  }

  for (; i < E; ++i) {
    if (TEXT[i] == '<') tag_read = true;
    if (tag_read) tag += TEXT[i];
    std::cout << TEXT[i];
    if (tag_read && TEXT[i] == '>') {
      tag_read = false;
      if (tag[1] != '/') tag_stack.push_back(tag);
      else tag_stack.pop_back();
      tag = "";
    }
  }

  while (tag_stack.empty() != true) {
    tag = tag_stack.back();
    tag_stack.pop_back();
    tag.insert(1, "/");
    std::cout << tag;
  }
  std::cout << '\n';
};

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int B, E;
  std::string TEXT;
  while (std::cin >> B >> E) {
    if (B == -1 && E == -1) break;
    std::cin.ignore();
    std::getline(std::cin, TEXT);
    query(B, E, TEXT);    
  }
}