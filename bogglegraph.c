#include "bogglegraph.h"

//Calculates the linear index of an element in a table given its row and column.
int linearIndex(int currentRow, int currentCol, int totalCol) {
  //assuming linear index starts at zero
  int linearIndex = currentCol + currentRow * totalCol;
  return linearIndex;
}

//Creates a boggle board in an array format.
char** createBoggleBoardTable(int rows, int cols) {
  srand(time(NULL));
  char** boggleBoardTable = malloc(rows * sizeof(char *));
  for(int i=0; i < cols; i++) {
      boggleBoardTable[i] = malloc(cols * sizeof(char));
  }

  int qFlag = 0;

  for (int i = 0; i <rows;  i++) {
    for (int j = 0; j <cols; j++) {
      boggleBoardTable[i][j] = ("%c ", 'a' + (rand() % 26));
      if(boggleBoardTable[i][j] == 'q') {
        if (j>0) {
          boggleBoardTable[i][j-1] = 'u';
        }
        else if (i>0) {
          boggleBoardTable[i-1][j] = 'u';
        }
        else qFlag = 1;
      }
    }
  }

  if (qFlag == 1 && cols > 0) {
    boggleBoardTable[0][1] = 'u';
  }
  return boggleBoardTable;
}

//Prints the boggele board (still in table format)
void printBoggleBoard(char** boggleBoardTable, int rows, int cols) {
  printf("YOUR BOARD IS:\n" );
  printf("\n\n\n");
  for (int i = 0; i <rows;  i++) {
    for (int j = 0; j <cols; j++) {
      printf("%c ", boggleBoardTable[i][j]);
    }
    printf("\n");
  }
  printf("\n\n\n");
  return;
}

//Creates a one dimensional array in which the ith position corresponds to the ith character (using linear indexing).
//Purpose: The adjacency list holds boggle board entries by their integer position. To access the corresponding letter, this list is used.
char* createBoggleBoardNodeList(char **boggleBoardTable, int rows, int cols){
  char* boggleBoardNodeList = malloc(rows * cols * sizeof(char));
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      boggleBoardNodeList[linearIndex(i,j, cols)] = boggleBoardTable[i][j];
      //printf("%d\n", linearIndex(i,j, cols));
      //printf("%c\n", boggleBoardNodeList[linearIndex(i,j, cols)]);
    }
  }
  return boggleBoardNodeList;
}

//Creates an empty graph
//Code reused from https://www.programiz.com/dsa/graph-adjacency-list
struct Graph* createGraph(int numberVertices)
{
  struct Graph* graph = malloc(sizeof(struct Graph));
  graph -> numVertices = numberVertices;
  graph -> adjLists = malloc(numberVertices * sizeof(struct AdjListNode));
  for (int i = 0; i < numberVertices; i++)
       graph->adjLists[i] = NULL;
  return graph;
}

//Creates a node for an adjacency list given the letter and number of the boggle entry
// Code reused from https://www.programiz.com/dsa/graph-adjacency-list
struct AdjListNode* createNode(int index, char letter)
{
   struct AdjListNode* newNode = malloc(sizeof(struct AdjListNode));
   newNode->index = index;
   newNode->letter = letter;
   newNode->next = NULL;
   return newNode;
}

//Adds an edge between two nodes to an adjacency adjacency list
// Code reused from https://www.programiz.com/dsa/graph-adjacency-list
void createEdge(struct Graph* graph, int srcIndex, char srcLetter, int destIndex, char destLetter)
{
  //From src to dest
  struct AdjListNode* node = createNode(destIndex, destLetter);
  node->next = graph->adjLists[srcIndex];
  graph->adjLists[srcIndex] = node;

  //From dest to src
  node = createNode(srcIndex, srcLetter);
  node ->next = graph->adjLists[destIndex];
  graph->adjLists[destIndex] = node;

}

/*void printGraph(struct Graph* graph) {
  printf("%d\n", graph->numVertices);
  int vertex;
  for (vertex = 0; vertex < graph->numVertices; vertex++) {
    //printf("Here\n");
    struct AdjListNode* temp = graph->adjLists[vertex];
        printf("\n Adjacency list of vertex %d \n ", vertex);
        while (temp!=NULL)
        {
            printf("%d %c     ", temp->index, temp->letter);
            temp = temp->next;
        }
        printf("\n");
  }
}*/

//Turns the boggle board array into adjacency lists
struct Graph* createBoggleBoardGraph(char** boggleBoardTable, int rows, int cols){
  int v = rows*cols;
  struct Graph *boggleBoardGraph = createGraph(v);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j <cols; j++){
      if (i < rows - 1) {
        //create edge to right
        createEdge(boggleBoardGraph, linearIndex(i, j, cols), boggleBoardTable[i][j],
                                     linearIndex(i + 1, j, cols), boggleBoardTable[i+1][j]);
                                    // printf("adding edge %c to %c\n",boggleBoardTable[i][j], boggleBoardTable[i+1][j]);
      }
      if (j < cols - 1){
        //create edge below
        createEdge(boggleBoardGraph, linearIndex(i, j, cols), boggleBoardTable[i][j],
                                     linearIndex(i, j+1, cols), boggleBoardTable[i][j+1]);
                                    //  printf("adding edge %c to %c\n",boggleBoardTable[i][j], boggleBoardTable[i][j+1]);
      }
      if (j < cols - 1 && i <rows - 1){
        //create edge below
        createEdge(boggleBoardGraph, linearIndex(i, j, cols), boggleBoardTable[i][j],
                                     linearIndex(i+1, j+1, cols), boggleBoardTable[i+1][j+1]);
                                    //  printf("adding edge %c to %c\n",boggleBoardTable[i][j], boggleBoardTable[i+1][j+1]);
      }
      if (j > 0 && i <rows - 1){
        //create edge below
        createEdge(boggleBoardGraph, linearIndex(i, j, cols), boggleBoardTable[i][j],
                                     linearIndex(i+1, j-1, cols), boggleBoardTable[i+1][j-1]);
                                    //  printf("adding edge %c to %c\n",boggleBoardTable[i][j], boggleBoardTable[i+1][j-1]);
      }
    }
  }
  return boggleBoardGraph;
}

/*struct WordListNode* findWords(struct Graph* graph, char* boggleList, int* visited, int startIndex,
                                          int count, char* str, struct WordListNode* wordList, struct TrieNode* dictionary){

    visited[startIndex] = 1; //1 indicates vertex has been visited
    char templetter = boggleList[startIndex];
    char temp[2];
    temp[0] = templetter;
    temp[1] = '\0';
    strcat(str, temp);
    //printf("%s\n", str);

    if (findWordInTrie(str, dictionary)) {
      struct WordListNode* wordNode = malloc(sizeof(struct WordListNode));
      wordNode -> word = malloc(strlen(str) + 1);
      strcpy(wordNode->word, str);
      wordNode->next = wordList;
      wordList = wordNode;
    }


    struct AdjListNode* node;
    node = graph->adjLists[startIndex];
    while(node != NULL) {
      if (visited[node->index] == 0 && findPrefixInTrie(str, dictionary)) {
        wordList = findWords(graph, boggleList, visited, node->index, count, str, wordList, dictionary);
      }
      node = node->next;
    }

    //once word path is done, resets use so the word can be used on future paths
    str[strlen(str)-1] = '\0';
    visited[startIndex] = 0;

    return wordList;
}*/

//Finds all words in the boggle board adjacency adjLists
//Compares words to words in a trie - once there are no more words starting with a series of letters, that search path is terminated
//Akin to a depth first search
struct TrieNode* findWordsTrie(struct Graph* graph, char* boggleList, int* visited, int startIndex,
                                          int count, char* str, struct TrieNode* wordList, struct TrieNode* dictionary){

    visited[startIndex] = 1;
    char templetter = boggleList[startIndex];
    char temp[2];
    temp[0] = templetter;
    temp[1] = '\0';
    strcat(str, temp);
    //printf("%s\n", str);

    if (findWordInTrie(str, dictionary)) {
       inserttrienode(str, wordList);
    }


    struct AdjListNode* node;
    node = graph->adjLists[startIndex];
    while(node != NULL) {
      if (visited[node->index] == 0 && findPrefixInTrie(str, dictionary)) {
        wordList = findWordsTrie(graph, boggleList, visited, node->index, count, str, wordList, dictionary);
      }
      node = node->next;
    }
    //once word path is done, resets use so the word can be used on future paths
    str[strlen(str)-1] = '\0';
    visited[startIndex] = 0;
    return wordList;
}
