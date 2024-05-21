/*
 *  Some light testing of our closest_AVL tree implementation.
 *  Note that you will need to add your own, much more extensive,
 *  testing to ensure correctness of your code.
 *
 *  Author: Akshay Arun Bapat.
 *  Based on materials developed by Anya Tafliovich and F. Estrada.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "closest_AVL_tree.h"

#define MAX_LIMIT 1024

closest_AVL_Node* createTree(FILE* f);
void testTree(closest_AVL_Node* root);
void printTreeReport(closest_AVL_Node* root);

int main(int argc, char* argv[])
{
  closest_AVL_Node* root = NULL;

  // If user specified a file for reading, create a tree with keys from it.
  if (argc > 1)
  {
    FILE* f = fopen(argv[1], "r");
    if (f == NULL)
    {
      fprintf(stderr, "Unable to open the specified input file: %s\n", argv[1]);
      exit(0);
    }
    root = createTree(f);
    fclose(f);
  }
  else
  {
    printf("You did not specify an input file.");
    printf(" We will start with an empty tree.\n");
  }

  testTree(root);
  return 0;
}

closest_AVL_Node* createTree(FILE* f)
{
  char line[MAX_LIMIT];
  int key = 0;
  closest_AVL_Node* root = NULL;

  while (fgets(line, MAX_LIMIT, f)) // read next line
  {
    key = atoi(line);
    printf("read %d\n", key);
    root = insert(root, key, NULL);  // no values for this simple tester
    printTreeReport(root);
  }
  return root;
}

void customTest(closest_AVL_Node* root) {
  printf("Height of root: %d\n", height(root));
}

void testTree(closest_AVL_Node* root)
{
  char line[MAX_LIMIT];
  closest_AVL_Node* node = NULL;

  while (1)
  {
    printf("Choose a command:");
    printf(" (s)earch, (i)nsert, (d)elete, (c)losest_pair, (q)uit\n");
    fgets(line, MAX_LIMIT, stdin);
    if (line[0] == 'q') // quit
    {
      printf("Quit selected. Goodbye!\n");
      deleteTree(root);
      return;
    }
    if (line[0] == 's') // search
    {
      printf("Search selected. Enter key to search for: ");
      fgets(line, MAX_LIMIT, stdin);
      node = search(root, atoi(line));
      if (node != NULL)
      {
        printf("Key %d was found at height %d, subtree min/max (%d / %d).\n",
            node->key, node->height, node->min, node->max);
      }
      else
      {
        printf("This key is not in the tree.\n");
      }
    }
    else if (line[0] == 'i') // insert
    {
      printf("Insert selected. Enter key to insert");
      printf(" (no values in this simple tester): ");
      fgets(line, MAX_LIMIT, stdin);
      root = insert(root, atoi(line), NULL);
      printTreeReport(root);
    }
    else if (line[0] == 'd') // delete
    {
      printf("Delete selected. Enter key to delete: ");
      fgets(line, MAX_LIMIT, stdin);
      root = delete(root, atoi(line));
      printTreeReport(root);
    }
    else if (line[0] == 'c') // closest_pair
    {
      printf("Get closest pair selected.");
      pair* p = getClosestPair(root);
      if (p != NULL)
      {
        printf("Closest pair found as (%d, %d).\n", p->lower, p->upper);
      }
      else
      {
        printf("Tree has less than 2 values");
      }
    }
    else if (line[0] == 't') { // my custom tests
      printf("Custom tests selected\n");
      customTest(root);
    }
  }
}

void printTreeReport(closest_AVL_Node* root)
{
  printf("** The tree is now:\n");
  printTreeInorder(root);
  printf("**\n");
}
