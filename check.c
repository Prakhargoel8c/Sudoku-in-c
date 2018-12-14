#include<stdio.h>
int main1(int a[9][9])
{
         int i,j,sum,temp,flag=1;
          if(flag==1)             /* if every input is in valid range then go for validation of Sudoku  */
         {
               for(i=0;i<9;i++)
               {
                    sum=0;
                    for(j=0;j<9;j++)
                    sum=sum+a[i][j];
                    if(sum!=45)
                       break;
                    /*   if sum is not 45 in any row then  go out of for loop  */
               }
               if(sum==45)                /*  if sum is 45 in all rows then check for columns   */
               {
                     for(i=0;i<9;i++)
                    {
                          sum=0;
                          for(j=0;j<9;j++)
                          sum=sum+a[j][i];
                          if(sum!=45)
                          break;        /*   if sum is not 45 in any column then  go out of for loop  */
                    }
                    if(sum==45)                              /* if sum is 45 in all columns too    */
                       printf("Valid");
                    else printf("invalid");
               }
               else
                   printf("\n Invalid");
         }
         return 0;
}

