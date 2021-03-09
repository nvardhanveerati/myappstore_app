#include "defn.h"

#include <iostream>
#include <string>
#include <typeinfo>
#include <cstring>

using namespace std;

static int pos = 0;

struct parsed_query{
	int query_type;
	string category_name;
};

void inorder(struct bst *root);

void inorder_insert(struct bst *root, float *max_heap);

void inorder_print(struct bst *root, float max_val);

void new_insert(struct bst *node, struct app_info ai, struct bst *ttemp);

void fillBST(struct bst *temp_bst, struct categories* app_store, int n_categories);