/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name:
 * Email:
 */

#include <stdlib.h>
#include <assert.h>

#include "pq.h"
#include "dynarray.h"

/*
 * struct that stores information for an element of the priority queue
 */
struct pq_element {
  void *data;
  int priority;
};

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 * in addition, you want to define an element struct with both data and priority, 
 * corresponding to the elements of the priority queue. 
 */
struct pq {
  struct dynarray *arr;
};


/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
  struct pq *tmp = (struct pq*)malloc(sizeof(struct pq));
  tmp->arr = dynarray_create();
  return tmp;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
  assert(pq);
  dynarray_free(pq->arr);
  free(pq);
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
  assert(pq);
  return !dynarray_length(pq->arr);
}


/*
 * Helper function to swap elements in a priority queue
 */
void swap(struct pq *pq, int first, int second) {
  struct pq_element* tmp = (struct pq_element*)dynarray_get(pq->arr, first);
  dynarray_set(pq->arr, first, dynarray_get(pq->arr, second));
  dynarray_set(pq->arr, second, tmp);
}

/*
 * Helper function to percolate an element up the heap.
 */
void percolate_up(struct pq *pq, int index) {
  while(index != 0) { // if the current node is the root node, we can't percolate up any further
    int parent = (index-1)/2; // calculate index of parent node
    // if the priority of current node is less than priority of parent node, we don't need to percolate up any further
    if (((struct pq_element*)dynarray_get(pq->arr, index))->priority < ((struct pq_element*)dynarray_get(pq->arr, parent))->priority) {
      break;
    }
    swap(pq, index, parent);
    index = parent;
  }
}

/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, higher priority
 * values are given precedent, and higher place in the queue.  In other words, the
 * element in the priority queue with the highest priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   data - the data value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, higher priority values
 *     should correspond to the first elements.  In other words,
 *     the element in the priority queue with the highest priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* data, int priority) {
  assert(pq);
  struct pq_element *new = (struct pq_element*)malloc(sizeof(struct pq_element)); // Allocate memory for new node
  new->data = data;
  new->priority = priority;
  dynarray_insert(pq->arr, -1, new); // append the new node to the end of the array
  percolate_up(pq, dynarray_length(pq->arr) - 1); // percolate the new node up the heap
}


/*
 * This function should return the data of the first element in a priority
 * queue, i.e. the data associated with the element with highest priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the data of the first item in pq, i.e. the item with
 *   max priority value.
 */
void* pq_max(struct pq* pq) {
  assert(!pq_isempty(pq));
  return ((struct pq_element*)dynarray_get(pq->arr, 0))->data; // max is the root node
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with highest priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with highest priority value.
 */
int pq_max_priority(struct pq* pq) {
  assert(!pq_isempty(pq));
  return ((struct pq_element*)dynarray_get(pq->arr, 0))->priority;
}

/*
 * Helper function to percolate nodes down the heap
 */
void percolate_down(struct pq* pq, int index) {
  while((index+1)*2-1 < dynarray_length(pq->arr)) {
    int left = (index+1)*2-1; // calculate index of left child node
    int right = ((index+1)*2 < dynarray_length(pq->arr)) ? (index+1)*2 : left; // Catch edge case where only a left child node exists
    
    // If the priority of the current node is less than its left or right child
    if (((struct pq_element*)dynarray_get(pq->arr, index))->priority < ((struct pq_element*)dynarray_get(pq->arr, left))->priority || 
        ((struct pq_element*)dynarray_get(pq->arr, index))->priority < ((struct pq_element*)dynarray_get(pq->arr, right))->priority) 
    {
      // Find the child node with the greatest priority and swap
      if (((struct pq_element*)dynarray_get(pq->arr, left))->priority > ((struct pq_element*)dynarray_get(pq->arr, right))->priority) {
        swap(pq, index, left);
        index = left;
      }
      else {
        swap(pq, index, right);
        index = right;
      }
    }
    else {
      break;
    }
  }
}

/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with highest priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   highest priority value.
 */
void* pq_max_dequeue(struct pq* pq) {
  assert(!pq_isempty(pq));
  void *tmp = pq_max(pq); // Data that will be returned
  free((struct pq_element*)dynarray_get(pq->arr, 0)); // free memory allocated to previous root node
  dynarray_set(pq->arr, 0, dynarray_get(pq->arr, -1)); // replace root with last node in heap
  dynarray_remove(pq->arr, -1); // remove the old last node
  percolate_down(pq, 0); // percolate the node down the heap to restore heap property
  return tmp;
}
