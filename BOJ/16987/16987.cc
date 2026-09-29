#include <iostream>
#include <vector>

int N;

struct egg {
  int HP;
  int weight;

  egg() : HP(0), weight(0) {}

  int IsBroken() { return HP <= 0; }
};

std::vector<egg> eggs;
int max;

void Backtracking(int pos) {
  if (pos == N) {
    int count{0};
    for (int i{0}; i < N; ++i) {
      if (eggs[i].IsBroken()) ++count;
    }
    max = std::max(max, count);
    return;
  }

  if (eggs[pos].IsBroken()) {
    Backtracking(pos + 1);
    return;
  }

  bool isAllBroken{true};

  for (int i{0}; i < N; ++i) {
    if (i != pos && !eggs[i].IsBroken()) {
      isAllBroken = false;
      eggs[pos].HP -= eggs[i].weight;
      eggs[i].HP -= eggs[pos].weight;

      Backtracking(pos + 1);

      eggs[pos].HP += eggs[i].weight;
      eggs[i].HP += eggs[pos].weight;
    }
  }

  if (isAllBroken) Backtracking(N);
}

int main() {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(0); std::cout.tie(0);

  std::cin >> N;
  eggs.resize(N);

  for (int i{0}; i < N; ++i) {
    std::cin >> eggs[i].HP >> eggs[i].weight;
  }
  Backtracking(0);  
  
  std::cout << max;
}