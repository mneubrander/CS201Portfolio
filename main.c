#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include "trie.h"
#include "bogglegraph.h"
#include "gameplay.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(void){

  printf("-------------------------------------------------------------------------\n\
--------------------------WELCOME TO BOGGLE!-----------------------------\n-------------------------------------------------------------------------\n");  //OPEN DICTIONARY FILE
  FILE* fp;
  fp = fopen("BoggleDictionary.txt", "r");
  if (fp == NULL) {
    printf("ERROR: PLEASE CREATE A DICTIONARY FILE NAMED BoggleDictionary.txt AND STORE THIS FILE IN THE CURRENT FOLDER.\n THEN TRY RUNNING THE PROGRAM AGAIN.");
    return -1;
  }

  //CREATE DICTIONARY IN TRIE
  char word[100];
  struct TrieNode* dictionary = CreateNewTrieNode();
  fscanf(fp, "%99s", word);
  while (!feof(fp)){
    if(!StringIsLower(word)) {
      printf("ERROR: PLEASE MAKE SURE YOUR DICTIONARY FILE CONTAINS ONLY LOWERCASE WORDS\n");
      return -1;
    }
    InsertTrieNode(word, dictionary);
    fscanf(fp, "%99s", word);
  }

  fclose(fp);

  //DISPLAY MAIN SCREEN
  int choice = ChooseMode();

  //PLAY GAME CHOSEN BY USER.
  HandleChoice(choice, dictionary);

  return 0;
}
