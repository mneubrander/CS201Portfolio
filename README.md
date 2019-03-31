# CS201Portfolio

Video instructions can be found at https://www.youtube.com/watch?v=WB_kxWOzwms&t=643s (or  https://www.youtube.com/channel/UCQsz1IX7ijjDrZxaOMnmLNw if the previous link does not work).

## Getting Started
This project is expected to run on Ubuntu 18.04 - my testing was done on the Ubuntu 18.04 app for Windows.

### File Structure
All necessary files **except for the dictionary** (which will be discussed later) will be directly in the CS201Portfolio folder downloaded.
Files with code are main.c, gameplay.c, trie.c, and bogglegraph.c, along with their corresponding .h header files.

#### main.c
In main.c, the dictionary is read into the program. The user then chooses their mode of gameplay, which is handled by functions in gameplay.c.

#### gameplay.c
In gameplay.c, there is code for handling direct aspects of playing the game. This includes the functions for the different modes of gameplay, handling user input,
and finding words in a board.

#### bogglegraph.c
In bogglegraph.c, there is code for handling and building the boggle board as a graph.

#### trie.c
In trie.c, there is code for building and handling tries.


### Dictionary File
The project expects a dictionary file to be located in the folder that you are running the project in.
The file must be:
  - named BoggleDictionary.txt
  - words of completely *lowercase letters* (no special characters, numbers, uppercase, etc.)
  - one word per line (words and newlines only)

#### Script
Included in the repository is a script - PrepareScript.sh - that will download and prepare a dictionary.
The process for running the script (demonstrated in the video) is as follows:
  1. Type `chmod 755 PrepareScript.sh` into terminal
  2. Run `./PrepareScript.sh`
This will use wget to download the dictionary, remove unnecessary files downloaded, and remove special characters from the file.
If you decide to use a different dictionary, make sure it follows all of the required properties.

### Building and Running

To build the program, simply enter `make` on the command line (there is a Makefile). Use `./boggle` to run the program.
If for some reason this does not work, you may use `gcc main.c bogglegraph.c trie.c gameplay.c` and run `./a.out`.

## Game Play

There are several options that will appear upon running the program - further details about these are provided below.
However, one common theme of note to all sections is entering a character when the program expects an integer
*will* cause the program to exit.

### Entering Words
  - **Max Length**: Words have a maximum length of 50 letters - the longest word in the English language is *pneumonoultramicroscopicsilicovolcanoconiosis*,
    which is 45 characters, so this should be plenty! However, in case a longer word is entered, only the first 50 characters will be read - the rest will be
    discarded. Additionally, words must be all lowercase to be counted. In checking for valid input or not, the first (up to) 50 characters will be counted - if
    any of these are invalid, you will have to try your input again. For this reason, you should type your word and then immediately press enter - do not put a space
    after your word!
  - **Timer**: The game is played on a 3 minute timer. The timer begins once you are able to begin entering words. The time elapsed is checked every time you
    input a word - if more than 3 minutes has elapsed, that word will not be counted and your turn will be up.

### Player vs. Computer and Player vs. Computer - Reduced Difficulty
  - In Player vs. Computer Mode, you play against the computer. You will type in all of the words you have found and receive your score.
    The computer will then print all the words it found (which will be all of them). *Winning will be impossible*, but you can try to tie for a real challenge!
  - The score of player vs. computer is tracked between matches. Once the player vs. computer mode is exited, the score will be reset to 0-0!
  - The board size can be changed between matches.
  - Player vs. Computer - Reduced Difficulty functions just like player vs. computer, but with the computer only outputting a portion of the words. Of course,
    the computer actually knows all of them, however, this mode is still quite challenging!

### Player vs. Player
  - In Player vs. Player Mode, two players go head to head entering words found on the same board. Once one player enters all of their words, the time immediately
    starts for the next player.
  - The score of player vs. player is tracked between matches. Once the player vs. player mode is exited, the score will be reset to 0-0!
  - The board can be resized between matches.

### One Player and One Player - Save Progress
  - In one player mode, you are playing to beat your high score (the score of the game that would normally determine a winner) for a particular sized board.
  - In one player mode, the size of the board cannot be changed between matches - comparing high score for say, a 2x2 with a 8x8 board does not make sense.
  - One Player - Save Progress is just like One Player, but it saves the high score for a particular board to a txt file *boardsize*.txt. If no file exists,
    the current high score for that board size is assumed to be zero. **DO NOT MODIFY** this file!!
  - Why would you use one player vs. one player - save progress? Perhaps your friend is playing on your computer, and you don't want their high score to over-write
    yours!

### Instructions
In the instructions tab, an overview of how to play the game (scoring, rules, etc.) is given. This is more similar to an instructions manual you would fine in a
board game than a readme. Additionally, a brief overview functionality of each mode of game play is given so that the user does not have to return to the readme.

## Data Structures/Algorithms Implemented and Justification

### Game Board - Adjacency List
I stored the boggle board as an adjacency list as opposed to an adjacency matrix as the graph will be relatively sparse as the size of the board increases (ach node is connected to a maximum of 8 others) - storing this as an adjacency matrix could lead to a good bit of wasted memory compared to an adjacency list.

### Dictionary - Trie
Storing the dictionary as a trie makes sense because we can both search for words and insert words in O(L) time, where L is the length of the word. Additionally, when the computer is searching for words on the board, it can use the trie to discover when there are no more words beginning with the sequence of letters it is on and cut off that search path.

### Finding Words - Depth First Search
Using a depth first search to find all of the words in a boggle board makes sense because it will cover all possible paths, and has lower space complexity compared to a
breadth first search.


### Lists of Found Words - Trie
Using tries to store words found by both users and the computer makes sense as just like with the dictionary file, words will have a relatively limited and not very large Length, and we can insert/search in O(L) time.
Additionally, a word can only be counted once per board, and a trie will only store a single word once. Furthermore, the trie makes printing in alphabetical order easy.
