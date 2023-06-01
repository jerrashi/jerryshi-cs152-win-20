#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"
#include "bst.h"
#include "hw7.h"

/* reads in a file and creates a binary search tree from data
 * inputs:
 *   filename - name of file
 *   cmp - function pointer of compare function to be used
 * outputs:
 *   rv - pointer to created binary search tree
 */
bst* read_memory_blocks(char *filename, int (*cmp)
		(const void* x, const void* y))
{
  FILE *fp;
  char buf[BUFSIZ] = "buffer";
  int i = 0;
  char *address;
  char *size;
  memory* temp;
  bst * rv = (bst *)malloc(sizeof(bst));
  rv = bst_new(cmp);

  // attempt to open the file, then check whether that worked.
  if ((fp = fopen(filename, "r")) == NULL)
  {
    fprintf(stderr,"Could not open file %s\n",filename);
    return rv;
  }

  // for each line of the file, read it in and then print it out
  while ( !feof(fp)) //fgets(buf, sizeof(buf), fp) != NULL)
  {
    if (fgets(buf, sizeof(buf),fp) != NULL)
    {
	#ifndef DEBUG
	printf("\nLin %4d: %s", i, buf);
	#endif
	address = strtok(buf, ",");
    	size = strtok(NULL, ",");
	//convert to unsigned int
	unsigned int address_ui = (unsigned int)atoi(address);
	unsigned int size_ui = (unsigned int)atoi(size);
	temp = memory_new(address_ui, size_ui);
	bst_insert(rv, (void*)temp);
	#ifndef DEBUG
	printf("\n    Memory address: %s", address);
	printf("\n    Memory size: %s", size);
	i++;
	#endif
    }
  }

  return rv;
  //fclose(fp);
}
