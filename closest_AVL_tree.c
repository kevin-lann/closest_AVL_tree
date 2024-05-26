/*
 *  closest_AVL (augmented with closest-pair AVL) tree implementation.
 *  Author: Akshay Arun Bapat.
 *  Based on materials developed by Anya Tafliovich and F. Estrada.
 */

#include "closest_AVL_tree.h"

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
 * Returns the min key in the tree rooted at node 'node'.
 * Returns INT_MAX if 'node' is NULL.  Note: this should be an O(1) operation.
 */
int getMin(closest_AVL_Node* node) {
  return node ? node->min : INT_MAX;
}

/*
 * Returns the max key in the tree rooted at node 'node'.
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
  int h_left = height(node->left), h_right = height(node->right);
  node->height = 1 + (h_left > h_right ? h_left : h_right);
}

/*
 * Updates the min key of the tree rooted at node 'node' based on the
 * min value of its children. Note: this should be an O(1) operation.
 */
void updateMin(closest_AVL_Node* node) {
  int left = getMin(node->left);
  node->min = left < node->key ? left : node->key;
}

/*
 * Updates the max key of the tree rooted at node 'node' based on the
 * max value of its children. Note: this should be an O(1) operation.
 */
void updateMax(closest_AVL_Node* node) {
  int right = getMax(node->right);
  node->max = node->key > right ? node->key : right;
}

/*
 * Updates the closest pair of the tree rooted at node 'node' based on the
 * values from its children. Note: this should be an O(1) operation.
 */
void updateClosestPair(closest_AVL_Node* node) {
  if (!node->left && !node->right) {
    node->closest_pair = NULL;
  }

  int smallest_diff = INT_MAX;
  int leftUpper, leftLower, rightUpper, rightLower;
  int *nodeUpper, *nodeLower;

  // check for closest pair existence
  if(!node->closest_pair) {
    node->closest_pair = (pair*)malloc(sizeof(pair));
  }
  nodeUpper = &(node->closest_pair->upper);
  nodeLower = &(node->closest_pair->lower);

  if (node->left) {
    if (node->left->closest_pair) {
      leftUpper = node->left->closest_pair->upper;
      leftLower = node->left->closest_pair->lower;
    }
    else {
      leftUpper = 0;
      leftLower = 0;
    }
  }
  if (node->right) {
    if (node->right->closest_pair) {
      rightUpper = node->right->closest_pair->upper;
      rightLower = node->right->closest_pair->lower;
    }
    else {
      rightUpper = 0;
      rightLower = 0;
    }
  }
  

  // -- Find minimum of following 4 values and update node->pair accordingly --
  // 1. closest_pair of left subtree (if it exists)
  if(node->left && leftUpper != leftLower) {
    *nodeUpper = leftUpper;
    *nodeLower = leftLower;
    smallest_diff = leftUpper - leftLower;
  }
  // 2. closest_pair of right subtree (if it exists)
  if (node->right && rightUpper != rightLower && rightUpper - rightLower < smallest_diff) {
    *nodeUpper = rightUpper;
    *nodeLower = rightLower;
    smallest_diff = rightUpper - rightLower;
  }
  // 3. Check difference of node's key and left child's max (if it exists)
  if (node->left && node->key - node->left->max < smallest_diff) {
    *nodeUpper = node->key;
    *nodeLower = node->left->max;
    smallest_diff = node->key - node->left->max;
  }
  // 4. Check difference of node's key and right child's min (if it exists)
  if (node->right && node->right->min - node->key < smallest_diff) {
    *nodeUpper = node->right->min;
    *nodeLower = node->key;
    smallest_diff = node->right->min - node->key;
  }
}

/*
 * Returns the balance factor (height of left subtree - height of right
 * subtree) of node 'node'. Returns 0 if node is NULL.  Note: this should be
 * an O(1) operation.
 */
int balanceFactor(closest_AVL_Node* node) {
  return node ? height(node->left) - height(node->right) : 0;
}

/*
 * Returns the result of performing the corresponding rotation in the
 * closest_AVL tree rooted at 'node'.
 */
// single rotations: right/clockwise
closest_AVL_Node* rightRotation(closest_AVL_Node* node){
  closest_AVL_Node* leftChild = node->left;
  closest_AVL_Node* s = node->left->right;

  node->left = s;
  leftChild->right = node;

  updateHeight(node);
  updateMin(node);
  updateMax(node);

  updateHeight(leftChild);
  updateMin(leftChild);
  updateMax(leftChild);

  updateClosestPair(node);
  updateClosestPair(leftChild);

  return leftChild;
}

// single rotations: left/counter-clockwise
closest_AVL_Node* leftRotation(closest_AVL_Node* node) {
  closest_AVL_Node* rightChild = node->right;
  closest_AVL_Node* s = node->right->left;

  node->right = s;
  rightChild->left = node;

  updateHeight(node);
  updateMin(node);
  updateMax(node);

  updateHeight(rightChild);
  updateMin(rightChild);
  updateMax(rightChild);

  updateClosestPair(node);
  updateClosestPair(rightChild);

  return rightChild;
}

// double rotation: right/clockwise then left/counter-clockwise
closest_AVL_Node* rightLeftRotation(closest_AVL_Node* node) {
  node->right = rightRotation(node->right);
  return leftRotation(node);
}

// double rotation: left/counter-clockwise then right/clockwise
closest_AVL_Node* leftRightRotation(closest_AVL_Node* node) {
  node->left = leftRotation(node->left);
  return rightRotation(node);
}

/*
 * Rebalances the tree rooted at 'node' and returns the rebalanced node.
 */
closest_AVL_Node* rebalance(closest_AVL_Node* node) {
  // left heavy
  if (balanceFactor(node) > 1) {
    closest_AVL_Node* x = node->left;
    if (balanceFactor(x) >= 0) {
      node = rightRotation(node);
    }
    else {
      node = leftRightRotation(node);
    }
  }
  // right heavy
  else if (balanceFactor(node) < -1) {
    closest_AVL_Node* x = node->right;
    if (balanceFactor(x) <= 0) {
      node = leftRotation(node);
    }
    else {
      node = rightLeftRotation(node);
    }
  }
  return node;
}

/*
 * Returns the successor node of 'node'.
 */
closest_AVL_Node* successor(closest_AVL_Node* node) {
  if (node->right) {
    node = node->right;
  }
  else {
    return NULL;
  }
  while (node->left) {
    node = node->left;
  }
  return node;
}

/*
 * Creates and returns a closest_AVL tree node with key 'key', value 'value',
 * height 1, min and max value 'key', and left, right and closest_pair NULL.
 */
closest_AVL_Node* createNode(int key, void* value) {
  closest_AVL_Node* node = (closest_AVL_Node*)malloc(sizeof(closest_AVL_Node));
  if (!node) {
    return NULL;
  }

  node->key = key;
  node->value = value;
  node->height = 1;
  node->min = key;
  node->max = key;
  node->left = NULL;
  node->right = NULL;
  node->closest_pair = NULL;

  return node;
}

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
  if (!node || node->key == key) {
    return node;
  }
  if (node->key < key) {
    return search(node->right, key);
  }
  else {
    return search(node->left, key);
  }
}

closest_AVL_Node* insert(closest_AVL_Node* node, int key, void* value)
{
  // insertion
  if(!node) {
    closest_AVL_Node* newNode = createNode(key, value);
    return newNode;
  }
  if (key < node->key) {
    node->left = insert(node->left, key, value);
  }
  else if (key > node->key) {
    node->right = insert(node->right, key, value);
  }
  // update height
  updateHeight(node);

  node = rebalance(node);
  
  updateMin(node);
  updateMax(node);
  updateClosestPair(node);
  
  return node;
}

closest_AVL_Node* delete(closest_AVL_Node* node, int key)
{
  if (!node) {
    return node;
  }

  if (key < node->key) {
    node->left = delete(node->left, key);
  }
  else {
    node->right = delete(node->right, key);
  }
  
  if (key == node->key) {
    // 0 or 1 child
    if (!node->left) {
      closest_AVL_Node* tmp = node->right;
      free(node);
      return tmp;
    }
    else if (!node->right) {
      closest_AVL_Node* tmp = node->left;
      free(node);
      return tmp;
    }
    // 2 children
    else {
      closest_AVL_Node* suc = successor(node);
      int sucKey = suc->key;
      void *sucVal = suc->value;
      node->right = delete(node->right, suc->key);
      node->key = sucKey;
      node->value = sucVal;
    }
  }

  updateHeight(node);

  node = rebalance(node);

  updateMin(node);
  updateMax(node);
  updateClosestPair(node);
  
  return node;
}

/*************************************************************************
 ** Required functions
 ** Must run in O(1)
 *************************************************************************/

pair* getClosestPair(closest_AVL_Node* node)
{
  return node->closest_pair ? node->closest_pair : NULL;
}
