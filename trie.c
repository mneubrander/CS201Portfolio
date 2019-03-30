
#include "trie.h"

//Allocates space for and returns an empty node
//https://www.geeksforgeeks.org/trie-insert-and-search/
struct TrieNode* CreateNewTrieNode() {
  struct TrieNode* newNode = malloc(sizeof(struct TrieNode));
  newNode->isWordEnd = 0;
  for (int i = 0; i < 26; i++) {
    newNode->nextLetters[i] = NULL;
  }
  return newNode;
}

//A node is not present in the trie already, this inserts the node
//https://www.geeksforgeeks.org/trie-insert-and-search/
void InsertTrieNode(char *word, struct TrieNode* trie) {
  struct TrieNode *insertNode = trie;
  int wordLength = strlen(word);
  for (int i = 0; i < wordLength; i++) {
    int nextLetterIndex = word[i] - 'a';
    if (!(insertNode->nextLetters[nextLetterIndex])) {
      insertNode -> nextLetters[nextLetterIndex] = CreateNewTrieNode();
    }
    insertNode = insertNode->nextLetters[nextLetterIndex];
  }
  insertNode->isWordEnd = 1;
}

//Searches for a word in the trie
//https://www.geeksforgeeks.org/trie-insert-and-search/
int FindWordInTrie(char *word, struct TrieNode* trie){
  struct TrieNode *findNode = trie;
  for (int i = 0; i < strlen(word); i++) {
    int nextLetterIndex = word[i] - 'a';
    //if no next index return 0
    if (!(findNode->nextLetters[nextLetterIndex])){
      return 0;
    }
    findNode = findNode->nextLetters[nextLetterIndex];
  }
  if (findNode && findNode->isWordEnd) return 1;
  else return 0;
}

//searches for a prefix of a word in a trie
//Modified using code above (modified borrowed code)
int FindPrefixInTrie(char *prefix, struct TrieNode *trie){
  struct TrieNode *findNode = trie;
  for (int i = 0; i < strlen(prefix); i++) {
    int nextLetterIndex = prefix[i] - 'a';
    //if no next index return 0
    if (!(findNode->nextLetters[nextLetterIndex])){
      return 0;
    }
    findNode = findNode->nextLetters[nextLetterIndex];
  }
    return 1;
}

//prints all words in a trie
//https://www.geeksforgeeks.org/trie-insert-and-search/
void PrintTrie(struct TrieNode* trie, char *word, int level, int *wordNumber) {
  if ((trie->isWordEnd)== 1) {
        word[level] = '\0';
        if (*wordNumber == 8) {
          printf("\n");
          *wordNumber = 0;
        }
        else{(*wordNumber)++;}
        printf("%s  ", word);
    }
    for (int i = 0; i < 26; i++){
        if (trie->nextLetters[i]){
            word[level] = i + 'a';
            PrintTrie(trie->nextLetters[i], word, level + 1, wordNumber);
        }
    }
}

void FreeTrie(struct TrieNode* trie) {
    for (int i = 0; i < 26; i++){
        if (trie->nextLetters[i]){
            FreeTrie(trie->nextLetters[i]);
        }
    }
    free(trie);
}
