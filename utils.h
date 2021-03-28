#pragma once
#include "bst.h"
#include "heap.h"

#include <iostream>
#include <string>
#include <typeinfo>
#include <cstring>

using namespace std;

static int pos =0;

struct parsed_query{
	int query_type;
	string category_name;
	string low;
	string high;
};

int num_of_elements(struct bst *root);

void tokenize(string line, string sep, string *str_ptr);

int app_present(struct hash_table_entry** hash_table_store, int hash_table_size, string app_name);

struct parsed_query parse_query(string query);

void execute_query(string query, struct parsed_query pq, struct categories *app_store, int n_categories, struct hash_table_entry** hash_table_store, int hash_table_size);