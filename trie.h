#ifndef TRIE_H
#define TRIE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct TrieNode
{
  struct TrieNode *nextLetters[26];
  int isWordEnd;
};

struct TrieNode* createnewtrienode();
void inserttrienode(char *word, struct TrieNode* trie);
int findWordInTrie(char *word, struct TrieNode* trie);
int findPrefixInTrie(char *prefix, struct TrieNode *trie);
void printtrie(struct TrieNode* trie, char *word, int level);

#endif
