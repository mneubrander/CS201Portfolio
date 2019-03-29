#ifndef BOGGLE_H
#define BOGGLE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "trie.h"
//#include "gameplay.h"

int LinearIndexCalc(int currentRow, int currentCol, int totalCol);
int ChooseBoardSize();

char** CreateBoggleBoardTable(int rows, int cols);
void PrintBoggleBoard(char** boggleBoardTable, int rows, int cols);
char* CreateBoggleBoardNodeList(char **boggleBoardTable, int rows, int cols);

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

struct Graph* CreateGraph(int numberVertices);
struct AdjListNode* CreateNode(int index, char letter);
void CreateEdge(struct Graph* graph, int srcIndex, char srcLetter, int destIndex, char destLetter);
struct Graph* CreateBoggleBoardGraph(char** boggleBoardTable, int rows, int cols);

struct WordListNode
{
  char* word;
  struct WordListNode* next;
} ;

struct WordListNode* findWords(struct Graph* graph, char* boggleList, int* visited, int startIndex,
                                          int count, char* str, struct WordListNode* wordList,
                                          struct TrieNode* dictionary);

struct TrieNode* FindWordsTrie(struct Graph* graph, char* boggleList, int* visited, int startIndex,
                                          int count, char* str, struct TrieNode*
                                          wordList, struct TrieNode* dictionary);

#endif
