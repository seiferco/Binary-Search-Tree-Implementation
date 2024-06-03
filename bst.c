/*
 * This file is where you should implement your binary search tree.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name:
 * Email:
 */

#include <stdlib.h>
#include <stdio.h>
#include "bst.h"
#include "stack.h"

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
  struct bst *bst = malloc(sizeof(struct bst));
  bst->root = NULL;
  return bst;
}

// Helper function for creating new nodes
struct bst_node* create_node(int key, void* value){
  struct bst_node* newNode = malloc(sizeof(struct bst_node));
  newNode->key = key;
  newNode->value = value;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
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
  if(bst == NULL){
    return;
  }
  // free all nodes, then free bst
  bst_free2(bst->root);

  free(bst);
  bst = NULL;
  return;
}

// helper function to free all the nodes in a BST so the root is used recursivly 
void bst_free2(struct bst_node* root){
  // empty tree or leaf node's right and left node no need to free node it's already NULL
  if(root == NULL){
    return;
  }
  // recursivly free all the left and right nodes in the tree
  // no need to clear the data stored in each tho, that is the callers job 
  bst_free2(root->left);
  bst_free2(root->right);
  free(root);
  root = NULL;
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
  size = bst_size2(bst->root, size);
  return size;
}

int bst_size2(struct bst_node* root, int size){
  //Using pre order traversal
  // covers base case if root is NULL return 0
  if(root == NULL){
    return size;
  }
  size++;
  size = bst_size2(root->left, size);
  size = bst_size2(root->right, size);

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
  
  struct bst_node* newNode = create_node(key, value); // new node to be inserted using helper function
  struct bst_node* curr = bst->root;

  // if root is empty, initialize root
  if(bst->root == NULL){
    bst->root = newNode;
    return;
  }

  // If current key is greater than current key, go right but check if NULL first. 
  // If right is NULL, set to new node that was created. Otherwise, continue down the tree until finding the NULL.
  while(1){
    if(key > curr->key){
      if(curr->right == NULL){
        curr->right = newNode;
        return;
      }else {
        curr = curr->right;
      }
    }else if(key < curr->key){
      if(curr->left == NULL){
        curr->left = newNode;
        return;
      }else {
        curr = curr->left;
      }
    }
  }
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
  struct bst_node* removedN = bst_remove2(bst->root, key);
  return;
}

// Helper function for using recursion on removing an element from a binary tree. 
struct bst_node* bst_remove2(struct bst_node* root, int key) {
    if (root == NULL) {
        return root;
    }
    
    if (key > root->key) {
        root->right = bst_remove2(root->right, key);
    } else if (key < root->key) {
        root->left = bst_remove2(root->left, key);
    } else {
        if (root->left == NULL) {
            struct bst_node* temp = root->right;
            free(root); 
            root = NULL;
            return temp; // Return right node
        } else if (root->right == NULL) {
            struct bst_node* temp = root->left;
            free(root); 
            root = NULL;
            return temp; // Return left node
        }
  
        // Find in-order successor
        struct bst_node* curr = root->right;
        while (curr->left != NULL) {
            curr = curr->left;
        }
        
        // Update key of the current node with key of the in-order successor
        root->key = curr->key;
        
        // Remove the in-order successor node from the right subtree
        root->right = bst_remove2(root->right, curr->key);
    }

    // Return the updated root node
    return root;
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
    struct bst_node* curr = bst->root;

    while(curr != NULL){
      if (curr->key == key){
        return curr->value;
      }else if (key < curr->key) {
        curr = curr->left;
      }else {
        curr = curr->right;
      }
    }

}

/*****************************************************************************
 **
 ** BST puzzle functions
 **
 *****************************************************************************/

/*
 * This function should return the height of a given BST, which is the maximum
 * depth of any node in the tree (i.e. the number of edges in the path from
 * the root to that node).  Note that the height of an empty tree is -1 by
 * convention.
 *
 * Params:
 *   bst - the BST whose height is to be computed
 *
 * Return:
 *   Should return the height of bst.
 */
int bst_height(struct bst* bst) {
  int height = bst_height2(bst->root);
  return height;
}

// this is a helper function for sending the root of a bst in order to use recursion to find the max depth of a tree
int bst_height2(struct bst_node* root){


  // my recitation code below
  int leftDepth;
  int rightDepth;

  if (root == NULL)
      return -1;

  if (root->left == NULL)
      return 1 + bst_height2(root->right);
  

  if (root->right == NULL)
      return 1 + bst_height2(root->left);
  

  leftDepth = bst_height2(root->left);
  rightDepth = bst_height2(root->right);
  

  if(leftDepth > rightDepth){
      return 1 + leftDepth;
  } else {
      return 1 + rightDepth;
  }

  if(rightDepth > leftDepth){
    return rightDepth;
  }
    return leftDepth;


}

/*
 * This function should determine whether a specified value is a valid path
 * sum within a given BST.  In other words, this function should check whether
 * the given BST contains any path from the root to a leaf in which the keys
 * sum to the specified value.
 *
 * Params:
 *   bst - the BST whose paths sums to search
 *   sum - the value to search for among the path sums of `bst`
 *
 * Return:
 *   Should return 1 if `bst` contains any path from the root to a leaf in
 *   which the keys add up to `sum`.  Should return 0 otherwise.
 */
int bst_path_sum(struct bst* bst, int sum) {
  // sums is an array that holds all the possible root -> leaf sums
  // Would be better off using a dynamic array if tree was not provided to me but this is hardcoded since I can see the tree size
  // should have 6 paths hence 6 leaves
  int sums[6] = {0}; 
  int sumCalc = 0;
  int temp = 0;
  int hasSum = -1;

  // gather path sums in an array
  temp = bst_path_sum2(bst->root, sums, sumCalc, 0);

  // go check if the value to search for among path of sums equals one of the path sums in tree
  hasSum = foundPath(sums, sum); 

  return hasSum;
}

// helper function to use recursion for bst_pth_sum
// This is a recursive function that traverses a BST left to right
// It adds the key's into sumCalc until it reaches a leaf node indicating the end of a path
// It then stores that path sum into the index of sums[] and then returns to find another path and so on...
// Index is returned each time to know what index of the array/path we are on
int bst_path_sum2(struct bst_node* root, int sums[], int sumCalc, int idx) {
    if(root == NULL) {
        return idx; 
    }

    sumCalc += root->key;

    if(root->left == NULL && root->right == NULL) {
        sums[idx] = sumCalc; // Store sum when leaf node is reached and increment index
        idx++;
        return idx; // Return the updated index
    }
    else {
        idx = bst_path_sum2(root->left, sums, sumCalc, idx);
        idx = bst_path_sum2(root->right, sums, sumCalc, idx);
        return idx; // Return the index after recursion from both subtrees
    }
}

// helper function that iterates through the sums array and compares the sum passed into function
// If there is a match, return 1, otherwise 0 indicating that is not a path sum.
int foundPath(int sums[], int sum){
  for(int i = 0; i < 6; i++){
    if(sums[i] == sum){
      return 1;
    }
  }
  return 0;
}

/*
 * This function should compute a range sum in a given BST.  Specifically, it
 * should compute the sum of all keys in the BST between a given lower bound
 * and a given upper bound.  For full credit, you should not process any subtree
 * whose keys cannot be included in the range sum.
 *
 * Params:
 *   bst - the BST within which to compute a range sum
 *   lower - the lower bound of the range over which to compute a sum; this
 *     should be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound should be included in the sum
 *   upper - the upper bound of the range over which to compute a sum; this
 *     should be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound should be included in the sum
 *
 * Return:
 *   Should return the sum of all keys in `bst` between `lower` and `upper`.
 */
int bst_range_sum(struct bst* bst, int lower, int upper) {
  int total = 0;
  bst_range_sum2(bst->root, lower, upper, &total);
  return total;
}

void bst_range_sum2(struct bst_node* root, int lower, int upper, int *total){
  if(root == NULL){  
    return;
  }
  
  // if the key is in bounds, add it to total, and check left and right subtrees (values can be smaller or larger)
  // if key is less than lower bound, explore right subtree as there may be values that fit in bounds there
  // else if key is greater than upper bound, check left sub-tree, there may be values that fit in bounds
  if(root->key >= lower && root->key <= upper){
    *total += root->key;
    bst_range_sum2(root->left, lower, upper, total);
    bst_range_sum2(root->right, lower, upper, total);
    return;
  }
  else if(root->key < lower){
    bst_range_sum2(root->right, lower, upper, total);
    return;
  }
  else if(root->key > upper){
    bst_range_sum2(root->left, lower, upper, total);
  }
}


/*****************************************************************************
 **
 ** BST iterator definition (extra credit only)
 **
 *****************************************************************************/

/*
 * Structure used to represent a binary search tree iterator.  It contains
 * only a reference to a stack to be used to implement the iterator.
 *
 * You should not modify this structure.
 */
struct bst_iterator {
  struct stack* stack;
};

/*
 * This function should allocate and initialize an iterator over a specified
 * BST and return a pointer to that iterator.
 *
 * Params:
 *   bst - the BST for over which to create an iterator.  May not be NULL.
 */
struct bst_iterator* bst_iterator_create(struct bst* bst) {
  /*
   * FIXME:
   */
  return NULL;
}

/*
 * This function should free all memory allocated to a given BST iterator.
 * It should NOT free any memory associated with the BST itself.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   iter - the BST iterator to be destroyed.  May not be NULL.
 */
void bst_iterator_free(struct bst_iterator* iter) {
  /*
   * FIXME:
   */
  return;
}

/*
 * This function should indicate whether a given BST iterator has more nodes
 * to visit.  It should specifically return 1 (true) if the iterator has at
 * least one more node to visit or 0 (false) if it does not have any more
 * nodes to visit.
 *
 * Param:
 *   iter - the BST iterator to be checked for remaining nodes to visit.  May
 *     not be NULL.
 */
int bst_iterator_has_next(struct bst_iterator* iter) {
  /*
   * FIXME:
   */
  return 0;
}

/*
 * This function should return both the value and key associated with the
 * current node pointed to by the specified BST iterator and advnce the
 * iterator to point to the next node in the BST (in in-order order).
 *
 * Because a function can't return two things, the key associated with the
 * current node should be returned the normal way, while its value should be
 * returned via the argument `value`.  Specifically, the argument `value`
 * is a pointer to a void pointer.  The current BST node's value (a void
 * pointer) should be stored at the address represented by `value` (i.e. by
 * dereferencing `value`).  This will look something like this:
 *
 *   *value = current_node->value;
 *
 * Parameters:
 *   iter - BST iterator.  The key and value associated with this iterator's
 *     current node should be returned, and the iterator should be updated to
 *     point to the next node in the BST (in in-order order).  May not be NULL.
 *   value - pointer at which the current BST node's value should be stored
 *     before this function returns.
 *
 * Return:
 *   This function should return the key associated with the current BST node
 *   pointed to by `iter`.
 */
int bst_iterator_next(struct bst_iterator* iter, void** value) {
  /*
   * FIXME:
   */
  if (value) {
    *value = NULL;
  }
  return 0;
}
