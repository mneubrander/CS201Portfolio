# CS201Portfolio

Video instructions can be found at *insert link here*.

## Dictionary File
The project expects a dictionary file to be located in the folder that you are running the project in.
The file must be:
  - named BoggleDictionary.txt
  - words of completely **lowercase** letters (no special characters, numbers, uppercase, etc.)
  - one word per line (words and newlines only)

### Script
Included in the repository is a script - PrepareScript.sh - that will download and prepare a dictionary.
The process for running the script (demonstrated in the video) is as follows:
  1. Type `chmod 755 PrepareScript.sh` into terminal
  2. Run `./PrepareScript.sh`

If you decide to use a different dictionary, make sure it follows all of the required properties.

## Building and Running

To build the program, simply enter `make` on the command line (there is a Makefile). Use `./boggle` to run the program.

## Playing

There are several options that will appear upon running the program - further details about these are provided below.
However, one common theme of note to all sections is entering a character when the program expects an integer
*will* cause the program to exit.

### Instructions
In the instructions tab, an overview of how to play the game (scoring, rules, etc.) is given. Additionally, the functionality
of each mode of game play is given so that the user does not have to return to the readme.

###Entering Words
  - max length 50
  - timer

### Player vs. Computer and Player vs. Computer - Reduced Difficulty
  - save between
  - can't win

### Player vs. Player
  - Each has own timer

### One Player and One Player - Save Progress
  - Save between games
