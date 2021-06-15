# Red-Black Tree

- 自我平衡
- Done balancing in $O(\lg(n))$

## Operations

- `Find`
- `Insert`
- `Delete`
- `Find-max/Find-min`
- `Find-successor/Find-predecessor`

## Rules

- 每個 node 不是黑色就是紅色
- 沒有接 child 的地方就接 "external node" / "NIL"，也就是每個 leaf 都應該是 external node
- 其他有包含資料的 node 稱為 internal node
- Root 是黑色的
- External node / leaf 都是黑色的
- **紅色 node 的兩個 children 都是黑色的**
- **對於任何一個 node，從它到任何 child leaf 的路徑上，都含有同樣數量的黑色 node (不含自己)**

### Black Height / 黑高度

`bh(x)` = 從 `x` 到 child leaf 路上有幾個黑色 node (不含自己)

### Representation

- `node.p`
- `node.left`, `node.right`
- `node.key`
- `node.color`

## Rotation

```
    y			    x
   / \			   / \
  x   c		=>	  a   y
 / \			     / \
a   b			    b   c
```

rotate 後大小關係依然維持！

## Insertion

`insert(z)`

- 用一般 BST 的方法插入 (走到一個他合法的葉子位置)
- 但 `z` 會是紅色，且兩個小孩都是 `nil`
- 最後處理違規的地方

可能違規的情況

- root 變成紅色的：只可能發生在整棵樹只有 `z`，所以就直接換成黑色
- 爸爸和小孩都是紅色的：需要處理



- 情形一： 紅叔叔
  - 爸爸和叔叔換成黑色，爺爺換成紅色
  - 從爺爺開始看有沒有合法
- 情形二： 黑叔叔
  - 用 rotate 讓自己、爸爸、爺爺變成一直線
  - rotate 讓自己和爸爸往上，爺爺往下
  - 把爸爸變成黑色，舊爺爺/新叔叔 變成紅色

