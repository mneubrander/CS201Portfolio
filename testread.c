#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int stringisalpha(char*str) {
  printf("%d\n", strlen(str));
  for (int i = 0; i < strlen(str); i++) {
    printf("%c ",*(str+i));
    printf("%d\n",isalpha(*(str+i)));
    if (!isalpha(*(str+i))) return 0;
  }
  return 1;
}

int main(void) {
  /*int maxlength = 10;
  char temp;
  int count = 0;

  char str[15]='\0';

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

  int maxlength = 10;
  char temp;
  int count = 0;

  char str[15]="\0";
  printf("Enter a word ");
  fgets(str, 11, stdin);
  str[strcspn(str, "\n")] = '\0';

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

  printf("word is %s\n", str);
  printf("%d\n", stringisalpha(str) );

return 0;

}
