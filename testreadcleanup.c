#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void readextra(){
  char temp = '\0';
  while(temp!='\n') {
    scanf("%c", &temp);
  }
return;
}

int stringisalpha(char*str) {
  for (int i = 0; i < strlen(str); i++) {
    if (!isalpha(*(str+i))) return 0;
  }
  return 1;
}

int main(void) {
  int maxlength = 11;
  char temp;
  int count = 0;
  int wordnum = 1;
  char str[15]="\0";

  printf("Enter word %d: ", wordnum);
  fgets(str, maxlength, stdin);
  str[strcspn(str, "\n")] = '\0';

  while (strcmp(str, "XXX") != 0) {
    if(!stringisalpha(str)) {
      if(strlen(str) == 10) {
        readextra();
      }
      printf("\tNot valid. Try again: ");
      fgets(str, maxlength, stdin);
      str[strcspn(str, "\n")] = '\0';
    }

    else{
      printf("\t Word Entered:%s\n", str);
      if(strlen(str) == 10) readextra();
      wordnum++;
      printf("Enter word %d (or XXX to quit)", wordnum);
      fgets(str, maxlength, stdin);
      str[strcspn(str, "\n")] = '\0';
    }
  }
}
