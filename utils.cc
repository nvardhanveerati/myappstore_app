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
	// cout << "penta penta "<< frst_str_ptr[1] << endl;
	// temp_pq.category_name = frst_str_ptr[1];
	// string to_tokenize = frst_str_ptr[0];
	// cout << "double penta penta: "<< frst_str_ptr[0] << endl;

	// tokenize(to_tokenize, " ", scnd_str_ptr);
	if(frst_str_ptr[0] == "print-apps category ")
	{
		// cout << "is it here?" << endl;
		temp_pq.category_name = frst_str_ptr[1];
		temp_pq.query_type = 3;
		temp_pq.high="";
		temp_pq.low="";
	}
	else if(frst_str_ptr[0] == "find app ")
	{
		// cout << "and here?" << endl;
		temp_pq.query_type = 1;
		temp_pq.category_name = frst_str_ptr[1];
		temp_pq.high="";
		temp_pq.low="";
	}
	else if(frst_str_ptr[0] == "find max price apps ")
	{
		// cout << "and here?" << endl;
		temp_pq.category_name = frst_str_ptr[1];
		temp_pq.query_type = 2;
		temp_pq.high="";
		temp_pq.low="";
	}
	else if(frst_str_ptr[0] == "find price free ")
	{
		// cout << "and here?" << endl;
		temp_pq.query_type = 4;
		temp_pq.category_name = frst_str_ptr[1];
		temp_pq.high="";
		temp_pq.low="";
	}
	else if(frst_str_ptr[0] == "range ")
	{
		// cout << "range query |"<< frst_str_ptr[2]<<endl;
		if(frst_str_ptr[2] == " app ")
		{
			temp_pq.category_name = frst_str_ptr[1];
			temp_pq.query_type = 6;
			// cout << "\tlow: "<<frst_str_ptr[3]<<endl;
			// cout << "\thigh: "<<frst_str_ptr[5]<<endl;
			temp_pq.high=frst_str_ptr[5];
			temp_pq.low=frst_str_ptr[3];
		}
		else
		{
			tokenize(frst_str_ptr[2], " ", scnd_str_ptr);
			// cout << "\tprice: "<<scnd_str_ptr[0]<<endl;
			// cout << "\tlow: "<<scnd_str_ptr[1]<<endl;
			// cout << "\thigh: "<<scnd_str_ptr[2]<<endl;
			if(scnd_str_ptr[0] == "price")
			{
				temp_pq.category_name = frst_str_ptr[1];
				temp_pq.query_type = 5;
				temp_pq.high = scnd_str_ptr[2];
				temp_pq.low = scnd_str_ptr[1];
			}
		}
		// if(scnd_str_ptr[2] == "price")
		// {
		// 	cout << frst_str_ptr[0] + frst_str_ptr[2]<<endl;
		// 	temp_pq.query_type = 5;
		// 	temp_pq.high=scnd_str_ptr[4];
		// 	temp_pq.low=scnd_str_ptr[3];
		// 	cout << "I am here " << endl;
		// }
		// else if(scnd_str_ptr[2] == "app")
		// {
		// 	temp_pq.query_type = 6;
		// 	temp_pq.high=scnd_str_ptr[4];
		// 	temp_pq.low=scnd_str_ptr[3];
		// }
		// cout << "\thigh: " << temp_pq.high<<endl;
		// cout << "\tlow: " << temp_pq.low<<endl;
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
	else if(pq.query_type == 5)
	{
		// cout << "Parsing range price 5" << endl;
		// cout << query <<endl;
		int flag = 1;
		for(int i=0;i<n_categories;i++)
		{
			// cout <<"\tThis is where it is going wrong: " << pq.category_name<<endl;
			if(pq.category_name == app_store[i].category)
			{

				flag = 0;
				float high = stof(pq.high);
				float low = stof(pq.low);
				cout << "\t" << low<<endl;
				cout << "\t" << high<<endl;
				int range_checker=0;
				range_inorder_checker_price(app_store[i].root, low, high, range_checker);
				cout << range_checker << endl;
				if(range_checker == 0)
				{
					cout << "No applications found in "<<pq.category_name<< " for the given price range ("<<low<<","<<high<<")."<<endl;
				}
				else
				{
					cout << "Applications in Price Range ("<<low<<","<<high<<") in Category: "<<pq.category_name <<".";
					range_inorder_price(app_store[i].root, low, high);
				}
			}
		}
		if(flag == 1)
		{
			cout<<"Category "<< pq.category_name<< " not found.";
		}
	}
	else if(pq.query_type == 6)
	{
		// cout << "Parsing range app 6" << endl;
		int flag = 1;
		for(int i=0;i<n_categories;i++)
		{
			if(pq.category_name == app_store[i].category)
			{
				flag = 0;
				int range_checker=0;
				range_inorder_checker_app(app_store[i].root, pq.low, pq.high, range_checker);
				cout << range_checker << endl;
				if(range_checker == 0)
				{
					cout << "No applications found in "<<pq.category_name<< " for the given range ("<<pq.low<<","<<pq.high<<")."<<endl;
				}
				else
				{
					cout << "Applications in Range ("<<pq.low<<","<<pq.high<<") in Category: "<<pq.category_name <<".";
					range_inorder_app(app_store[i].root, pq.low, pq.high);
				}
			}
		}
		if(flag == 1)
		{
			cout<<"Category "<< pq.category_name<< " not found.";
		}
	}
}
