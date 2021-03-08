#include "utils.cc"

#include <iostream>
#include <string>
#include <typeinfo>
#include <cstring>

using namespace std;

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

	struct bst *temp_bst;
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
            cout << endl;
        cout << queries_array[i]<<endl;
		execute_query(queries_array[i], pq, app_store, n_categories);
		if(i != q_queries-1)
			cout << endl;
	}
	// int number of queries
	// input all queries
	// parse query
	// execute query
	// Max heap
	// report
	// delete temp_bst;
	delete[] arr_ai;
	delete[] app_store;
	return 0;
}