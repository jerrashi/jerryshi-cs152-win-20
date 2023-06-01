#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"
#include "bst.h"
#include "hw7.h"

#define BUFSIZE 1024

int main(int argc, char *argv[])
{
        if (sizeof(*argv) == 0)
        {
                fprintf(stderr, "ERROR: must include one "
                                "filename");
                return 0;
        }

        bst* bst_address = read_memory_blocks(argv[1], memory_addr_cmp);
        bst* bst_size = read_memory_blocks(argv[1], memory_size_cmp);

        #ifndef DEBUG
        printf("\nBST sorted by address:");
        inorder_traversal(bst_address->root, memory_print);
        printf("\nBST sorted by size:");
        bst_inorder_traversal(bst_size, memory_print);
        
	printf("\n ---------TESTING SEARCH--------------");
	memory * mem1 = memory_new(1, 200);
	node * search1 = (node *)bst_search(bst_size, mem1);
	printf("\nEXPECTED: address 1, size 200\n");
	memory_print(search1->data);

        memory * mem2 = memory_new(4, 100);
        node * search2 = (node *)bst_search(bst_address, mem2);
        printf("\nEXPECTED: address 4, size 100\n");
        memory_print(search2->data);

        memory * mem3 = memory_new(5, 150);
        node * search3 = (node *)bst_search(bst_address, mem3);
        printf("\nEXPECTED: address 5, size 150\n");
        memory_print(search3->data);


	printf("\n ---------TESTING DELETE---------------");
	/*
	bst_delete(bst_size, mem1);
	printf("after deleting 1, 200");
	bst_inorder_traversal(bst_size, memory_print);
	*/
        
	bst_delete(bst_size, mem2);
        printf("\nafter deleting 4, 100\n");
        bst_inorder_traversal(bst_size, memory_print);

        /*
	node_delete(bst_size->root, mem3, memory_size_cmp);
        printf("after deleting 5, 150");
        bst_inorder_traversal(bst_size, memory_print);

	node_delete(bst_address->root, mem3, memory_addr_cmp);
        printf("after deleting 5, 150");
        bst_inorder_traversal(bst_address, memory_print);

        node_delete(bst_address->root, mem1, memory_addr_cmp);
        printf("after deleting 1, 200");
        bst_inorder_traversal(bst_address, memory_print);

        node_delete(bst_address->root, mem2, memory_addr_cmp);
        printf("after deleting 4, 100");
        bst_inorder_traversal(bst_address, memory_print);

        bst_delete(bst_size, mem1);
        printf("after deleting 1, 200 (edge case)");
        bst_inorder_traversal(bst_size, memory_print);
	*/
	#endif
        return 1;
}

