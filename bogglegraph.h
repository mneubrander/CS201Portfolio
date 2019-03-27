#ifndef BOGGLE_H
#define BOGGLE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "trie.h"
//#include "gameplay.h"

int linearIndex(int currentRow, int currentCol, int totalCol);
int chooseBoardSize();

char** createBoggleBoardTable(int rows, int cols);
void printBoggleBoard(char** boggleBoardTable, int rows, int cols);
char* createBoggleBoardNodeList(char **boggleBoardTable, int rows, int cols);

struct TrieNode;
struct AdjListNode
{
    int index;
    char letter;
    struct AdjListNode* next;
};

struct Graph
{
    int numVertices;
    struct AdjListNode** adjLists;
};

struct Graph* createGraph(int numberVertices);
struct AdjListNode* createNode(int index, char letter);
void createEdge(struct Graph* graph, int srcIndex, char srcLetter, int destIndex, char destLetter);
void printGraph(struct Graph* graph);
struct Graph* createBoggleBoardGraph(char** boggleBoardTable, int rows, int cols);

struct WordListNode
{
  char* word;
  struct WordListNode* next;
} ;

struct WordListNode* findWords(struct Graph* graph, char* boggleList, int* visited, int startIndex,
                                          int count, char* str, struct WordListNode* wordList,
                                          struct TrieNode* dictionary);

struct TrieNode* findWordsTrie(struct Graph* graph, char* boggleList, int* visited, int startIndex,
                                          int count, char* str, struct TrieNode*
                                          wordList, struct TrieNode* dictionary);

#endif
