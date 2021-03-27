#include "utils.h"
#include "hash.h"

#include <iostream>
#include <string>
#include <typeinfo>
#include <cstring>

using namespace std;

int main()
{
	// Takes in category data
	int n_categories;
	cin >> n_categories;
	cin >> ws;
	struct categories *app_store = new struct categories[n_categories];
	for(int i=0;i<n_categories;i++)
	{
		getline(cin,app_store[i].category);
		app_store[i].root = NULL;
	}

	// Takes in application data
	int m_apps;
	cin >> m_apps;
	cin >> ws;

	struct app_info *arr_ai = new struct app_info[m_apps];
	struct bst *arr_bst = new struct bst[m_apps];
	
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
		arr_bst[i].record = arr_ai[i];
		arr_bst[i].left = NULL;
		arr_bst[i].right = NULL;
	}
	int hash_table_size = size_of_hashtable(m_apps);
	cout << "\tsize of hashtable: "<< hash_table_size<<endl;
	struct hash_table_entry **hash_table_store = new struct hash_table_entry*[hash_table_size];
	struct hash_table_entry *hash_table_entries = new struct hash_table_entry[m_apps];
	for(int i=0;i<hash_table_size;i++)
	{
		hash_table_store[i] = NULL;
	}
	for(int i=0;i<m_apps;i++)
	{
		hash_table_entries[i].app_name = arr_ai[i].app_name;
		hash_table_entries[i].app_node = NULL;
		hash_table_entries[i].next = NULL;
	}
	for(int i=0;i<m_apps;i++)
	{
		cout << "\t"<< hash_table_entries[i].app_name << endl;
		fillBST(&arr_bst[i], app_store,n_categories);
		fillHashTable(&arr_bst[i], hash_table_store, hash_table_entries[i], hash_table_size);
	}
	// cout << "\t"<< arr_bst[0].left->record.app_name << endl;
	int q_queries;
	cin>> q_queries;
	cin >> ws;
	string queries_array[q_queries];

	for(int i=0;i<q_queries;i++)
	{
		getline(cin, queries_array[i]);
		// struct parsed_query pq = parse_query(queries_array[i]);
		// if(i!=0)
        //     cout << endl;
        // cout << queries_array[i]<<endl;
		// execute_query(queries_array[i], pq, app_store, n_categories);
		// if(i != q_queries-1)
		// 	cout << endl;
	}
	delete[] hash_table_entries;
	delete[] hash_table_store;
	delete[] arr_bst;
	delete[] arr_ai;
	delete[] app_store;
	return 0;
}