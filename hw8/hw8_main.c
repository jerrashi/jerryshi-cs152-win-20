#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"
#include "bst.h"
#include "my_alloc.h"
#include "llist.h"

int main()
{
	extern bst* avail_mem;
	
	
	//test allocate_memory_page
	printf("\nTESTING: allocate_memory_page\n");
	memory * new_mem = allocate_memory_page();
	memory_print(new_mem);
	printf("\n----------------------------------\n");

        //test init_alloc
        printf("\nTESTING: init_alloc and first my_malloc\n");
        init_alloc();
        init_alloc(); //error case
        my_malloc(10); //edge case, bst is empty
        inorder_traversal(avail_mem->root, memory_print);
	printf("\n----------------------------------\n");

	//test split_memory and my_free and merge_memory
	printf("\nTESTING: split_memory\n");
	void * throwaway = split_memory(new_mem, 128);
	memory_print(new_mem);
	printf("\nTESTING: my_free\n");
	my_free(throwaway);
        inorder_traversal(avail_mem->root, memory_print);

        printf("\nTESTING: split_memory\n");
        throwaway = split_memory(new_mem, 500);
        memory_print(new_mem);
        printf("\nTESTING: my_free\n");
        my_free(throwaway);
        inorder_traversal(avail_mem->root, memory_print);

        printf("\nTESTING: split_memory\n");
        throwaway = split_memory(new_mem, 600);
        memory_print(new_mem);
        printf("\nTESTING: my_free\n");
        my_free(throwaway);
        inorder_traversal(avail_mem->root, memory_print);

        printf("\nTESTING: split_memory\n");
        throwaway = split_memory(new_mem, 2800); //edge case
        memory_print(new_mem);
        printf("\nTESTING: my_free\n");
        my_free(throwaway);
        inorder_traversal(avail_mem->root, memory_print);

        printf("\nTESTING: split_memory\n");
        throwaway = split_memory(new_mem, 5000); //error case
	printf("\n----------------------------------\n");


	//test my_malloc
	printf("\nTESTING: my_malloc\n");
	my_malloc(20);
        inorder_traversal(avail_mem->root, memory_print);
	my_malloc(30);
	inorder_traversal(avail_mem->root, memory_print);
	my_malloc(4000);
        inorder_traversal(avail_mem->root, memory_print);
	my_malloc(50);
        inorder_traversal(avail_mem->root, memory_print);
	printf("\n-----------------------------------\n");

	/*test bst_iterate
	void * item;
	for(item = bst_iterate(avail_mem); item != NULL; 
			item = bst_iterate(NULL)){
		memory_print((memory *)item);
	}
	

	//test compact_memory
	printf("\nTESTING: compact_memory\n");
	compact_memory();
	inorder_traversal(avail_mem->root, memory_print);
	*/

	return 1;
}
