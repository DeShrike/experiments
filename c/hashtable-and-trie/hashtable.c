#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "hashtable.h"

#define DELETED_NODE (person*)(0xFFFFFFFFFFFFFFFFUL)

person* hash_table[TABLE_SIZE];

unsigned int hash(char *name)
{
	int len = strnlen(name, MAX_NAME);
	unsigned int hash_value = 0;
	for (int i = 0; i < len; i++)
	{
		hash_value += name[i];
		hash_value *= name[i];
		hash_value = hash_value % TABLE_SIZE;
	}

	return hash_value;
}

void init_hash_table()
{
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		hash_table[i] = NULL;
	}
}

void print_table()
{
	printf("------------------------------------------\n");
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		if (hash_table[i] == NULL)
		{
			printf("\t%i\t---\n", i);
		}
		else if (hash_table[i] == DELETED_NODE)
		{
			printf("\t%i\t(DELETED)\n", i);
		}
		else
		{
			printf("\t%i\t%s\n", i, hash_table[i]->name);
		}
	}

	printf("------------------------------------------\n");
}

bool hash_table_insert(person *p)
{
	if (p == NULL)
	{
		return false;
	}

	int index = hash(p->name);

	for (int i = 0; i < TABLE_SIZE; i++)
	{
		int try = (i + index) % TABLE_SIZE;
		if (hash_table[try] == NULL || hash_table[try] == DELETED_NODE)
		{
			hash_table[try] = p;
			return true;
		}
	}

	return false;
}

person* hash_table_lookup(char *name)
{
	int index = hash(name);

	for (int i = 0; i < TABLE_SIZE; i++)
	{
		int try = (i + index) % TABLE_SIZE;
		if (hash_table[try] == NULL)
		{
			return NULL;
		}

		if (hash_table[try] == DELETED_NODE)
		{
			continue;
		}

		if (strncmp(hash_table[try]->name, name, MAX_NAME) == 0)
		{
			return hash_table[try];
		}
	}

	return NULL;
}

person* hash_table_delete(char *name)
{
	int index = hash(name);
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		int try = (i + index) % TABLE_SIZE;
		if (hash_table[try] == NULL)
		{
			return NULL;
		}

		if (hash_table[try] == DELETED_NODE)
		{
			continue;
		}

		if (strncmp(hash_table[try]->name, name, MAX_NAME) == 0)
		{
			person* tmp = hash_table[try];
			hash_table[try] = DELETED_NODE;
			return tmp;
		}
	}

	return NULL;
}
