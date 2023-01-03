#ifndef HASHTABLE_H
#define HASHTABLE_H

#define MAX_NAME	256
#define TABLE_SIZE	10

typedef struct 
{
	char name[MAX_NAME];
	int age;
} person;

unsigned int hash(char *name);
void init_hash_table();
void print_table();
bool hash_table_insert(person *p);
person* hash_table_lookup(char *name);
person* hash_table_delete(char *name);

#endif
