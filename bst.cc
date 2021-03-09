#include "defn.h"

#include <iostream>
#include <string>
#include <typeinfo>
#include <cstring>

using namespace std;
static int pos = 0;
struct parsed_query{
	int query_type;
	string category_name;
};
void inorder(struct bst *root)
{
	if(root == NULL)
		return;
	else
	{
		inorder(root->left);
		// cout << "\t" << root->record.app_name<<endl;
		cout << "\n\t" << root->record.app_name;
		inorder(root->right);
	}
}

void inorder_insert(struct bst *root, float *max_heap)
{
	// static int pos = 0;
	if(root == NULL)
		return;
	else
	{
		inorder_insert(root->left, max_heap);
		// cout << "\t" << root->record.app_name<<endl;
		// cout << "\t"<<pos<<") "<<root->record.price << "\n";
		max_heap[pos++] = root->record.price;
		inorder_insert(root->right, max_heap);
	}
}

void inorder_print(struct bst *root, float max_val)
{
	if(root == NULL)
		return;
	else
	{
		inorder_print(root->left, max_val);
		if(root->record.price == max_val)
		{
			// cout << "\t" << root->record.app_name <<endl;   
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
			// cout << "LEFT\t";
			new_insert(node->left, ai, ttemp);
		}
		else if(ai.app_name > node->record.app_name)
		{
			// cout << "RIGHT\t";
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
						break;
					}
					root = root->right;
				}
				else
				{
					if(root->left == NULL)
					{
						root->left = temp_bst;
						return;
					}
					root = root->left;
				}
			}
		}
	}
}