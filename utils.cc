#include "bst.h"
#include "heap.h"
#include "hash.h"

#include <iostream>
#include <string>
#include <typeinfo>
#include <cstring>
#include <iomanip>


using namespace std;

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

int height_of_bst(struct bst* root)
{
	if(root == NULL)
	{
		return 0;
	}
	if(root->left == NULL && root->right==NULL)
	{
		return 0;
	}
	else
	{
		int lh = height_of_bst(root->left);
		int rh = height_of_bst(root->right);
		return (max(lh,rh)+1);
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

int app_present(struct hash_table_entry** hash_table_store, int hash_table_size, string app_name)
{
	int index = hash_function(app_name) % hash_table_size;
	int out=0;
	hash_table_entry *ht_node = hash_table_store[index];
	while(ht_node != NULL)
	{
		if(ht_node->app_name == app_name)
		{
			out = 1;
			break;
		}
		ht_node = ht_node->next;
	}
	return out;
}

struct bst* get_bst_node(struct hash_table_entry** hash_table_store, int hash_table_size, string app_name)
{
	int index = hash_function(app_name) % hash_table_size;
	hash_table_entry *ht_node = hash_table_store[index];
	while(ht_node!= NULL)
	{
		if(app_name == ht_node->app_name)
		{
			break;
			// return ht_node->app_node;
		}
		ht_node = ht_node->next;
	}
	return ht_node->app_node;
}

struct bst* get_min_val_node(struct bst* root)
{
	bst* temp = root;
    while (temp && temp->left != NULL)
    {
		temp = temp->left;
	}
	return temp;
}

int max_length_of_chain(struct hash_table_entry** hash_table_store, int hash_table_size)
{
	hash_table_entry* ht_node;
	int max_val = 0;
	int count = 0;
	for(int i=0;i<hash_table_size;i++)
	{
		ht_node = hash_table_store[i];
		while(ht_node!=NULL)
		{
			count++;
			ht_node = ht_node->next;
		}
		// cout << "Length of index "<<i<<" is "<<count<<endl;
		if(max_val<count)
		{
			max_val = count;
		}
		count = 0;
	}
	return max_val;
}

int number_of_chains(struct hash_table_entry** hash_table_store, int hash_table_size, int len_chain)
{
	int count_size = 0;
	int count_freq = 0;
	hash_table_entry* ht_node;
	for(int i=0;i<hash_table_size;i++)
	{
		ht_node = hash_table_store[i];
		while(ht_node!=NULL)
		{
			count_size++;
			ht_node = ht_node->next;
		}
		// cout << "Length of index "<<i<<" is "<<count<<endl;
		if(len_chain == count_size)
		{
			count_freq++;
		}
		count_size = 0;
	}
	return count_freq;
}

string get_rand_app_name(struct hash_table_entry** hash_table_store, int hash_table_size)
{
	int n=1000;
	hash_table_entry* ht_node = hash_table_store[n%hash_table_size];
	int i=1;
	while(ht_node==NULL && i<hash_table_size)
	{
		ht_node = hash_table_store[(n+i)%hash_table_size];
		i++;
	}
	return ht_node->app_name;
}

string get_category_name(struct hash_table_entry** hash_table_store, int hash_table_size, string app_name)
{
	int index = hash_function(app_name) % hash_table_size;
	hash_table_entry *ht_node = hash_table_store[index];
	string app_category;
	while(ht_node!=NULL)
	{
		if(ht_node->app_name == app_name)
		{
			app_category = ht_node->app_node->record.category;
			break;
		}
		else
		{
			ht_node = ht_node->next;
		}
	}
	return app_category;
}

void custom_find_app(struct categories *app_store, int n_categories, string app_category, string app_name)
{
	for(int i=0;i<n_categories;i++)
	{
		if(app_category == app_store[i].category)
		{
			struct bst* temp_node = app_store[i].root;
			report_inorder(temp_node, app_name);
		}
	}
}

void delete_hash_node(struct hash_table_entry** hash_table_store, int hash_table_size, string app_name)
{
	int index = hash_function(app_name) % hash_table_size;
	hash_table_entry *ht_node = hash_table_store[index];

	if(ht_node->app_name == app_name)
	{
		hash_table_store[index] = ht_node->next;
		return;
	}
	hash_table_entry *ht_node_next;
	while(ht_node->next != NULL)
	{
		ht_node_next = ht_node->next;
		if(ht_node_next->app_name == app_name)
		{
			break;
		}
		ht_node = ht_node_next;
	}
	ht_node->next = ht_node_next->next;
	return;
}

struct bst* delete_bst_node(struct bst* delete_node, struct bst* main_root)
{
	string delete_node_app = delete_node->record.app_name;
	string main_root_app = main_root->record.app_name;
	if(main_root == NULL)
	{
		return main_root;
	}
	if(delete_node_app > main_root_app)
	{
		main_root->right = delete_bst_node(delete_node, main_root->right);
	}
	else if(delete_node_app < main_root_app)
	{
		main_root->left = delete_bst_node(delete_node, main_root->left);
	}
	else
	{
		struct bst* temp;
		if(main_root->left == NULL && main_root->right == NULL)
		{
			return NULL;
		}

		else if(main_root->left == NULL)
		{
			temp = main_root->right;
			return temp;
		}
		else if(main_root->right == NULL)
		{
			temp = main_root->left;
			return temp;
		}
		temp = get_min_val_node(main_root->right);
		main_root->record = temp->record;
		main_root->right = delete_bst_node(temp, main_root->right);
	}
	return main_root;
}

// returns metadata of the query
struct parsed_query parse_query(string query)
{
	string *frst_str_ptr = new string[100];
	string *scnd_str_ptr = new string[100];
	struct parsed_query temp_pq;

	tokenize(query,"\"",frst_str_ptr);
	// cout << frst_str_ptr[0] << "ikkada";
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
	else if(frst_str_ptr[0] == "delete ")
	{
		temp_pq.category_name = frst_str_ptr[1]; //category_name
		temp_pq.query_type = 7;
		temp_pq.high = temp_pq.low = frst_str_ptr[3]; //app_name
		// cout << "\tone: "<< frst_str_ptr[1] << endl;
		// cout << "\ttwo: "<< frst_str_ptr[2] << endl;
		// cout << "\tthree: "<<frst_str_ptr[3] << endl;
		// cout << "\tfour: "<<frst_str_ptr[4] << endl;
	}
	else if(frst_str_ptr[0] == "report" || frst_str_ptr[0] == "report ")
	{
		temp_pq.query_type = 8;
	}
	delete[] frst_str_ptr;
	delete[] scnd_str_ptr;
	return temp_pq;
}

// executes the query
void execute_query(string query, struct parsed_query pq, struct categories *app_store, int n_categories, struct hash_table_entry** hash_table_store, int hash_table_size)
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
			cout <<" \""<<pq.category_name<<"\" not found.";
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
				// cout << "\t" << low<<endl;
				// cout << "\t" << high<<endl;
				int range_checker=0;
				range_inorder_checker_price(app_store[i].root, low, high, range_checker);
				// cout << range_checker << endl;
				if(range_checker == 0)
				{
					cout << "No applications found in \""<<pq.category_name<< "\" for the given price range ($"<<fixed<<setprecision(2)<<low<<",$"<<fixed<<setprecision(2)<<high<<").";
				}
				else
				{
					cout << "Applications in Price Range ($"<<fixed<<setprecision(2)<<low<<",$"<<fixed<<setprecision(2)<<high<<") in Category: \""<<pq.category_name <<"\"";
					range_inorder_price(app_store[i].root, low, high);
				}
			}
		}
		if(flag == 1)
		{
			cout<<"Category \""<< pq.category_name<< "\" not found.";
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
				// cout << range_checker << endl;
				if(range_checker == 0)
				{
					cout << "No applications found in \""<<pq.category_name<< "\" for the given range (\""<<pq.low<<"\",\""<<pq.high<<"\").";
				}
				else
				{
					cout << "Applications in Range ("<<pq.low<<","<<pq.high<<") in Category: \""<<pq.category_name <<"\"";
					range_inorder_app(app_store[i].root, pq.low, pq.high);
				}
			}
		}
		if(flag == 1)
		{
			// cout<<"Category "<< pq.category_name<< " not found.";
			cout << "No applications found in \""<<pq.category_name<< "\" for the given range (\""<<pq.low<<"\",\""<<pq.high<<"\").";
		}
	}
	else if(pq.query_type == 1)
	{
		string app_name = pq.category_name;
		// cout << "\t" <<app_name << endl;
		if(app_present(hash_table_store, hash_table_size, app_name) == 0)
		{
			cout << "Application \""<<app_name<<"\" not found.";
		}
		else
		{
			struct bst* reqd_root = get_bst_node(hash_table_store, hash_table_size, app_name);
			cout << "Found Application: \""<<app_name<<"\""<<endl;
			cout << "\tCategory: " << reqd_root->record.category<<endl; // Name of category
  			cout << "\tApplication Name: " << reqd_root->record.app_name<<endl; // Name of the application
  			cout << "\tVersion: " << reqd_root->record.version<<endl; // Version number
  			cout << "\tSize: " << reqd_root->record.size<<endl; // Size of the application
  			cout << "\tUnits: " << reqd_root->record.units<<endl; // GB or MB
  			cout << "\tPrice: $" <<fixed<<setprecision(2)<<(reqd_root->record.price); // Price in $ of the applicationn
		}
	}
	else if(pq.query_type == 4)
	{
		int cat_flag = 0;
		int cat_index = 0;
		for(int i=0;i<n_categories;i++)
		{
			if(pq.category_name == app_store[i].category)
			{
				cat_flag = 1;
				cat_index = i;
			}
		}
		if(cat_flag == 0)
		{
			cout << "Category \""<<pq.category_name<<"\" not found.";
		}
		else
		{
			struct bst* reqd_node = app_store[cat_index].root;
			if(reqd_node == NULL)
			{
				cout << "Category \""<<pq.category_name<<"\" no free apps found.";
			}
			else
			{
				cout << "Free apps in Category: \""<<pq.category_name<<"\"";
				free_apps_inorder(reqd_node);
			}
		}
	}
	else if(pq.query_type == 7)
	{
		// cout << "Delete function Started"<<endl;
		string app_name = pq.low;
		if(app_present(hash_table_store, hash_table_size,app_name) == 0)
		{
			cout << "Application \""<<app_name<<"\" not found in category \""<<pq.category_name<<"\"; unable to delete";
		}
		else
		{
			int cat_flag = 0;
			int cat_index = 0;
			for(int i=0;i<n_categories;i++)
			{
				if(pq.category_name == app_store[i].category)
				{
					cat_flag = 1;
					cat_index = i;
				}
			}
			if(cat_flag!=0)
			{
				struct bst* main_root = app_store[cat_index].root;
				struct bst* delete_node = get_bst_node(hash_table_store, hash_table_size, app_name);
				// cout <<"\tdelete_node: "<<delete_node->record.app_name<<endl;
				main_root = delete_bst_node( delete_node, main_root);
			}
		}
	}
	else if(pq.query_type == 8)
	{
		// BST
		cout << "------------------------------------- BST ------------------------------------"<<endl;
		for(int i=0;i<n_categories;i++)
		{
			cout << "Category: " << app_store[i].category << endl;
			cout << "\tNumber of elements: "<<num_of_elements(app_store[i].root)<<endl;
			cout << "\tHeight of BST: "<<height_of_bst(app_store[i].root)<<endl;
			if(app_store[i].root!= NULL)
			{
				cout << "\tHeight of left subtree: "<<height_of_bst(app_store[i].root->left)<<endl;
				cout << "\tHeight of right subtree: "<<height_of_bst(app_store[i].root->right)<<endl;
			}
			else
			{
				cout << "\tHeight of left subtree: NA"<<endl;
				cout << "\tHeight of right subtree: NA"<<endl;
			}
		}

		//Hash Table
		int max_len = max_length_of_chain(hash_table_store, hash_table_size);
		cout << "--------------------------------- Hash Table ---------------------------------"<<endl;
		int chains[max_len+1];
		int count_chains=0;
		for(int i=0;i<max_len+1;i++)
		{
			chains[i] = number_of_chains(hash_table_store, hash_table_size, i);
			cout << "\tLength: "<< i<<"    Number of Chains: "<< chains[i]<<endl;
			count_chains += i*chains[i];
		}
		double load_factor = count_chains*1.0/hash_table_size;
		// double d = 5 / (double) 20;
		cout << "Load Factor of this Hash Table: "<< load_factor<<endl;
		cout << "----------------------------- Compare query Times -----------------------------"<<endl;
		string ran_app_name = get_rand_app_name(hash_table_store, hash_table_size);
		cout << ran_app_name <<endl;

		time_t a_start, a_end;
		time_t b_start, b_end;
		a_start = clock();
		string app_category = get_category_name(hash_table_store,hash_table_size, ran_app_name);
		custom_find_app(app_store, n_categories, app_category, ran_app_name);
		a_end = clock();

		b_start = clock();
		struct parsed_query new_pq;
		new_pq.category_name = ran_app_name;
		new_pq.query_type = 1;
		string our_query = "find app "+ran_app_name;

		execute_query(our_query, new_pq, app_store, n_categories, hash_table_store, hash_table_size);
		b_end = clock();

		double duration_1 = double(a_end - a_start);
		cout <<endl<< "Duration of Process 1: "<<duration_1<< " clock ticks";

		double duration_2 = double(b_end - b_start);
		cout <<endl<< "Duration of Process 2: "<<duration_2<< " clock ticks";
	}
}
