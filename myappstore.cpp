#include <iostream>
#include <string>
#include "defn.h"
#include <typeinfo>

using namespace std;

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
		cout << "\t" << root->record.app_name<<endl;
		inorder(root->right);
	}
}

void inorder_insert(struct bst *root, float *max_heap)
{
	static int pos = 0;
	if(root == NULL)
		return;
	else
	{
		inorder_insert(root->left, max_heap);
		// cout << "\t" << root->record.app_name<<endl;
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
			cout << "\t" << root->record.app_name <<endl;
		}
		inorder_print(root->right, max_val);
	}
}

void maxHeapify(float *max_heap, int i, int n)
{
	int largest = i;
	int l = 2*i;
	int r = 2*i+1;

	if(l<n && max_heap[l]>max_heap[i])
	{
		largest = l;
	}
	if(r<n && max_heap[largest] < max_heap[r])
	{
		largest = r;
	}

	if(largest!=i)
	{
		float temp = max_heap[largest];
		max_heap[largest] = max_heap[i];
		max_heap[i] = temp;

		maxHeapify(max_heap,largest,n);
	}
}

void build_max_heap(float *max_heap, int n)
{
	for(int i=n/2;i>=0;i--)
	{
		maxHeapify(max_heap,i,n);
	}
}

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
	token = strtok(str, sepa);

	int i=0;
	while (token != NULL)
	{
		str_ptr[i] = token;
		token = strtok(NULL, sepa);
		i++;
	}
}

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

void execute_query(string query, struct parsed_query pq, struct categories *app_store, int n_categories)
{
	if(pq.query_type == 2)
	{
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
					cout <<pq.category_name<<" no apps found."<< endl;
				}
				else
				{
					// cout << "\nCategory: "<<pq.category_name;
					cout <<pq.category_name<<endl;
					//get the number of elements in the tree
					int count = num_of_elements(app_store[i].root);
					// cout << "\t" << count << endl;

					float *max_heap = new float[count];
					inorder_insert(app_store[i].root, max_heap);
					// cout << "\tone: " << max_heap[0] << "\ttwo: " << max_heap[1] << "\tthree: " << max_heap[2] << "\tfour: " << max_heap[3]<<endl;
					build_max_heap(max_heap,count);
					// cout << "\tone: " << max_heap[0] << "\ttwo: " << max_heap[1] << "\tthree: " << max_heap[2] << "\tfour: " << max_heap[3]<<endl;
					float max_price = max_heap[0];
					inorder_print(app_store[i].root, max_price);
				}
			}
		}

	}
	else if(pq.query_type == 3)
	{
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
					cout <<pq.category_name<<" no apps found."<< endl;
				}
				else
				{
					// cout << "\nCategory: "<<pq.category_name<<endl;
					cout <<pq.category_name<<endl;
					//print by traversing inorder
					inorder(app_store[i].root);
				}
			}
		}
		if(flag == 0)
		{
			// cout << "\nCategory "<<pq.category_name<<" not found."<<endl;
			cout <<pq.category_name<<" not found."<<endl;
		}
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

// void insertIntoBST(struct bst *node, )
void fillBSTData(struct app_info *arr_ai, struct categories *app_store, int m_apps, int n_categories)
{
	for(int i=0;i<m_apps;i++)
	{
		// cout << "\t" << arr_ai[i].app_name << endl;
		for(int j=0;j<n_categories;j++)
		{
			if(arr_ai[i].category ==  app_store[j].category)
			{
				if(app_store[j].root == NULL)
				{
					// cout << "This is the base:\t";
					struct bst *temp_bst = new struct bst;
					temp_bst->record = arr_ai[i];
					temp_bst->left = NULL;
					temp_bst->right = NULL;
					app_store[j].root = temp_bst;
				}
				else
				{
					// cout << "This is not at base:\t";
					struct bst *temp_bst = new struct bst;
					temp_bst = insert(app_store[j].root, arr_ai[i]);
					// cout << "\ninserted "<< arr_ai->app_name << endl;
				}
			}
		}
		// cout << "app done" << endl<<endl;
	}
}

int main()
{
	int n_categories;
	cin >> n_categories;
	cin >> ws;
	struct categories *app_store = new struct categories[n_categories];
	for(int i=0;i<n_categories;i++)
	{
		getline(cin,app_store[i].category);
		app_store[i].root = NULL;
	}
	int m_apps;
	cin >> m_apps;
	cin >> ws;
	//for now
	struct app_info *arr_ai = new struct app_info[m_apps];
	//end
	for(int i=0;i<m_apps;i++)
	{
		string s[6];
		getline(cin,s[0]);
		getline(cin,s[1]);
		getline(cin,s[2]);
		getline(cin,s[3]);
		getline(cin,s[4]);
		getline(cin,s[5]);

		struct app_info ai = {s[0], s[1], s[2], stof(s[3]), s[4], stof(s[5])};
		arr_ai[i] = ai;
	}

	fillBSTData(arr_ai, app_store,m_apps,n_categories);
	// dont store it as an array of app_info, but push it into BST as soon as you read it.
	// insert into BST
	int q_queries;
	cin>> q_queries;
	cin >> ws;
	string queries_array[q_queries];
	// cout << "\n\n------------------- OUTPUT ------------------------ \n\n";
	for(int i=0;i<q_queries;i++)
	{
		getline(cin, queries_array[i]);
		struct parsed_query pq = parse_query(queries_array[i]);
		if(i!=0)
			cout <<"\n";
		cout << "Category ";
		execute_query(queries_array[i], pq, app_store, n_categories);
	}
	// int number of queries
	// input all queries
	// parse query
	// execute query
	// Max heap
	// report
	delete[] arr_ai;
	delete[] app_store;
	return 0;
}