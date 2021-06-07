# String Matching

## Problem Statement

Text (`T`): 長度為 `n` 的一個字串
Pattern (`P`): 長度為 `m` 的一個字串，且`m` <= `n`
在 `T` 中找所有和 `P` match的子字串

---

## Naive Method

```pseudocode
function naive_string_match(T, P)
	N = T.len
	M = P.len
	valid_shifts = array()
	for s from 0 to n-m
		if T[s+1..s+m] == P[1..m]
			valid_shifts.add(s)
	return valid_shifts
```

- 時間複雜度：$O(mn)$ (糟糕)
- 問題：上次比對後的資訊沒有被利用

---

## Rabin-Karp Algorithm

假設可能有 `d` 種字元，把每個可能的字元對應到一個整數(`1`~`d`)
長度 `k` 的字串就可以被視為一個有 `k` 位的 `d` 進位數

`t_s`：`T[s+1..s+m]` 對應的數
`p`： `P` 對應的數
$\Rightarrow$ `t_s` == `p` 等價於 `s` 是一個 valid shift
$t_{i+1} = d(t_i - d^{m-1}T[i]) + T[i+1+m]$ (常數時間)

小問題：數字過大會 overflow
解決方法：mod `q`

modular 的小問題：導致 `t_s` == `p` 不保證 valid shift (a.k.a. spurious hit)
解決方法：取大、範圍內的 `q` 並額外做檢查

```pseudocode
function Rabin_Karp_Matcher(T,P,d,q)
    n = T.len
    m = P.len
    h = d mod q
    p = 0
    t = 0
    valid_shifts = array()
    for i from 1 to m
        p = (d*p + P[i]) % q
        t = (d*t + T[i]) % q
    for s from 0 to n-m
        if p == t
            if P[1..m]==T[s+1..s+m]
                valid_shifts.add(s)
        if s<n-m
            t=(d(t-T[s+1]h)+T[s+m+1]) mod q
    return valid_shifts
```

- Worst Case ：每次都 spurious hit，時間 $O(mn)$
- Average Case ： modular 後平均分布，時間 $O(n)$ (nice)

---

