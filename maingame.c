#include <stdio.h>
#include<stdlib.h>
int writefile(int i)
{
 FILE *minor;
    minor = fopen("min.txt", "w");


   if (minor == NULL)
   {
        puts("error");
   exit(1);
 }
fprintf(minor,"%d",i);
fclose(minor);
   return 0;
}


