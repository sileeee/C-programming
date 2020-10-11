#include <stdio.h>
#include<conio.h>

/*
0: ��, 1: ��, 2: ������, 3: ������
*/

struct _tagPoint
{
	int x;
	int y;

};
typedef _tagPoint POINT;
typedef _tagPoint* PPOINT;

void SetMaze(char Maze[21][21], PPOINT pPlayerPos, PPOINT pStartPos, PPOINT pEndPos)
{
	pStartPos->x = 0;
	pStartPos->y = 0;

	pEndPos->x = 19;
	pEndPos->y = 19;

	*pPlayerPos = *pStartPos; //���������� �÷��̾� ����

	strcpy_s(Maze[0],  "21100000000000000000");
	strcpy_s(Maze[1],  "00111111111100000000");
	strcpy_s(Maze[2],  "00100000000111111100");
	strcpy_s(Maze[3],  "01100001000000000100");
	strcpy_s(Maze[4],  "01000001111000111100");
	strcpy_s(Maze[5],  "01000000000111100000");
	strcpy_s(Maze[6],  "01100000000100000000");
	strcpy_s(Maze[7],  "00100000000111111000");
	strcpy_s(Maze[8],  "00001110000000001100");
	strcpy_s(Maze[9],  "01111001111111111000");
	strcpy_s(Maze[10], "00000001000000010000");
	strcpy_s(Maze[11], "00011111001111111000");
	strcpy_s(Maze[12], "00000001110000000000");
	strcpy_s(Maze[13], "00011111000000000000");
	strcpy_s(Maze[14], "00000010000000000000");
	strcpy_s(Maze[15], "00111111111111111100");
	strcpy_s(Maze[16], "00100000000011111100");
	strcpy_s(Maze[17], "0011100000111011100");
	strcpy_s(Maze[18], "0000111100000010000");
	strcpy_s(Maze[19], "00000000011111111113");
}

void Output(char Maze[21][21], PPOINT pPlayerPos)
{
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			if (pPlayerPos->x == j && pPlayerPos->y == i)
			{
				printf("��");
			}
			if (Maze[i][j] == '0')
			{
				printf("��");
			}
			else if (Maze[i][j] == '1')
			{
				printf(" ");

			}
			else if (Maze[i][j] == '2')
			{
				printf("��");
			}
			else if (Maze[i][j] == '3')
			{
				printf("��");
			}
			printf("\n");
		}
	}
}

void MoveUp(char Maze[21][21], PPOINT pPlayerPos)
{
	if (pPlayerPos->y - 1 >= 0)//���� �̵� ������ ���
	{
		//������ Ȯ��
		if (Maze[pPlyerPos->y - 1][pPlayerPos->x] != '0')
		{
			--pPlayerPos->y;
		}
	}
}
void MoveDown(char Maze[21][21], PPOINT pPlayerPos)
{
	if (pPlayerPos->y + 1 < 20)//�Ʒ��� �̵� ������ ����
	{
		//������ Ȯ��
		if (Maze[pPlyerPos->y + 1][pPlayerPos->x] != '0')
		{
			++pPlayerPos->y;
		}
	}
}
void MoveRight(char Maze[21][21], PPOINT pPlayerPos)
{
	if (pPlayerPos->x + 1  < 20)//���� �̵� ������ ���
	{
		//������ Ȯ��
		if (Maze[pPlyerPos->y][pPlayerPos->x+1] != '0')
		{
			++pPlayerPos->x;
		}
	}
}
void MoveLeft(char Maze[21][21], PPOINT pPlayerPos)
{
	if (pPlayerPos->x - 1 < 20)//���� �̵� ������ ���
	{
		//������ Ȯ��
		if (Maze[pPlyerPos->y][pPlayerPos->x - 1] != '0')
		{
			--pPlayerPos->x;
		}
	}
}

void MovePlayer(char Maze[21][21], PPOINT pPlyerPos, char cintput)
{
	switch (cintput)
	{
	case'w':
	case'W':
		MoveUp(Maze, pPlyerPos);
	case's':
	case'S':
		MoveDown(Maze, pPlyerPos);
	case'a':
	case'A':
		MoveRight(Maze, pPlyerPos);
	case'd':
	case'D':
		MoveLeft(Maze, pPlyerPos);
	}
}


int main()
{
	char strMaze[21][21] = {};

	POINT tPlayerPos;
	POINT tStartPos;
	POINT tEndPos;

	SetMaze(strMaze, &tPlayerPos, &tStarPos, tEndPos);

	while (true)
	{
		system("cls");
		//�̷� ���
		Output(strMaze, &tPlayerPos);

		if (tPlayerPos.x == tEndPos.x && tPlayerPos.y == tEndPos.y)
		{
			printf("�����߽��ϴ�\n");
			break;
		}
		printf("w : ��, s : �Ʒ�, a : ����, d : ������, q : ����");
		char cinput = getch(); //Ű���� �Է½� �ٷ� ����
		if (cinput == 'q' || cinput == 'Q')
			break;

		MovePlayer(strMaze, &tPlayerPos, cinput);
	}

	return 0;
}