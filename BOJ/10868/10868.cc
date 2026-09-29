#include <iostream>

int numbers[100'001][20];

int msb(int x) {
  return x & (~x + 1);
}

int nth(int x) {
  int count{ 0 };
  for (; (1 << count) != x; count++);
  return count;
}

// [left..right]에서의 최소값을 구하는 함수
int getMin(int left, int right) {
  int count{right - left + 1};
  int min{0x7FFFFFFF};
  while (count) {
    auto deletion = msb(count);
    min = std::min(min, numbers[right][nth(deletion)]);
    right -= deletion;
    count &= ~deletion;
  }
  return min;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N, M;
  std::cin >> N >> M;

  for (int i{1}; i <= N; i++) std::cin >> numbers[i][0];

  for (int i{1}; i <= N; i++) {
    for (int s{1}; s <= 16; s++) {
      if (i < (1 << (s - 1))) continue;
      numbers[i][s] = std::min(numbers[i][s - 1], numbers[i - (1 << (s - 1))][s - 1]);
    }
  }

  while (M-- != 0) {
    int a, b;
    std::cin >> a >> b;
    std::cout << getMin(a, b) << '\n';
  }
}