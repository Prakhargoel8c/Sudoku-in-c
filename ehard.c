#include<stdio.h>
int genrand();
int hole[9][9];
int checkokehard(int i)
{
    int j,flag1=0;
    for(j=0; j<9; j++)
    {
        if(hole[i][j]==1)
        {
            flag1++;
        }
    }
    if(flag1>6)
    {
        return 0;
    }
    else
    {
        return 1;
    }

}
int ehard()
{
    int i=9*9-38;
    //int i=1;
    int j,k,loc;
    //int l;
    for(j=0; j<9; j++)
        for(k=0; k<9; k++)
        {
            hole[i][j]=0;
        }
    for(j=0; j<9; j++)
    {
        for(k=0; k<3; k++)
        {
            if(i>0&&checkokehard(k))
            {
                loc=genrand();
                i--;
                if(hole[j][loc]!=1)
                {
                    hole[j][loc]=1;
                }
                else
                {
                    k--;
                    i++;
                }
            }
        }
    }
    /*for(j=0;j<9;j++)
        for(k=0;k<9;k++)
    {
        printf("%d ,",hole[j][k]);
    }*/
    return 0;
}
int holeehard(int i,int j)
{
    return(hole[j][i]);
}



