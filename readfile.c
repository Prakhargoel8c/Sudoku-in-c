# include <stdio.h>
# include <string.h>
int read()
{
  FILE* file = fopen ("min.txt", "r");
  int i;

  fscanf (file, "%d", &i);
  fclose (file);
  printf("%d",i);
  return i;
}
