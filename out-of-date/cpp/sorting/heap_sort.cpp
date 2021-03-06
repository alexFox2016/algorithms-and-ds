#include <cstdio>

/* The HEAP data structure:
 *     - From the first to the 2nd last level, it's a COMPLETE TREE (node has 0
 *     or 2 children). Elements are inserted FROM LEFT->RIGHT in the last level
 *
 *     - Heap property: A[parent(i)] <= A[i] (min-heap)
 *                      A[parent(i)] >= A[i] (max-heap)
 *
 *     - Due to the heap property (above), extract min/max requires O(1) + cost
 *     to maintain the heap property
 *
 *     - Since the heap is a complete binary tree, its height is lg(n). The
 *     implication of this is that any operation in a branch will be O(log(n))
 *
 *     Properties (using arrays):
 *         - given a k-th element, any k > (heap_size / 2) is a LEAF
 *         - For the sake of simplicity, ROOT = A[1] (A[0] = SENTINEL)
 *         - A.length    => Length of A (max capacity)
 *         - A.heap_size => # of values in the heap (0 <= A.heap_size <= A.length)
 *         - parent(i):     A[i >> 1];
 *         - left(i):       A[i << 1];
 *         - right(i):      A[(i << 1) + 1];
 */
int length;
int heap_size;
// int *values; since we are using local pointers, this is not necessary

inline int parent(int i) { return (i >> 1); }
inline int left(int i) { return (i << 1); }
inline int right(int i) { return (i << 1) + 1; }

/* HEAPFY (max-heap)
 * 
 * Running time: O(log(n))
 *
 * Responsible to maintain the HEAP PROPERTY.
 * Assumes the children of i obeys the heap property but it's not guaranteed
 * that i is in the right place.
 *
 * "floats" down the improper element. As we saw previously, it's an operation
 * from a node to the root. Worst case is that the node floats from the root to
 * the leaf, therefore height = log(n).
 */
void heapfy(int *a, int i) {
	int lft = left(i);
	int rght = right(i);
	int largest = i;
	if (lft <= heap_size && a[i] < a[lft])
		largest = lft;
	if (rght <= heap_size && a[largest] < a[rght])
		largest = rght;
	if (largest != i) {
		int tmp = a[i];
		a[i] = a[largest];
		a[largest] = tmp;   // A[largest] has the old A[i] value!
		heapfy(a, largest); // Needs to check if i is in the proper place
	}
}

/* BUILD HEAP
 *
 * Running time: O(n). Because it iterates over n/2 nodes and calls HEAPFY for
 * each of them, we are attempted to say that it's an O(n * log(n)) algorithm.
 * However, mathematical proof shows that this bound can be tighter to O(n).
 * It's jut a matter of summations and getting a better bound.
 *
 * The underlying idea is to call HEAPFY for all internal nodes.
 */
void build(int *a, int n) {
	heap_size = length = n;
	a[0] = -1; // sentinel
	n >>= 1;   // only iterate over non-leaves until reach the root
	while(n >= 1) {
		heapfy(a, n);
		n--;
	}
}

/* Heap Sort
 *
 * Like INSERTION SORT, it's a in-place sorting algorithm
 * Like MERGE SORT, it's a linear-logarithmic sorting O(n * log(n))
 *
 * Unlike the mentioned algorithms, HEAP SORT uses a DATA STRUCTURE to manage
 * information (the HEAP).
 *
 * The underlying idea of HEAP SORT is organizing a list of keys in a MAX-HEAP,
 * then we exchange the ROOT with A[heap_size]. After that is just a matter of
 * excluding the last element and calling HEAPFY to the root.
 */
void heapsort(int *a, int n) {
	build(a, n);
	int i = 1;
	while (i <= heap_size) {
		int tmp = a[heap_size];
		a[heap_size] = a[i];
		a[i] = tmp;
		
		// this HAVE to be decreased before calling HEAPFY and AFTER swapping
		// the values. What would happen if we decrease after calling HEAPFY?
		heap_size--; 

		heapfy(a, i);
	}
}


// Driver based on Figure 6.2, 6.3 from Cormen. Use as input the file test_heap.txt
void print(int *values) {
	for (int i=1; i <= length; i++) printf("%d ", values[i]);
	printf("\n");
}

int main() {
	int n;
	scanf("%d", &n);

	// heap initialization
	int *values = new int[n+1];
	heap_size = 0;
	length = n;
	values[0] = -1; // sentinel

	// inserting elements
	for (int i=1; i <= n; i++) { scanf("%d", (values+i)); heap_size++; };
	heapfy(values, 2);
	print(values);

	// Testing build heap
	scanf("%d", &n);
	int *a = new int[n+1];
	for (int i=1; i <= n; i++) { scanf("%d", (a+i)); };
	build(a, n);
	print(a);

	// Testing heapsort
	printf("Sorting the following heap: ");
	print(values);
	heapsort(values, n);
	print(values);

	printf("Sorting the following heap: ");
	print(a);
	heapsort(a, n);
	print(a);

	delete [] values;
	delete [] a;

	return 0;
}
