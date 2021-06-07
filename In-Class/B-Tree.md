# B-Tree

- Balanced, non-binary serach tree
- Large branching factor (一個節點有很多子節點)
- $O(\log n)$ 高度，但有非常小的係數
- Usage: 大量資料儲存，部份存於memory，部份存於secondary storage(SSD, HDD)
- Goal
  - 減少disk I/O次數
  - 減少CPU time

## Definition

- `x.n`: number of `x`'s keys 
- `x.key_1`, `x.key_2` ... , `x.key_n`
- `x.leaf`: is value is `TRUE`, `x` is a leaf
- `x.c_1`, `x.c_2` ... , `x.c_n+1`

讓 `k_i` 是 `x.c_i` 的任何一個key，則有這個性質：
$k_1 \le x.key_1 \le k_2 \le \cdots \le x.key_{x.n} \le k_{x.n+1}$

- All leaves have the same depth
- minimum degree `t` >= 2
  - Every node have at least `t` children and at most `2t` children.
  - A node with `2t` children is **full**

## Search

跟BST的搜尋很像

```pseudocode
function B_Tree_search(x, k)
	i = 1
	while i <= x.n and k > x.key_i /* loop stops when k <= x.key_i */
		i += 1
	if i <= x.n and k == x.key_i /* found the right key */
		return (x, i)
	else if x.leaf /* can't go further */
		return NIL
	else DISK_READ(x.c_i)
		return B_Tree_search(x.c_i, k)
```

CPU Time: $t\log_t{n}$
Disk I/O: $\log_t{n}$

## Insert

先用 `search` 找到應該放在哪裡，把路徑上的 full node 由 root 往 leaf 做 `split_child`

> `split_child`
>
> 1. 把 `x.key` 中間的那個 `key` 往上面一層丟 (原本是 root 的話就長一層)
> 2. 其他的 `key` 分好，往下做
>
> ```pseudocode
> function B_Tree_split_child(x, i) /* split x's i-th child */
> 	z = allocate_node()
> 	y = x.c_i
> 	z.leaf = y.leaf
> 	z.n = t-1
> 	for j = 1 to t-1
> 		z.key_j = y.key_{j+t} /* get the second half of keys */
> 	if not y.leaf
> 		for j=1 to t
> 			z.c_j = y.c_{j+t}
> 	y.n = t-1
> 	for j = x.n+1 downto i+1
> 		x.c_{j+1} = x.c_j /* move childs back to get space */
> 	x.c_{i+1} = z
> 	for j = x.n downto i
> 		x.key_{j+1} = x.key_j /* move keys back to get space */
> 	x.key_i = y.key_t
> 	x.n += 1
> 	DISK_WRITE(y)
> 	DISK_WRITE(Z)
> ```

最後再把要 insert 的值丟進去

