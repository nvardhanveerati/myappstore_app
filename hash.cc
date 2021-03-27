#include "prime.h"
#include "defn.h"
#include <iostream>

using namespace std;

int hash_function(string app_name)
{
    int sum=0;
    for(int i=0;i<app_name.length();i++)
    {
        sum += int(app_name[i]);
    }
    return sum;
}

int size_of_hashtable(int num_elements)
{
    int size = 2*num_elements;
    while(true)
    {
        if(TestForPrime(++size))
        {
            return size;
        }
    }
}

void fillHashTable(struct bst *temp_bst, struct hash_table_entry **hash_table_store, hash_table_entry ht_entry, int hash_table_size)
{
    string temp_app_name = ht_entry.app_name;
    int index = hash_function(temp_app_name) % hash_table_size;
    cout << "\t" << temp_app_name << ": "<<index<< "\t" <<  hash_function(temp_app_name)<< endl;

    if(hash_table_store[index] == NULL)
    {
        hash_table_store[index] = &ht_entry;
    }
    else
    {
        hash_table_entry *old_head = hash_table_store[index];
        hash_table_store[index] = &ht_entry;
        hash_table_store[index]->next = old_head;
    }
}