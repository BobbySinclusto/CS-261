struct pq* pq_create();
    This function allocates memory for a new priority queue struct, allocates memory
    for the dynamic array that acts as the framework for the heap, then returns the 
    address of the new priority queue.

void pq_free(struct pq* pq);
    This function frees the memory allocated for the dynamic array, then the memory
    allocated for the priority queue.

int pq_isempty(struct pq* pq);
    This function checks whether or not the priority queue is empty by checking
    whether or not the dynamic array contains any elements.

void swap(struct pq *pq, int first, int second);
    This function swaps the element at the index specified by first with the element
    at the index specified by second.

void percolate_up(struct pq *pq, int index);
    This function percolates the element at the given index up the heap. We begin by
    checking whether or not the index is zero, which would indicate the root node.
    While this is not the case, we calculate the index of the paprent node, then
    determine whether the node's priority is less than that of its parent. If it is,
    we don't need to percolate any further, so we break out of the while loop.
    Otherwise, we swap the current node with its parent, and set index to the index
    of the parent node.

void pq_insert(struct pq* pq, void* data, int priority);
    This function creates a new element with a specified data value and priority.
    First we allocate memory for the new node and set its members to the given values.
    Next we append the new node to the end of the dynamic array. Finally, we percolate
    the new node up the heap, so that the heap property is preserved.

void* pq_max(struct pq* pq);
    This function returns the value of the element with the highest priority value.
    This is easy, because that's just the value of the root node.

int pq_max_priority(struct pq* pq);
    This function returns the priority of the element with the highest priority. Again,
    this is just the root node.

void percolate_down(struct pq* pq, int index);
    This function percolates the node at the given index down the heap.  First we
    calculate the index of the left and right children, then swap the node at the 
    current index with the child node with the greatest priority, as long as that
    priority is greater than the current node's priority. Then we update the index to
    whatever the index of the parent node is.

void* pq_max_dequeue(struct pq* pq);
    This function returns the value of the element with the maximum priority and removes
    that element from the queue. First we create a temporary pointer to hold the address
    of the value to return. Next we free the memory allocated to the previous root node
    and replace it with the last node in the heap. After removing the old last node, we
    percolate the new root node down the heap to restore the heap property.