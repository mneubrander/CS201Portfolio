#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int stringisalpha(char*str) {
  for (int i = 0; i < strlen(str); i++) {
    if (!isalpha(*(str+i))) return 0;
  }
  return 1;
}

int main(void) {
  /*int maxlength = 10;
  char temp;
  int count = 0;

  char str[15]="\0";

  printf("Enter a word ");
  while(temp!='\n'){
    scanf("%c", &temp);
    if (isalpha(temp) && islower(temp) && count <maxlength){
      char t[2];
      t[0] = temp;
      t[1] = '\0';
      strncat(str, t,1);
    }
    count++;
  }

  printf("word is %s\n", str);*/

  int maxlength = 11;
  char temp;
  int count = 0;
  int wordnum = 1;
  char str[15]="\0";
  printf("Enter word 1: ");
  fgets(str, maxlength, stdin);
  str[strcspn(str, "\n")] = '\0';
  //scanf("%11s", str);

  while (strcmp(str, "XXX") != 0) {
    if(!stringisalpha(str)) {
      if(strlen(str) == 10) {
        temp = '\0';
        while(temp!='\n') {
          scanf("%c", &temp);
        }
      }
      printf("\tNot valid. Try again: ");

      fgets(str, maxlength, stdin);
      str[strcspn(str, "\n")] = '\0';
      //scanf("%11s", str);

    }
    else{
      printf("\t Word Entered:%s\n", str);
      if(strlen(str) == 10) {
        temp = '\0';
        while(temp!='\n') {
          scanf("%c", &temp);
        }
      }
      wordnum++;
      printf("Enter word %d (or XXX to quit)", wordnum);
      //fgets(word, maxlength, stdin);
      fgets(str, maxlength, stdin);
      str[strcspn(str, "\n")] = '\0';
      //scanf("%11s", str);
    }
    }

  /*while(temp!='\n'){
    scanf("%c", &temp);
    if (isalpha(temp) && islower(temp) && count <maxlength){
      char t[2];
      t[0] = temp;
      t[1] = '\0';
      strncat(str, t,1);
    }
    count++;
  }*/

  //printf("word is %s\n", str);
  //printf("%d\n", stringisalpha(str) );

return 0;

}
