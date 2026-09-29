#include <algorithm>
#include <iostream>
#include <vector>

int N, M;
std::vector<long long> T;

void Update(int Tidx, int start, int end, int Aidx, int value) {
  if (Aidx < start || end < Aidx) return;
  if (start == end) {
    T[Tidx] = value;
    return;
  }

  int mid = start + ((end - start) >> 1);
  Update(Tidx << 1, start, mid, Aidx, value);
  Update(Tidx << 1 | 1, mid + 1, end, Aidx, value);
  T[Tidx] = T[Tidx << 1] + T[Tidx << 1 | 1];
}

long long Get(int Tidx, int start, int end, int left, int right) {
  if (right < start || end < left) return 0;
  if (left <= start && end <= right) return T[Tidx];

  int mid = start + ((end - start) >> 1);
  return Get(Tidx << 1, start, mid, left, right) +
         Get(Tidx << 1 | 1, mid + 1, end, left, right);
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  std::cin >> N;
  T.resize(N << 2);
  for (int i{1}; i <= N; ++i) {
    int A; std::cin >> A;
    Update(1, 1, N, i, A);
  }

  std::vector<std::vector<int>> type1;
  std::vector<std::vector<int>> type2;
  std::vector<std::vector<long long>> result;

  std::cin >> M;
  size_t cnt{0};
  for (int i{0}; i < M; ++i) {
    int op;
    std::cin >> op;
    if (op == 1) {
      int a, b;
      std::cin >> a >> b;
      type1.push_back({a, b});
    } else {
      int a, b, c;
      std::cin >> a >> b >> c;
      type2.push_back({a, b, c, (int)++cnt});
    }
  }

  std::sort(type2.begin(), type2.end(),
            [](const auto& lhs, const auto& rhs) { return lhs[0] < rhs[0]; });

  cnt = 0;

  for (size_t i{0}; i < type1.size(); ++i) {
    while (cnt < type2.size() && type2[cnt][0] == i) {
      result.push_back({Get(1, 1, N, type2[cnt][1], type2[cnt][2]), type2[cnt][3]});
      ++cnt;
    }
    Update(1, 1, N, type1[i][0], type1[i][1]);
  }
  while (cnt < type2.size() &&
         type2[cnt][0] == static_cast<int>(type1.size())) {
    result.push_back({Get(1, 1, N, type2[cnt][1], type2[cnt][2]), type2[cnt][3]});
    ++cnt;
  }

  std::sort(result.begin(), result.end(),
            [](const auto& lhs, const auto& rhs) { return lhs[1] < rhs[1]; });

  for (int i{0}; i < cnt; ++i) {
    std::cout << result[i][0] << '\n';
  }
}