#include "bst.cc"
#include "heap.cc"

#include <iostream>
#include <string>
#include <typeinfo>
#include <cstring>

using namespace std;

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

struct parsed_query parse_query(string query)
{
	string *frst_str_ptr = new string[100];
	string *scnd_str_ptr = new string[100];
	struct parsed_query temp_pq;

	// old_tokenize(query,"\"",frst_str_ptr);
	tokenize(query,"\"",frst_str_ptr);
	temp_pq.category_name = frst_str_ptr[1];
	string to_tokenize = frst_str_ptr[0];
	
	// old_tokenize(to_tokenize, " ", scnd_str_ptr);
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

void execute_query(string query, struct parsed_query pq, struct categories *app_store, int n_categories)
{
	if(pq.query_type == 2)
	{
		cout << "Category";
		// cout << pq.query_type << "\t" << pq.category_name <<endl;
		int flag = 0;
		for(int i=0;i<n_categories;i++)
		{
			if(pq.category_name == app_store[i].category)
			{
				flag = 1;
				if(app_store[i].root == NULL)
				{
					// cout << "\nCategory "<<pq.category_name<<" no apps found."<< endl;
					// cout << " \""<<pq.category_name<<"\" no apps found.\n";
					cout << " \""<<pq.category_name<<"\" no apps found.";
				}
				else
				{
					// cout << "\nCategory: "<<pq.category_name;
					// cout <<": \""<<pq.category_name<<"\""<<endl;
					cout <<": \""<<pq.category_name<<"\"";
					//get the number of elements in the tree
					int count = num_of_elements(app_store[i].root);
					// cout << "\tLALALALALALA number of apps in "<<pq.category_name<<":\t" << count << endl;

					float *max_heap = new float[count];
					// float max_heap[count];
					// cout << "\tINSIDE INORDER_INSERT: "<<endl;
					// cout << "\t";
					// int *pos = new int;
					pos = 0;
					inorder_insert(app_store[i].root, max_heap);
					pos=0;
					// cout << "\tone: " << max_heap[0] << "\ttwo: " << max_heap[1] << "\tthree: " << max_heap[2] << "\tfour: " << max_heap[3]<<endl;
					// cout << "\n\tOUTSSIDE INORDER_INSERT: "<<endl;
					// cout << "\t";
					// for(int pp=0;pp<count;pp++)
					// {
					// 	cout << max_heap[pp] << "\t";
					// }
					// cout << endl;

					build_max_heap(max_heap,count);
					// cout << "\tone: " << max_heap[0] << "\ttwo: " << max_heap[1] << "\tthree: " << max_heap[2] << "\tfour: " << max_heap[3]<<endl;
					float max_price = max_heap[0];
					inorder_print(app_store[i].root, max_price);
					delete[] max_heap;
					// delete pos;
				}
			}
		}

	}
	else if(pq.query_type == 3)
	{
		cout << "Category";
		int flag = 0;
		// cout << pq.query_type << "\t" << pq.category_name <<endl;
		// if(app_store)
		for(int i=0;i<n_categories;i++)
		{
			if(pq.category_name == app_store[i].category)
			{
				flag = 1;
				if(app_store[i].root == NULL)
				{
					// cout << "\nCategory "<<pq.category_name<<" no apps found."<< endl;
					// cout << " \""<<pq.category_name<<"\" no apps found."<<endl;
					cout << " \""<<pq.category_name<<"\" no apps found.";
				}
				else
				{
					// cout << "\nCategory: "<<pq.category_name<<endl;
					// cout <<": \""<<pq.category_name<<"\""<<endl;
					cout <<": \""<<pq.category_name<<"\"";
					//print by traversing inorder
					inorder(app_store[i].root);
				}
			}
		}
		if(flag == 0)
		{
			// cout << "\nCategory "<<pq.category_name<<" not found."<<endl;
			cout <<"\""<<pq.category_name<<"\" not found.";
		}
	}
}
