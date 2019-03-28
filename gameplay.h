#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include "trie.h"
#include "bogglegraph.h"

void readextra();
int stringisalpha(char*str);
int chooseBoardSize();
void printStatus(int mode, char* namePlayerOne, int scorePlayerOne,
                           char* namePlayerTwo, int scorePlayerTwo);
int chooseMode();
int scoreword(char *word, struct TrieNode* dictionary);
struct TrieNode* getuserwords();
int scoreFoundWords(struct TrieNode* trie, char *word, int level, int score, struct TrieNode* dictionary, int* wordOnLine) ;
int scoreFoundWordsEasy(struct TrieNode* trie, char *word, int level, int score, struct TrieNode* dictionary, int justPrinted, int* wordOnLine);
void playagainstcomputer(int playerScore, int computerScore, struct TrieNode* dictionary, int difficultyLevel);
void playervsplayer(int player1Score, int player2Score, struct TrieNode* dictionary);
void oneplayer(int playerHighScore, struct TrieNode* dictionary, int size);
void handleChoice(int choice, struct TrieNode* dictionary);

#endif
