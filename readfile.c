# include <stdio.h>
# include <string.h>
int read()
{
  FILE* file = fopen ("min.txt", "r");
  int i = 0;

  fscanf (file, "%d", &i);
  fclose (file);
  return i;
}
