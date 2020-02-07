/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Brayden Tremper
 * Email: Tremperb@oregonstate.edu
 */

#include <stdlib.h>

#include "pq.h"
#include "dynarray.h"


/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq {
  struct dynarray* arr;
};

/*
 * Maybe something like this
 */
struct pq_node {
  void* val;
  int priority;
};


/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {

  struct pq* queue = malloc(sizeof(struct pq)); //create our queue
  queue->arr = dynarray_create(); //create our array

  return queue;
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
  
  dynarray_free(pq->arr);
  free(pq);
  
  return;
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
  if(dynarray_size(pq->arr) == 0) {
    return 1;
  }
  return 0;
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* value, int priority) {
  struct pq_node* node = malloc(sizeof(struct pq_node));  //create our node
  node->priority = priority;  //assign the values
  node->val = value;
  dynarray_insert(pq->arr, node); //Inserts our node at end of array
  
  /////////////////////////
  //Now we need to percolate to adjust elements in array based on priority
  //smallest key at top then go left to right(kinda)
  int parent_idx;
  int size = dynarray_size(pq->arr) - 1;

  struct pq_node* parent; //good
  
  while(1 == 1) {
    parent_idx = size / 2;  //divide size by 2 each time don't need left and right for insert function
    parent = dynarray_get(pq->arr, parent_idx); //get the node from the parents index

    if(node->priority < parent->priority) {   //if our nodes priority is less than parents then switch
      
      dynarray_set(pq->arr, size, parent);
      dynarray_set(pq->arr, parent_idx, node);
      size = parent_idx;  
    }
    else {
      break;  //at right spot so break
    }
  }
 
  return;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) { 
  struct pq_node* node = dynarray_get(pq->arr, 0); //get our first node

  return node->val; //return that nodes value
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
  struct pq_node* node = dynarray_get(pq->arr, 0); //get our first node

  return node->priority;  //return that nodes priority value
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {
  int size = dynarray_size(pq->arr) - 1;
  struct pq_node* first = dynarray_get(pq->arr, 0);
  struct pq_node* last = dynarray_get(pq->arr, size);
  dynarray_set(pq->arr, 0, last); //reset our first node with our last
  dynarray_remove(pq->arr, size); //now remove the last element that was there
  ////////////

  //Now we need to percolate that element back down
  if(dynarray_size(pq->arr) > 0) {
    struct pq_node* parent = dynarray_get(pq->arr, 0);
    struct pq_node* child;
    int child_idx;
    int start_idx = 0;
    while(1 == 1) { //infinite loop keeps going 
      int left_idx = (start_idx*2) + 1; //get our starting index for our left node 
      int right_idx = (start_idx*2) + 2; //get starting index for right node
      if(right_idx >= dynarray_size(pq->arr)) {   //if our right index has reached our array bounds
        if(left_idx >= dynarray_size(pq->arr)) {  //still possible left is okay so check that too
          break;  //If both nodes are out of array bounds break 
        }
        else {    //otherwise left is still in 
          child_idx = left_idx;   //so our child index is automatically our left 
          child = dynarray_get(pq->arr, left_idx);  //get the node for that child and jump to swapping it
        }
      } 
      else {  //both nodes are within the bounds
        struct pq_node* left = dynarray_get(pq->arr, left_idx); //get our left
        struct pq_node* right = dynarray_get(pq->arr, right_idx); //get our right
        if(left->priority < right->priority) {  //if the lefts priority is less than rights go that side
          child_idx = left_idx; //Now we know we are going to left so make that our child
          child = left;
        }
        else {  //otherwise we are on right
          child_idx = right_idx;
          child = right;
        }
      }
      //now we know where to swap the nodes

      if(parent->priority > child->priority) {  //swap only if the parents is more since its a minimizing heap
        dynarray_set(pq->arr, start_idx, child);  //make the node of the starting index for that parent now the child
        dynarray_set(pq->arr, child_idx, parent); //make the node at the childs index now equal to the parent
        start_idx = child_idx;  //update our new parents value to keep percolating down the tree
      }
      else {
        break;  //break if at right spot (could do this in the while loop but i like it this way)
      }
    }
  }
  void* firstVal = first->val;  //temp to hold our value so we can free it
  free(first);  //actually remove the value that was stored in the node in the array
  return firstVal; //return the value that was removed
}

