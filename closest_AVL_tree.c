/*
 *  closest_AVL (augmented with closest-pair AVL) tree implementation.
 *  Author: Akshay Arun Bapat.
 *  Based on materials developed by Anya Tafliovich and F. Estrada.
 */

#include "closest_AVL_tree.h"
#include <math.h>

/*************************************************************************
 ** Suggested helper functions -- part of starter code
 *************************************************************************/

/*
 * Returns the height (number of nodes on the longest root-to-leaf path) of
 * the tree rooted at node 'node'. Returns 0 if 'node' is NULL.  Note: this
 * should be an O(1) operation.
 */
int height(closest_AVL_Node* node) {
  return node ? node->height : 0;
}

/*
 * Returns the min value in the tree rooted at node 'node'.
 * Returns INT_MAX if 'node' is NULL.  Note: this should be an O(1) operation.
 */
int getMin(closest_AVL_Node* node) {
  return node ? node->min : INT_MAX;
}

/*
 * Returns the max value in the tree rooted at node 'node'.
 * Returns INT_MIN if 'node' is NULL.  Note: this should be an O(1) operation.
 */
int getMax(closest_AVL_Node* node) {
  return node ? node->max : INT_MIN;
}

/*
 * Updates the height of the tree rooted at node 'node' based on the heights
 * of its children. Note: this should be an O(1) operation.
 */
void updateHeight(closest_AVL_Node* node) {
  node->height = height(node->left) - height(node->right);
}

/*
 * Updates the min value of the tree rooted at node 'node' based on the
 * min value of its children. Note: this should be an O(1) operation.
 */
void updateMin(closest_AVL_Node* node) {
  int left = getMin(node->left);
  int right = getMin(node->right);
  node->min = left < right ? left : right;
}

/*
 * Updates the max value of the tree rooted at node 'node' based on the
 * max value of its children. Note: this should be an O(1) operation.
 */
void updateMax(closest_AVL_Node* node) {
  int left = getMax(node->left);
  int right = getMax(node->right);
  node->min = left > right ? left : right;
}

/*
 * Updates the closest pair of the tree rooted at node 'node' based on the
 * values from its children. Note: this should be an O(1) operation.
 */
void updateClosestPair(closest_AVL_Node* node) {
  int left_diff = node->left->pair->upper - node->left->pair->lower;
  int right_diff = node->right->pair->upper - node->right->pair->lower;
  int node_diff_left = node->key - node->left->key;
  int node_diff_right = node->right->key - node.key;

  // Find minimum of the above 4 values and update node->pair accordingly
  
  node->pair->upper = node->left->pair->upper;
  node->pair->lower = node->left->pair->lower;
  int cur_diff = left_diff

  if (right_diff < cur_diff) {
    node->pair->upper = node->right->pair->upper;
    node->pair->lower = node->right->pair->lower;
    cur_diff = right_diff
  }
  if (node_diff_left < cur_diff) {
    node->pair->upper = node->key;
    node->pair->lower = node->left->key;
    cur_diff = node_diff_left
  }
  if (node_diff_right < cur_diff) {
    node->pair->upper = node->right->key;
    node->pair->lower = node->key;
  }
}

/*
 * Returns the balance factor (height of left subtree - height of right
 * subtree) of node 'node'. Returns 0 if node is NULL.  Note: this should be
 * an O(1) operation.
 */
int balanceFactor(closest_AVL_Node* node);

/*
 * Returns the result of performing the corresponding rotation in the
 * closest_AVL tree rooted at 'node'.
 */
// single rotations: right/clockwise
closest_AVL_Node* rightRotation(closest_AVL_Node* node);
// single rotations: left/counter-clockwise
closest_AVL_Node* leftRotation(closest_AVL_Node* node);
// double rotation: right/clockwise then left/counter-clockwise
closest_AVL_Node* rightLeftRotation(closest_AVL_Node* node);
// double rotation: left/counter-clockwise then right/clockwise
closest_AVL_Node* leftRightRotation(closest_AVL_Node* node);

/*
 * Returns the successor node of 'node'.
 */
closest_AVL_Node* successor(closest_AVL_Node* node);

/*
 * Creates and returns a closest_AVL tree node with key 'key', value 'value',
 * height 1, min and max value 'value', and left, right and closest_pair NULL.
 */
closest_AVL_Node* createNode(int key, void* value);

/*************************************************************************
 ** Provided functions
 *************************************************************************/

void printTreeInorder_(closest_AVL_Node* node, int offset)
{
  if (node == NULL)
  {
    return;
  }
  printTreeInorder_(node->right, offset + 1);
  if (node->left == NULL && node->right == NULL)
  {
    printf("%*s %d [%d / %d / %d / NULL]\n", offset, "",
        node->key, node->height, node->min, node->max);
  }
  else
  {
    printf("%*s %d [%d / %d / %d / (%d, %d)]\n", offset, "",
        node->key, node->height, node->min, node->max,
        node->closest_pair->lower, node->closest_pair->upper);
  }
  printTreeInorder_(node->left, offset + 1);
}

void printTreeInorder(closest_AVL_Node* node)
{
  printTreeInorder_(node, 0);
}

void deleteTree(closest_AVL_Node* node)
{
  if (node == NULL)
  {
    return;
  }
  deleteTree(node->left);
  deleteTree(node->right);
  free(node);
}

/*************************************************************************
 ** Required functions
 ** Must run in O(log n) where n is the number of nodes in a tree rooted
 **  at 'node'.
 *************************************************************************/

closest_AVL_Node* search(closest_AVL_Node* node, int key)
{
  return NULL;
}

closest_AVL_Node* insert(closest_AVL_Node* node, int key, void* value)
{
  return NULL;
}

closest_AVL_Node* delete(closest_AVL_Node* node, int key)
{
  return NULL;
}

/*************************************************************************
 ** Required functions
 ** Must run in O(1)
 *************************************************************************/

pair* getClosestPair(closest_AVL_Node* node)
{
  return NULL;
}
