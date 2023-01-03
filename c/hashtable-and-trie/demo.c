#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <termios.h>
#include "hashtable.h"
#include "trie.h"

void test_hashtable()
{
	init_hash_table();

	person jacob = { .name = "Jacob", .age = 1234 };
	person mary = { .name = "Mary", .age = 2341 };
	person john = { .name = "John", .age = 3412 };
	person bob = { .name = "Bob", .age = 4123 };
	person jane = { .name = "Jane", .age = 423 };
	person kate = { .name = "Kate", .age = 23 };

	hash_table_insert(&jacob);
	hash_table_insert(&mary);
	hash_table_insert(&john);
	hash_table_insert(&bob);
	hash_table_insert(&jane);
	hash_table_insert(&kate);

	print_table();

	hash_table_delete("Jane");

	print_table();
}

void test_trie()
{
	trienode *root = NULL;
	trie_insert(&root, "hello");
	trie_insert(&root, "world");
	trie_insert(&root, "words");
	trie_insert(&root, "how");
	trie_insert(&root, "python");
	trie_insert(&root, "compiler");
	trie_insert(&root, "C++");
	trie_insert(&root, "are");
	trie_insert(&root, "C#");
	trie_insert(&root, "you");

	trie_print(root);

	printf("compiler: %d\n", trie_search(root, "compiler"));
	printf("python: %d\n", trie_search(root, "python"));
	printf("golang: %d\n", trie_search(root, "golang"));

	trie_delete(&root, "python");
	trie_delete(&root, "words");

	trie_print(root);
}

int main(void)
{
	struct termios old_settings;
	struct termios new_settings;

	tcgetattr(STDIN_FILENO, &old_settings);
	new_settings = old_settings;

	new_settings.c_lflag &= (~ICANON);
	new_settings.c_lflag &= (~ECHO);

	tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);

	printf("Select:\n");
	printf("(H)ashtable\n");
	printf("(T)rie\n");
	printf("(Q)uit\n");
	char c;
	while ((c = getc(stdin)) != EOF)
	{
		if (c == 'q' || c == 'Q')
		{
			break;
		}
		else if (c == 'h' || c == 'H')
		{
			printf("\n");
			test_hashtable();
			break;
		}
		else if (c == 't' || c == 'T')
		{
			printf("\n");
			test_trie();
			break;
		}
	}

	tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);
	return 0;
}