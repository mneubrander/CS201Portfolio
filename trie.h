#ifndef TRIE_H
#define TRIE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//#include "gameplay.h"
#include "bogglegraph.h"

struct TrieNode
{
  struct TrieNode *nextLetters[26];
  int isWordEnd;
};

struct TrieNode* CreateNewTrieNode();
void InsertTrieNode(char *word, struct TrieNode* trie);
int FindWordInTrie(char *word, struct TrieNode* trie);
int FindPrefixInTrie(char *prefix, struct TrieNode *trie);
void PrintTrie(struct TrieNode* trie, char *word, int level);
void FreeTrie(struct TrieNode* trie);

#endif
