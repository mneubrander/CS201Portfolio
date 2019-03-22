#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "trie.h"
#include "bogglegraph.h"

int main(void){

  //MAKE DICTIONARY
  FILE* fp;
  fp = fopen("2of12inf.txt", "r");

  char word[100];
  struct TrieNode* dictionary = createnewtrienode();
  fscanf(fp, "%s", word);
  while (!feof(fp)){
    inserttrienode(word, dictionary);
    fscanf(fp, "%s", word);
  }

  //DO BOGGLE

  int scorePlayerOne = 0;
  int scorePlayerTwo = 0;
  printf("Hello! Welcome to Boggle!\n");
  int mode = chooseMode();
  int size = chooseBoardSize();
  printStatus(mode, scorePlayerOne, scorePlayerTwo);
  char **boggleBoardTable = createBoggleBoardTable(size, size);
  printBoggleBoard(boggleBoardTable, size, size);
  char* list = createBoggleBoardNodeList(boggleBoardTable, size, size);
  struct Graph* boggleBoardGraph = createBoggleBoardGraph(boggleBoardTable, size, size);
  //printGraph(boggleBoardGraph);


  int* visited = malloc(size*size * sizeof(int));

  for (int i = 0; i <size*size;  i++){
      visited[i] = 0;
    }


  /*int visited[size*size];
  for (int i = 0; i < size*size; i++) {
    visited[i] = 0;
  }*/
  char str[50];
  strcpy(str, "\0");
  int startIndex = 0;
  int count = 0;
  /*for (int i=0; i<size; i++) {
    for (int j = 0; j<size; j++) {
    free(boggleBoardTable[i][j]);
    }
}
  free(boggleBoardTable);*/
  //struct WordListNode* wordList = NULL;

  struct TrieNode* wordList = createnewtrienode();
  for (int i = 0; i <size*size; i++) {
    startIndex = i;
    wordList= findWordsTrie(boggleBoardGraph, list, visited, startIndex, count, str, wordList, dictionary);
  }

  /*while (wordList != NULL) {
    printf("%s\n", wordList->word);
    wordList = wordList -> next;
  }*/

  char str2[30];
  int level = 0;
  printtrie(wordList, str2, level);




  return 0;
}
