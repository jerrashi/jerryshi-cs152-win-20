#include<stdio.h>
#include<stdlib.h>
#include "bst.h"

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

  int compare = cmp(root->data, data);

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
  if (compare > 0) //root is greater than data
  {
	root->left = node_delete(root->left, data, cmp);
  }

  else if (compare < 0) //root is less than data
  {
	root->right = node_delete(root->right, data, cmp);
  }

  else if (compare == 0)
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

	else 
	{
		node * successor = root->left;

		while(successor->right != NULL)
		{
			successor = successor->right;
		}

		root->data = successor->data;

		root->right = node_delete(root->right, successor->data, cmp);
	}
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

