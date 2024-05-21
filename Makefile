mainprog: closest_AVL_tree_tester.o closest_AVL_tree.o
	gcc -g closest_AVL_tree_tester.o closest_AVL_tree.o -o mainprog

closest_AVL_tree_tester.o: closest_AVL_tree_tester.c closest_AVL_tree.c
	gcc -g -c closest_AVL_tree_tester.c

closest_AVL_tree.o: closest_AVL_tree.c closest_AVL_tree.h
	gcc -g -c closest_AVL_tree.c

clean:
	rm -f *.o mainprog
.PHONY: clean