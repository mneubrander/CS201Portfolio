#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char* readstring(int maxlength) {

  char temp;
  int count = 0;
  char* str= malloc(maxlength*sizeof(char));

  while(temp!='\0'){
    scanf("%c", &temp);
    if (isalpha(temp) && islower(temp) && count <maxlength){
      char t[2];
      t[0] = temp;
      t[1] = '\0';
      printf("%s\n", str);
      strncat(str, t,1);
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
