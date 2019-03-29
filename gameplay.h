#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include "trie.h"
#include "bogglegraph.h"

void ReadExtra();
int StringIsLower(char*str);
int ChooseBoardSize();
void PrintStatus(int mode, char* namePlayerOne, int scorePlayerOne,
                           char* namePlayerTwo, int scorePlayerTwo);
int ChooseMode();
int ScoreWord(char *word, struct TrieNode* dictionary);
struct TrieNode* GetUserWords();
int ScoreFoundWords(struct TrieNode* trie, char *word, int level, int score, struct TrieNode* dictionary, int* wordOnLine) ;
int ScoreFoundWordsEasy(struct TrieNode* trie, char *word, int level, int score, struct TrieNode* dictionary, int justPrinted, int* wordOnLine);
void PlayAgainstComputer(int playerScore, int computerScore, struct TrieNode* dictionary, int difficultyLevel);
void PlayerVsPlayer(int player1Score, int player2Score, struct TrieNode* dictionary);
void OnePlayer(int playerHighScore, struct TrieNode* dictionary, int size);
void OnePlayerSaveScore(int playerHighScore, struct TrieNode* dictionary, int size);
void DisplayInstructions(struct TrieNode * dictionary);
void HandleChoice(int choice, struct TrieNode* dictionary);

#endif
