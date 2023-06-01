#include<stdio.h>
#include<stdlib.h>
#include "memory.h"
#include "llist.h"
#include "bst.h"

extern bst* avail_mem;

/* memory_new
 * create a new memory struct, initialize its address and size
 */
memory* memory_new(void * addr, unsigned int size){
  memory* m = (memory*)malloc(sizeof(memory));
  m->addr = addr;
  m->size = size;
  return m;
}

/* free the dynamically allocated memory struct
 */
void memory_free(void* p){
  memory* m = (memory*)p;
  free(m);
}

/* compare two memory variables x and y by address 
 * if x is less than y, return -1
 * if x is greater than y, return 1
 * if they are equal, return 0
 */
int memory_addr_cmp(const void* x, const void* y){
  const memory* x_mem = (const memory*)x;
  const memory* y_mem = (const memory*)y;
  if (x_mem->addr < y_mem->addr)
  {
	return -1;
  }
  else if (x_mem->addr == y_mem->addr)
  {
	return 0;
  }
  else
  {
	return 1;
  }
}

/* compare two memory variables x and y by size 
 * if x is less than y, return -1
 * if x is greater than y, return 1
 * if they are equal, return 0
 */
int memory_size_cmp(const void* x, const void* y){
  const memory* x_mem = (const memory*)x;
  const memory* y_mem = (const memory*)y;

  if (x_mem->size < y_mem->size)
  {
        return -1;
  }
  else if (x_mem->size == y_mem->size)
  {
        return 0;
  }
  else
  {
        return 1;
  }
}

/* print the memory address and size
 */
void memory_print(void* data){
  if (data == NULL) return;
  memory* m = (memory*)data;
  printf("address: %p, size: %u\n", m->addr, m->size);
}

/* allocate_memory_page
 *
 * Call malloc to request a page of data - 4096 bytes. Create
 * a memory struct and initialize it to store the resulting
 * large chunk of data that was allocated. Return a pointer
 * to the memory struct.
 */
memory *allocate_memory_page()
{
	memory * rv = (memory *)malloc(sizeof(memory));
	rv->addr = malloc(4096);

	rv->size = 4088;
	return rv;
}

/* split_memory
 *
 * Given a memory struct and a desired size of memory,
 * perform the operations necessary to remove the desired
 * size of memory from the end of the chunk and record
 * the new information for the smaller chunk. Return a
 * pointer to the beginning of the chunk you are handing out.
 */
void *split_memory(memory* data, unsigned int size_desired)
{
	if (size_desired >= data->size){
		fprintf(stderr, "SPLIT_MEMORY ERROR: size_desired is too big\n");
		return NULL;
	}
	else if (size_desired <= 0){
		fprintf(stderr, "SPLIT_MEMORY ERROR: size_desired must be > 0\n");
		return NULL;
	}

	data->size = data->size - 8 - size_desired;
	//move to header position of new memory block
	char * ret_val = 8 + (char *)data->addr + data->size;
	//matching pointer to data type, otherwise large numbers are cut off
	int * copy = (int *)ret_val;
	*copy = size_desired;
	ret_val += 8; // moves to return position
	return (void *)ret_val;
}

/* merge_memory
 *
 * Given two memory structs, check to see if the two can be
 * merged. They can be merged if the two are next to each other
 * in memory with no break in between. If they can be merged,
 * return a memory struct pointer to a struct containing the information
 * for a single memory chunk containing the old two chunks.
 * If they cannot be merged (there is space between them), then
 * return NULL;
 *
 * Make sure that you free any memory structs that you need to.
 */
memory *merge_memory(memory *first, memory *second)
{
	char * first_addr = (char *)first->addr;
	char * second_addr = (char *)second->addr;
	//remember to compensate for first header
	if(first_addr + first->size + 8 == second_addr)
	{
		//update bst
		bst_delete(avail_mem, first);
		bst_delete(avail_mem, second);

		//update first memory struct
		first->size = first->size + second->size + 8;
		*first_addr = first->size + second->size + 8;

		//update bst and memory
		bst_insert(avail_mem, first);
		free(second);
		
		return first;
	}
	else
	{
		return NULL;
	}
}
