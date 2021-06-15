## Performance Evaluation

### Asymptotic Notation

- When input has **large** size
- Cares about **growth**, and constants don't matter
- $O$ (aka big-O)
  - If $f(n)$ grows **similar or slower** than $g(n)$, we say $f(n) = O(g(n))$.
  - $\displaystyle \lim_{n \to \infty} \frac{f(n)}{g(n)} \le constant$  $\Rightarrow$  $f(n) = O(g(n))$   (proof in slides)
  - $=O(g(n))$, $\in O(g(n))$
- $\Omega, \Theta, o, \omega$

### Some Analysis Examples

#### Sequential Search

- Best case: $\Theta(1)$
  - The target is the first element
- Average case: $\Theta(n)$
- Worst case: $\Theta(n)$

#### Binary Search

- Best case: $\Theta(1)$
  - The target is the element in the middle
- Worst case: $\Theta(\log n)$

### Properties

- 封閉律
- 遞移律
- 併吞律



