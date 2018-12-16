#include<stdio.h>
#include<windows.h>
int checkifValid(int a[9][9])
{
    int i,j,Total,flag=1;
    //int temp;
    if(flag==1)             /* if every input is in valid range then go for validation of Sudoku  */
    {
        for(i=0; i<9; i++)
        {
            Total=0;
            for(j=0; j<9; j++)
                Total=Total+a[i][j];
            if(Total!=45)
                break;
            /*   if Total is not 45 in any row then  go out of for loop  */
        }
        if(Total==45)                /*  if Total is 45 in all rows then check for columns   */
        {
            for(i=0; i<9; i++)
            {
                Total=0;
                for(j=0; j<9; j++)
                    Total=Total+a[j][i];
                if(Total!=45)
                    break;        /*   if Total is not 45 in any column then  go out of for loop  */
            }
            if(Total==45)                              /* if Total is 45 in all columns too    */
               {
                 printf("Valid");
                     MessageBox(0,"You Won.Press Ok to continue to nexl level.", "Soduku", MB_OK );
                     return 1;
               }

            else
                printf("invalid");
        }
        else
            printf("\n Invalid");
    }
    MessageBox(0,"Incorrect Answer.Press Ok to continue .", "Soduku", MB_OK );

    return 0;
}

