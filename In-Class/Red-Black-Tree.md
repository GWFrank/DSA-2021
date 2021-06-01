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
- External node 都是黑色的
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



## Insertion