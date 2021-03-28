#pragma once
#include "prime.h"
#include <iostream>

using namespace std;


int hash_function(string app_name);
int size_of_hashtable(int num_elements);
void fillHashTable(struct bst *temp_bst, struct hash_table_entry **hash_table_store, struct hash_table_entry &ht_entry, int hash_table_size);