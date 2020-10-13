#include <stdio.h>
#include<conio.h>
#include<string.h>
#include<windows.h>

/*
0: ��, 1: ��, 2: ������, 3: ������, 4: ��ź
*/
typedef struct _tagPoint
{
	int x;
	int y;

} _tagPoint, * _tagPPoint;

void SetMaze(char Maze[21][21], _tagPPoint PlayerPos, _tagPPoint pStartPos, _tagPPoint pEndPos)
{
	pStartPos->x = 0;
	pStartPos->y = 0;

	pEndPos->x = 19;
	pEndPos->y = 19;

	*PlayerPos = *pStartPos; //���������� �÷��̾� ����

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
	strcpy_s(Maze[12], 21, "00000001110000000000");
	strcpy_s(Maze[13], 21, "11111111000000000000");
	strcpy_s(Maze[14], 21, "00000010000000000000");
	strcpy_s(Maze[15], 21, "00000011111111111000");
	strcpy_s(Maze[16], 21, "00000010000000001000");
	strcpy_s(Maze[17], 21, "11111001111110111000");
	strcpy_s(Maze[18], 21, "00001111100000000000");
	strcpy_s(Maze[19], 21, "00000000111111100113");
}

void Output(char Maze[21][21], _tagPPoint PlayerPos)
{
	for (int i = 0; i < 21; ++i)
	{
		for (int j = 0; j < 21; ++j)
		{
			if (Maze[i][j] == '4')//��ź
				printf("��");
			else if (PlayerPos->x == j && PlayerPos->y == i) //�÷��̾��� ��ġ
			{
				printf("��");
			}
			else if (Maze[i][j] == '0')//��
			{
				printf("��");
			}
			else if (Maze[i][j] == '1')//��
			{
				printf("  ");

			}
			else if (Maze[i][j] == '2')//������
			{
				printf("��");
			}
			else if (Maze[i][j] == '3')//������
			{
				printf("��");
			}

		}printf("\n");
	}
}

void MoveUp(char Maze[21][21], _tagPPoint PlayerPos)
{
	if (PlayerPos->y - 1 >= 0)//���� �̵� ������ ���
	{
		//��, ��ź���� Ȯ��
		if (Maze[PlayerPos->y - 1][PlayerPos->x] != '0' &&
			Maze[PlayerPos->y - 1][PlayerPos->x] != '4')
		{
			--PlayerPos->y;
		}
	}
}
void MoveDown(char Maze[21][21], _tagPPoint PlayerPos)
{
	if (PlayerPos->y + 1 < 21)//�Ʒ��� �̵� ������ ����
	{
		//��, ��ź���� Ȯ��
		if (Maze[PlayerPos->y + 1][PlayerPos->x] != '0' &&
			Maze[PlayerPos->y + 1][PlayerPos->x] != '4')
		{
			++PlayerPos->y;
		}
	}
}
void MoveRight(char Maze[21][21], _tagPPoint PlayerPos)
{
	if (PlayerPos->x + 1 < 21)//���������� �̵� ������ ���
	{
		//��, ��ź���� Ȯ��
		if (Maze[PlayerPos->y][PlayerPos->x + 1] != '0' &&
			Maze[PlayerPos->y][PlayerPos->x + 1] != '4')
		{
			++PlayerPos->x;
		}
	}
}
void MoveLeft(char Maze[21][21], _tagPPoint PlayerPos)
{
	if (PlayerPos->x - 1 < 21)
	{
		//��, ��ź���� Ȯ��
		if (Maze[PlayerPos->y][PlayerPos->x - 1] != '0' &&
			Maze[PlayerPos->y][PlayerPos->x - 1] != '4')
		{
			--PlayerPos->x;
		}
	}
}

void MovePlayer(char Maze[21][21], _tagPPoint PlayerPos, char cintput)
{
	switch (cintput)
	{
	case'w':
	case'W':
		MoveUp(Maze, PlayerPos);
		break;
	case's':
	case'S':
		MoveDown(Maze, PlayerPos);
		break;
	case'a':
	case'A':
		MoveLeft(Maze, PlayerPos);
		break;
	case'd':
	case'D':
		MoveRight(Maze, PlayerPos);
		break;
	}
}

void CreateBomb(char Maze[21][21], const _tagPPoint Player, _tagPPoint BombArr, int* BombCnt, int* BombUsingCnt)
{
	if (*BombCnt == 5) //�ִ� �ټ������� ��ź ��ġ ����
		return;

	for (int i = 0; i < *BombCnt; ++i) //�ߺ���ġ�� ��ġ �Ұ���
	{
		if (Player->x == BombArr[i].x && Player->y == BombArr[i].y)
			return;
	}
	BombArr[*BombCnt] = *Player; //��ġ�� ��ź�� ��ġ�� �迭�� ����
	++(*BombCnt);

	Maze[Player->y][Player->x] = '4';
	++(*BombUsingCnt);
}

void Fire(char Maze[21][21], _tagPPoint Player, _tagPPoint BombArr, int* BombCnt)
{
	for (int i = 0; i < *BombCnt; ++i)
	{
		//�Ͷ߸� ��ź�� ������
		Maze[BombArr[i].y][BombArr[i].x] = '1';

		if (BombArr[i].y + 1 < 20)
		{
			if (Maze[BombArr[i].y + 1][BombArr[i].x] == '0')//���� ���� ����
				Maze[BombArr[i].y + 1][BombArr[i].x] = '1';

			//�÷��̾ ��ź�� ������ ���������� ���ư�
			if (Player->x == BombArr[i].x && Player->y == BombArr[i].y + 1)
			{
				Player->x = 0;
				Player->y = 0;
			}
		}
		if (BombArr[i].y - 1 < 20)
		{
			if (Maze[BombArr[i].y - 1][BombArr[i].x] == '0')//�Ʒ� ���� ����
				Maze[BombArr[i].y - 1][BombArr[i].x] = '1';

			if (Player->x == BombArr[i].x && Player->y == BombArr[i].y - 1)
			{
				Player->x = 0;
				Player->y = 0;
			}
		}
		if (BombArr[i].x - 1 >= 0)
		{
			if (Maze[BombArr[i].y][BombArr[i].x - 1] == '0')//���� ���� ����
				Maze[BombArr[i].y][BombArr[i].x - 1] = '1';

			if (Player->x == BombArr[i].x - 1 && Player->y == BombArr[i].y)
			{
				Player->x = 0;
				Player->y = 0;
			}
		}
		if (BombArr[i].x + 1 < 20)
		{
			if (Maze[BombArr[i].y][BombArr[i].x + 1] == '0')//������ ���� ����
				Maze[BombArr[i].y][BombArr[i].x + 1] = '1';
			if (Player->x == BombArr[i].x + 1 && Player->y == BombArr[i].y)
			{
				Player->x = 0;
				Player->y = 0;
			}
		}
	}
	*BombCnt = 0;
}
int main()
{
	char strMaze[21][21] = { 0, };

	_tagPoint PlayerPos;
	_tagPoint StartPos;
	_tagPoint EndPos;

	int BombCnt = 0;
	_tagPoint BombPos[5];

	int BombUsingCnt = 0;

	SetMaze(strMaze, &PlayerPos, &StartPos, &EndPos);

	while (1)
	{
		system("cls");
		//�̷� ���
		Output(strMaze, &PlayerPos);

		if (PlayerPos.x == EndPos.x && PlayerPos.y == EndPos.y)
		{
			printf("�����߽��ϴ�\n");
			printf("����Ͻ� ��ź�� ������ %d �Դϴ�.", BombUsingCnt);
			break;
		}
		printf("t : ��ź ��ġ, u : ��ź �Ͷ߸���\n");
		printf("w : ��, s : �Ʒ�, a : ����, d : ������, q : ����");
		char cinput = _getch(); //Ű���� �Է½� �ٷ� ����
		if (cinput == 'q' || cinput == 'Q')
			break;
		else if (cinput == 't' || cinput == 'T')
		{
			CreateBomb(strMaze, &PlayerPos, BombPos, &BombCnt, &BombUsingCnt);
		}
		else if (cinput == 'u' || cinput == 'U')
		{
			Fire(strMaze, &PlayerPos, BombPos, &BombCnt);
		}
		else
		{
			MovePlayer(strMaze, &PlayerPos, cinput);
		}
	}

	return 0;
}