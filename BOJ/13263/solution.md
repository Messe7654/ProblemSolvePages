나무 자르기
==

$s_i$를 $i$번 나무를 모두 자르기 위한 최소의 비용이라 하자.

$$
s_1 = 0 \\
s_i = \min_{1 \le j \lt i}(s_j + b_j \times a_i) 
$$

모두 계산하게 되면 $O(N^2)$으로 아마 시간 초과.

다른 정보를 사용해야함

일단 눈에 띄는 정보는
$$
a_1 = 1, b_N = 0\ (이미\ 사용) \\
\forall i, j \text{ S.T. } i \lt j,\ a_i \lt a_j \\
\forall i, j \text{ S.T. } i \lt j,\ b_i \gt b_j
$$

<hr>

일단, $s_i$를 쭉 나열해봄
$$
\begin{aligned}
s_1 &= 0 \\
s_2 &= s_1 + b_1 \times a_2 \\
s_3 &= \min(s_1 + b_1 \times a_3 , s_2 + b_2 \times a_3) \\
s_i &= \min_{1 \le j \lt 3}(s_j + b_j \times a_i)
\end{aligned}
$$

$s_i$를 구할 때, 고려하는 항들은 기존에 사용한 $s_j$, $b_j$는 변하지 않고 $a_i$만 변함

재활용을 할 수 있을지도 (우선 pair로 $s_j$, $b_j$를 넣고 관리)

$s_i$ := 아마도 단조 증가 \
$a_i$ := 증가 \
$b_i$ := 감소

$\forall j, k$ s.t. $j \lt k, (s_j+b_j\times a_i) \gt (s_k+b_k\times a_i)$, \
$j \lt k, (s_j+b_j\times a_{i + 1}) \gt (s_k+b_k\times a_{i + 1})$

즉, 후보군에서 제거할 수 있음. (그렇다면, 모든 $j, k$ 쌍에 대하여 검사를 해야 하는가?)

$x = \displaystyle\argmin_{1 \le j \lt i}(s_j + b_j \times a_i)$이라 하면,
$$
\begin{aligned}
(s_i + b_i \times a_{i + 1}) - (s_x+b_x \times a_{i+1}) &= (s_i + b_i \times a_{i + 1}) - (s_x+b_x \times a_{i+1} + b_x \times a_i - b_x \times a_i) \\
&= b_i \times a_{i+1} - (b_x \times (a_{i + 1} - a_i)) \\
&= (b_i - b_x)(a_{i + 1} - a_i) + b_i \times a_i
\end{aligned}
$$

수식이 딱 맞아 떨어지진 않는데, 일단 $s_i$에 대한 거만 검사를 해보는 것두...
<hr>

deque로 관리해서 front에서 빼는 식으로 구현을 해봤는데, 시간 초과. \
또 다른 최적화 방법이 필요해보임.

$C$는 유효한 집합을 나타낸다 하자. $C$는 monotone queue로 관리 \
$C$는 $\forall j \lt k, \text{s.t.} C_j < C_k \And (s_{C_j}+b_{C_j} \times a_i \lt s_{C_k}+b_{C_k} \times a_i)$

결과적으로 $C$의 front가 $\displaystyle\argmin_{1 \le j \lt i}(s_j + b_j \times a_i)$

$a_i$가 달라지면, $C$가 관리하는 유효 범위 또한 달라짐. 이것을 최적화 할 수는 없는가? \
만약, $C_j$ 가 유효하지 않다면, $\forall k < j$는 모두 유효하지 않음 (확실함?)

$$
\text{if } \exist x, \text{ s.t. } j \lt x \And (s_j + b_j \times a_{i+1}) \gt (s_x+b_x \times a_{i+1}) \\
\forall k < j, \\
\begin{aligned}
cond &: (s_k+b_k \times a_{i+1}) - (s_j + b_j \times a_{i+1})\\
&: \underset{\lt 0}{\{(s_k + b_k \times a_i) - (s_j + b_j \times a_i)\}} + \underset{\lt 0}{(b_k - b_j)}\underset{\gt 0}{(a_{i+1} - a_i)} < 0
\end{aligned}
$$
맞는듯.

이진탐색 느낌으로 찾아도 되나? => 일단 시도

구현 중 든 생각. 그렇다면, 인접한 $j$, $k$에 대해서만 테스트 해봐도 되지 않나?

인접한 $j$, $k$에 대해서 $s_j+b_j \times a_i = s_k + b_k \times a_i$인 $a_i$는?
1차 방정식의 형태이므로, unique하게 나옴, 이 시점 이상인지 아닌지에 대해 test 가능

인접한 $C_j, C_{j + 1}$에 대해서 구한 시점을 $tp_{j + 1}$라 하자. \
$a_i$와 $tp_{j + 1}$를 비교

<script type="text/javascript" src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML"></script>
<script type="text/x-mathjax-config"> MathJax.Hub.Config({ tex2jax: {inlineMath: [['$', '$']]}, messageStyle: "none" });</script>