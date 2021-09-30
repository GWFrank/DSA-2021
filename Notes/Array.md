## Array

#### Properties

- fast random access

### Ordered array

#### Properties

- `insert` : "cut in" from back/front
- `construct` : insertion sort, which is just multiple `insert`

#### Search

- application : book search in libraries
- naive approach : sequential search
- sequential search with cut
  - when the next element is already larger than our target, we can cut.
- binary search
  - using cut multiple times
  - need both ordered (for cut) and array (for fast access to compare)
