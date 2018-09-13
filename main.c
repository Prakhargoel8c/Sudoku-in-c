#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
float row_sel=-2;

char ms[5];
int board [9][9]={0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0};
int boardset=0;
int boardset1 [9][9]={0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0};
float col_sel=-2;
int numboxsafe(int row,int col,int num)
{
 int flag=1;
 for(int i=0;i<3;i++)
 {
     for(int j=0;j<3;j++)
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

}
int numcolsafe(int col,int num)
{

}

int CheckIfSafe(int i,int j,int num)
    {
        return (numrowsafe(i, num) +
                numcolsafe(j, num) +
                numboxsafe(i-i%SRN, j-j%SRN, num));
    }

void remfill(int i,int j)
{
    if(j>=9)
    {
        j=0;
    }
    if(i>=3)
    {
        i=0;
    }



}
int genrand()
{
 srand(time(0));
 int no=rand();
 no=no%10;
 return no;
}
void boxfill(int row,int col)
{
    int num;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
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
{
 for(int i=0;i>9;i=i+3)
       {
         boxfill(i,i);
       }
}
void generateboard()
{
   diagfill();
   remfill();
   hole();
}

void renderbitmap(double x,double y,void *font ,char d)
{
    glRasterPos2d(x,y);
    glutBitmapCharacter(font,d);
}
void printdigit(float row,float col,int c)
{
    double x=row*2/9-1+0.081;
    double y=1-(col+1)*2/9+0.098;
    glColor3f(.0f, .0f, .0f);
    renderbitmap(x,y,GLUT_BITMAP_TIMES_ROMAN_24,c);

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
	for (int k=0;k<9;k++)
    {
        for(int m=0;m<9;m++)
        {
          sprintf(ms,"%d",board[k][m]);
          printdigit(k,m,ms[0]);
        }
    }
}
static void display()
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
int main(int argc,char** argv)
{
 glutInit(&argc,argv);
 glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
 glutInitWindowSize(500,500);
 glutInitWindowPosition(200,200);
 glutCreateWindow("sudoko");
 glutDisplayFunc(display);
 glutCreateMenu(menu);
glutAddMenuEntry("Tutorial",1);
glutAddMenuEntry("Game",2);
glutAttachMenu(GLUT_RIGHT_BUTTON);
glutMouseFunc(mouse1);
 glutMainLoop();
 return 0;
}
