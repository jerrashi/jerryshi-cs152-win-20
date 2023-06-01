#ifndef HW7_H
#define HW7_H

/* reads in a file and creates a binary search tree from data
 * inputs:
 *   filename - name of file
 *   cmp - function pointer of compare function to be used
 * outputs:
 *   rv - pointer to created binary search tree
 */
bst* read_memory_blocks(char *filename, int (*cmp)
                (const void* x, const void* y));

#endif
