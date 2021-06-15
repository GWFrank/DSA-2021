# Graph

## 名詞

`G`: 圖
`V`: 頂點(vertex)
`E`: 邊(edge)

Directed, undirected: 邊有方向性/無方向性

adjacent: u, v是相鄰的 `<=>` 他們之間有邊直接連起來

degree: 一個頂點接了幾條邊
in-degree, out-degree: digraph才有的，顧名思義
所有頂點 degree 總和 = 總邊數*2

path: u 到 v 的路徑表示有邊可以走到
simple path: u, v 外其他點都沒有重複走過
cycle: u=v 的 simple path

connected: u, v 是相連的代表有一條路從 u 往 v
connected graph: 任兩個頂點都相連

## 性質

connected + (邊數 = 頂點數-1) => tree
很多 tree 互不相連 => forest
邊數 >= 頂點數 => 有環

## Graph 表示法

- Adjacency matrix
  - 查詢 $O(1)$
  - 耗空間 $O(V^2)$
- Adjacency list
  - 查詢$O(V)$
  - 省空間 $O(V+E)$

## BFS

- 廣度優先
- 可以找最短路徑
- 會做出一棵樹: Breadth-First Tree

## DFS

- 深度優先
- 會做出 forest
- 記錄 timestamp
  - 可以用來做 topological sort
- 看 undirected graph 是否 connected
- 列出 undirected graph 的所有 connected component