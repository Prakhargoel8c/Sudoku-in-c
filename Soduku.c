#include <stdio.h>
#include <string.h>
#define MAX_COL 1100
#define MAX_ROW 4100
#define SQ_OFFSET 0
#define RW_OFFSET 81
#define CL_OFFSET 162
#define BX_OFFSET 243
int main1(int a[9][9]);

struct str_node {

	struct str_node * Header;

	struct str_node * Left;
	struct str_node * Right;
	struct str_node * Up;
	struct str_node * Down;

	char IDName;
	int IDNum;
	int count;
};
	static int Sodoku[9][9] = { };


int nCol;int board[9][9];
int nRow;
struct str_node Matrix[MAX_COL][MAX_ROW];
struct str_node Root;
struct str_node *RootNode = &Root;
struct str_node *RowHeader[MAX_ROW];
char Data[MAX_COL][MAX_ROW];
int Result[MAX_ROW];
int nResult = 0;
char Finished;
int GlobalProgressUpdate;
int MaxK;
// --> Initialisation functions
int dataLeft(int i) {
	return i - 1 < 0 ? nCol - 1 : i - 1;
}
 int dataRight(int i) {
	return (i + 1) % nCol;
}
 int dataUp(int i) {
	return i - 1 < 0 ? nRow - 1 : i - 1;
}
 int dataDown(int i) {
	return (i + 1) % nRow;
}

void CreateMatrix(void) {
	int a, b, i, j;
	//Build toroidal linklist matrix according to data bitmap
	for (a = 0; a < nCol; a++) {
		for (b = 0; b < nRow; b++) {
			if (Data[a][b] != 0) {
				// Left pointer
				i = a;
				j = b;
				do {
					i = dataLeft(i);
				} while (Data[i][j] == 0);
				Matrix[a][b].Left = &Matrix[i][j];
				// Right pointer
				i = a;
				j = b;
				do {
					i = dataRight(i);
				} while (Data[i][j] == 0);
				Matrix[a][b].Right = &Matrix[i][j];
				// Up pointer
				i = a;
				j = b;
				do {
					j = dataUp(j);
				} while (Data[i][j] == 0);
				Matrix[a][b].Up = &Matrix[i][j];
				// Down pointer
				i = a;
				j = b;
				do {
					j = dataDown(j);
				} while (Data[i][j] == 0);
				Matrix[a][b].Down = &Matrix[i][j];
				// Header pointer
				Matrix[a][b].Header = &Matrix[a][nRow - 1];
				Matrix[a][b].IDNum = b;
				//Row Header
				RowHeader[b] = &Matrix[a][b];
			}
		}
	}
	for (a = 0; a < nCol; a++) {
		Matrix[a][nRow - 1].IDName = 'C';
		Matrix[a][nRow - 1].IDNum = a;
	}
	//Insert root
	Root.IDName = 'R';
	Root.Left = &Matrix[nCol - 1][nRow - 1];
	Root.Right = &Matrix[0][nRow - 1];
	Matrix[nCol - 1][nRow - 1].Right = &Root;
	Matrix[0][nRow - 1].Left = &Root;
}

// --> DLX Algorithm functions
int countOnes(struct str_node *c) {
	struct str_node *r;
	int i = 0;
	for (r = c->Down; r != c; r = r->Down)
		i++;
	return i;
}

struct str_node *ChooseColumn(void) {
	struct str_node *best, *c;
	int minOnes = 100000;
	for (c = RootNode->Right; c != RootNode; c = c->Right)
		if (minOnes > c->count)
			minOnes = c->count, best = c;
	return best;
}

void Cover(struct str_node *ColNode) {
	struct str_node *RowNode, *RightNode;
	ColNode->Right->Left = ColNode->Left;
	ColNode->Left->Right = ColNode->Right;
	for (RowNode = ColNode->Down; RowNode != ColNode; RowNode = RowNode->Down) {
		for (RightNode = RowNode->Right; RightNode != RowNode; RightNode = RightNode->Right) {
			RightNode->Up->Down = RightNode->Down;
			RightNode->Down->Up = RightNode->Up;
			RightNode->Header->count--;
		}
	}
}

void UnCover(struct str_node *ColNode) {
	struct str_node *RowNode, *LeftNode;
	for (RowNode = ColNode->Up; RowNode != ColNode; RowNode = RowNode->Up) {
		for (LeftNode = RowNode->Left; LeftNode != RowNode; LeftNode = LeftNode->Left) {
			LeftNode->Up->Down = LeftNode;
			LeftNode->Down->Up = LeftNode;
			LeftNode->Header->count++;
		}
	}
	ColNode->Right->Left = ColNode;
	ColNode->Left->Right = ColNode;
}

void SolutionRow(struct str_node *RowNode) {
	Cover(RowNode->Header);
	struct str_node *RightNode;
	for (RightNode = RowNode->Right; RightNode != RowNode; RightNode = RightNode->Right) {
		Cover(RightNode->Header);
	}
}

void PrintSolution(void);

void Search(int k) {
	/*if(GlobalProgressUpdate < k) {
	 printf("== Search(%d)\n", k);
	 PrintSolution();
	 GlobalProgressUpdate = k;
	 }*/
	if ((RootNode->Left == RootNode && RootNode->Right == RootNode) || k == (81 - MaxK)) {
		//Valid solution!
	printf("----------- SOLUTION FOUND -----------\n");
		PrintSolution();
		Finished = 1;
		return;
	}
	struct str_node *Column = ChooseColumn();
	if (Column->count == 0)
		return;
	Cover(Column);

	struct str_node *RowNode;
	struct str_node *RightNode;
	for (RowNode = Column->Down; RowNode != Column && !Finished; RowNode = RowNode->Down) {
		// Try this row node on!
		Result[nResult++] = RowNode->IDNum;
		for (RightNode = RowNode->Right; RightNode != RowNode; RightNode = RightNode->Right) {
			Cover(RightNode->Header);
		}
		Search(k + 1);
		// Ok, that node didn't quite work
		for (RightNode = RowNode->Left; RightNode != RowNode; RightNode = RightNode->Left) {
			UnCover(RightNode->Header);
		}
		Result[--nResult] = 0;
	}

	UnCover(Column);
}

// --> Sodoku to Exact Cover conversion

// Functions that extract data from a given 3-digit integer index number in the format [N] [R] [C].
 int retNb(int N) {
	return N / (81);
}
 int retRw(int N) {
	return (N / 9) % 9;
}
 int retCl(int N) {
	return N % 9;
}
 int retBx(int N) {
	return ((retRw(N) / 3) * 3) + (retCl(N) / 3);
}
 int retSq(int N) {
	return retRw(N) * 9 + retCl(N);
}
 int retRn(int N) {
	return retNb(N) * 9 + retRw(N);
}
 int retCn(int N) {
	return retNb(N) * 9 + retCl(N);
}
 int retBn(int N) {
	return retNb(N) * 9 + retBx(N);
}
// Function that get 3-digit integer index from given info
 int getIn(int Nb, int Rw, int Cl) {
	return Nb * 81 + Rw * 9 + Cl;
}

void PrintSolution(void) {
	int a, b;
	for (a = 0; a < 9; a++)
		for (b = 0; b < 9; b++)
			Sodoku[a][b] = -1;
	for (a = 0; a < nResult; a++)
		Sodoku[retRw(Result[a])][retCl(Result[a])] = retNb(Result[a]);
	for (a = 0; a < 9; a++) {
		for (b = 0; b < 9; b++) {
			printf("%i", Sodoku[a][b]+1);
		}
		printf("\n");
	}
}
int data(int i,int j)
{
    return(Sodoku[i][j]+1);
}

void BuildData(void) {
	int a, b, c;
	int Index;
	nCol = 4 * 9 * 9;
	nRow = 9 * 9 * 9;
	for (a = 0; a < 9; a++) {
		for (b = 0; b < 9; b++) {
			for (c = 0; c < 9; c++) {
				Index = getIn(c, a, b);
				Data[SQ_OFFSET + retSq(Index)][Index] = 1; //Constraint 1: Only 1 per square
				Data[RW_OFFSET + retRn(Index)][Index] = 1; //Constraint 2: Only 1 of per number per Row
				Data[CL_OFFSET + retCn(Index)][Index] = 1; //Constraint 3: Only 1 of per number per Column
				Data[BX_OFFSET + retBn(Index)][Index] = 1; //Constraint 4: Only 1 of per number per Box
			}
		}
	}
	for (a = 0; a < nCol; a++) {
		Data[a][nRow - 1] = 2;
	}
	CreateMatrix();
	for (a = 0; a < RW_OFFSET; a++) {
		Matrix[a][nRow - 1].IDName = 'S';
		Matrix[a][nRow - 1].IDNum = a;
	}
	for (a = RW_OFFSET; a < CL_OFFSET; a++) {
		Matrix[a][nRow - 1].IDName = 'R';
		Matrix[a][nRow - 1].IDNum = a - RW_OFFSET;
	}
	for (a = CL_OFFSET; a < BX_OFFSET; a++) {
		Matrix[a][nRow - 1].IDName = 'C';
		Matrix[a][nRow - 1].IDNum = a - CL_OFFSET;
	}
	for (a = BX_OFFSET; a < nCol; a++) {
		Matrix[a][nRow - 1].IDName = 'B';
		Matrix[a][nRow - 1].IDNum = a - BX_OFFSET;
	}
}

void AddNumber(int N, int R, int C) {
	SolutionRow(RowHeader[getIn(N, R, C)]);
	MaxK++;
	Result[nResult++] = getIn(N, R, C);
}

/*
char nextchar() {
	char c;
	do {
		c = getchar();
	} while (c == ' ' || c == '\n');
	return c;
}
*/

void LoadPuzzle() {
	int a, b;
	char temp[20];
	for (a = 0; a < 9; a++) {
		for (b = 0; b < 9; b++) {
                int c=board[a][b];
			if (c >= 1 && c <= 9) {
				AddNumber((c - 1), a, b);
			}
		}
	}
}
int** driver(int num[9][9]) {
    int i,j;
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            board[i][j]=num[i][j];
        }
    }
		memset(Data, 0, sizeof(Data));
		Finished = 0;
		MaxK = 0;
		nResult = 0;
		BuildData();
		LoadPuzzle(num);
		struct str_node *r;
		for (r = RootNode->Right; r != RootNode; r = r->Right)
			r->count = countOnes(r);
		Search(0);
			printf("\n");
        return board;
}