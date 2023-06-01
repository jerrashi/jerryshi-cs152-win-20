#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hw6.h"

//#define DEBUG //delete characters at beginning of line to turn off debug outputs

int main(int argc, char *argv[])
{
	
	// make sure there are two arguments - hw6 and filename
	if (argc < 2)
	{
		printf("Usage: ./hw6 filename. Missing filename\n");
		exit(1);
	}
	char *filename = argv[1];

	// open file for reading
	FILE *fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Could not open file %s for reading\n",filename);
		exit(2);
	}

	// initialize variables to make linked list
	node * head = NULL;
	node * head_product = NULL;
	node * head_category = NULL;
	product_info * p;

	// read in each record from the file
	char buffer[BUFSIZ];
	while (!feof(fp) && (fgets(buffer,500,fp) != NULL))
	{
		// parse the line to split up the fields
		char *category;
		char *name;
		uint pID;
		uint current_stock;
		uint min_stock;
		uint max_stock;
		char *tmp_s;

		// first field is category
		category = strtok(buffer," ,\n\r");
		// second field is name
		name = strtok(NULL," ,\n\r");
		// third is pID;
		tmp_s = strtok(NULL," ,\n\r");
		pID = atoi(tmp_s);
		// fourth is current
		tmp_s = strtok(NULL," ,\n\r");
		current_stock = atoi(tmp_s);
		// fifth is min
		tmp_s = strtok(NULL," ,\n\r");
		min_stock = atoi(tmp_s);
		// sixth is max
		tmp_s = strtok(NULL," ,\n\r");
		max_stock = atoi(tmp_s);

		printf("Read in record: %s, %s, %u, %u, %u, %u\n",
			category, name, pID, current_stock, min_stock,
			max_stock);
		
		p = create_product(name, category, pID, current_stock, 
					min_stock, max_stock);
		head = insert_head(head, p);
		head_product = add_sorted_productID(p, head_product);
		head_category = add_sorted_category_ID(p, head_category);
	}
	
	#ifndef DEBUG
	printf("\n Linked List Created from File:\n");
	node * tmp;
	if (head == NULL)
	{	
		printf("ERROR: head is null\n");
	}
	else
	{
		printf("\nSorted by productID:\n");
		print_list(head_product, stdout);
                printf("\nSorted by category:\n");
		print_list(head_category, stdout);
                printf("\nUnordered:\n");
		print_list(head, stdout);
	}
        
	printf("\n Testing product_sold---\n");
	product_sold(head, 2956);
	product_sold(head, 1000);
	product_sold(head, 92656);
	product_sold(head, 38590);
	print_list(head,stdout);

        /*
	printf("\n Testing single restocking---\n");
        record_restocked_single(head, 2956);
        record_restocked_single(head, 1000);
        record_restocked_single(head, 92656);
        record_restocked_single(head, 38590);
        print_list(head,stdout);
	*/

	printf("\n Testing restocking-----\n");
	printf("\nrestocked_list:\n");
	print_list(make_restock_list(head), stdout);
	record_restocked_list(make_restock_list(head), head);
	print_list(head,stdout);	
		
	printf("\n Manual Testing ------------------------------------------");
        printf("\nTesting create_product:----------\n");
	char * s1 = "Tomatoes";
        char * s2 = "Grocery";
        p = create_product(s1, s2, 1, 20, 15, 20);
        printf("Trial 1: \n");
	printf("    category value is %d\n", p->category);
	printf("    expected: 0\n");

	char * s3 = "Chess";
	char * s4 = "Hobby";
	product_info * p1 = create_product(s3, s4, 2, 20, 15, 20);
	printf("Trial 2: \n");
	printf("    category value is %d\n", p1->category);
	printf("    expected: 3\n");

        char * s5 = "Notebooks";
        char * s6 = "Office";
        product_info * p2 = create_product(s5, s6, 3, 20, 15, 20);
        printf("Trial 3: \n");
        printf("    category value is %d\n", p2->category);
	printf("    expected: 1\n");

	printf("\nTesting insert_head:-----------\n");
	node * node1 = (node *)malloc(sizeof(node));
	node * node2 = (node *)malloc(sizeof(node));
	head = node1;
	node1->product = p1;
	node1->next = node2;
	node2->product = p2;
	node2->next = NULL;
	printf("Trial 1:\n");
	printf("---Before inserting head: ");
	for(tmp = head; tmp != NULL; tmp = tmp->next)
		printf("%s, ", tmp->product->name);
	head = insert_head(head, p);
        printf("\n---After inserting head: ");
	for(tmp = head; tmp != NULL; tmp = tmp->next)
                printf("%s, ", tmp->product->name);

        printf("\nTrial 2:\n");
        printf("---Before inserting head: ");
        for(tmp = head; tmp != NULL; tmp = tmp->next)
                printf("%s, ", tmp->product->name);
        head = insert_head(head, p1);
        printf("\n---After inserting head: ");
        for(tmp = head; tmp != NULL; tmp = tmp->next)
                printf("%s, ", tmp->product->name);

        printf("\nTrial 3:\n");
        printf("---Before inserting head: ");
        for(tmp = head; tmp != NULL; tmp = tmp->next)
                printf("%s, ", tmp->product->name);
        head = insert_head(head, p2);
        printf("\n---After inserting head: ");
        for(tmp = head; tmp != NULL; tmp = tmp->next)
                printf("%s, ", tmp->product->name);


	printf("\n\nTesting find:-----------\n");
	product_info * temp;
	temp = find(head, 3);
	printf("Trial 1:\n");
	printf("    product ID: %d\n", temp->productID);
	printf("    expected: 3\n");

	temp = find(head, 2);
        printf("Trial 1:\n");
        printf("    product ID: %d\n", temp->productID);
	printf("    expected: 2\n");

        temp = find(head, 1);
        printf("Trial 3:\n");
        printf("    product ID: %d\n", temp->productID);
	printf("    expected: 1\n");
	#endif
}
