#include<stdio.h>
int checkifValid(int a[9][9])
{
         int i,j,Total,temp,flag=1;
          if(flag==1)             /* if every input is in valid range then go for validation of Sudoku  */
         {
               for(i=0;i<9;i++)
               {
                    Total=0;
                    for(j=0;j<9;j++)
                    Total=Total+a[i][j];
                    if(Total!=45)
                       break;
                    /*   if Total is not 45 in any row then  go out of for loop  */
               }
               if(Total==45)                /*  if Total is 45 in all rows then check for columns   */
               {
                     for(i=0;i<9;i++)
                    {
                          Total=0;
                          for(j=0;j<9;j++)
                          Total=Total+a[j][i];
                          if(Total!=45)
                          break;        /*   if Total is not 45 in any column then  go out of for loop  */
                    }
                    if(Total==45)                              /* if Total is 45 in all columns too    */
                       printf("Valid");
                    else printf("invalid");
               }
               else
                   printf("\n Invalid");
         }
         return 0;
}

