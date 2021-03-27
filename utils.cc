#include "bst.h"
#include "heap.h"

#include <iostream>
#include <string>
#include <typeinfo>
#include <cstring>

using namespace std;

// static int pos =0;

// struct parsed_query{
// 	int query_type;
// 	string category_name;
// };

// Returns the number of elements in the BST
int num_of_elements(struct bst *root)
{
	int c = 1;
	if(root == NULL)
		return 0;
	else
	{
		c += num_of_elements(root->left);
		c += num_of_elements(root->right);
		return c;
	}
}

// Tokenizes the string based on the separater provided
void tokenize(string line, string sep, string *str_ptr)
{
    const char* sepa = sep.c_str();

    char* token;
	char str[line.length()];
    strcpy(str, line.c_str());
    char *rest = str;

    int i=0;
    while ((token = strtok_r(rest, sepa, &rest))) 
        str_ptr[i++] = token;
}

// returns metadata of the query
struct parsed_query parse_query(string query)
{
	string *frst_str_ptr = new string[100];
	string *scnd_str_ptr = new string[100];
	struct parsed_query temp_pq;

	tokenize(query,"\"",frst_str_ptr);
	temp_pq.category_name = frst_str_ptr[1];
	string to_tokenize = frst_str_ptr[0];
	
	tokenize(to_tokenize, " ", scnd_str_ptr);
	if(scnd_str_ptr[0] == "print-apps")
	{
		temp_pq.query_type = 3;
	}
	else if(scnd_str_ptr[0] == "find")
	{
		temp_pq.query_type = 2;
	}
	delete[] frst_str_ptr;
	delete[] scnd_str_ptr;
	return temp_pq;
}

// executes the query
void execute_query(string query, struct parsed_query pq, struct categories *app_store, int n_categories)
{
	if(pq.query_type == 2)
	{
		cout << "Category";
		int flag = 0;
		for(int i=0;i<n_categories;i++)
		{
			if(pq.category_name == app_store[i].category)
			{
				flag = 1;
				if(app_store[i].root == NULL)
				{
					cout << " \""<<pq.category_name<<"\" no apps found.";
				}
				else
				{
					cout <<": \""<<pq.category_name<<"\"";
					int count = num_of_elements(app_store[i].root);

					float *max_heap = new float[count];
					int posi = 0;
					inorder_insert(app_store[i].root, max_heap, posi);
					pos=0;
					posi=0;
					
					build_max_heap(max_heap,count);
			
					float max_price = ret_maximum(max_heap);
					inorder_print(app_store[i].root, max_price);
					delete[] max_heap;
				}
			}
		}

	}
	else if(pq.query_type == 3)
	{
		cout << "Category";
		int flag = 0;
		for(int i=0;i<n_categories;i++)
		{
			if(pq.category_name == app_store[i].category)
			{
				flag = 1;
				if(app_store[i].root == NULL)
				{
					cout << " \""<<pq.category_name<<"\" no apps found.";
				}
				else
				{
					cout <<": \""<<pq.category_name<<"\"";
					inorder(app_store[i].root);
				}
			}
		}
		if(flag == 0)
		{
			cout <<"\""<<pq.category_name<<"\" not found.";
		}
	}
}
