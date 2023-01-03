#ifndef TRIE_H
#define TRIE_H

#define NUM_CHARS 256

typedef struct 
{
	struct trienode *children[NUM_CHARS];
	bool terminal;
} trienode;

bool trie_insert(trienode **root, char* signedtext);
bool trie_search(trienode *root, char* signedtext);
bool trie_delete(trienode **root, char* signedtext);
void trie_print(trienode *root);

#endif
