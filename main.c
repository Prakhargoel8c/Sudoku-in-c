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
int reigon(int i)
{
    int j=i/9;
    if(j==0||j==1||j==2||j==9||j==10||j==11||j==18||j==19||j==20)
    {
        j=0;
    }
    else if(j==3||j==4||j==5||j==12||j==13||j==14||j==21||j==22||j==23)
    {
        j=1;
    }
    else if(j==6||j==7||j==9||j==15||j==16||j==17||j==24||j==25||j==26)
    {
        j=2;
    }
    else if(j==27||j==28||j==29||j==36||j==37||j==38||j==45||j==46||j==47)
    {
        j=3;
    }
    else if(j==30||j==31||j==32||j==39||j==40||j==41||j==48||j==49||j==50)
    {
        j=4;
    }
    else if(j==33||j==34||j==35||j==42||j==43||j==44||j==51||j==52||j==53)
    {
        j=5;
    }
    else if(j==54||j==55||j==56||j==63||j==64||j==65||j==72||j==73||j==74)
    {
        j=6;
    }
    else if(j==57||j==58||j==59||j==66||j==67||j==68||j==75||j==76||j==77)
    {
        j=7;
    }
    else if(j==60||j==61||j==62||j==69||j==70||j==71||j==78||j==79||j==80)
    {
        j=8;
    }


    return j;
}

int fillRemaining()
    {
        int orgboard[9][9];
        int exsol[729][324];
        int sol[9][9];
        int i,j,q,k;
        for(i=0;i<9;i++)
        {
            for(j=0;j<9;j++)
            {
                orgboard[i][j]=board[i][j];
            }
        }
        for(i=0;i<729;i++)
        {
            for(j=0;j<324;j++)
            {
                exsol[i][j]=0;
            }
        }
        j=0;
        for(i=0;i<729;i++)//cell constraint
        {
           for(q=0;q<9;q++)
           {
               exsol[i++][j]=1;
               }
               j++;
        }
        j=81;
        for(i=0;i<729;i++)//row constraint
        {
            if(i%81!=0)
            {
                j=81;
            }
            for(q=0;q<9;q++)
            {
                exsol[i++][j++]=1;
            }
        }
        j=162;
        q=0;
        for(i=0;i<729;i++)//column constraint
        {
            j=162;
            for(q=0;q<80;q++)
            {
                exsol[i++][j++]=1;
            }
            exsol[i][j]=1;
        }
        j=243;
        for(i=0;i<729;i++)//box constraint
        {
           j=243+9*reigon(i);


        }

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
    clock_t t1=clock();
        clock_t t2;
double timetaken;
   diagfill();
   fillRemaining(0,SRN);
   //digholes();
   t2=clock();
   t1=t2-t1;
   timetaken=(((double)t1)/CLOCKS_PER_SEC);
   printf("%lf",timetaken);
   return 0;

}
void check()
{

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
      else if(key=='=')
      {
          check();
      }
      }
      glutPostRedisplay();
  }
void SpecialKeys(int key, int x, int y)
{
    switch (key)
	{
		case GLUT_KEY_LEFT:
		    if(row_sel!=0)
		{
		    row_sel=row_sel-1;
		}
		glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT:
		  if(row_sel!=8)
		{
		    row_sel=row_sel+1;
		}
		glutPostRedisplay();
			break;
		case GLUT_KEY_UP:
		    if(col_sel!=0)
	        {
	            col_sel=col_sel-1;
	        }
	        glutPostRedisplay();
			break;
		case GLUT_KEY_DOWN:
		if(col_sel!=8)
	        {
	            col_sel=col_sel+1;
	        }
		glutPostRedisplay();
			break;
	}
}
int main(int argc,char** argv)
{
 srand(time(0));
 generateboard();
 glutInit(&argc,argv);
 glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
 glutInitWindowSize(500,500);
 glutInitWindowPosition(200,200);
 glutCreateWindow("Sudoku");
 glutDisplayFunc(display);
 glutCreateMenu(menu);
glutAddMenuEntry("Tutorial",1);
glutAddMenuEntry("Game",2);
glutAttachMenu(GLUT_RIGHT_BUTTON);
glutMouseFunc(mouse1);
glutKeyboardFunc(keyboard);
glutSpecialFunc(SpecialKeys);
 glutMainLoop();
 return 0;
}
