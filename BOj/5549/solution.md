https://www.acmicpc.net/problem/5549
=
## 문제
$N \times M$ board에 'J', 'O', 'I'가 주어진다. \
각 쿼리는 다음과 같이 주어진다.
> $a\space b\space c\space  d$\
> 왼쪽 위 모서리가 $(a, b)$, 오른쪽 아래 모서리가 $(c, d)$인 공간에서\
> 각각 'J', 'O', 'I'가 주어진 갯수를 공백을 기준으로 구분하여 출력한다.

$K$개의 쿼리가 주어질 때, 답을 출력하라.

## 문제 접근
keyword는 다음과 같습니다.

__2차원__ 에서 __특정 구간에__ 존재하는 __갯수__ 를 여러번 구하는 문제

일단 2차원을 배제하고, 특정 구간에 존재하는 갯수를 구하는 쿼리는
일반적으로 누적합 테크닉을 사용하여 많이 풉니다.\
예전에 대충 정리해놓은 글은 [여기] 있습니다.

이것을 이제 2차원으로 확장해야 합니다.

2차원으로의 확장은 __포함 배제의 원리를__ 통해 구할 수 있습니다.

그 이전에 일단 2차원 누적합 테이블을 정의하고 갑시다.

$pre[i][j]$는 특정 board에서 $(1, 1)$을 왼쪽 위 모서리, $(i, j)$를 오른쪽 아래 모서리로 하는 구간을 전부 더한 결과라고 하겠습니다.

이제 저희가 구할 (a, b) => (c, d)는 다음과 같이 구할 수 있게 됩니다.

$pre[c][d] - pre[a - 1][d] - pre[c][b - 1] + pre[a - 1][b - 1]$
직접 한 번 그려보시면 어렵지 않게 이해가 가실테지만,
표를 그리기는 귀찮아서 생략하도록 하겠습니다.

아무튼 이러한 테크닉을 통해 문제를 풀어나갈 수 있을 것 같습니다.

## 구현
<details>
<summary>접기/펼치기</summary>

```python
import sys

INPUT = sys.stdin.readline
OUTPUT = sys.stdout.write

N, M = map(int, INPUT().split())
K = int(INPUT().rstrip())

index_map = {'J' : 0, 'O' : 1, 'I' : 2}
board = [[[0, 0, 0] for col in range(M + 1)] for row in range(N + 1)]

for row in range(N):
  line = INPUT().rstrip()
  for col in range(M):
    c = line[col]
    board[row + 1][col + 1][index_map[c]] = 1
    
for row in range(1, N + 1):
  for col in range(2, M + 1):
    board[row][col][0] += board[row][col - 1][0]
    board[row][col][1] += board[row][col - 1][1]
    board[row][col][2] += board[row][col - 1][2]
    
for col in range(1, M + 1):
  for row in range(2, N + 1):
    board[row][col][0] += board[row - 1][col][0]
    board[row][col][1] += board[row - 1][col][1]
    board[row][col][2] += board[row - 1][col][2]

def query(a, b, c, d):
  ans = [
    board[c][d][i] - board[a - 1][d][i] - board[c][b -1][i] + board[a - 1][b - 1][i]
    for i in range(3)
  ]
  OUTPUT(f"{ans[0]} {ans[1]} {ans[2]}\n")

for i in range(K):
  a, b, col, d = map(int, INPUT().split())
  query(a, b, col, d)
```
</details>


[여기]: https://cafe.naver.com/dremdeveloper/153