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

struct bst* insert(struct bst *node, struct app_info ai)
{
	if(node != NULL)
	{
		if(ai.app_name <= node->record.app_name)
		{
			// cout << "LEFT\t";
			node->left = insert(node->left, ai);
		}
		else if(ai.app_name > node->record.app_name)
		{
			// cout << "RIGHT\t";
			node->right = insert(node->right, ai);
		}
	}
	if(node == NULL)
	{
		struct bst *ttemp = new struct bst;
		ttemp->record = ai;
		ttemp->left = NULL;
		ttemp->right = NULL;
		return ttemp;
	}
	return node;
}

void fillBSTData(struct app_info *arr_ai, struct categories *app_store, int m_apps, int n_categories)
{
	for(int i=0;i<m_apps;i++)
	{
		// cout << "\t" << arr_ai[i].app_name << endl;
		for(int j=0;j<n_categories;j++)
		{
			if(arr_ai[i].category ==  app_store[j].category)
			{
				struct bst *temp_bst;
				if(app_store[j].root == NULL)
				{
					// cout << "This is the base:\t";
					temp_bst = new struct bst;
					temp_bst->record = arr_ai[i];
					temp_bst->left = NULL;
					temp_bst->right = NULL;
					app_store[j].root = temp_bst;
					temp_bst = NULL;
				}
				else
				{
					// cout << "This is not at base:\t";
					temp_bst = new struct bst;
					temp_bst = insert(app_store[j].root, arr_ai[i]);
					// cout << "\ninserted "<< arr_ai->app_name << endl;
					temp_bst = NULL;
				}
				delete temp_bst;
			}
		}
		// cout << "app done" << endl<<endl;
	}
}
