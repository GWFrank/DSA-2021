# Disjoint Sets

## 基本操作

`make_set(x)`: 做一個只包含 `x` 的 set

`union(x, y)`: 把 `x` 所在的集合和 `y` 所在的集合聯集

`find_set(x)`: 回傳 `x` 所在集合的 identifier

Note: 在 `union(x, y)` 前會先做 `find_set(x)` 和 `find_set(y)` 確定是在兩個不同的 set ，因此 `union(x, y)` 的時間複雜度不考慮找到所屬 set 的時間

## Implementation

### 方法一 - Naive Array

開 array ， element 當作 index ， array 存該 element 所屬 set 的 id

`find_set(x)`: $O(1)$

`union(x, y)`: $O(N)$
因為要車過 array 把同一個 set id 的都改掉

### 方法二 - Tree

把每個 set 當作一個樹，element 當作 node 。一種簡單的方法是開 array `p` ，用 `p[x]` 存 `x` 的長輩。root 節點的 `p[x]` 會指到自己。

`find_set(x)`: $O(N)$
最差情況是樹長得像linked list，要一路往回跑

`union(x, y)`: $O(1)$
直接把一個 root 的 parent 指到另一個的 root

### 方法三 - Linked List

每個 set 就是一個 linked list，存頭和尾。每個 node 會有指標指回代表 set 的東西

`find_set(x)`: $O(1)$

`union(x, y)`: $O(N)$
進去 set 把每個元素指到另一個 set

## 優化

### Union By Size / Rank

把小的併入大的，這樣可以改比較少東西。

均攤後 `find_set()` 可以只花 $O(\log n)$

### Path Compression

對 tree implementation 有效

在每次 `find_set(x)` 的時候，順便把一路上經過的人都直接指到 root

均攤後 `find_set()` 也是 $O(\log n)$

### Union By Rank + Path Compression

總共做 $m$ 個 `find_set()`, `union()`, `make_set()` ，且其中有 $n$ 個 `make_set()`

總時間是 $O(m \cdot \alpha (n))$ ， $\alpha()$ 是 Ackermann's Function 的反函數，成長非常緩慢，大多數的時候 $\le 4$

