#include "bst.cc"
#include "heap.cc"

#include <iostream>
#include <string>
#include <typeinfo>
#include <cstring>

using namespace std;

int num_of_elements(struct bst *root);

void tokenize(string line, string sep, string *str_ptr);

struct parsed_query parse_query(string query);

void execute_query(string query, struct parsed_query pq, struct categories *app_store, int n_categories);