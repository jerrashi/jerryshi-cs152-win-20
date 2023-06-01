#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hw6.h"

char *category_strings[] = { "Grocery", "Office", "Pharmacy", "Hobby"};

// Standardized print product_info function
void print_product(product_info *p, FILE *fp)
{
	fprintf(fp,"%s (%u) %s:",p->name, p->productID,
		category_strings[p->category]);
	fprintf(fp, "current: %u, min: %u, max: %u",
		p->current_stock, p->min_for_restock, p->max_after_restock);
}

// Standardized print linked list function
void print_list(node *head, FILE *fp)
{
	node *tmp;
	printf("Product Status:\n");
	for(tmp = head; tmp != NULL; tmp = tmp->next)
	{
		print_product(tmp->product,fp);
		printf("\n");
	}
}

/* Allocates memory and fills in the fields for a new product info. For the 
 * string arguments, text is copied over.
 * Inputs - product info (name category, product id, current stock, etc.)
 * Outputs - a pointer to the newly allocated and initialized memory
*/
product_info *create_product(char *name, char *category, uint id,
				uint current, uint mn, uint mx)
{
	product_info * rv = (product_info *)malloc(sizeof(product_info));

	int i, name_length = strlen(name); //, cat_length = strlen(category);
	
	//copy over name
	for(i = 0; i<=name_length; i++)
	{
		rv->name[i] = name[i];
	}
	
	
	/* Unimplemented code to prevent string formatting errors
	//convert formatting of category string to product_info format
	if ((category[1] >= 'a') && (category[1] <= 'z'))
	{
		category[1] = category[1] + ('A' - 'a');
	}
	for(i = 1; i<cat_length; i++)
	{
		if ((category[i] >= 'A') && (category[i] <= 'Z'))
		{
			category[i] = category[i] - ('A' - 'a');
		}
	}
	*/
	
	//set category value by matching with category_strings
	if (strcmp((const char*)category, (const char*)category_strings[0]) == 0)
	{
		rv->category = GROCERY;
	}
	else if (strcmp(category, category_strings[1]) == 0)
	{
		rv->category = OFFICE;
	}
	else if (strcmp(category, category_strings[2]) == 0)
	{
		rv->category = PHARMACY;
	}
	else if (strcmp(category, category_strings[3]) == 0)
	{
		rv->category = HOBBY;
	}
	else
	{
		fprintf(stderr, "CREATE_PRODUCT ERROR: category string does not "
			"match any strings in category list\n");
	}

	//setting rest of values
	rv->productID = id;
	rv->current_stock = current;
	rv->min_for_restock = mn;
	rv->max_after_restock = mx;

	return rv;
}

/* Adds a product to the "head" or beginning of a list. The new first node of
 * the list will point to pinfo.
 * Inputs - head of list, pointer to product_info object pinfo
 * Outputs - a pointer to the first node in the modified list
 */
node* insert_head(node *head, product_info *pinfo)
{
	node* newnode = (node *)malloc(sizeof(node));
	newnode->product = pinfo;
	newnode->next = head;
	head = newnode;
	return head;
}

/* Finds the record for first product_info object matching inputted product ID.
 * Output - pointer to that record
 */
product_info * find(node *head, uint pID)
{
	if (head == NULL) //empty list
	{
		fprintf(stderr, "FIND ERROR: linked list is empty");
		return NULL;
	}

	node * tmp;
	for(tmp = head; tmp != NULL; tmp=tmp->next) //iterate through list
	{
		if (tmp->product->productID == pID)
		return tmp->product;
	}
	
	fprintf(stderr, "FIND ERROR:product id not found in list\n");
	return NULL;
}

/* Replaces the current number of items with the max number of items after
 * restocking.
 * Inputs:
 *      head - pointer to beginning of linked list
 *      pID - product ID of product to be restocked
 * Outputs:
 *      none
 */
void record_restocked_single(node *head, uint pID)
{
	product_info * p = find(head, pID);
	if (p != NULL)
	{
		p->current_stock = p->max_after_restock;
	}
}

/* Finds the record for the product and decrements the number of items 
 * currently in stock for that item.
 * Inputs:
 *      head - pointer to beginning of linked list
 *      pID - product ID of product to be restocked
 * Outputs:
 *      none
 */
void product_sold(node *head, uint pID)
{
	product_info * p = find(head, pID);
	if (p != NULL)
	{
		p->current_stock = p->current_stock - 1;
	}
}

/* Inserts product_info immediately prior to the first product with a larger 
 * productID than pinfo. If there is no product with a larger productID, then 
 * pinfo is placed at the end of the list.
 * Inputs:
 *      head - pointer to beginning of linked list
 *      pID - product ID of product to be restocked
 * Outputs:
 * 	node pointer to beginning of list
 */
node *add_sorted_productID(product_info *pinfo, node *head)
{

        // for empty list or first item is greater
        if((head == NULL) || (head->product->productID > pinfo->productID))
        {
                return insert_head(head, pinfo);
        }

	//variable declaration
	node * tmp = head;
	node * newnode = (node *)malloc(sizeof(node));
	newnode->product = pinfo;

	// iterate through list
	for(tmp=head; tmp->next != NULL; tmp=tmp->next)
	{
		// pinfo goes after tmp
		if (tmp->next->product->productID > pinfo->productID)
		{
			newnode->next = tmp->next;
			tmp->next = newnode;
			return head;
		}
	}
	
	// insert at end of list
	newnode->next = NULL;
        tmp->next = newnode;
        return head;
}

/* Inserts product_info into sorted list. Within each category, products are
 * sorted by productIDs in increasing order.
 * Inputs:
 * 	head - pointer to beginning of linked list
 * 	pID - product ID of product to be restocked
 * Outputs:
 * 	node pointer to beginning of list
 */
node *add_sorted_category_ID(product_info *pinfo, node *head)
{
        // for empty list
        if(head == NULL)
	{
		return insert_head(head, pinfo);
	}

	// first item in list goes after pinfo
	if ((head->product->category == pinfo->category)
	 && (head->product->productID > pinfo->productID))
        {
                return insert_head(head, pinfo);
        }

	// variable declaration
	node * tmp = head;
        node * newnode = (node *)malloc(sizeof(node));
        newnode->product = pinfo;

        // iterate through list
        for(tmp=head; tmp->next != NULL; tmp=tmp->next)
        {
		// next item is same category and has greater productID
		if ((tmp->next->product->category == pinfo->category)
		 && (tmp->next->product->productID > pinfo->productID))
		{
			newnode->next = tmp->next;
                        tmp->next = newnode;
                        return head;
		}

                // end of category reached
                if (tmp->next->product->category > pinfo->category)
                {
                        newnode->next = tmp->next;
                        tmp->next = newnode;
                        return head;
                }
        }
	
	// insert at end of list
        newnode->next = NULL;
	tmp->next = newnode;
	return head;
}

/* Inserts node at the end of inputted linked list.
 * Inputs:
 * 	node * head - points to beginning of linked list
 * 	product_info * p - pointer to product_info object
 * Outputs:
 * 	node * head - pointer to beginning of modified linked list
 */
node *insert_tail(product_info *p, node * head)
{
	node * newnode = (node *)malloc(sizeof(node));
	
	if(head == NULL)
	{
		return insert_head(head, p);
	}
	
	node * tmp;
	for(tmp = head; tmp->next != NULL; tmp=tmp->next)
		; //tmp is now the last item in the linked list
	newnode->product = p;
	newnode->next = NULL;
	tmp->next = newnode;
	return head;
}

/* Creates a linked list of product_info records that need to be restocked 
 * (current_stock < min_for_restock). Returns the head of this new linked list.
 * If there is nothing to restock, or the original list is empty, returns NULL.
 * Inputs:
 * 	head - points to beginning of linked list
 * Outputs:
 * 	node - points to linked list of products_info records to be restocked
 */
node *make_restock_list(node *head)
{
	if (head == NULL) //list is empty
	{
		return NULL;
	}

	node * tmp;
	node * rv = NULL; //creating new list

	//iterate through original linked list
	for(tmp = head; tmp != NULL; tmp=tmp->next)
	{
		if (tmp->product->current_stock <= tmp->product->min_for_restock)
		{
			rv = insert_head(rv, tmp->product);
		}
	}


	return rv;
}

/* Given a list of restocked items, goes through the original list and changes 
 * the current_stock value to be equal to max_after_restock.
 * Inputs:
 * 	node * restocked_list - pointer to linked list of products to restock
 * 	node * head - pointer to linked list of products
 * Outputs:
 * 	none
 */
void record_restocked_list(node *restocked_list, node *head)
{
	//check for empty list
	if (head == NULL)
	{
		fprintf(stderr, "RECORD_RESTOCKED_LIST: original linked list "
				"is empty");
		return;
	}
	if (restocked_list == NULL)
	{
		fprintf(stderr, "RECORD_RESTOCKED_LIST: restocked_list is "
				"empty");
	}

	node * rs;	
	for (rs = restocked_list; rs != NULL; rs = rs->next)
	{
		record_restocked_single(head, rs->product->productID);
	}
}
