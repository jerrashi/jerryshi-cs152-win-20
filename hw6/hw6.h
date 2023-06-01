#ifndef HW5_H
#define HW5_H

typedef unsigned int uint;

enum Category { GROCERY=0, OFFICE, PHARMACY, HOBBY};
#define NUM_CATEGORIES 4

typedef struct {
 enum Category category;
 char name[40];
 uint productID;
 uint current_stock;
 uint min_for_restock;
 uint max_after_restock;
} product_info;

// for the linked list, we will use the following struct
typedef struct _node node;

struct _node{
 product_info *product;
 node *next;
};

extern char *category_strings[];

// Standardized print product_info function
void print_product(product_info *p, FILE *fp);


// Standardized print linked list function
void print_list(node *head, FILE *fp);

/* Allocates memory and fills in the fields for a new product info. For the
 * string arguments, text is copied over.
 * Inputs - product info (name category, product id, current stock, etc.)
 * Outputs - a pointer to the newly allocated and initialized memory
*/
product_info *create_product(char *name, char *category, uint id,
				uint current, uint mn, uint mx);
/* Adds a product to the "head" or beginning of a list. The new first node of 
 * the list will point to pinfo.
 * Inputs - head of list, pointer to product_info object pinfo
 * Outputs - a pointer to the first node in the modified list
 */
node* insert_head(node *head, product_info *pinfo);

/* Finds the record for first product_info object matching inputted product ID.
 * Output - pointer to that record
 */
product_info *find(node *head, uint pID);

/* Replaces the current number of items with the max number of items after 
 * restocking.
 * Inputs:
 * 	head - pointer to beginning of linked list
 * 	pID - product ID of product to be restocked
 * Outputs:
 * 	none
 */
void record_restocked_single(node *head, uint pID);

/* Finds the record for the product and decrements the number of items
 * currently in stock for that item.
 * Inputs:
 *      head - pointer to beginning of linked list
 *      pID - product ID of product to be restocked
 * Outputs:
 *      none
 */
void product_sold(node *head, uint pID);

/* Inserts product_info immediately prior to the first product with a larger
 * productID than pinfo. If there is no product with a larger productID, then
 * pinfo is placed at the end of the list.
 * Inputs:
 *      head - pointer to beginning of linked list
 *      pID - product ID of product to be restocked
 * Outputs:
 *      node pointer to inserted object
 */
node *add_sorted_productID(product_info *pinfo, node *head);

/* Inserts product_info into sorted list. Within each category, products are
 * sorted by productIDs in increasing order.
 * Inputs:
 *      head - pointer to beginning of linked list
 *      pID - product ID of product to be restocked
 * Outputs:
 *      node pointer to inserted object
 */
node *add_sorted_category_ID(product_info *pinfo, node *head);

/* Inserts node at the end of inputted linked list.
 * Inputs:
 *      node * head - points to beginning of linked list
 *      product_info * p - pointer to product_info object
 * Outputs:
 *      None
 */
node *insert_tail(product_info * p, node *head);

/* Creates a linked list of product_info records that need to be restocked
 * (current_stock < min_for_restock). Returns the head of this new linked list.
 * If there is nothing to restock, or the original list is empty, returns NULL.
 * Inputs:
 *      head - points to beginning of linked list
 * Outputs:
 *      node - points to linked list of products_info records to be restocked
 */
node *make_restock_list(node *head);

/* Given a list of restocked items, goes through the original list and changes
 * the current_stock value to be equal to max_after_restock.
 * Inputs:
 *      node * restocked_list - pointer to linked list of products to restock
 *      node * head - pointer to linked list of products
 * Outputs:
 *      none
 */
void record_restocked_list(node *restocked_list, node *head);

#endif
