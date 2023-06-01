#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "memory.h"

/* Global variables
 * By declaring these outside of a function:
 *   Scope: Every function inside of this file may use them. 
 *   		No functions in other files may use them.
 *   Lifetime: They exist for the entire program - they are created
 *		when the program begins and exist until the program
 *		ends.
 */   		

/* This is the tree that holds the available memory. */
bst *avail_mem = NULL;

/* This includes all of the functions for the memory allocator.
 * The last two functions (my_malloc and my_free) are public 
 * functions with prototypes in the header function. The rest of the
 * functions are helper functions only called by my_malloc and 
 * my_free. You must implement these helper functions. If you wish,
 * you may add helper functions we did not define.
 */

/* compact_memory
 *
 * Search through all available memory and attempt to merge memory
 * that is stored next to each other.
 * This uses global variable avail_mem, so it does not need any
 * input parameters. Look at the bst functions and memory functions.
 */
void compact_memory()
{
    static llist * list = NULL;
    if (list == NULL){
	create_llist();
    }
    bst_to_llist(avail_mem->root, list, sorted_insert);

    llist_node * head = (llist_node *)list->head;
    llist_node * temp = head->next;
    llist_node * prev = head;
    memory * mem = NULL;

    while (temp!=NULL){
	mem = merge_memory((memory *)prev->item, (memory *)temp->item);
	if (mem != NULL){
	    bst_delete(avail_mem, temp->item);
	    bst_delete(avail_mem, prev->item);
	    bst_insert(avail_mem, mem);
	}
	//iterate to next node in llist
	prev = temp;
	temp = temp->next;
    }

}

/* print_available_memory 
 *
 * Print out all available memory in ascending order by size.
 */
void print_memory()
{
	fprintf(stderr,"print_memory not implemented yet\n");
}

/* init_alloc
 *
 * Initializes the data structures. This initializes avail_mem so 
 * that, instead of being a NULL pointer, it points to a valid bst
 * struct whose root pointer is NULL.
 */
void init_alloc()
{
	static int run = 0;
	if (run % 2 == 0){
		avail_mem = (bst *)malloc(sizeof(bst));
		avail_mem->root = NULL;
		avail_mem->cmp = memory_size_cmp;
		run = 1;
	}
	else{
		fprintf(stderr, "ERROR: init_alloc already run.\n");
	}
}

/* my_malloc
 * 
 * function that finds a piece of available memory that is at least
 * num_bytes size. A pointer to the beginning of the usable piece of
 * that chunk is returned.
 */
void *my_malloc(int num_bytes)
{
	//make sure num_bytes is a multiple of eight and greater than 24
	while (num_bytes % 8 != 0 || num_bytes < 24)
	{
		num_bytes++;
	}
	
	memory * item = memory_new(NULL, num_bytes);

	void * mem = bst_item_or_successor(avail_mem, (void *)item);
	memory * mem_p = (memory *)mem;

	//create new page of memory and split if no memory is big enough
	if ((mem == NULL) || (mem_p->size < num_bytes)){
		memory * new_mem = allocate_memory_page();
                void * ret_val = split_memory(new_mem, num_bytes);
                //update bst
		bst_insert(avail_mem, new_mem);
                return ret_val;
        }
	//split if size is (more than) double what is needed
	else if(mem_p->size >= 2 * num_bytes)
	{
		bst_delete(avail_mem, mem);
		void * ret_val = split_memory(mem_p, num_bytes);
		//update bst
		printf("%p\n", mem);
		printf("size: %d\n", mem_p->size);
		bst_insert(avail_mem, mem);
		return ret_val;
	}

	//whole chunk is used if it is larger/equal to but not twice as big
	else
	{
		//update bst
		bst_delete(avail_mem, mem);
		return mem;
	}
}

/* my_free
 * 
 * Function that returns the memory chunk whose usable piece starts
 * at that address back to the set of available memory so that it can
 * be reused in a subsequent free call
 */
void my_free(void *address)
{
	char * length = (char *)address - 8;
	int * copy = (int *)length;
	memory * mem = memory_new(address, (unsigned int)*copy);
	bst_insert(avail_mem, (void *)mem);	
}
