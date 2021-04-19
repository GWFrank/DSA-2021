# 2015

## 1.

### (a)

```c
#include <stdio.h>
#include <stdlib>

int* leak() {
    int *arr1 = malloc(1024*sizeof(int));
    int *arr2 = malloc(1024*sizeof(int));
    arr1 = arr2;
    return arr1;
}

int main() {
    int *p = leak();
    return 0;
}
```

## 2.

### (b)

```c
node* invert(node* head) {
    node* cur = head;
    node* prv = NULL;
    node* nxt = NULL;
    while (cur->next != NULL) {
        nxt = cur->next;
        cur->next = prv;
        prv = cur;
        cur = nxt;
    }
    return head;
}
```



---

# 2014

## 1.

```
3 6
```

## 2.

```
dsa/
|
|- instructor
|
|- ta/
|  |- ta1
|  |- ta2
|  |- ta3
|
|- hw/
|  |
```

## 3.

### (a)

```

```





## 5.

```pseudocode
function squareDistance(v, u)
	dist = 0
	v_traversed = false
	u_traversed = false
	while !v_traversed && !u_travered
		if v[0] < u[0]
			dist += square(v[1])
			// proceed v to next element
			if v is not tail
				v = v.next
			else
				v_traversed = true
		else if v[0] > u[0]
			dist += square(u[1])
			// proceed v to next element
			if u is not tail
				u = u.next
			else
				u_traversed = true
		else
			dist += square(v[1]-u[1])
			if v is not tail
				v = v.next
			else
				v_traversed = true
			if u is not tail
				u = u.next
			else
				u_traversed = true
	
			
```

---

# 2013

## 3

### (a)

```c
DNode* transform(Node* head) {
    DNode* new_head = malloc(sizeof(DNode));
    Node* cur_node = head;
    DNode* cur_dnode = new_head;
    DNode* prv = NULL;
    while (cur_node) {
        cur_dnode->value = cur_node->value;
		cur_dnode->prev = prv;
        prv = cur_dnode;
        if (cur_node->next) {
        	cur_dnode->next = malloc(sizeof(DNode));
        } else {
            cur_dnode->next = NULL;
        }
        cur_dnode = cur_dnode->next;
        Node* unused = cur_node;
        cur_node = cur_node->next;
        free(unused);
    }
    return new_head;
}
```

### (b)

```c
DNode* transform(Node* head) {
    DNode* new_head = malloc(sizeof(DNode));
    Node* cur_node = head;
    DNode* cur_dnode = new_head;
    DNode* nxt = NULL;
    while (cur_node) {
        cur_dnode->value = cur_node->value;
		cur_dnode->next = nxt;
        nxt = cur_dnode;
        if (cur_node->next) {
        	cur_dnode->prev = malloc(sizeof(DNode));
            new_head = cur_dnode->prev;
        } else {
            cur_dnode->prev = NULL;
        }
        cur_dnode = cur_dnode->prev;
        Node* unused = cur_node;
        cur_node = cur_node->next;
        free(unused);
    }
    return new_head;
}
```

## 8.

### (C)

```pseudocode
function getRankOfThird(heap_arr)
	target = arr[3]
	rank = 0
	check_queue = empty queue
	check_queue.enqueue(1)
	while checking is not empty
		chk = check_queue.dequeue()
		if heap_arr[chk] > target
			rank++
			check_queue.enqueue(2*chk)
			check_queue.enqueue(2*chk+1)
		else if heap_arr[chk] == target
			rank++
	return rank
```

