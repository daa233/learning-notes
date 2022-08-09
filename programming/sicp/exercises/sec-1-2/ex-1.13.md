## Exercise 1.13

### 题目
> Prove that Fib(n) is the closest integer to $\varphi^n / \sqrt{5}$, where $\varphi = (1 + \sqrt{5}) / 2$. Hint: Let $\psi = (1 - \sqrt{5}) / 2$. Use induction and the definition of the Fibonacci numbers (see Section 1.2.2) to prove that $\text{Fib}(n) = (\varphi^n − \psi^n )/\sqrt{5}$.

### 证明
一、先证明 $\text{Fib}(n) = (\varphi^n − \psi^n )/\sqrt{5}$。

初值验证
- 当 n = 0 时， $\text{Fib}(0) = (\varphi^0 − \psi^0 )/\sqrt{5} = 0$ 成立；
- 当 n = 1 时， $\text{Fib}(1) = (\varphi^1 − \psi^1 )/\sqrt{5} = 1$ 成立；

假设
- 当 $n = k（n \geq 1）$ 时， $\text{Fib}(k) = (\varphi^k − \psi^k )/\sqrt{5}$ 成立；
* 当 $n = k + 1（n \geq 1）$ 时， $\text{Fib}(k+1) = (\varphi^{k+1} − \psi^{k+1})/\sqrt{5}$ 成立；

则

$$
\begin{align}
\text{Fib}(k+2) &= \text{Fib}(k+1) + \text{Fib}(k) \newline
&= (\varphi^{k+1} − \psi^{k+1})/\sqrt{5} + (\varphi^k − \psi^k )/\sqrt{5} \newline
&= ((\varphi^{k+1} + \varphi^k) − (\psi^{k+1} + \psi^k)) / \sqrt{5} \newline
&= (\varphi^k (\varphi + 1) - \psi^k (\psi + 1)) / \sqrt{5} \newline
&= (\varphi^k \varphi^2  - \psi^k \psi^2) / \sqrt{5} \newline
&= (\varphi^{k+2} − \psi^{k+2} )/\sqrt{5} \newline
\end{align}
$$

即当 $n = k + 2（n \geq 1）$ 时也成立。

综合以上，对于任意的 $n \geq 0$， $\text{Fib}(n) = (\varphi^n − \psi^n )/\sqrt{5}$ 均成立。

二、再证明 $\text{Fib}(n)$ 是距离 $\varphi^n /\sqrt{5}$ 最近的整数。

欲证明 $\text{Fib}(n) = \text{round}(\varphi^n/\sqrt{5})$，即等价于证明 $\left|\text{Fib}(n) - \varphi^n/\sqrt{5} \right| < \frac{1}{2}$。

可证

$$
\begin{align}
\left| \text{Fib}(n) - \varphi^n/\sqrt{5} \right| &= \left| (\varphi^n − \psi^n )/\sqrt{5} - \varphi^n/\sqrt{5} \right| \newline
&= \left| - \psi^n / \sqrt{5} \right| \newline
&= \frac{((\sqrt{5} - 1)/ 2)^n}{\sqrt{5}} \newline
&\leq \frac{1}{\sqrt{5}} \newline
&< \frac{1}{2}
\end{align}
$$

因此， $\text{Fib}(n)$ 是距离 $\varphi^n /\sqrt{5}$ 最近的整数。
