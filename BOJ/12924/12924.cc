#include <string>
#include <vector>
#include <iostream>

using namespace std;

long long GetSum(int i) {
    return (1LL * (i + 1) * i) >> 1;    
}

int solution(int n) {
    long long s;
    int ans{0};
    for (int i{1}; ((s = GetSum(i)) && s <= n); ++i) {
        if ((n - s) % i == 0) ++ans;
    }
    return ans;
}

int main() {
  int n = 15;
  cout << solution(n);
}