#include <stdio.h>
#include<conio.h>
#include<string.h>
#include<windows.h>

/*
0: ��, 1: ��, 2: ������, 3: ������
*/
typedef struct _tagPoint
{
	int x;
	int y;

} _tagPoint, * _tagPPoint;
//typedef struct _tagPoint POINT;
//typedef struct _tagPoint* PPOINT;

void SetMaze(char Maze[21][21], _tagPPoint pPlayerPos, _tagPPoint pStartPos, _tagPPoint pEndPos)
{
	pStartPos->x = 0;
	pStartPos->y = 0;

	pEndPos->x = 19;
	pEndPos->y = 19;

	*pPlayerPos = *pStartPos; //���������� �÷��̾� ����

	strcpy_s(Maze[0], 21, "21100000000000000000");
	strcpy_s(Maze[1], 21, "00111111111110000000");
	strcpy_s(Maze[2], 21, "00100000000011111100");
	strcpy_s(Maze[3], 21, "11111111000000000100");
	strcpy_s(Maze[4], 21, "01000001111000111100");
	strcpy_s(Maze[5], 21, "01000000000111100000");
	strcpy_s(Maze[6], 21, "01100000000100000000");
	strcpy_s(Maze[7], 21, "00100000000111111000");
	strcpy_s(Maze[8], 21, "00100000000000001000");
	strcpy_s(Maze[9], 21, "01111001111111111000");
	strcpy_s(Maze[10], 21, "00010001000000010000");
	strcpy_s(Maze[11], 21, "00011110001111111110");
	strcpy_s(Maze[12], 21, "00000001111000000000");
	strcpy_s(Maze[13], 21, "11111111000000000000");
	strcpy_s(Maze[14], 21, "00000010000000000000");
	strcpy_s(Maze[15], 21, "00000011111111111000");
	strcpy_s(Maze[16], 21, "00000000000000001000");
	strcpy_s(Maze[17], 21, "11111001111110111000");
	strcpy_s(Maze[18], 21, "00001111100000100000");
	strcpy_s(Maze[19], 21, "00000000111111111113");
}

void Output(char Maze[21][21], _tagPPoint pPlayerPos)
{
	for (int i = 0; i < 21; ++i)
	{
		for (int j = 0; j < 21; ++j)
		{
			if (pPlayerPos->x == j && pPlayerPos->y == i) //�÷��̾��� ��ġ
			{
				printf("��");
			}
			else if (Maze[i][j] == '0')
			{
				printf("��");
			}
			else if (Maze[i][j] == '1')
			{
				printf("  ");

			}
			else if (Maze[i][j] == '2')
			{
				printf("��");
			}
			else if (Maze[i][j] == '3')
			{
				printf("��");
			}

		}printf("\n");
	}
}

void MoveUp(char Maze[21][21], _tagPPoint pPlayerPos)
{
	if (pPlayerPos->y - 1 >= 0)//���� �̵� ������ ���
	{
		//������ Ȯ��
		if (Maze[pPlayerPos->y - 1][pPlayerPos->x] != '0')
		{
			--pPlayerPos->y;
		}
	}
}
void MoveDown(char Maze[21][21], _tagPPoint pPlayerPos)
{
	if (pPlayerPos->y + 1 < 21)//�Ʒ��� �̵� ������ ����
	{
		//������ Ȯ��
		if (Maze[pPlayerPos->y + 1][pPlayerPos->x] != '0')
		{
			++pPlayerPos->y;
		}
	}
}
void MoveRight(char Maze[21][21], _tagPPoint pPlayerPos)
{
	if (pPlayerPos->x + 1 < 21)//���������� �̵� ������ ���
	{
		//������ Ȯ��
		if (Maze[pPlayerPos->y][pPlayerPos->x + 1] != '0')
		{
			++pPlayerPos->x;
		}
	}
}
void MoveLeft(char Maze[21][21], _tagPPoint pPlayerPos)
{
	if (pPlayerPos->x - 1 < 21)
	{
		//������ Ȯ��
		if (Maze[pPlayerPos->y][pPlayerPos->x - 1] != '0')
		{
			--pPlayerPos->x;
		}
	}
}

void MovePlayer(char Maze[21][21], _tagPPoint pPlayerPos, char cintput)
{
	switch (cintput)
	{
	case'w':
	case'W':
		MoveUp(Maze, pPlayerPos);
		break;
	case's':
	case'S':
		MoveDown(Maze, pPlayerPos);
		break;
	case'a':
	case'A':
		MoveLeft(Maze, pPlayerPos);
		break;
	case'd':
	case'D':
		MoveRight(Maze, pPlayerPos);
		break;
	}
}


int main()
{
	char strMaze[21][21] = { 0, };

	_tagPoint tPlayerPos;
	_tagPoint tStartPos;
	_tagPoint tEndPos;

	SetMaze(strMaze, &tPlayerPos, &tStartPos, &tEndPos);

	while (1)
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
		char cinput = _getch(); //Ű���� �Է½� �ٷ� ����
		if (cinput == 'q' || cinput == 'Q')
			break;

		MovePlayer(strMaze, &tPlayerPos, cinput);
	}

	return 0;
}