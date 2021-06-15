# Linear Time Sorting

## Counting Sort

- 要排序的 array 叫 `A`
- 建一個 array `C`，用 `A` 可能的 element 當作 index
- Linear time 車過 `A` ，在 `C` 數各個 element 出現幾次
- 把 `C` 建成 prefix sum，`C[A[i]]` 會是指 `A[i]` 應該擺在輸出 array `B` 的哪個位置
- 從尾巴車過 `A`，用 `C[A[i]]` 當 index 把 `A[i]` 放到 `B ` (Stable!)

---

## Radix Sort

其實就是很多次 counting sort ，從最小位數往最大位數

一樣是 linear time

---

## Bucket Sort

把輸入資料一某種方式(例如小數點後第一位)分桶子，每個桶子內做insertion sort，最後按照桶子順序輸出。

