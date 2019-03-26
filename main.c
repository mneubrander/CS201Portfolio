#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include "trie.h"
#include "bogglegraph.h"

#define MAXIMUMLENGTH 15

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
  printf("What n x n size of board would you like to play on? (Enter an integer greater than 0.): ");
  if (scanf("%d", &choice) != 1) {
    printf("Expected Integer. Program Exiting.\n");
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
  if (mode == 1 || mode == 2) {
    strcpy(modeString, "Player vs. Computer");
  }
  else if (mode == 3) {
    strcpy(modeString, "Player1 vs. Player2");
  }
  else if (mode == 4) {
    strcpy(modeString, "One Player");
  }
  printf("\n");

  if(mode == 1 || mode == 2 || mode == 3) {
  printf("You are playing in %s mode. The score is: \n \n \
            %s: %d \n \
            %s: %d \n \n", modeString, namePlayerOne, scorePlayerOne, namePlayerTwo,scorePlayerTwo);
  }
  else{
    printf("You are playing in %s mode. The high score is: \n \n \
              %s: %d \n \n", modeString, namePlayerOne, scorePlayerOne);
  }

  return;
}


int chooseMode() {
  char seperator[100] = "--------------------------------------------------------------------";
  int choice;
  printf("\n");
  printf("%s\n", seperator);
  printf("Hello! You are on Boggle Game's Home page. What would you like to do?\n");
  printf("\t (1) Player vs. Computer\n");
  printf("\t (2) Player vs. Computer - Reduced Difficulty\n");
  printf("\t (3) Player vs. Player\n");
  printf("\t (4) One Player\n");
  printf("\t (5) Exit\n");
  printf("\n");
  printf("Enter Number corresonding to choice: ");

  if (scanf("%d", &choice) != 1) {
    printf("Error: Expected Integer. Program Exiting.\n");
    exit(1);
  }
  printf("\n");
  if (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5) {
    printf("Please enter a valid choice number: 1 2 3 4 or 5.");
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
  time_t start = time(NULL);

  //readextra();
  printf("Enter word %d (or XXX to quit): ", wordnum);
  fgets(str, maxlength, stdin);
  str[strcspn(str, "\n")] = '\0';

  while (strcmp(str, "XXX") != 0) {
    time_t now =time(NULL);
    if (now-start > 180) {
      printf("\n\tLast input was enterred after 3 Minutes. Time is up!\n \tRegardless of validity, it will not be counted.\n\n");
      if(strlen(str) == maxlength-1) readextra();
      break;
    }
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
        if(strlen(word) > 2) {
          printf("[%s - %d]   ", word, scoreword(word, dictionary));
        }
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

//Scores all of the words found by a user/computer.
int scoreFoundWordsEasy(struct TrieNode* trie, char *word, int level, int score, struct TrieNode* dictionary, int justPrinted) {
  if ((trie->isWordEnd)== 1)
    {
        word[level] = '\0';
        if(justPrinted == 0) {
          if(strlen(word) > 2) {
            printf("[%s - %d]   ", word, scoreword(word, dictionary));
          }
          score = score + scoreword(word, dictionary);
          justPrinted = 1;
        }
        else justPrinted = 0;
    }


    for (int i = 0; i < 26; i++)
    {
        if (trie->nextLetters[i])
        {
            word[level] = i + 'a';
            score = scoreFoundWordsEasy(trie->nextLetters[i], word, level + 1, score, dictionary, justPrinted);
        }
    }
    return score;
}

//Asks the player if they would like to play the game (in the same mode) again.
int playagain() {
  printf("Would you like to play again?\n\t(1) Yes \n\t(2) No\n\n");
  printf("Enter number corresonding to choice: ");
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
void playagainstcomputer(int playerScore, int computerScore, struct TrieNode* dictionary, int difficultyLevel) {
  char seperator[100] = "--------------------------------------------------------------------";
  printf("%s\n",seperator);
  //MODE = 1 means playing against computer
  printStatus(1, "Player  ", playerScore, "Computer", computerScore);

  //Get size of board. This can change before every game.
  int size = chooseBoardSize();


  //MAKE BOGGLE BOARD TABLE
  char **boggleBoardTable = createBoggleBoardTable(size, size);
  printBoggleBoard(boggleBoardTable, size, size);

  //MAKE BOGGLE BOARD INTO GRAPH
  char* list = createBoggleBoardNodeList(boggleBoardTable, size, size);
  struct Graph* boggleBoardGraph = createBoggleBoardGraph(boggleBoardTable, size, size);


  char seperatorFinding[100] = "-------------------- Finding All Words ... --------------------------";
  printf("\n%s\n", seperatorFinding);
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
  readextra();
  struct TrieNode* userWords =  getuserwords();

  //Score and print the number of points the player and computer each earned.
  char playerScoreSeperator[100] = "------------------------Player's Points------------------------------";
  char computerScoreSeperator[100] = "-----------------------Computer's Points-----------------------------";

  char str2[50];
  int level = 0;
  int playerGameScore = 0;
  printf("\n%s\n\n", playerScoreSeperator);
  playerGameScore = scoreFoundWords(userWords,  str2, level, playerGameScore, wordList);
  printf("\n\nPLAYER TOTAL:  %d\n\n", playerGameScore);

  char str3[50];
  level = 0;
  int computerGameScore = 0;
  printf("\n%s\n\n", computerScoreSeperator);
  if(difficultyLevel == 2){
    computerGameScore = scoreFoundWords(wordList,  str2, level, computerGameScore, wordList);
  }
  else if (difficultyLevel == 1) {
    computerGameScore = scoreFoundWordsEasy(wordList,  str2, level, computerGameScore, wordList, 0);
  }
  printf("\n\nCOMPUTER TOTAL: %d\n\n", computerGameScore);

  //FREE ALL VARIABLES WOW

  for (int i = 0; i < size; i++) {
    free(boggleBoardTable[i]);
  }
  free(boggleBoardTable);

  free(list);

  for (int i = 0; i < size*size; i++) {
    free(boggleBoardGraph->adjLists[i]);
  }
  free(boggleBoardGraph);
  free(visited);

  freetrie(wordList);
  freetrie(userWords);

  char winnerSeperator[100] = "---------------------------- Winner ---------------------------------";
  //Determine and increment score of winner.
  printf("\n%s\n", winnerSeperator);
  if (playerGameScore > computerGameScore) {
      playerScore++;
      printf("Player won. Score is now: \n \t Player  : %d \n \t Computer: %d\n\n", playerScore, computerScore);
    }
  else if (playerGameScore < computerGameScore) {
        computerScore++;
        printf("Computer won. Score is now: \n \t Player  : %d \n \t Computer: %d\n\n", playerScore, computerScore);
      }
  else {
    playerScore++;
    computerScore++;
    printf("There was a tie! Score is now: \n \t Player  : %d \n \t Computer: %d\n\n", playerScore, computerScore);
  }

  //Decide whether to play again.
  int playAgain = playagain();

  if (playAgain == 1) {
    playagainstcomputer(playerScore, computerScore, dictionary, difficultyLevel);
  }
  else {
    int newGame = chooseMode();
    handleChoice(newGame, dictionary);
  }

  return;
}


void playervsplayer(int player1Score, int player2Score, struct TrieNode* dictionary) {
  char seperator[100] = "--------------------------------------------------------------------";
  printf("%s\n", seperator );
  //MODE = 2 means player vs. player
  printStatus(3, "Player One", player1Score, "Player Two", player2Score);
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
  readextra();
  printf("Player One - Please enter your words now.\n");
  struct TrieNode* userWordsOne =  getuserwords();
  printf("\n\n\n");
  printf("\n\n\n");
  printf("\n\n\n");
  printf("\n\n\n");
  printf("\n\n\n");

  printBoggleBoard(boggleBoardTable, size, size);
  printf("Player Two - Please enter your words now.\n");
  struct TrieNode* userWordsTwo =  getuserwords();

  char playerOneScoreSeperator[100] = "----------------------Player One's Points----------------------------";
  char playerTwoScoreSeperator[100] = "----------------------Player Two's Points----------------------------";
  char str2[50];
  int level = 0;
  int playerOneGameScore = 0;
  printf("\n%s\n\n", playerOneScoreSeperator );
  playerOneGameScore = scoreFoundWords(userWordsOne,  str2, level, playerOneGameScore, wordList);
  printf("\n\nPLAYER ONE TOTAL: %d\n", playerOneGameScore);

  printf("\n\n");



  char str3[50];
  level = 0;
  int playerTwoGameScore = 0;
  printf("\n%s\n\n", playerTwoScoreSeperator);
  playerTwoGameScore = scoreFoundWords(userWordsTwo,  str3, level, playerTwoGameScore, wordList);
  printf("\n\nPLAYER TWO TOTAL: %d\n", playerTwoGameScore);

  printf("\n\n\n");

  for (int i = 0; i < size; i++) {
    free(boggleBoardTable[i]);
  }
  free(boggleBoardTable);

  free(list);

  for (int i = 0; i < size*size; i++) {
    free(boggleBoardGraph->adjLists[i]);
  }
  free(boggleBoardGraph);
  free(visited);

  freetrie(userWordsOne);
  freetrie(userWordsTwo);
  char winnerSeperator[100] = "---------------------------- Winner ---------------------------------";
  printf("\n%s\n", winnerSeperator);
  if (playerOneGameScore > playerTwoGameScore) {
      player1Score++;
      printf("Player One won. Score is now: \n \t Player One: %d \n \t Player Two: %d\n\n", player1Score, player2Score);
    }
  else if (playerOneGameScore < playerTwoGameScore) {
        player2Score++;
      printf("Player Two won. Score is now: \n \t Player One: %d \n \t Player Two: %d\n\n", player1Score, player2Score);      }
  else {
       player1Score++;
       player2Score++;
      printf("There was a tie! Score is now: \n \t Player One: %d \n \t Player Two: %d\n\n", player1Score, player2Score);  }

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

void oneplayer(int playerHighScore, struct TrieNode* dictionary) {
  //MODE = 1 means playing against computer
  printStatus(4, "Player One", playerHighScore, "NA", 0);
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
  readextra();
  //printf("Please enter your words now.\n");
  struct TrieNode* userWordsOne =  getuserwords();

  char str2[50];
  int level = 0;
  int playerOneGameScore = 0;
  char playerScoreSeperator[100] = "-----------------------------Points-----------------------------------";

  printf("\n%s\n", playerScoreSeperator);
  playerOneGameScore = scoreFoundWords(userWordsOne,  str2, level, playerOneGameScore, wordList);
  printf("\n\nTotal: %d\n", playerOneGameScore);



  for (int i = 0; i < size; i++) {
    free(boggleBoardTable[i]);
  }
  free(boggleBoardTable);

  free(list);

  for (int i = 0; i < size*size; i++) {
    free(boggleBoardGraph->adjLists[i]);
  }
  free(boggleBoardGraph);
  free(visited);

  freetrie(userWordsOne);
  char highScoreSeparator[100] = "---------------------------High Score---------------------------------";

  printf("\n\n%s\n\n", highScoreSeparator);
  if (playerOneGameScore > playerHighScore) {
      playerHighScore = playerOneGameScore;
      printf("You beat your high score!\nHigh score is now: %d \n\n", playerHighScore);
    }
  else {
        printf("High score is still: %d\n\n", playerHighScore);
      }
  int playAgain = playagain();

  if (playAgain == 1) {
    oneplayer(playerHighScore, dictionary);
  }
  else {
    int newGame = chooseMode();
    handleChoice(newGame, dictionary);
  }

  return;
}


void handleChoice(int choice, struct TrieNode* dictionary) {
  if (choice == 1) {//1 INDICATES PLAYING AGAINST COMPUTER - Normal Difficulty
    playagainstcomputer(0,0, dictionary,2);//playagainstcomputer takes arguments (playerScore, computerScore, dictionary, difficultyLevel)
                                            //difficultyLevel = 2 indicates normal difficulty
  }
  else if (choice == 2) { //2 INDICATES PLAYING AGAINST COMPUTER - Reduced Difficulty
    playagainstcomputer(0,0, dictionary,1); //playagainstcomputer takes arguments (playerScore, computerScore, dictionary, difficultyLevel)
                                            //difficultyLevel = 1 indicates reduced difficulty
  }
  else if (choice == 3) {
    playervsplayer(0,0,dictionary);
    return;
  }
  else if (choice == 4) {
    oneplayer(0,dictionary);
  }
  else {
    freetrie(dictionary);
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
    if(!stringisalpha(word)) {
      printf("ERROR: PLEASE MAKE SURE YOUR DICTIONARY FILE CONTAINS ONLY LOWERCASE WORDS\n");
      return -1;
    }
    inserttrienode(word, dictionary);
    fscanf(fp, "%s", word);
  }

  fclose(fp);

  //DISPLAY MAIN SCREEN
  int choice = chooseMode();

  //Playe Game Chosen By User
  handleChoice(choice, dictionary);

  return 0;
}
