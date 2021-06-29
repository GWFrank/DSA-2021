# Hash Table

把各種 key 用一個 hash function $h(key)$ 對應到一個 table 裡的一個位置

搜尋、插入、刪除都是 $O(1)$

Overflow: table 滿了
Collision: 不同的 key 對到同一個 table 上的位置

## Open Addressing

Collision 的話就用某種方式找另一個位置(Probing)，看可不可以放 

Probing sequence: 用 probing 會去試的 index 形成的數列

Linear probing: $(h(k) + i )\mod{m}$
$m$ 種 probing sequence ( $h(k)$  相同就會一樣 )

Quadratic probing: $(h(k) + c_1i + c_2i^2) \mod{m}$
$m$ 種 probing sequence ( $h(k)$  相同就會一樣 )

Double hashing: $(h_1(k) + i \cdot h_2(k)) \mod{m}$
$m^2$ 種 probing sequence ( $h_1(k)$ 和 $h_2(k)$  相同才會一樣，兩個各有 $m$ 種可能，且互相獨立 )

Worst case: $O(n)$

優點：可以用單個 array 做完，不用管指標
缺點：會 overflow

## Chaining

每個 slot 都是一個 linked list ， node 存 (key, value) pair

Worst case: $O(\log n)$
每個 slot 可以用一個 BST 來做

優點：不會 overflow

## Dynamic Hashing with Directory

取 hash 後的最後 `i` 個 bit 來當 index ，每個 slot 會是一個指到 array-like 的指標 (directory)

`i` 從 1 開始，碰到 directory 滿的時候加 1，把 directory 擴大，原本想要丟進去的 slot 重新 hash + insert ，其他的就把指標指向舊的 directory