#include "trie.h"
#include "gameplay.h"

#define VSCOMPUTER 1
#define VSCOMPUTEREASY 2
#define VSPLAYER 3
#define ONEPLAYER 4
#define ONEPLAYERSAVE 5
#define BOGGLEINSTRUCTIONS 6
#define EXITGAME 7

#define MAXLENGTH 51
int wordOnLine = 0;
struct TrieNode;


void ReadExtra(){
  char temp = '\0';
  while(temp!='\n') {
    scanf("%c", &temp);
  }
return;
}

int StringIsLower(char*str) {
  //if(strlen(str) == 0) return 0;
  for (int i = 0; i < strlen(str); i++) {
    if (!islower(*(str+i))) return 0;
  }
  return 1;
}

//Allows user to choose the size of board they want to play on.
int ChooseBoardSize() {
  int choice = 0;
  printf("What n x n size of board would you like to play on?\n\t*WARNING: Board dimension greater than 40 may cause poor display.*\n\tEnter an integer greater than 0 : ");
  if (scanf("%d", &choice) != 1) {
    printf("Expected Integer. Program Exiting.\n");
    exit(1);
  }
  else if(choice <1) {
    printf("A board cannot have size less than 1. Try again.\n");
    choice = ChooseBoardSize();
  }
  printf("\n");
  return choice;

}

//Prints the current score of player one versus. Not borrowed.
void PrintStatus(int mode, char* namePlayerOne, int scorePlayerOne,
                           char* namePlayerTwo, int scorePlayerTwo) {
  char modeString[31];
  if (mode == VSCOMPUTER) {
    strncpy(modeString, "Player vs. Computer", 30);
  }
  else if ( mode == VSCOMPUTEREASY){
    strncpy(modeString, "Player vs. Computer - Reduced Difficulty", 30);
  }
  else if (mode == VSPLAYER) {
    strncpy(modeString, "Player vs. Player",30);
  }
  else if (mode == ONEPLAYER) {
    strncpy(modeString, "One Player",30);
  }
  else if (mode == ONEPLAYERSAVE) {
    strncpy(modeString, "One Player - Saving High Scores",30);
  }
  printf("\n");

  if(mode == VSCOMPUTER || mode == VSCOMPUTEREASY || mode == VSPLAYER) {
  printf("You are playing in %s mode. The score is: \n \n \
            %s: %d \n \
            %s: %d \n \n", modeString, namePlayerOne, scorePlayerOne, namePlayerTwo,scorePlayerTwo);
  }
  else{
    printf("You are playing in %s mode.\n\tHigh score: %d \n \n", modeString, scorePlayerOne);
  }

  return;
}


int ChooseMode() {
  char seperator[100] = "-------------------------------------------------------------------------";
  int choice;
  printf("\n");
  printf("%s\n", seperator);
  printf("Hello! You are on Boggle Game's Home page. What would you like to do?\n");
  printf("\t (1) Player vs. Computer\n");
  printf("\t (2) Player vs. Computer - Reduced Difficulty\n");
  printf("\t (3) Player vs. Player\n");
  printf("\t (4) One Player\n");
  printf("\t (5) One Player - Saving High Score\n");
  printf("\t (6) Review Boggle Instructions\n");
  printf("\t (7) Exit\n");
  printf("\n");
  printf("Enter Number corresonding to choice: ");

  if (scanf("%d", &choice) != 1) {
    printf("Error: Expected Integer. Program Exiting.\n");
    exit(1);
  }
  printf("\n");
  if (choice != VSCOMPUTER && choice != VSCOMPUTEREASY && choice != VSPLAYER && choice != ONEPLAYER && choice != ONEPLAYERSAVE && choice!= BOGGLEINSTRUCTIONS && choice != EXITGAME) {
    printf("Please enter a valid choice number: 1 2 3 4 5 6 or 7.");
    choice = ChooseMode();
  }
  return choice;
}

//Computes and returns the score of a word in boggle based off of word length and presence on game board and in dictionary.
int ScoreWord(char *word, struct TrieNode* dictionary) {
  int score = 0;
  if (!FindWordInTrie(word, dictionary)) {
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
struct TrieNode* GetUserWords() {
  struct TrieNode* userWords = CreateNewTrieNode();
  char seperator[100] = "--------------------------Time Starts Now!--------------------------------";
  printf("\n%s\n\n", seperator);
  int wordnum = 1;
  char str[MAXLENGTH+1] = "\0";
  //int maxlength = 10;
  char temp;
  time_t start = time(NULL);

  //ReadExtra();
  printf("Enter word %d (or XXX to quit): ", wordnum);
  fgets(str, MAXLENGTH, stdin);
  str[strcspn(str, "\n")] = '\0';

  while (strcmp(str, "XXX") != 0) {
    time_t now =time(NULL);
    if (now-start > 180) {
      printf("\n\tLast input was enterred after 3 Minutes. Time is up!\n \tRegardless of validity, it will not be counted.\n\n");
      if(strlen(str) == MAXLENGTH-1) ReadExtra();
      break;
    }
    if(!StringIsLower(str)) {
      if(strlen(str) == MAXLENGTH -1) {
        ReadExtra();
      }
      printf("\tNot valid input. Try again: ");
      fgets(str, MAXLENGTH, stdin);
      str[strcspn(str, "\n")] = '\0';
    }
    else{
      InsertTrieNode(str, userWords);
      if(strlen(str) == MAXLENGTH-1) ReadExtra();
      wordnum++;
      printf("Enter word %d (or XXX to quit): ", wordnum);
      fgets(str, MAXLENGTH, stdin);
      str[strcspn(str, "\n")] = '\0';
    }
  }
  return userWords;

}

//Scores all of the words found by a user/computer.
int ScoreFoundWords(struct TrieNode* trie, char *word, int level, int score, struct TrieNode* dictionary, int *wordOnLine) {
  if ((trie->isWordEnd)== 1)
    {
        word[level] = '\0';
        printf("[%s - %d]  ", word, ScoreWord(word, dictionary));
        if (*wordOnLine == 5) {
          printf("\n");
          *wordOnLine = 0;
        }
        else{(*wordOnLine)++;}
        score = score + ScoreWord(word, dictionary);
    }

    for (int i = 0; i < 26; i++)
    {
        if (trie->nextLetters[i])
        {
            word[level] = i + 'a';
            score = ScoreFoundWords(trie->nextLetters[i], word, level + 1, score, dictionary, wordOnLine);
        }
    }
    return score;
}

//Scores half of the words found.
//This allows a user to play against the computer with a chance of winning
int ScoreFoundWordsEasy(struct TrieNode* trie, char *word, int level, int score, struct TrieNode* dictionary, int justPrinted, int *wordOnLine) {
  if ((trie->isWordEnd)== 1)
    {
        word[level] = '\0';
        if(justPrinted == 0) {
          //if(strlen(word) > 2) {
            //If word is length two or less, it is not a valid boggle word. It's score will be zero and shouldn't be printed.
            printf("[%s - %d]   ", word, ScoreWord(word, dictionary));
            if (*wordOnLine == 5) {
              printf("\n");
              *wordOnLine = 0;
            }
            else{(*wordOnLine)++;}
        //  }
          score = score + ScoreWord(word, dictionary);
          justPrinted = 1;
        }
        else justPrinted = 0;
    }

    for (int i = 0; i < 26; i++)
    {
        if (trie->nextLetters[i])
        {
            word[level] = i + 'a';
            score = ScoreFoundWordsEasy(trie->nextLetters[i], word, level + 1, score, dictionary, justPrinted, wordOnLine);
        }
    }
    return score;
}

//Asks the player if they would like to play the game (in the same mode) again.
int PlayAgain() {
  printf("Would you like to play again?\n\t(1) Yes \n\t(2) No\n\n");
  printf("Enter number corresonding to choice: ");
  int choice = 0;
  if (scanf("%d", &choice) != 1) {
    printf("Error: Must enter a valid integer. Try running the program again.\n");
    exit(1);
  }
  if (choice != 1 && choice != 2) {
    printf("Please enter a valid number - 1 or 2- representing your choice.");
    choice = PlayAgain();
  }
  return choice;
}


int ViewFullList() {
  printf("Would you like to see the full list of words?\n\t(1) Yes \n\t(2) No\n\n");
  printf("Enter number corresonding to choice: ");
  int choice = 0;
  if (scanf("%d", &choice) != 1) {
    printf("Error: Must enter a valid integer. Try running the program again.\n");
    exit(1);
  }
  if (choice != 1 && choice != 2) {
    printf("Please enter a valid number - 1 or 2- representing your choice.");
    choice = ViewFullList();
  }
  return choice;
}

//Function signature - HandleChoice is called by PlayAgainstComputer but defined later (it calls PlayAgainstComputer)
//void HandleChoice(int choice, struct TrieNode* dictionary);

//Function to handle player playing against a computer.
//difficultyLevel is the mode the player is playing in - it indicates easy or normal.

void PlayAgainstComputer(int playerScore, int computerScore, struct TrieNode* dictionary, int difficultyLevel) {

  char seperator[100] = "-------------------------------------------------------------------------";
  printf("%s\n",seperator);
  PrintStatus(difficultyLevel, "Player  ", playerScore, "Computer", computerScore);

  //Get size of board. This can change before every game. Print and make the board.
  int size = ChooseBoardSize();
  char **boggleBoardTable = CreateBoggleBoardTable(size, size);
  PrintBoggleBoard(boggleBoardTable, size, size);

  char* list = CreateBoggleBoardNodeList(boggleBoardTable, size, size);
  struct Graph* boggleBoardGraph = CreateBoggleBoardGraph(boggleBoardTable, size, size);

  //Have computer find all possible words.
  int* visited = malloc(size*size * sizeof(int));
  for (int i = 0; i <size*size;  i++){
      visited[i] = 0;
    }
  char str[MAXLENGTH + 1] = "\0";
  int startIndex = 0;
  int count = 0;
  struct TrieNode* wordList = CreateNewTrieNode();

  for (int i = 0; i <size*size; i++) {
    startIndex = i;
    wordList= FindWordsTrie(boggleBoardGraph, list, visited, startIndex, count, str, wordList, dictionary);
  }

  //Get user's words
  ReadExtra(); //reads an extra newline/other inupt from previous screen interaction
  struct TrieNode* userWords =  GetUserWords();

  //Score and print the number of points the player and computer each earned.
  char playerScoreSeperator[100] = "---------------------------Player's Points--------------------------------";
  char computerScoreSeperator[100] = "--------------------------Computer's Points-------------------------------";

  char str2[MAXLENGTH+1];
  int level = 0;
  int playerGameScore = 0;
  printf("\n%s\n\n", playerScoreSeperator);
  wordOnLine = 0;
  playerGameScore = ScoreFoundWords(userWords,  str2, level, playerGameScore, wordList, &wordOnLine);
  printf("\n\nPLAYER TOTAL:  %d\n\n", playerGameScore);

  char str3[MAXLENGTH+1];
  level = 0;
  int computerGameScore = 0;
  printf("\n%s\n\n", computerScoreSeperator);
  wordOnLine = 0;
  if(difficultyLevel == VSCOMPUTER){
    computerGameScore = ScoreFoundWords(wordList,  str2, level, computerGameScore, wordList,&wordOnLine);
  }
  else if (difficultyLevel == VSCOMPUTEREASY) {
    computerGameScore = ScoreFoundWordsEasy(wordList,  str2, level, computerGameScore, wordList, 0, &wordOnLine);
  }
  printf("\n\nCOMPUTER TOTAL: %d\n\n", computerGameScore);

  //Free dynamically allocated variables - they are no longer needed.
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

  FreeTrie(wordList);
  FreeTrie(userWords);

  //Determine and print winner. Increment the winner's score.
  char winnerSeperator[100] = "------------------------------- Winner -----------------------------------";
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
  int playAgain = PlayAgain();
  if (playAgain == 1) {
    PlayAgainstComputer(playerScore, computerScore, dictionary, difficultyLevel);
  }
  else {
    int newGame = ChooseMode();
    HandleChoice(newGame, dictionary);
  }
  return;
}


void PlayerVsPlayer(int player1Score, int player2Score, struct TrieNode* dictionary) {
  char seperator[100] = "-------------------------------------------------------------------------";
  printf("%s\n", seperator );
  PrintStatus(VSPLAYER, "Player One", player1Score, "Player Two", player2Score);

  //Get size of board. This can change before every game. Print and make the board.
  int size = ChooseBoardSize();
  char **boggleBoardTable = CreateBoggleBoardTable(size, size);
  PrintBoggleBoard(boggleBoardTable, size, size);
  char* list = CreateBoggleBoardNodeList(boggleBoardTable, size, size);
  struct Graph* boggleBoardGraph = CreateBoggleBoardGraph(boggleBoardTable, size, size);

  //Find all words in boggle board.
  int* visited = malloc(size*size * sizeof(int));
  for (int i = 0; i <size*size;  i++){
      visited[i] = 0;
    }
  char str[MAXLENGTH+1] = "\0";
  int startIndex = 0;
  int count = 0;

  struct TrieNode* wordList = CreateNewTrieNode();
  for (int i = 0; i <size*size; i++) {
    startIndex = i;
    wordList= FindWordsTrie(boggleBoardGraph, list, visited, startIndex, count, str, wordList, dictionary);
  }

  //Get players' words.
  ReadExtra();
  printf("Player One - Please enter your words now.\n");
  struct TrieNode* userWordsOne =  GetUserWords();

  //print enough newlines so player two (on a specific sized window) won't see player ones words.
  printf("\n\n\n");
  printf("\n\n\n");
  printf("\n\n\n");
  printf("\n\n\n");
  printf("\n\n\n");
  printf("\n\n\n");
  printf("\n\n\n");
  printf("\n\n\n");
  printf("\n\n\n");


  PrintBoggleBoard(boggleBoardTable, size, size);
  printf("Player Two - Please enter your words now.\n");
  struct TrieNode* userWordsTwo =  GetUserWords();

  //Score and print player's words.
  char playerOneScoreSeperator[100] = "-------------------------Player One's Points------------------------------";
  char playerTwoScoreSeperator[100] = "-------------------------Player Two's Points------------------------------";
  char str2[MAXLENGTH+1];
  int level = 0;
  int playerOneGameScore = 0;
  printf("\n%s\n\n", playerOneScoreSeperator );
  wordOnLine = 0;
  playerOneGameScore = ScoreFoundWords(userWordsOne,  str2, level, playerOneGameScore, wordList,&wordOnLine);
  printf("\n\nPLAYER ONE TOTAL: %d\n", playerOneGameScore);

  printf("\n\n");

  char str3[MAXLENGTH+1];
  level = 0;
  int playerTwoGameScore = 0;
  printf("\n%s\n\n", playerTwoScoreSeperator);
  wordOnLine = 0;
  playerTwoGameScore = ScoreFoundWords(userWordsTwo,  str3, level, playerTwoGameScore, wordList,&wordOnLine);
  printf("\n\nPLAYER TWO TOTAL: %d\n", playerTwoGameScore);

  printf("\n\n\n");

  //Determine and print winner.
  char winnerSeperator[100] = "------------------------------- Winner -----------------------------------";
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

  char str4[MAXLENGTH+1];
  level = 0;
  int wordNumber = 0;
  int viewList = ViewFullList();
  if (viewList == 1) {
    PrintTrie(wordList, str4, level, &wordNumber);
  }
  printf("\n\n");

  //Free dynamically allocated variables - they are no longer needed
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

  FreeTrie(userWordsOne);
  FreeTrie(userWordsTwo);
  FreeTrie(wordList);

  //Ask players if they would like to play again.
  int playAgain = PlayAgain();

  if (playAgain == 1) {
    PlayerVsPlayer(player1Score, player2Score, dictionary);
  }
  else {
    int newGame = ChooseMode();
    HandleChoice(newGame, dictionary);
  }

  return;
}

void OnePlayer(int playerHighScore, struct TrieNode* dictionary, int size) {
  PrintStatus(ONEPLAYER, "Player One", playerHighScore, "NA", 0);

  //Make and print boggle board.
  //int size = ChooseBoardSize();
  char **boggleBoardTable = CreateBoggleBoardTable(size, size);
  PrintBoggleBoard(boggleBoardTable, size, size);
  char* list = CreateBoggleBoardNodeList(boggleBoardTable, size, size);
  struct Graph* boggleBoardGraph = CreateBoggleBoardGraph(boggleBoardTable, size, size);

  //Find all words in board.
  int* visited = malloc(size*size * sizeof(int));
  for (int i = 0; i <size*size;  i++){
      visited[i] = 0;
    }
  char str[MAXLENGTH+1] = "\0";
  int startIndex = 0;
  int count = 0;

  struct TrieNode* wordList = CreateNewTrieNode();
  for (int i = 0; i <size*size; i++) {
    startIndex = i;
    wordList= FindWordsTrie(boggleBoardGraph, list, visited, startIndex, count, str, wordList, dictionary);
  }

  //Get user words.
  ReadExtra();
  struct TrieNode* userWordsOne =  GetUserWords();

  //Score and print the words the player found.
  char str2[MAXLENGTH+1];
  int level = 0;
  int playerOneGameScore = 0;
  char playerScoreSeperator[100] = "--------------------------------Points-------------------------------------";
  printf("\n%s\n", playerScoreSeperator);
  wordOnLine=0;
  playerOneGameScore = ScoreFoundWords(userWordsOne,  str2, level, playerOneGameScore, wordList,&wordOnLine);
  printf("\n\nTotal: %d\n", playerOneGameScore);

  //Find high score of user. Instead of keeping track of wins, keeps track of high score.
  char highScoreSeparator[100] = "------------------------------High Score-----------------------------------";

  printf("\n\n%s\n\n", highScoreSeparator);
  if (playerOneGameScore > playerHighScore) {
      playerHighScore = playerOneGameScore;
      printf("You beat your high score!\nHigh score is now: %d \n\n", playerHighScore);
  }
  else {
      printf("High score is still: %d\n\n\n", playerHighScore);
  }

  char str3[MAXLENGTH+1];
  level = 0;
  int wordNumber = 0;
  int viewList = ViewFullList();
  if (viewList == 1) {
    PrintTrie(wordList, str3, level, &wordNumber);
  }
  printf("\n\n");

  //Free dynamically allocated variables - they are no longer needed.
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

  FreeTrie(userWordsOne);
  FreeTrie(wordList);

  int playAgain = PlayAgain();

  if (playAgain == 1) {
    OnePlayer(playerHighScore, dictionary, size);
  }
  else {
    int newGame = ChooseMode();
    HandleChoice(newGame, dictionary);
  }

  return;
}

void OnePlayerSaveScore(int playerHighScore, struct TrieNode* dictionary, int size) {

  char boardSizeAsString[snprintf(NULL, 0, "%d", size) + 1];
  sprintf(boardSizeAsString, "%d", size);
  strncat(boardSizeAsString, ".txt", 4);

  int savedHighScore = 0;

  FILE* fpHighScore;
  fpHighScore = fopen(boardSizeAsString, "r");
  if (fpHighScore != NULL) {
    if (fscanf(fpHighScore, "%d", &savedHighScore)!=1) {
      savedHighScore = 0;
    }
    fclose(fpHighScore);
  }

  playerHighScore = savedHighScore;

  PrintStatus(ONEPLAYERSAVE, "Player One", playerHighScore, "NA", 0);

  //Make and print boggle board.
  //int size = ChooseBoardSize();
  char **boggleBoardTable = CreateBoggleBoardTable(size, size);
  PrintBoggleBoard(boggleBoardTable, size, size);
  char* list = CreateBoggleBoardNodeList(boggleBoardTable, size, size);
  struct Graph* boggleBoardGraph = CreateBoggleBoardGraph(boggleBoardTable, size, size);

  //Find all words in board.
  int* visited = malloc(size*size * sizeof(int));
  for (int i = 0; i <size*size;  i++){
      visited[i] = 0;
    }
  char str[MAXLENGTH+1] = "\0";
  int startIndex = 0;
  int count = 0;

  struct TrieNode* wordList = CreateNewTrieNode();
  for (int i = 0; i <size*size; i++) {
    startIndex = i;
    wordList= FindWordsTrie(boggleBoardGraph, list, visited, startIndex, count, str, wordList, dictionary);
  }

  //Get user words.
  ReadExtra();
  struct TrieNode* userWordsOne =  GetUserWords();

  //Score and print the words the player found.
  char str2[MAXLENGTH+1];
  int level = 0;
  int playerOneGameScore = 0;
  char playerScoreSeperator[100] = "--------------------------------Points-------------------------------------";
  printf("\n%s\n", playerScoreSeperator);
  wordOnLine=0;
  playerOneGameScore = ScoreFoundWords(userWordsOne,  str2, level, playerOneGameScore, wordList,&wordOnLine);
  printf("\n\nTotal: %d\n", playerOneGameScore);



  //Find high score of user. Instead of keeping track of wins, keeps track of high score.
  char highScoreSeparator[100] = "------------------------------High Score-----------------------------------";

  printf("\n\n%s\n\n", highScoreSeparator);
  if (playerOneGameScore > playerHighScore) {
      playerHighScore = playerOneGameScore;
      fpHighScore = fopen(boardSizeAsString, "w");
      fprintf(fpHighScore,"%d",playerHighScore);
      fclose(fpHighScore);
      printf("You beat your high score!\nHigh score is now: %d \n\n", playerHighScore);
    }
  else {
        printf("High score is still: %d\n\n", playerHighScore);
      }

  char str3[MAXLENGTH+1];
  level = 0;
  int wordNumber = 0;
  int viewList = ViewFullList();
  if (viewList == 1) {
    PrintTrie(wordList, str3, level, &wordNumber);
  }

  //Free dynamically allocated variables - they are no longer needed.
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

  FreeTrie(userWordsOne);
  FreeTrie(wordList);

  printf("\n\n");
  int playAgain = PlayAgain();

  if (playAgain == 1) {
    OnePlayerSaveScore(playerHighScore, dictionary, size);
  }
  else {
    int newGame = ChooseMode();
    HandleChoice(newGame, dictionary);
  }

  return;
}

void DisplayInstructions(struct TrieNode * dictionary) {

  printf("\n\
  Hello! Welcome to Boggle Game, a mind-boggling game of word fun. \n\
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\
  HOW TO PLAY:\n\
      The goal of the game is to connect the letters on the board to form words.\n\
      You may connect letters in any direction (up, down, left, right, diagonal),\n\
      but you may not use a letter more than once (for instance, if there are two\n\
      different 'a' tiles on the board, you may use each once, but you may not hit a\n\
      single tile twice). Additionally, if a word exists in two separate positions, \n\
      it will only be counted once. You will have three minutes to do this! After\n\
      three minutes, you will be timed out any word you entered will not be counted.\n\
  \n\
  SCORING:\n\
      The boggle words are scored according to their word length. Of course, words\n\
      must be in the dictionary being used to get any points.\n\
  \n\
            < 3 letters: 0  Points\n\
            3-4 letters: 1  Point\n\
            5   letters: 2  Points\n\
            6   letters: 3  Points\n\
            7   letters: 5  Points\n\
            8+  letters: 11 Points\n\
  \n\
  MODES OF GAMEPLAY:\n\
  \n\
      As you can see, there are several modes of gameplay! They all follow the same general\n\
      rules, but each has its own characteristics.\n\
  \n\
      VS COMPUTER:\n\
        In playing against the computer, you will type in all of the words you have found and\n\
        receive your score. The computer will then print all the words it found (which will be\n\
        all of them). Winning will be impossible, but you can try to tie for a real challenge!\n\
        Once you enter playing against computer mode, you may play several matches in a row, and\n\
        the computer will keep track of the number of wins for a you and the computer (until you\n\
        exit this mode). You may change the board size between matches.\n\
  \n\
      VS COMPUTER, REDUCED DIFFICULTY:\n\
        Just like vs. computer, but the computer only prints and scores a portion of the words\n\
        it finds - now, you can win!\n\
  \n\
      PLAYER VS PLAYER:\n\
        Each of two players will have a turn to enter their words (on the same board) on a three\n\
        minute timer. You may play several matches in a row, and the computer will keep track of\n\
        the number of wins for each player (until you exit this mode). You may change the board\n\
        size between matches.\n\
  \n\
      ONE PLAYER:\n\
        Though initially this may seem like playing against the computer, it is quite different\n\
        - the only person you can lose to (or beat!) is yourself. Here, the computer keeps track\n\
        of the high score of your consecutive matches. You may not change board size between matches,\n\
        as comparing raw scores between different size boards doesn't make sense. \n\
  \n\
      ONE PLAYER - SAVE PROGRESS:\n\
        This is just like one player, but saves your high score between sessions. Why would you use one \n\
        player instead of one player save progress? Perhaps your friend is playing on your computer and \n\
        you don't want your high score to be their play!\n" );

    printf("\n\n Press enter to continue: ");
    char enter;
    scanf("%c", &enter);
    scanf("%c", &enter);
    while (enter != '\n') {
      scanf("%c", &enter);
    }

    int choice = ChooseMode();
    HandleChoice(choice, dictionary);
  return;
}


void HandleChoice(int choice, struct TrieNode* dictionary) {
  if (choice == VSCOMPUTER) {
    PlayAgainstComputer(0,0, dictionary, VSCOMPUTER);//PlayAgainstComputer takes arguments (playerScore, computerScore, dictionary, difficultyLevel)
                                            //difficultyLevel = 2 indicates normal difficulty
  }
  else if (choice == VSCOMPUTEREASY) {
    PlayAgainstComputer(0,0, dictionary, VSCOMPUTEREASY); //PlayAgainstComputer takes arguments (playerScore, computerScore, dictionary, difficultyLevel)
                                            //difficultyLevel = 1 indicates reduced difficulty
  }
  else if (choice == VSPLAYER) {
    PlayerVsPlayer(0,0,dictionary);
    return;
  }
  else if (choice == ONEPLAYER) {
    int size = ChooseBoardSize();
    OnePlayer(0,dictionary, size);
  }
  else if (choice == ONEPLAYERSAVE) {
    int size = ChooseBoardSize();
    OnePlayerSaveScore(0,dictionary, size);
  }
  else if (choice == BOGGLEINSTRUCTIONS) {
      DisplayInstructions(dictionary);
  }
  else {
    FreeTrie(dictionary);
    return;
  }
}
