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