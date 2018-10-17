#include <windows.h>
#include <gl/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<math.h>
int row_sel=-2;
int i,j,SRN=3,k,m,N=9;

char ms[5];
int board[9][9]={0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0};
int boardset=0;
int boardset1[9][9]={0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0};
int col_sel=-2;
int roundNo(float num)
{
    return num < 0 ? num - 0.5 : num + 0.5;
}
int genrand()
{

 int no=rand();
 if(no>=10)
 {
   no=no%10;
 }
 if(no==0)
 {
     genrand();
 }
return no;

}
int numboxsafe(int row,int col,int num)
{
 int flag=1;
 for(i=0;i<3;i++)
 {
     for(j=0;j<3;j++)
     {
         if(board[row+i][col+j]==num)
         {
             flag=0;
         }
     }
 }
 return flag;
}
int numrowsafe(int row,int num)
{
    int flag=1;
    for(i=0;i<9;i++)
    {
        if(board[row][i]==num)
        {
            flag=0;
        }
    }
return flag;
}
int numcolsafe(int col,int num)
{
    int flag=1;
    for(i=0;i<9;i++)
    {
        if(board[i][col]==num)
        {
            flag=0;
        }
         }
return flag;
}

int CheckIfSafe(int a,int b,int num)
    {
        int res=numrowsafe(a, num) +
                numcolsafe(b, num) +
                numboxsafe(a-a%SRN, b-b%SRN, num);
        return (res);
    }

int fillRemaining(int i, int j)
    {
        int num;
        if (j>=N && i<N-1)
        {
            i = i + 1;
            j = 0;
        }
        if (i>=N && j>=N)
            return 1;

        if (i < SRN)
        {
            if (j < SRN)
                j = SRN;
        }
        else if (i < N-SRN)
        {
            if (j==(int)(i/SRN)*SRN)
                j =  j + SRN;
        }
        else
        {
            if (j == N-SRN)
            {
                i = i + 1;
                j = 0;
                if (i>=N)
                    return 1;
            }
        }

        for ( num = 1; num<=N; num++)
        {
            if (CheckIfSafe(i, j, num)==3)
            {
                board[i][j] = num;
                boardset1[i][j]=num;
                if (fillRemaining(i, j+1))
                    return 1;

                board[i][j] = 0;
            }
        }
        return 0;
    }

void boxfill(int row,int col)
{
    int num,i,j;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            do
            {
                 num=genrand();
            }
            while (numboxsafe(row,col,num)!=1);
            board[row+i][col+j]=num;
            boardset1[row+i][col+j]=num;
        }
    }


}
void diagfill()
{ int p;
           for(p=0;p<9;p=p+3)
           {
               boxfill(p,p);
           }

}
void digholes()
{
    int a,rh,ch,i=17;
    for(a=0;a<=i;a++)
    {
        rh=genrand()-1;
        ch=genrand()-1;
        if(board[rh][ch]!=0)
        {
            board[rh][ch]=0;
            boardset1[rh][ch]=0;
        }
        else
        {
            a--;
        }

    }
}
int generateboard()
{
   diagfill();
   fillRemaining(0,SRN);
   digholes();
   return 0;

}
void renderbitmap(double x,double y,void *font ,char d)
{
    glRasterPos2d(x,y);
    glutBitmapCharacter(font,d);
}
void printdigit(float row,float col,int c)
{
    int row1=roundNo(row);
    int col1=roundNo(col);
    if(boardset1[row1][col1]!=0)
    {double x=row*2/9-1+0.081;
    double y=1-(col+1)*2/9+0.098;
    glColor3f(255.0f, .0f, .0f);
    renderbitmap(x,y,GLUT_BITMAP_TIMES_ROMAN_24,c);
    }
    else
    {
        double x=row*2/9-1+0.081;
    double y=1-(col+1)*2/9+0.098;
    glColor3f(.0f, .0f, .0f);
    renderbitmap(x,y,GLUT_BITMAP_TIMES_ROMAN_24,c);
    }

}
void maingame()
{
 glClearColor(0.98,0.98,0.823,1);
    glClear(GL_COLOR_BUFFER_BIT);
 int h,v;

    	glLineWidth(1);
	glBegin(GL_LINES);
	glColor3f(.0f, .0f, .0f);
	double i=2.0/9.0;
	for( h  = 0; h < 9; ++h) {
		glVertex2f(1,  (i * h) - 1);
		glVertex2f(-1, (i * h) - 1);
	}

	for( v  = 0; v < 9; ++v) {
		glVertex2f(-1 + (i * v),  1);
		glVertex2f(-1 + (i * v), -1);
	}
	glEnd();
	    	glLineWidth(5);
	glBegin(GL_LINES);
	double l=2.0/6.0;
	glColor3f(.0f, .0f, 255.0f);

	glVertex2f(-1, l);
	glVertex2f( 1, l);

	glVertex2f(-1, -l);
	glVertex2f( 1, -l);
	glVertex2f(-1,  l);
	glVertex2f( 1,  l);

	glVertex2f(-l, -1);
	glVertex2f(-l,  1);

	glVertex2f( l,  1);
	glVertex2f( l, -1);
	if(row_sel!=-2&& col_sel!=-2)
    {
        glColor3f(255.0f, .0f, .0f);

	//horizontal lines//
	glVertex2f(((row_sel * i) - 1), (1 - ((col_sel + 1) * i)));
	glVertex2f(((row_sel * i) - 1)  + i, (1 - ((col_sel + 1) * i)));

	glVertex2f(((row_sel * i) - 1), (1 - ((col_sel) * i)));
	glVertex2f(((row_sel * i) - 1)  + i, (1 - ((col_sel) * i)));

	//vertical lines//
	glVertex2f(((row_sel * i) - 1), (1 - ((col_sel + 1) * i)));
	glVertex2f(((row_sel * i) - 1), (1 - ((col_sel) * i)));

	glVertex2f((((row_sel + 1) * i) - 1), (1 - ((col_sel + 1) * i)));
	glVertex2f((((row_sel + 1) * i) - 1), (1 - ((col_sel) * i)));
	/*--------------------------------------------------*/
    }
	glEnd();
	for ( k=0;k<9;k++)
    {
        for( m=0;m<9;m++)
        {
          if(board[k][m]!=0){
          sprintf(ms,"%d",board[k][m]);
          printdigit(k,m,ms[0]);
        }
        }
    }
}
void display()
{
    	glClearColor(0.98,0.98,0.823,1);
    glClear(GL_COLOR_BUFFER_BIT);
 maingame();
 glFlush();
}
void mouse1(int button,int state,int x,int y)
{

    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        row_sel  = x / (500 / 9);
	col_sel  = y / (500 / 9);
        }

    glutPostRedisplay();
}
void menu(int id)
{
   switch(id)
   {
      case 1:
      break;

       case 2:
       break;

     }
  }
  void keyboard(unsigned char key,int x,int y)
  {
      int rowk=row_sel;
      int colk=col_sel;
      if(boardset1[rowk][colk]==0)
      {if(key=='1')
      {
          board[rowk][colk]=1;
      }
      else if(key=='2')
      {
          board[rowk][colk]=2;
      }
      else if(key=='3')
      {
          board[rowk][colk]=3;
      }
      else if(key=='4')
      {
          board[rowk][colk]=4;
      }
      else if(key=='5')
      {
          board[rowk][colk]=5;
      }
      else if(key=='6')
      {
          board[rowk][colk]=6;
      }
      else if(key=='7')
      {
          board[rowk][colk]=7;
      }
      else if(key=='8')
      {
          board[rowk][colk]=8;
      }
      else if(key=='9')
      {
          board[rowk][colk]=9;
      }
      }
      glutPostRedisplay();
  }
int main(int argc,char** argv)
{
 srand(time(0));
 generateboard();
 glutInit(&argc,argv);
 glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
 glutInitWindowSize(500,500);
 glutInitWindowPosition(200,200);
 glutCreateWindow("sudokonew");
 glutDisplayFunc(display);
 glutCreateMenu(menu);
glutAddMenuEntry("Tutorial",1);
glutAddMenuEntry("Game",2);
glutAttachMenu(GLUT_RIGHT_BUTTON);
glutMouseFunc(mouse1);
glutKeyboardFunc(keyboard);
 glutMainLoop();
 return 0;
}
