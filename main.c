#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include "trie.h"
#include "bogglegraph.h"

void readextra(){
  char temp = '\0';
  while(temp!='\n') {
    scanf("%c", &temp);
  }
return;
}

int stringisalpha(char*str) {
  //if(strlen(str) == 0) return 0;
  for (int i = 0; i < strlen(str); i++) {
    if (!islower(*(str+i))) return 0;
  }
  return 1;
}

//Allows user to choose the size of board they want to play on.
int chooseBoardSize() {
  int choice = 0;
  printf("What n x n size of board would you like to play on?");
  if (scanf("%d", &choice) != 1) {
    printf("Expected Integer. Program Exiting.");
    exit(1);
  }
  else if(choice <1) {
    printf("A board cannot have size less than 1. Try again.\n");
    choice = chooseBoardSize();
  }
  printf("\n");
  return choice;

}

//Prints the current score of player one versus. Not borrowed.
void printStatus(int mode, char* namePlayerOne, int scorePlayerOne,
                           char* namePlayerTwo, int scorePlayerTwo) {
  char modeString[30];
  if (mode == 1) {
    strcpy(modeString, "Player1 vs. Computer");
  }
  else if (mode == 2) {
    strcpy(modeString, "Player1 vs. Player2");
  }
  printf("\n");
  printf("You are playing in %s mode. The score is: \n \n \
            %s: %d \n \
            %s: %d \n \n", modeString, namePlayerOne, scorePlayerOne, namePlayerTwo,scorePlayerTwo);
  return;
}


int chooseMode() {
  int choice;
  printf("\n");
  printf("--------------------------------------------------------------------\n");
  printf("Hello! You are on Boggle Game's Home page. What would you like to do?\n");
  printf("\t (1) Player vs. Computer\n");
  printf("\t (2) Player vs. Player\n");
  printf("\t (3) Exit\n");
  printf("\n");
  printf("Enter Number corresonding to choice: ");

  if (scanf("%d", &choice) != 1) {
    printf("Error: Expected Integer. Program Exiting.\n");
    exit(1);
  }
  printf("\n");
  if (choice != 1 && choice != 2 && choice != 3) {
    printf("Please enter a valid choice number: 1 2 or 3.");
    choice = chooseMode();
  }
  return choice;
}

//Computes and returns the score of a word in boggle based off of word length and presence on game board and in dictionary.
int scoreword(char *word, struct TrieNode* dictionary) {
  int score = 0;
  if (!findWordInTrie(word, dictionary)) {
      score = 0;
  }
  else {
    if (strlen(word) <3) score = 0;
    else if (strlen(word) < 5) score = 1;
    else if (strlen(word) < 6) score = 2;
    else if (strlen(word) < 7) score = 3;
    else if (strlen(word) < 8) score = 5;
    else score = 11;
  }
  return score;
}

//Gets words user has found in the boggle board. Returns user's words as a trie.
//Storing user words in a trie makes sense as duplicates are not allowed and words are all (relatively) short
struct TrieNode* getuserwords() {
  struct TrieNode* userWords = createnewtrienode();

  int wordnum = 1;
  char str[15] = "\0";
  int maxlength = 10;
  char temp;

  readextra();
  printf("Enter word %d (or XXX to quit): ", wordnum);
  fgets(str, maxlength, stdin);
  str[strcspn(str, "\n")] = '\0';

  while (strcmp(str, "XXX") != 0) {
    if(!stringisalpha(str)) {
      if(strlen(str) == maxlength -1) {
        readextra();
      }
      printf("\tNot valid input. Try again: ");
      fgets(str, maxlength, stdin);
      str[strcspn(str, "\n")] = '\0';
    }
    else{
      inserttrienode(str, userWords);
      if(strlen(str) == maxlength-1) readextra();
      wordnum++;
      printf("Enter word %d (or XXX to quit): ", wordnum);
      fgets(str, maxlength, stdin);
      str[strcspn(str, "\n")] = '\0';
    }
  }
  return userWords;

}

//Scores all of the words found by a user/computer.
int scoreFoundWords(struct TrieNode* trie, char *word, int level, int score, struct TrieNode* dictionary) {
  if ((trie->isWordEnd)== 1)
    {
        word[level] = '\0';
        printf("%s - %d\n", word, scoreword(word, dictionary));
        score = score + scoreword(word, dictionary);
    }


    for (int i = 0; i < 26; i++)
    {
        if (trie->nextLetters[i])
        {
            word[level] = i + 'a';
            score = scoreFoundWords(trie->nextLetters[i], word, level + 1, score, dictionary);
        }
    }
    return score;
}

//Asks the player if they would like to play the game (in the same mode) again.
int playagain() {
  printf("Would you like to play again? (1) YES or (2) NO?\n");
  int choice = 0;
  if (scanf("%d", &choice) != 1) {
    printf("Error: Must enter a valid integer. Try running the program again.\n");
    exit(1);
  }
  if (choice != 1 && choice != 2) {
    printf("Please enter a valid number - 1 or 2- representing your choice.");
    choice = playagain();
  }
  return choice;
}

//Function signature - handleChoice is called by playagainstcomputer but defined later (it calls playagainstcomputer)
void handleChoice(int choice, struct TrieNode* dictionary);

//Function to handle player playing against a computer.
void playagainstcomputer(int playerScore, int computerScore, struct TrieNode* dictionary) {

  //MODE = 1 means playing against computer
  printStatus(1, "Player One", playerScore, "Computer", computerScore);

  //Get size of board. This can change before every game.
  int size = chooseBoardSize();


  //MAKE BOGGLE BOARD TABLE
  char **boggleBoardTable = createBoggleBoardTable(size, size);
  printBoggleBoard(boggleBoardTable, size, size);

  //MAKE BOGGLE BOARD INTO GRAPH
  char* list = createBoggleBoardNodeList(boggleBoardTable, size, size);
  struct Graph* boggleBoardGraph = createBoggleBoardGraph(boggleBoardTable, size, size);

  //Have computer find all possible words.
  int* visited = malloc(size*size * sizeof(int));
  for (int i = 0; i <size*size;  i++){
      visited[i] = 0;
    }
  char str[50];
  strcpy(str, "\0");
  int startIndex = 0;
  int count = 0;

  struct TrieNode* wordList = createnewtrienode();
  for (int i = 0; i <size*size; i++) {
    startIndex = i;
    wordList= findWordsTrie(boggleBoardGraph, list, visited, startIndex, count, str, wordList, dictionary);
  }

  //GET USER'S WORDS
  struct TrieNode* userWords =  getuserwords();

  //Score and print the number of points the player and computer each earned.
  char str2[50];
  int level = 0;
  int playerGameScore = 0;
  playerGameScore = scoreFoundWords(userWords,  str2, level, playerGameScore, wordList);
  printf("\nPLAYER'S POINTS:  %d\n\n", playerGameScore);

  char str3[50];
  level = 0;
  int computerGameScore = 0;
  computerGameScore = scoreFoundWords(wordList,  str2, level, computerGameScore, wordList);
  printf("\nCOMPUTER'S POINTS: %d\n\n", computerGameScore);

  //Determine and increment score of winner.
  if (playerGameScore > computerGameScore) {
      playerScore++;
      printf("Player 1 won. Score is now: \n \t %d player - %d computer.\n\n", playerScore, computerScore);
    }
  else if (playerGameScore < computerGameScore) {
        computerScore++;
        printf("Computer won. Score is now: \n \t %d player - %d computer.\n\n", playerScore, computerScore);
      }
  else {
       printf("There was a tie! Computer won. Score is now: \n \t %d player - %d computer.\n\n", playerScore, computerScore);
  }

  //Decide whether to play again.
  int playAgain = playagain();

  if (playAgain == 1) {
    playagainstcomputer(playerScore, computerScore, dictionary);
  }
  else {
    int newGame = chooseMode();
    handleChoice(newGame, dictionary);
  }

  return;
}


void playervsplayer(int player1Score, int player2Score, struct TrieNode* dictionary) {

  //MODE = 1 means playing against computer
  printStatus(2, "Player One", player1Score, "Player Two", player2Score);
  int size = chooseBoardSize();

  //MAKE BOGGLE BOARD TABLE
  char **boggleBoardTable = createBoggleBoardTable(size, size);
  printBoggleBoard(boggleBoardTable, size, size);

  //MAKE BOGGLE BOARD INTO GRAPH
  char* list = createBoggleBoardNodeList(boggleBoardTable, size, size);
  struct Graph* boggleBoardGraph = createBoggleBoardGraph(boggleBoardTable, size, size);

  //FIND ALL WORDS
  int* visited = malloc(size*size * sizeof(int));
  for (int i = 0; i <size*size;  i++){
      visited[i] = 0;
    }
  char str[50];
  strcpy(str, "\0");
  int startIndex = 0;
  int count = 0;

  struct TrieNode* wordList = createnewtrienode();
  for (int i = 0; i <size*size; i++) {
    startIndex = i;
    wordList= findWordsTrie(boggleBoardGraph, list, visited, startIndex, count, str, wordList, dictionary);
  }

  //GET USER'S WORDS

  printf("PLAYER 1 - Please enter your words now.\n");
  struct TrieNode* userWordsOne =  getuserwords();

  char str2[50];
  int level = 0;
  int playerOneGameScore = 0;
  playerOneGameScore = scoreFoundWords(userWordsOne,  str2, level, playerOneGameScore, wordList);
  printf("PLAYER ONE'S SCORE IS %d\n", playerOneGameScore);

  printf("\n\n");

  printf("PLAYER 2 - Please enter your words now.\n");
  struct TrieNode* userWordsTwo =  getuserwords();

  char str3[50];
  level = 0;
  int playerTwoGameScore = 0;
  playerTwoGameScore = scoreFoundWords(userWordsTwo,  str3, level, playerTwoGameScore, wordList);
  printf("PLAYER TWO'S SCORE IS %d\n", playerTwoGameScore);

  printf("\n\n\n");


  if (playerOneGameScore > playerTwoGameScore) {
      player1Score++;
      printf("Player 1 won. Score is now: \n \t %d Player 1 - %d Player 2.\n\n", player1Score, player2Score);
    }
  else if (playerOneGameScore < playerTwoGameScore) {
        player2Score++;
        printf("Computer won. Score is now: \n \t %d Player 1 - %d Player 2.\n\n", player1Score, player2Score);
      }
  else {
       player1Score++;
       player2Score++;
       printf("There was a tie! Computer won. Score is now: \n \t %d Player 1 - %d Player 2.\n\n", player1Score, player2Score);
  }

  int playAgain = playagain();

  if (playAgain == 1) {
    playervsplayer(player1Score, player2Score, dictionary);
  }
  else {
    int newGame = chooseMode();
    handleChoice(newGame, dictionary);
  }

  return;
}



void handleChoice(int choice, struct TrieNode* dictionary) {
  if (choice == 1) {
    playagainstcomputer(0,0, dictionary);
  }
  else if (choice == 2) {
    playervsplayer(0,0,dictionary);
    return;
  }
  else {
    return;
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(void){

  //OPEN DICTIONARY FILE
  FILE* fp;
  fp = fopen("2of12inf.txt", "r");
  if (fp == NULL) {
    printf("ERROR: PLEASE CREATE A DICTIONARY FILE NAMED 2of12inf.txt AND STORE THIS FILE IN THE CURRENT FOLDER. THEN TRY RUNNING THE PROGRAM AGAIN.");
    return -1;
  }

  //CREATE DICTIONARY IN TRIE
  char word[100];
  struct TrieNode* dictionary = createnewtrienode();
  fscanf(fp, "%s", word);
  while (!feof(fp)){
    inserttrienode(word, dictionary);
    fscanf(fp, "%s", word);
  }

  //DISPLAY MAIN SCREEN
  int choice = chooseMode();
  handleChoice(choice, dictionary);

  //playagainstcomputer(0,0, dictionary);

  //char str2[30];
  //int level = 0;
  //printtrie(wordList, str2, level);


  return 0;
}
