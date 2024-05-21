/*
 *  Header file for our closest-AVL (augmented with closest-pair AVL)
 *  tree implementation.
 *
 *  Author: Akshay Arun Bapat.
 *  Based on materials developed by Anya Tafliovich and F. Estrada.
 *
 *  You will NOT be submitting this file. Your code will be tested with the
 *  original version of this file, so make sure you do not modify it!
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#ifndef __closest_AVL_tree_header
#define __closest_AVL_tree_header

typedef struct pair
{
  int lower;            // lower value of the pair
  int upper;            // upper value of the pair
} pair;

typedef struct closest_AVL_node
{
  int key;                  // key stored in this node
  void* value;              // value associated with this node's key
  int height;               // height of tree rooted at this node
  int min;                  // min value in tree rooted at this node
  int max;                  // max value in tree rooted at this node
  struct pair* closest_pair; // closest-pair in tree rooted at this node
  struct closest_AVL_node* left;   // this node's left child
  struct closest_AVL_node* right;  // this node's right child
} closest_AVL_Node;

/*
 * Returns the node, from the tree rooted at 'node', that contains key 'key'.
 * Returns NULL if 'key' is not in the tree.
 */
closest_AVL_Node* search(closest_AVL_Node* node, int key);

/*
 * Inserts the key/value pair 'key'/'value' into the closest-AVL tree rooted
 * at 'node'.  If 'key' is already a key in the tree, updates the value
 * associated with 'key' to 'value'. Returns the root of the resulting tree.
 */
closest_AVL_Node* insert(closest_AVL_Node* node, int key, void* value);

/*
 * Deletes the node with key 'key' from the closest-AVL tree rooted at 'node'.
 * If 'key' is not a key in the tree, the tree is unchanged.
 * Returns the root of the resulting tree.
 */
closest_AVL_Node* delete(closest_AVL_Node* node, int key);

/*
 * Returns the closest pair within the tree rooted at 'node'.
 * Returns NULL if the tree has less than 2 elements.
 */
pair* getClosestPair(closest_AVL_Node* node);

/*
 * Prints the keys of the closest-AVL tree rooted at 'node',
 * in the in-order traversal order.
 */
void printTreeInorder(closest_AVL_Node* node);

/*
 * Frees all memory allocated for a closest-AVL tree rooted at 'node'.
 */
void deleteTree(closest_AVL_Node* node);

#endif
