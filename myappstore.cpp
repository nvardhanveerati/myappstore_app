#include <iostream>
#include <string>
#include "defn.h"
#include <typeinfo>

using namespace std;

// string compareStrings(string a, string b)
// {
// 	if(a>b)
// 		return ">";
// 	if(a<b)
// 		return "<";
// 	return "==";
// }

struct bst* insert(struct bst *node, struct app_info ai)
{
	if(node != NULL)
	{
		if(ai.category <= node->record.category)
		{
			cout << ai.category << "\t<=\t" << node->record.category <<endl;
			cout << "LEFT\t";
			node->left = insert(node->left, ai);
		}
		else if(ai.category > node->record.category)
		{
			cout << ai.category << "\t>\t" << node->record.category <<endl;
			cout << "RIGHT\t";
			node->right = insert(node->right, ai);
		}
	}
	cout <<endl;
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
void fillBSTData(struct app_info *arr_ai, struct categories *total_categories, int m_apps, int n_categories)
{
	for(int i=0;i<m_apps;i++)
	{
		cout << "\t" << arr_ai[i].app_name << endl;
		for(int j=0;j<n_categories;j++)
		{
			if(arr_ai[i].category ==  total_categories[j].category)
			{
				if(total_categories[j].root == NULL)
				{
					//add to base
					// THIS IS WORKING! 
					cout << "This is the base" << "\t" << arr_ai[i].app_name<<endl;
					struct bst *temp_bst = new struct bst;
					temp_bst->record = arr_ai[i];
					temp_bst->left = NULL;
					temp_bst->right = NULL;
					total_categories[j].root = temp_bst;
				}
				else
				{
					//add while loop to go to the right place and add 
					// THIS IS NOT. FIX THIS FIRST
					// THIS WORKED! ALTHOUGH ORDER IS WRONG
					cout << "This is not at base" << "\t" << arr_ai[i].app_name<<endl;
					struct bst *temp_bst = new struct bst;
					temp_bst = insert(total_categories[j].root, arr_ai[i]);
					cout << "inserted "<< arr_ai->app_name << endl;
				}
			}
		}
		cout << "app done" << endl << endl;
	}
}

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
	// for(int i=0;i<n_categories-1;i++)
	// {
	// 	cout << total_categories[i].category << compareStrings(total_categories[i].category,total_categories[i+1].category) << total_categories[i+1].category << endl;
	// }
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
	// for(int i=0;i<m_apps;i++)
	// {
	// 	cout << arr_ai[i].category << "\t" << arr_ai[i].app_name << "\t" << arr_ai[i].version << "\t" << arr_ai[i].size << "\t" << arr_ai[i].units << "\t" << arr_ai[i].price << endl;
	// 	// cout << typeid(arr_ai[i].category).name() << "\t" << typeid(arr_ai[i].app_name).name() << "\t" << typeid(arr_ai[i].version).name() << "\t" << typeid(arr_ai[i].size).name() << "\t" << typeid(arr_ai[i].units).name() << "\t" << typeid(arr_ai[i].price).name() << endl;
	// 	// cout << endl;
	// }

	fillBSTData(arr_ai, total_categories,m_apps,n_categories);
	cout << "this is outside: " << total_categories[0].root->record.app_name << endl;
	cout << "this is outside: " << total_categories[1].root->record.app_name << endl;
	cout << "this is outside: " << total_categories[2].root->record.app_name << endl;
	cout << "this is outside: " << total_categories[0].root->left->record.app_name;
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