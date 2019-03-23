#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char* readstring(char* str) {

  char temp;
  int count = 0;
  str="\0";
  int maxlength = 10;

  while(temp!='\0'){
    scanf("%c", &temp);
    if (isalpha(temp) && islower(temp) && count <maxlength){
      char t[2];
      t[0] = temp;
      t[1] = '\0';
      printf("%s\n", str);
    }
    else{break;}
    count++;
  }
return str;
}


int main (void) {
//printf("Enter word d (or XXX to quit)");
char *word = malloc(15*sizeof(char));

word = readstring(word);

//while (strcmp(word, "XXX") != 0) {
  printf("\nword was %s\n", word);
  //printf("Enter word (or XXX to quit)");
  //free(word);
  //word = malloc(15*sizeof(char));
  //char* word = readstring(word);
//}
return 0;
}
