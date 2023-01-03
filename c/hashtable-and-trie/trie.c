#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "trie.h"

trienode* create_node()
{
	trienode *newnode = malloc(sizeof(*newnode));

	for (int i = 0; i < NUM_CHARS; i++)
	{
		newnode->children[i] = NULL;
	}

	newnode->terminal = false;
	return newnode;
}

bool trie_insert(trienode **root, char* signedtext)
{
	if (*root == NULL)
	{
		*root = create_node();
	}

	unsigned char* text = (unsigned char*)signedtext;
	trienode *tmp = *root;
	int length = strlen(signedtext);

	for (int i = 0; i < length; i++)
	{
		if (tmp->children[text[i]] == NULL)
		{
			tmp->children[text[i]] = (struct trienode*)create_node();	
		}

		tmp = (trienode*)tmp->children[text[i]];
	}

	if (tmp->terminal)
	{
		// word is already in the trie.
		return false;
	}

	tmp->terminal = true;
	return true;
}

void trie_print_rec(trienode *node, unsigned char* prefix, int length)
{
	unsigned char newprefix[length + 2];
	memcpy(newprefix, prefix, length);
	newprefix[length + 1] = 0;

	if (node->terminal == true)
	{
		printf("Word: %s\n", prefix);
	}

	for (int i = 0; i < NUM_CHARS; i++)
	{
		if (node->children[i] != NULL)
		{
			newprefix[length] = i;
			trie_print_rec((trienode*)node->children[i], newprefix, length + 1);
		}		
	}
}

void trie_print(trienode *root)
{
	if (root == NULL)
	{
		printf("EMPTY\n");
		return;
	}

	trie_print_rec(root, NULL, 0);
}

bool trie_search(trienode *root, char* signedtext)
{
	if (root == NULL)
	{
		return false;
	}

	unsigned char* text = (unsigned char*)signedtext;
	int length = strlen(signedtext);

	trienode* tmp = root;
	for (int i = 0; i < length; i++)
	{
		if (tmp->children[text[i]] == NULL)
		{
			return false;
		}

		tmp = (trienode*)tmp->children[text[i]];
	}

	return tmp->terminal;
}

bool trie_node_has_children(trienode* node)
{
	if (node == NULL)
	{
		return false;
	}

	for (int i = 0; i < NUM_CHARS; i++)
	{
		if (node->children[i] != NULL)
		{
			return true;
		}
	}

	return false;
}

trienode* trie_delete_rec(trienode *node, unsigned char* text, bool *deleted)
{
	if (node == NULL)
	{
		return node;
	}

	if (*text == '\0')
	{
		if (node->terminal)
		{
			node->terminal = false;
			*deleted = true;

			if (trie_node_has_children(node) == false)
			{
				free(node);
				node = false;
			}
		}

		return node;
	}

	node->children[text[0]] = (struct trienode*)trie_delete_rec((trienode*)node->children[text[0]], text + 1, deleted);
	if (*deleted && trie_node_has_children(node) == false && node->terminal == false)
	{
		free(node);
		node = NULL;
	}

	return node;
}

bool trie_delete(trienode** root, char* signedtext)
{
	if (*root == NULL)
	{
		return false;
	}

	unsigned char* text = (unsigned char*)signedtext;
	bool result = false;

	*root = trie_delete_rec(*root, text, &result);

	return result;	
}
