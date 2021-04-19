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



# 2014

## 5.

```pseudocode
function squareDistance(v, u, k)
	dist = 0
	while true
		if v[0] < u[0]
			dist += square(v[1])
			v = v.next
		else if v[0] > u[0]
			dist += square(u[1])
			u = u.next
		else
			dist += square(v[1]-u[1])
			v = v.next
			u = u.next
		
			
```

