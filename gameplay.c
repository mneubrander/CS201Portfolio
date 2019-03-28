#include "trie.h"
#include "gameplay.h"

#define VSCOMPUTER 1
#define VSCOMPUTEREASY 2
#define VSPLAYER 3
#define ONEPLAYER 4
#define EXITGAME 5

#define MAXLENGTH 51
int wordOnLine = 0;
struct TrieNode;


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
  printf("What n x n size of board would you like to play on?\n\
  \t*WARNING: Board dimension greater than 40 may cause poor display.*\n\
  \tEnter an integer greater than 0 : ");
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
  if (choice != VSCOMPUTER && choice != VSCOMPUTEREASY && choice != VSPLAYER && choice != ONEPLAYER && choice != EXITGAME) {
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
  char seperator[100] = "-----------------------Time Starts Now!------------------------------";
  printf("\n%s\n\n", seperator);
  int wordnum = 1;
  char str[MAXLENGTH+1] = "\0";
  //int maxlength = 10;
  char temp;
  time_t start = time(NULL);

  //readextra();
  printf("Enter word %d (or XXX to quit): ", wordnum);
  fgets(str, MAXLENGTH, stdin);
  str[strcspn(str, "\n")] = '\0';

  while (strcmp(str, "XXX") != 0) {
    time_t now =time(NULL);
    if (now-start > 180) {
      printf("\n\tLast input was enterred after 3 Minutes. Time is up!\n \tRegardless of validity, it will not be counted.\n\n");
      if(strlen(str) == MAXLENGTH-1) readextra();
      break;
    }
    if(!stringisalpha(str)) {
      if(strlen(str) == MAXLENGTH -1) {
        readextra();
      }
      printf("\tNot valid input. Try again: ");
      fgets(str, MAXLENGTH, stdin);
      str[strcspn(str, "\n")] = '\0';
    }
    else{
      inserttrienode(str, userWords);
      if(strlen(str) == MAXLENGTH-1) readextra();
      wordnum++;
      printf("Enter word %d (or XXX to quit): ", wordnum);
      fgets(str, MAXLENGTH, stdin);
      str[strcspn(str, "\n")] = '\0';
    }
  }
  return userWords;

}

//Scores all of the words found by a user/computer.
int scoreFoundWords(struct TrieNode* trie, char *word, int level, int score, struct TrieNode* dictionary, int *wordOnLine) {
  if ((trie->isWordEnd)== 1)
    {
        word[level] = '\0';
        printf("[%s - %d]  ", word, scoreword(word, dictionary));
        if (*wordOnLine == 5) {
          printf("\n");
          *wordOnLine = 0;
        }
        else{(*wordOnLine)++;}
        score = score + scoreword(word, dictionary);
    }

    for (int i = 0; i < 26; i++)
    {
        if (trie->nextLetters[i])
        {
            word[level] = i + 'a';
            score = scoreFoundWords(trie->nextLetters[i], word, level + 1, score, dictionary, wordOnLine);
        }
    }
    return score;
}

//Scores half of the words found.
//This allows a user to play against the computer with a chance of winning
int scoreFoundWordsEasy(struct TrieNode* trie, char *word, int level, int score, struct TrieNode* dictionary, int justPrinted, int *wordOnLine) {
  if ((trie->isWordEnd)== 1)
    {
        word[level] = '\0';
        if(justPrinted == 0) {
          //if(strlen(word) > 2) {
            //If word is length two or less, it is not a valid boggle word. It's score will be zero and shouldn't be printed.
            printf("[%s - %d]   ", word, scoreword(word, dictionary));
            if (*wordOnLine == 5) {
              printf("\n");
              *wordOnLine = 0;
            }
            else{(*wordOnLine)++;}
        //  }
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
            score = scoreFoundWordsEasy(trie->nextLetters[i], word, level + 1, score, dictionary, justPrinted, wordOnLine);
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
//void handleChoice(int choice, struct TrieNode* dictionary);

//Function to handle player playing against a computer.
//difficultyLevel is the mode the player is playing in - it indicates easy or normal.

void playagainstcomputer(int playerScore, int computerScore, struct TrieNode* dictionary, int difficultyLevel) {

  char seperator[100] = "--------------------------------------------------------------------";
  printf("%s\n",seperator);
  printStatus(difficultyLevel, "Player  ", playerScore, "Computer", computerScore);

  //Get size of board. This can change before every game. Print and make the board.
  int size = chooseBoardSize();
  char **boggleBoardTable = createBoggleBoardTable(size, size);
  printBoggleBoard(boggleBoardTable, size, size);

  char* list = createBoggleBoardNodeList(boggleBoardTable, size, size);
  struct Graph* boggleBoardGraph = createBoggleBoardGraph(boggleBoardTable, size, size);

  //Have computer find all possible words.
  int* visited = malloc(size*size * sizeof(int));
  for (int i = 0; i <size*size;  i++){
      visited[i] = 0;
    }
  char str[MAXLENGTH + 1] = "\0";
  int startIndex = 0;
  int count = 0;
  struct TrieNode* wordList = createnewtrienode();

  for (int i = 0; i <size*size; i++) {
    startIndex = i;
    wordList= findWordsTrie(boggleBoardGraph, list, visited, startIndex, count, str, wordList, dictionary);
  }

  //Get user's words
  readextra(); //reads an extra newline/other inupt from previous screen interaction
  struct TrieNode* userWords =  getuserwords();

  //Score and print the number of points the player and computer each earned.
  char playerScoreSeperator[100] = "------------------------Player's Points------------------------------";
  char computerScoreSeperator[100] = "-----------------------Computer's Points-----------------------------";

  char str2[MAXLENGTH+1];
  int level = 0;
  int playerGameScore = 0;
  printf("\n%s\n\n", playerScoreSeperator);
  wordOnLine = 0;
  playerGameScore = scoreFoundWords(userWords,  str2, level, playerGameScore, wordList, &wordOnLine);
  printf("\n\nPLAYER TOTAL:  %d\n\n", playerGameScore);

  char str3[MAXLENGTH+1];
  level = 0;
  int computerGameScore = 0;
  printf("\n%s\n\n", computerScoreSeperator);
  wordOnLine = 0;
  if(difficultyLevel == VSCOMPUTER){
    computerGameScore = scoreFoundWords(wordList,  str2, level, computerGameScore, wordList,&wordOnLine);
  }
  else if (difficultyLevel == VSCOMPUTEREASY) {
    computerGameScore = scoreFoundWordsEasy(wordList,  str2, level, computerGameScore, wordList, 0, &wordOnLine);
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

  freetrie(wordList);
  freetrie(userWords);

  //Determine and print winner. Increment the winner's score.
  char winnerSeperator[100] = "---------------------------- Winner ---------------------------------";
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
  printStatus(VSPLAYER, "Player One", player1Score, "Player Two", player2Score);

  //Get size of board. This can change before every game. Print and make the board.
  int size = chooseBoardSize();
  char **boggleBoardTable = createBoggleBoardTable(size, size);
  printBoggleBoard(boggleBoardTable, size, size);
  char* list = createBoggleBoardNodeList(boggleBoardTable, size, size);
  struct Graph* boggleBoardGraph = createBoggleBoardGraph(boggleBoardTable, size, size);

  //Find all words in boggle board.
  int* visited = malloc(size*size * sizeof(int));
  for (int i = 0; i <size*size;  i++){
      visited[i] = 0;
    }
  char str[MAXLENGTH+1] = "\0";
  int startIndex = 0;
  int count = 0;

  struct TrieNode* wordList = createnewtrienode();
  for (int i = 0; i <size*size; i++) {
    startIndex = i;
    wordList= findWordsTrie(boggleBoardGraph, list, visited, startIndex, count, str, wordList, dictionary);
  }

  //Get players' words.
  readextra();
  printf("Player One - Please enter your words now.\n");
  struct TrieNode* userWordsOne =  getuserwords();

  //print enough newlines so player two (on a specific sized window) won't see player ones words.
  printf("\n\n\n");
  printf("\n\n\n");
  printf("\n\n\n");
  printf("\n\n\n");
  printf("\n\n\n");

  printBoggleBoard(boggleBoardTable, size, size);
  printf("Player Two - Please enter your words now.\n");
  struct TrieNode* userWordsTwo =  getuserwords();

  //Score and print player's words.
  char playerOneScoreSeperator[100] = "----------------------Player One's Points----------------------------";
  char playerTwoScoreSeperator[100] = "----------------------Player Two's Points----------------------------";
  char str2[MAXLENGTH+1];
  int level = 0;
  int playerOneGameScore = 0;
  printf("\n%s\n\n", playerOneScoreSeperator );
  wordOnLine = 0;
  playerOneGameScore = scoreFoundWords(userWordsOne,  str2, level, playerOneGameScore, wordList,&wordOnLine);
  printf("\n\nPLAYER ONE TOTAL: %d\n", playerOneGameScore);

  printf("\n\n");

  char str3[MAXLENGTH+1];
  level = 0;
  int playerTwoGameScore = 0;
  printf("\n%s\n\n", playerTwoScoreSeperator);
  wordOnLine = 0;
  playerTwoGameScore = scoreFoundWords(userWordsTwo,  str3, level, playerTwoGameScore, wordList,&wordOnLine);
  printf("\n\nPLAYER TWO TOTAL: %d\n", playerTwoGameScore);

  printf("\n\n\n");

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

  freetrie(userWordsOne);
  freetrie(userWordsTwo);

  //Determine and print winner.
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

  //Ask players if they would like to play again.
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

void oneplayer(int playerHighScore, struct TrieNode* dictionary, int size) {
  printStatus(ONEPLAYER, "Player One", playerHighScore, "NA", 0);

  //Make and print boggle board.
  //int size = chooseBoardSize();
  char **boggleBoardTable = createBoggleBoardTable(size, size);
  printBoggleBoard(boggleBoardTable, size, size);
  char* list = createBoggleBoardNodeList(boggleBoardTable, size, size);
  struct Graph* boggleBoardGraph = createBoggleBoardGraph(boggleBoardTable, size, size);

  //Find all words in board.
  int* visited = malloc(size*size * sizeof(int));
  for (int i = 0; i <size*size;  i++){
      visited[i] = 0;
    }
  char str[MAXLENGTH+1] = "\0";
  int startIndex = 0;
  int count = 0;

  struct TrieNode* wordList = createnewtrienode();
  for (int i = 0; i <size*size; i++) {
    startIndex = i;
    wordList= findWordsTrie(boggleBoardGraph, list, visited, startIndex, count, str, wordList, dictionary);
  }

  //Get user words.
  readextra();
  struct TrieNode* userWordsOne =  getuserwords();

  //Score and print the words the player found.
  char str2[MAXLENGTH+1];
  int level = 0;
  int playerOneGameScore = 0;
  char playerScoreSeperator[100] = "-----------------------------Points-----------------------------------";
  printf("\n%s\n", playerScoreSeperator);
  wordOnLine=0;
  playerOneGameScore = scoreFoundWords(userWordsOne,  str2, level, playerOneGameScore, wordList,&wordOnLine);
  printf("\n\nTotal: %d\n", playerOneGameScore);


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

  freetrie(userWordsOne);

  //Find high score of user. Instead of keeping track of wins, keeps track of high score.
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
    oneplayer(playerHighScore, dictionary, size);
  }
  else {
    int newGame = chooseMode();
    handleChoice(newGame, dictionary);
  }

  return;
}


void handleChoice(int choice, struct TrieNode* dictionary) {
  if (choice == VSCOMPUTER) {//1 INDICATES PLAYING AGAINST COMPUTER - Normal Difficulty
    playagainstcomputer(0,0, dictionary, VSCOMPUTER);//playagainstcomputer takes arguments (playerScore, computerScore, dictionary, difficultyLevel)
                                            //difficultyLevel = 2 indicates normal difficulty
  }
  else if (choice == VSCOMPUTEREASY) { //2 INDICATES PLAYING AGAINST COMPUTER - Reduced Difficulty
    playagainstcomputer(0,0, dictionary, VSCOMPUTEREASY); //playagainstcomputer takes arguments (playerScore, computerScore, dictionary, difficultyLevel)
                                            //difficultyLevel = 1 indicates reduced difficulty
  }
  else if (choice == VSPLAYER) { //3 INDICATES PLAYING PLAYER VS PLAYER
    playervsplayer(0,0,dictionary);
    return;
  }
  else if (choice == ONEPLAYER) { //4 INDICATES ONE PLAYER - NOT AGAINST COMPUTER
    int size = chooseBoardSize();
    oneplayer(0,dictionary, size);
  }
  else {
    freetrie(dictionary);
    return;
  }
}
