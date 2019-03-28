#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  int x;
  scanf("%d", &x);

  char buffer[snprintf(NULL, 0, "%d", x) + 1];
  sprintf(buffer, "%d", x);

  strncat(buffer, ".txt", 4);
  printf("%s\n", buffer);

  int y = 0;
  FILE* fp;
  fp = fopen(buffer, "r");
  if (fp != NULL) {
    if (fscanf(fp, "%d", &y)!=1) y = 0;;
  }
  fclose(fp);

  y++;

  fp = fopen(buffer, "w");
  fprintf(fp,"%d",y);
  fclose(fp);


}
