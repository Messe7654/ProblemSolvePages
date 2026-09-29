#include <cassert>
#include <iostream>

struct picture {
  int shape_idx;
  int s_color_idx;
  int b_color_idx;
};

picture pictures[9];

bool Hap(const picture& p1, const picture& p2, const picture& p3) {
  unsigned shape_flag{0}, s_color_flag{0}, b_color_flag{0};
  shape_flag |= (1U << p1.shape_idx);
  shape_flag |= (1U << p2.shape_idx);
  shape_flag |= (1U << p3.shape_idx);

  s_color_flag |= (1U << p1.s_color_idx);
  s_color_flag |= (1U << p2.s_color_idx);
  s_color_flag |= (1U << p3.s_color_idx);

  b_color_flag |= (1U << p1.b_color_idx);
  b_color_flag |= (1U << p2.b_color_idx);
  b_color_flag |= (1U << p3.b_color_idx);

  auto shape_count = __builtin_popcount(shape_flag);
  auto s_color_count = __builtin_popcount(s_color_flag);
  auto b_color_count = __builtin_popcount(b_color_flag);

  return shape_count != 2 && s_color_count != 2 && b_color_count != 2;
}

int GetShapeIdx(std::string_view shape) {
  if ("CIRCLE" == shape) return 0;
  if ("TRIANGLE" == shape) return 1;
  if ("SQUARE" == shape) return 2;
  assert(false && "올바르지 않은 도형의 모양 입력");
  return -1;
}

int GetSColorIdx(std::string_view s_color) {
  if ("YELLOW" == s_color) return 0;
  if ("RED" == s_color) return 1;
  if ("BLUE" == s_color) return 2;
  assert(false && "올바르지 않은 도형의 색 입력");
  return -1;
}

int GetBColorIdx(std::string_view b_color) {
  if ("GRAY" == b_color) return 0;
  if ("WHITE" == b_color) return 1;
  if ("BLACK" == b_color) return 2;
  assert(false && "올바르지 않은 배경색 입력");
  return -1;
}

bool precompute[0x800];

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  for (int i{0}; i < 9; ++i) {
    std::string S, C, B;
    std::cin >> S >> C >> B;
    pictures[i].shape_idx = GetShapeIdx(S);
    pictures[i].s_color_idx = GetSColorIdx(C);
    pictures[i].b_color_idx = GetBColorIdx(B);
  }

  int total_hap_count{0};
  int call_hap_count{0};
  int result{0};
  bool gyeol_flag{false};

  for (int i1{0}; i1 < 7; ++i1) {
    for (int i2{i1 + 1}; i2 < 8; ++i2) {
      for (int i3{i2 + 1}; i3 < 9; ++i3) {
        if (Hap(pictures[i1], pictures[i2], pictures[i3]) == true) {
          precompute[(1U << i1) | (1U << i2) | (1U << i3)] = true;
          ++total_hap_count;
        }
      }
    }
  }

  int n; std::cin >> n;
  for (int i{0}; i < n; ++i) {
    char op; std::cin >> op;
    if ('H' == op) {
      int a, b, c;
      std::cin >> a >> b >> c;
      --a; --b; --c;
      if (precompute[(1U << a) | (1U << b) | (1U << c)]) {
        ++call_hap_count;
        precompute[(1U << a) | (1U << b) | (1U << c)] = false;
        result += 1;
      }
      else {
        result -= 1;
      }
    }
    else {
      if (total_hap_count == call_hap_count && gyeol_flag == false) {
        gyeol_flag = true;
        result += 3;
      }
      else {
        result -= 1;
      }
    }
  }

  std::cout << result;
}