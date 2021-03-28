#include "defn.h"
#include "utils.h"

#include <iostream>
#include <string>
#include <typeinfo>
#include <cstring>

using namespace std;

// static int pos = 0;
// struct parsed_query{
// 	int query_type;
// 	string category_name;
// };

// Performs and inorder traversal and prints the nodes
void inorder(struct bst *root)
{
	if(root == NULL)
		return;
	else
	{
		inorder(root->left);
		cout << "\n\t" << root->record.app_name;
		inorder(root->right);
	}
}


void range_inorder_checker_price(struct bst *root, float low, float high, int &count)
{
	if(root == NULL)
		return;
	else
	{
		range_inorder_checker_price(root->left, low, high, count);
		if(root->record.price >= low && root->record.price <= high)
		{
			count++;
		}
		range_inorder_checker_price(root->right, low, high, count);
	}
}

void range_inorder_price(struct bst *root, float low, float high)
{
	if(root == NULL)
		return;
	else
	{
		range_inorder_price(root->left, low, high);
		if(root->record.price >= low && root->record.price <= high)
		{
			cout << "\n\t" << root->record.app_name;
		}
		range_inorder_price(root->right, low, high);
	}
}

void range_inorder_checker_app(struct bst *root, string low, string high, int &count)
{
	if(root == NULL)
		return;
	else
	{
		range_inorder_checker_app(root->left, low, high, count);
		if(root->record.app_name >= low && root->record.app_name <= high)
		{
			count++;
		}
		range_inorder_checker_app(root->right, low, high, count);
	}
}

void range_inorder_app(struct bst *root, string low, string high)
{
	if(root == NULL)
		return;
	else
	{
		range_inorder_app(root->left, low, high);
		if(root->record.app_name >= low && root->record.app_name <= high)
		{
			cout << "\n\t" << root->record.app_name;
		}
		range_inorder_app(root->right, low, high);
	}
}

// Performs inorder traversal and assigns the nodes to the array
void inorder_insert(struct bst *root, float *max_heap, int &pos)
{
	if(root == NULL)
		return;
	else
	{
		inorder_insert(root->left, max_heap, pos);
		max_heap[pos++] = root->record.price;
		inorder_insert(root->right, max_heap, pos);
	}
}

// Prints the app name by traversing through the BST inorder
void inorder_print(struct bst *root, float max_val)
{
	if(root == NULL)
		return;
	else
	{
		inorder_print(root->left, max_val);
		if(root->record.price == max_val)
		{
			cout << "\n\t" << root->record.app_name;   
		}
		inorder_print(root->right, max_val);
	}
}


void new_insert(struct bst *node, struct app_info ai, struct bst *ttemp)
{
	if(node != NULL)
	{
		if(ai.app_name <= node->record.app_name)
		{
			new_insert(node->left, ai, ttemp);
		}
		else if(ai.app_name > node->record.app_name)
		{
			new_insert(node->right, ai, ttemp);
		}
	}
	if(node == NULL)
	{
		ttemp->record = ai;
		ttemp->left = NULL;
		ttemp->right = NULL;
	}
}

// Inserts the BST data into the app store
void fillBST(struct bst *temp_bst, struct categories* app_store, int n_categories)
{
	string name_tempapp = temp_bst->record.app_name;
	for(int i=0;i<n_categories;i++)
	{
		if(temp_bst->record.category == app_store[i].category)
		{
			if(app_store[i].root == NULL)
			{
				app_store[i].root = temp_bst;
				return;
			}
			struct bst *root = app_store[i].root;
			string name_rootapp;
			while(root)
			{
				name_rootapp = root->record.app_name;
				if(name_tempapp > name_rootapp)
				{
					if(root->right == NULL)
					{
						root->right = temp_bst;
						return ;
					}
					root = root->right;
				}
				else
				{
					if(root->left == NULL)
					{
						root->left = temp_bst;
						return ;
					}
					root = root->left;
				}
			}
		}
	}
}