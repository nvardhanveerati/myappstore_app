#pragma once
#include "defn.h"
#include "utils.h"

#include <iostream>
#include <string>
#include <typeinfo>
#include <cstring>

using namespace std;

// static int pos = 0;

// struct parsed_query{
// 	int query_type;
// 	string category_name;
// };

void inorder(struct bst *root);

void free_apps_inorder(struct bst* root);

void inorder_insert(struct bst *root, float *max_heap, int &pos);

void inorder_print(struct bst *root, float max_val);

void new_insert(struct bst *node, struct app_info ai, struct bst *ttemp);

void fillBST(struct bst *temp_bst, struct categories* app_store, int n_categories);

void range_inorder_checker_price(struct bst *root, float low, float high, int &count);

void range_inorder_price(struct bst *root, float low, float high);

void range_inorder_checker_app(struct bst *root, string low, string high, int &count);

void range_inorder_app(struct bst *root, string low, string high);

void report_inorder(struct bst* root, string app_name);