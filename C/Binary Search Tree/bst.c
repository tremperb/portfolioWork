/*
 * This file is where you should implement your binary search tree.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name: Brayden Tremper
 * Email: tremperb@oregonstate.edu
 */

#include <stdlib.h>

#include "bst.h"

/*
 * This structure represents a single node in a BST.  In addition to containing
 * pointers to its two child nodes (i.e. `left` and `right`), it contains two
 * fields representing the data stored at this node.  The `key` field is an
 * integer value that should be used as an identifier for the data in this
 * node.  Nodes in the BST should be ordered based on this `key` field.  The
 * `value` field stores data associated with the key.
 *
 * You should not modify this structure.
 */
struct bst_node {
  int key;
  void* value;
  struct bst_node* left;
  struct bst_node* right;
};


/*
 * This structure represents an entire BST.  It specifically contains a
 * reference to the root node of the tree.
 *
 * You should not modify this structure.
 */
struct bst {
  struct bst_node* root;
};

/*
 * This function should allocate and initialize a new, empty, BST and return
 * a pointer to it.
 */
struct bst* bst_create() {
  struct bst* newTree = malloc(sizeof(struct bst));
  newTree->root = NULL;

  return newTree;
}

/*
 * This function should free the memory associated with a BST.  While this
 * function should up all memory used in the BST itself, it should not free
 * any memory allocated to the pointer values stored in the BST.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   bst - the BST to be destroyed.  May not be NULL.
 */
void bst_free(struct bst* bst) {
  delete_node(bst->root);
  free(bst);
  return;
}

void delete_node(struct bst_node* node) {
  if(node == NULL) {
    return;
  } 
  else {
    delete_node(node->left);
    delete_node(node->right);

    free(node);
  }
}

/*
 * This function should return the total number of elements stored in a given
 * BST.
 *
 * Params:
 *   bst - the BST whose elements are to be counted.  May not be NULL.
 */
int bst_size(struct bst* bst) {
  int size = 0;
  struct bst_node* rightTemp = bst->root;
  struct bst_node* leftTemp = bst->root;
  if(bst->root != NULL) {
    size++;               //if it isn't NULL so add 1 for our starter, if NULL size will be 0
  }
  while(leftTemp != NULL) { //check left side
    leftTemp = leftTemp->left;
    size++;
  }

  while(rightTemp != NULL) { //check right side
    rightTemp = rightTemp->right;
    size++;
  }

  return size;
}

/*
 * This function should insert a new key/value pair into the BST.  The key
 * should be used to order the key/value pair with respect to the other data
 * stored in the BST.  The value should be stored along with the key, once the
 * right location in the tree is found.
 *
 * Params:
 *   bst - the BST into which a new key/value pair is to be inserted.  May not
 *     be NULL.
 *   key - an integer value that should be used to order the key/value pair
 *     being inserted with respect to the other data in the BST.
 *   value - the value being inserted into the BST.  This should be stored in
 *     the BST alongside the key.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void bst_insert(struct bst* bst, int key, void* value) {
  
  bst->root = nodeLooper(bst->root, value, key);
  
  return;
}

struct bst_node* nodeLooper(struct bst_node* node, void* val, int key) {
  if(node == NULL) {
    
    return newNode(val, key); 
  }
  else if(key < node->key) {
    node->left = nodeLooper(node->left, val, key);
  }
  else {
    node->right = nodeLooper(node->right, val, key);
  }

  return node;
}

struct bst_node* newNode(void* val, int key) {
  struct bst_node* node = malloc(sizeof(struct bst_node));
  node->value = val;
  node->key = key;
  node->left = NULL;
  node->right = NULL;

  return node;
}

/*
 * This function should remove a key/value pair with a specified key from a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should remove the first one it encounters (i.e. the one closest to
 * the root of the tree).
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair to be removed from the BST.
 */
void bst_remove(struct bst* bst, int key) {
  struct bst_node* root = bst->root;
  struct bst_node* parent = bst->root;
  while(root != NULL) { //tried iteratiive approach for this one
    if(key == root->key) {  //if equal then we found it
      remove_node(root, parent);
      break;
    }
    else if(key < root->key) {  //if its less then go to left side
      parent = root;
      root = root->left;
    }
    else {
      parent = root;
      root = root->right; //otherwise its greater sp update our root
    }
  }

  return;
}

/*
 * Remove our found node based on the possible scenarios.
 * takes in our matched node and that nodes parent.
 */
void remove_node(struct bst_node* node, struct bst_node* parent) {
  
  if(node->left == NULL && node->right == NULL) { //no children so free
    free(node);
  }
  else if (node->left != NULL && node->right != NULL) { //has 2 children
   
   struct bst_node* minNode = node->right; 
  
    while (minNode && minNode->left != NULL) {
       parent = minNode;
       minNode = minNode->left; //get our succesor
    }

    struct bst_node* temp = minNode;
    node->key = temp->key; //store our data
    node->value = temp->value; //store our data
   
    remove_node(temp, parent); //but now we have to delete the node which replaced the other so go back and delete it
    
  }
  else if(node->left != NULL && node->right == NULL) { //1 left child. 
    if(parent->left->key == node->key) {
        parent->left = node->left;
        free(node);
        node = parent->left;
    }
    else {
        parent->right = node->left;
        free(node);
        node = parent->right;
    }
  }
  else if(node->right != NULL && node->left == NULL) {  //1 right child
    if(parent->left->key == node->key) {  //we know the parent but not whether the childs node is on right or left of it
        parent->left = node->right; //value is on left of parent, so make parents left that next node
        free(node); //free the current
        node = parent->left;  //reinitialize
    }
    else {
        parent->right = node->right;
        free(node);
        node = parent->right;
    } 
  }
}

/*
 * This function should return the value associated with a specified key in a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should return the first one it encounters (i.e. the one closest to
 * the root of the tree).  If the BST does not contain the specified key, this
 * function should return NULL.
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair whose value is to be returned.
 *
 * Return:
 *   Should return the value associated with the key `key` in `bst` or NULL,
 *   if the key `key` was not found in `bst`.
 */
void* bst_get(struct bst* bst, int key) {
  
  struct bst_node* root = bst->root;
  
  while(root != NULL) { //tried iteratiive approach for this one
    if(key == root->key) {  //if equal then we found it
      return root->value;
    }
    else if(key < root->key) {  //if its less then go to left side
      root = root->left;
    }
    else {
      root = root->right; //otherwise its greater sp update our root
    }
  }

  return NULL;
}
