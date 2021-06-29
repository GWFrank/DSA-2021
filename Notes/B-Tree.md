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
	while i <= x.n and k > x.key[i] /* loop stops when k <= x.key_i */
		i += 1
	if i <= x.n and k == x.key[i] /* found the right key */
		return (x, i)
	else if x.leaf /* can't go further */
		return NIL
	else DISK_READ(x.c[i])
		return B_Tree_search(x.c[i], k)
```

CPU Time: $t\log_t{n}$
Disk I/O: $\log_t{n}$

## Split child

`split_child`

1. 把 `x.key` 中間的那個 `key` 往上面一層丟 (原本是 root 的話就長一層)
2. 其他的 `key` 分好，往下做

```pseudocode
function B_Tree_split_child(x, i) /* split x's i-th child */
	z = allocate_node()
	y = x.c[i]
	z.leaf = y.leaf
	z.n = t-1
	for j = 1 to t-1
		z.key[j] = y.key[j+t] /* get the second half of keys */
	if not y.leaf
		for j=1 to t
			z.c[j] = y.c[j+t]
	y.n = t-1
	for j = x.n+1 downto i+1
		x.c[j+1] = x.c[j] /* move childs back to get space */
	x.c[i+1] = z
	for j = x.n downto i
		x.key[j+1] = x.key[j] /* move keys back to get space */
	x.key[i] = y.key[t]
	x.n += 1
	DISK_WRITE(y)
	DISK_WRITE(Z)
```

## Insert

先用 `search` 找到應該放在哪裡，把路徑上的 full node 由 root 往 leaf 做 `split_child`
最後再把要 insert 的值丟進去

```pseudocode
function B_Tree_insert(T, k)
	r = T.root
	if r.n == 2*t-1
		s = allocate_node()
		T.root = s
		s.leaf = False
		s.n = 0
		s.c_1 = r
		B_Tree_split_child(s, 1)
		B_Tree_insert_nonfull(s, k)
	else
		B_Tree_insert_nonfull(r, k)
```

## Insert nonfull

```pseudocode
function B_Tree_insert_nonfull(x, k)
	i = x.n
	if x.leaf
		while i >= 1 and k < x.key[i]
			x.key[i+1] = x.key
			i -= 1
		x.key{i+1} = k
		x.n += 1
		DISK_WRITE(x)
	else
		while i >= 1 and k < x.key[i]
			i -= 1
		i += 1
		DISK_READ(x.c[i])
		if x.c[i].n == 2*t-1
			B_TREE_split_child(x, i)
			if k > x.key[i]
				i += 1
		B_Tree_insert_nonfull(x.c[i], k)
```

## Delete

### Merge

```pseudocode
function B_Tree_merge(x, m)
    // Merge key[m] down
    y = x.c[m]
    z = x.c[m+1]
    y.key[t] = m
    for j=1 to t-1
        y.key[t+j] = z.key[j]
    if not y.left
        for j=1 to t
            y.c[t+j] = z.c[j]
    y.n = 2*t-1
    free(z)
    for j=m to x.n-1
        x.key[j] = x.key[j-1]
    for j=m+1 to x.n
        x.c[j] = x.c[j+1]
    x.n -= 1
    DISK_WRITE(y)
    DISK_WRITE(z)
```



```pseudocode
function B_Tree_delete(T, k)
    r = T.root
    if r.n == 1
        DISK_READ(r.c[1])
        DISK_READ(r.c[2])
        if r.c[1].n < t and r.c[2].n < t
            // Special case that decreases height
            B_Tree_merge(r, 1)
            T.root = r.c[1]
            free(r)
            B_Tree_sub_delete(T.root, k)
        else
            B_Tree_sub_delete(r, k)
    else
        B_Tree_sub_delete(r, k)
```







```pseudocode
function B_Tree_sub_delete(x, k)
    i = 1
    if x.leaf
        // case 1
        while i <= x.n and x.key[i] < k
            i += 1
        while i <= x.n
            x.key[i] = x.key[i+1]
            i += 1
        x.n += 1
        DISK_WRITE(x)
    else
        while i <= x.n and x.key[i] < k
            i += 1
        if x.key[i] == k
            // case 2
            DISK_READ(x.c[i])
            DISK_READ(x.c[i+1])
            if x.c[i].n >= t
                // case 2a
                pre = x.c[i]
                while pre.c[pre.n+1]
                    pre = pre.c[pre.n+1]
                k_prime = pre.key[pre.n]
                x.key[i] = k_prime
                B_Tree_sub_delete(x.c[i], k_prime)
            else if x.c[i+1] >= t
                // case 2b
                suc = x.c[i+1]
                while suc.c[1]
                    suc = suc.c[1]
                k_prime = suc.key[1]
                key[i] = k_prime
                B_Tree_sub_delete(x.c[i+1], k_prime)
            else
                // case 2c
                B_Tree_merge(x, i)
                B_Tree_sub_delete(x.c[i], k)
        else
            // case 3
            DISK_READ(x.c[i])
            if x.c[i].n >= t
                B_Tree_sub_delete(x.c[i], k)
            else
                l_exist = False; l_few = True
                r_exist = False; r_few = True
                // case 3a
                if i-1 >= 1
                    DISK_READ(x.c[i-1])
                    l_exist = True
                    if x.c[i-1].n >= t
                        l_few = False
                        y = x.c[i]
                        z = x.c[i-1]
                        for j=t to 2
                            y.key[j] = y.key[j-1]
                        y.key[1] = x.key[i]
                        x.key[i] = z.key[z.n]
                        if not y.leaf
                            for j=t+1 to 2
                                y.c[j] = y.c[j-1]
                            y.c[1] = z.c[z.n+1]
                        y.n += 1
                        z.n -= 1
                        B_Tree_sub_delete(y, k)
                if i+1 <= x.n+1
                    DISK_READ(x.c[i+1])
                    r_exist = True
                    if x.c[i+1].n >= t
                        r_few = False
                        y = x.c[i]
                        z = x.c[i+1]
                        y.key[t] = x.key[i]
                        x.key[i] = z.key[1]
                        for j=1 to z.n-1
                            z.key[j] = z.key[j+1]
                        if not y.leaf
                            y.c[t+1] = z.c[1]
                            for j=1 to z.n
                                z.c[j] = z.c[j+1]
                        y.n += 1
                        z.n -= 1
                        B_Tree_sub_delete(y, k)
                // case 3b
                if l_few and r_few
                    if l_exist
                        B_Tree_merge(x, i-1)
                        B_Tree_sub_delete(x.c[i-1], k)
                    else
                        B_Tree_merge(x, i)
                        B_Tree_sub_delete(x.c[i], k)
```







