#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#define debug if (local) std::cout
#ifdef DEBUG
constexpr bool local = true;
#else
constexpr bool local = false;
#endif

long long sum[1 << 19];
long long cnt[1 << 19];
constexpr int size = 1 << 18;
constexpr long long kmod = 1'000'000'007;

void update(int index) {
  int value = index;
  index |= size;

  sum[index] = sum[index] + value;
  cnt[index] = cnt[index] + 1;

  while (index >>= 1) {
    sum[index] = sum[index << 1] + sum[index << 1 | 1];
    cnt[index] = cnt[index << 1] + cnt[index << 1 | 1];
  }
}

std::pair<long long, long long> query(int left, int right) {
  left |= size; right |= size;
  std::pair<long long, long long> ret{0, 0};
  while (left <= right) {
    if (left & 1) {
      assert(ret.second - kmod + cnt[left] < 0);
      ret.first = (ret.first + sum[left]) % kmod;
      ret.second = (ret.second + cnt[left]) % kmod;
      ++left;
    }
    if (~right & 1) {
      assert(ret.second - kmod + cnt[right] < 0);
      ret.first = (ret.first + sum[right]) % kmod;
      ret.second = (ret.second + cnt[right]) % kmod;
      --right;
    }
    left >>= 1; right >>= 1;
  }
  return ret;
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  int N; std::cin >> N;
  
  int pos; std::cin >> pos;
  update(pos);
  long long ans{1};
  for (int i{2}; i <= N; i++) {
    std::cin >> pos;
    auto lhs = query(0, pos - 1);
    auto rhs = query(pos + 1, 199'999);
    update(pos);
    long long distance = 
        (((lhs.second * pos) % kmod - lhs.first + kmod) % kmod
        + (rhs.first - (rhs.second * pos) % kmod + kmod) % kmod) % kmod;
    ans = (ans * distance) % kmod;
    debug << i << "\'s tree cost : " << distance << '\n';
  }

  std::cout << ans;
}