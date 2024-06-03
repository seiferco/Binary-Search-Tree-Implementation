/*
 * This file contains the definition of the interface for the binary search
 * tree you'll implement.  You should not modify anything in this file.  You
 * can find descriptions of the binary search tree functions, including their
 * parameters and their return values, in bst.c.
 */

#ifndef __BST_H
#define __BST_H


/*
 * Structure used to represent a binary search tree.
 */
struct bst;

/*
 * Basic binary search tree interface function prototypes.  Refer to bst.c for
 * documentation about each of these functions.
 */
struct bst* bst_create();
struct bst_node* create_node(int key, void* value);
void bst_free(struct bst* bst);
void bst_free2(struct bst_node* root);
int bst_size(struct bst* bst);
int bst_size2(struct bst_node* root, int size);
void bst_insert(struct bst* bst, int key, void* value);
void bst_remove(struct bst* bst, int key);
struct bst_node* bst_remove2(struct bst_node* root, int key);
void* bst_get(struct bst* bst, int key);

/*
 * Binary search tree "puzzle" function prototypes.  Refer to bst.c for
 * documentation about each of these functions.
 */
int bst_height(struct bst* bst);
int bst_height2(struct bst_node* root);
int bst_path_sum(struct bst* bst, int sum);
int bst_path_sum2(struct bst_node* root, int sums[], int sumCalc, int idx);
int foundPath(int sums[], int sum);
int bst_range_sum(struct bst* bst, int lower, int upper);
void bst_range_sum2(struct bst_node* root, int lower, int upper, int *total);


/*
 * Structure used to represent a binary search tree iterator.
 */
struct bst_iterator;

/*
 * Binary search tree iterator interface prototypes.  Refer to bst.c for
 * documentation about each of these functions.
 */
struct bst_iterator* bst_iterator_create(struct bst* bst);
void bst_iterator_free(struct bst_iterator* iter);
int bst_iterator_has_next(struct bst_iterator* iter);
int bst_iterator_next(struct bst_iterator* iter, void** value);

#endif
