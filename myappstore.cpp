#include <iostream>
#include <string>
#include "defn.h"
#include <typeinfo>

using namespace std;

string compareStrings(string a, string b)
{
	if(a>b)
		return ">";
	if(a<b)
		return "<";
	return "==";
}

// void insertIntoBST(struct bst *node, )

int main()
{
	int n_categories;
	cin >> n_categories;
	cin >> ws;
	struct categories *total_categories = new struct categories[n_categories];
	for(int i=0;i<n_categories;i++)
	{
		getline(cin,total_categories[i].category);
		total_categories[i].root = NULL;
	}
	for(int i=0;i<n_categories-1;i++)
	{
		cout << total_categories[i].category << compareStrings(total_categories[i].category,total_categories[i+1].category) << total_categories[i+1].category << endl;
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
	for(int i=0;i<m_apps;i++)
	{
		cout << arr_ai[i].category << "\t" << arr_ai[i].app_name << "\t" << arr_ai[i].version << "\t" << arr_ai[i].size << "\t" << arr_ai[i].units << "\t" << arr_ai[i].price << endl;
		// cout << typeid(arr_ai[i].category).name() << "\t" << typeid(arr_ai[i].app_name).name() << "\t" << typeid(arr_ai[i].version).name() << "\t" << typeid(arr_ai[i].size).name() << "\t" << typeid(arr_ai[i].units).name() << "\t" << typeid(arr_ai[i].price).name() << endl;
		// cout << endl;
	}
	// dont store it as an array of app_info, but push it into BST as soon as you read it.
	// insert into BST
	// int number of queries
	// input all queries
	// parse query
	// execute query
	// Max heap
	// report
	return 0;
}