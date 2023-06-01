#include<stdio.h>
#include<stdlib.h>
#include "bst.h"
#include "llist.h"
#include "memory.h"

/* malloc a new node and assign the data
 * pointer to its data field
 */
node* node_new(void* data){
  node* new_node = (node *)malloc(sizeof(node));
  new_node->left = NULL;
  new_node->right = NULL;
  new_node->data = data;
  return new_node;
}

/* create a new bst, initialize its root to be NULL
 */
bst* bst_new(int (*cmp)(const void* x, const void* y)){
  bst* new_bst = (bst *)malloc(sizeof(bst));
  new_bst->root = NULL;
  new_bst->cmp = cmp;
  return new_bst;
}

/* Insert a node to to a subtree with a root node as parameter
 * Insertion is in sorted order. 
 * Return the new root of the modified subtree.  
 */
node* node_insert(node* root, void* data, 
    int (*cmp)(const void* x, const void* y)){

  //Base case
  if (root == NULL)
  {
	root = node_new(data);
	return root;
  }

  //printf("root data: %d\n", root->data);
  int compare = cmp(root->data, data);
  //printf("\n compare = %d\n", compare);

  //Recursive case
  if (compare == -1) //root value is less than data
  {
	root->right = node_insert(root->right, data, cmp);
  }

  else if (compare == 1) //root value is greater than data
  {
	root->left = node_insert(root->left, data, cmp);
  }

  return root;
}

/* Insert a new node to the bst
 */
void bst_insert(bst* b, void* data){
  if (b->root == NULL)
  {
	b->root = node_new(data);
  }
  else
  {
	node_insert(b->root, data, b->cmp);
	printf("root not null");
  }
}

/* delete a node from a subtree with a given root node
 * use the comparison function to search the node and delete 
 * it when a matching node is found. This function only
 * deletes the first occurrence of the node, i.e, if multiple 
 * nodes contain the data we are looking for, only the first node 
 * we found is deleted. 
 * Return the new root node after deletion.
 */
node* node_delete(node* root, void* data, 
    int (*cmp)(const void* x, const void* y)){
  //base case
  if (root == NULL)
  {
	return root;
  }

  int compare = (cmp)(root->data, data);

  //recursive case
  if (compare == 1) //root is greater than data
  {
	root->left = node_delete(root->left, data, cmp);
  }

  else if (compare == -1) //root is less than data
  {
	root->right = node_delete(root->right, data, cmp);
  }

  else //root and data are equal
  {
	if (root->left == NULL)
	{
		node* temp = root->right;
		free(root);
		return temp;
	}

	else if (root->right == NULL)
	{
		node* temp = root->left;
		free(root);
		return temp;
	}

	node * successor = root->right;

	while(successor->left != NULL){
		successor = successor->left;
	}

	root->data = successor->data;

	root->right = node_delete(root->right, successor->data, cmp);
  }
  return root;
}

/* delete a node containing data from the bst
 */
void bst_delete(bst* b, void* data){
  node_delete(b->root, data, b->cmp);
}

/* Search for a node containing data in a subtree with
 * a given root node. Use recursion to search that node. 
 * Return the first occurrence of node. 
 */
void* node_search(node* root, void* data, 
    int (*cmp)(const void* x, const void* y)){
  
  int compare = (cmp)(root->data, data);

  if (compare == -1)
  {
	return node_search(root->right, data, cmp);
  }

  else if (compare == 1)
  {
	return node_search(root->left, data, cmp);
  }

  else
  {
	  return (void *)root;
  }
}

/* Search a node with data in a bst. 
 */
void* bst_search(bst* b, void* data){
  return node_search(b->root, data, b->cmp);
}

/* traverse a subtree with root in ascending order. 
 * Apply func to the data of each node. 
 */
void inorder_traversal(node* root, void(*func)(void* data)){
  if (root == NULL)
  {
	return;
  }	
  else
  {
	inorder_traversal(root->left, func);
	if(root->data != NULL)
	{
	  func(root->data);
	}
	inorder_traversal(root->right, func);
	return;
  }
  return;
}

/* traverse a bst in ascending order. 
 * Apply func to the data of each node. 
 */
void bst_inorder_traversal(bst* b, void(*func)(void* data)){
  inorder_traversal(b->root, func);
}


/* helper function for bst_free to delete all nodes
 */
void node_free(node* node)
{
	if (node == NULL)
	{
		return;
	}

	node_free(node->left);
	node_free(node->right);

	free(node);
}

/* free the bst with 
 */
void bst_free(bst* b){

  //delete all data
  inorder_traversal(b->root, free);
  
  //delete all nodes
  node_free(b->root);

  //delete bst object
  free(b);
}

/*****************************
 *    HOMEWORK 8
 *****************************/
/* Helper function specifially made for for applying linked 
 * list functions to a bst.
 */
void bst_to_llist(node* root, llist* list, void(*func)
		(llist *list, void *item))
{
  if (root == NULL)
  {
        return;
  }
  else
  {
        bst_to_llist(root->left, list, insert_tail);
        if(root->data != NULL)
        {
            func(list, root->data);
        }
        bst_to_llist(root->right, list, insert_tail);
        return;
  }
  return;
}

/* an iterator to iterate through the bst in ascending order
*/
void* bst_iterate(bst* b)
{
	static llist * list = NULL;
	if (list == NULL)
	{
		list = create_llist();
		bst_to_llist(b->root, list, insert_tail);
	}

	printf("%p", list);
	return iterate(list);
}
/* 
 * item_or_successor
 * 
 * find an item that is equal or, if there isn't one that is 
 * equal, find the one that is next larger to the requested
 * item.
 *
 * The purpose of this function is that, given a size of a 
 * chunk of memory desired, it attempts to find an available
 * chunk of memory the same size. If there is no chunk of 
 * memory the same size, it finds the chunk of memory that is 
 * closest to that size but larger.
 *
 * It returns a pointer to the memory struct. The compare 
 * function in the bst is the one that performs the comparisons.
 */
void* node_item_or_successor(node *n, void *item,
        int (*cmp)(const void* x, const void* y))
{
	//while node data less than item
	while ((cmp((const void *)n->data, (const void *)item) == -1)
	       && (n->right != NULL)){
		    n = n->right;
	}

	//if largest data is still less than item
	if (cmp((const void *)n->data, (const void *)item) == -1){
		fprintf(stderr, "NODE_ITEM_OR_SUCESSOR ERROR: no item "
			       	"larger than input\n");
		return NULL;
	}
	else{
	    return n->data;
	}
}

void* bst_item_or_successor(bst *b, void *item)
{
	if(b->root == NULL){ //empty bst case
		return NULL;
	}
	else{
		return node_item_or_successor(b->root, item, b->cmp);
	}
}

/* helper function to add items from bst into sorted linked list
 * data should be a memory struct
 */
void sorted_insert(llist * list, void * mem)
{
    llist_node * head = (llist_node *)list->head;
    llist_node * temp = head;
    llist_node * prev = NULL;

    //initialize new node
    llist_node * new_node = (llist_node *)malloc(sizeof(llist_node));
    new_node->item = mem;
    new_node->next = NULL;
    
    //empty list case
    if (head == NULL){
	insert_tail(list, mem);
    }
    
    else{
	//iterate to correct position for data to be inserted
	while (temp!=NULL){
	    if (memory_addr_cmp((const void *)temp, (const void *)mem) == 1){
		break;
	    }
	    else{
		prev = temp;
		temp = temp->next;
	    }
	}
	//data is bigger than everything in list so it is appended
	if (temp == NULL){
	    insert_tail(list, mem);
	}

	else{
	    //data is smaller than everything in list so it is prepended
	    if(prev == NULL){
		new_node->next = temp;
		head = new_node;
	    }
	    //data is inserted normally
	    else{
		new_node->next = temp;
		prev->next = new_node;
	    }
	}
    }
}
