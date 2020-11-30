#include <stdio.h>
#include<conio.h>
#include<string.h>
#include<windows.h>
#define MAXBOMB 100

/*
0: 벽, 1: 길, 2: 시작점, 3: 도착점, 4: 폭탄
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

	*PlayerPos = *pStartPos; //시작점에서 플레이어 시작

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
	strcpy_s(Maze[19], 21, "00000000111111111113");
}

void Output(char Maze[21][21], _tagPPoint PlayerPos)
{
	for (int i = 0; i < 21; ++i)
	{
		for (int j = 0; j < 21; ++j)
		{
			if (Maze[i][j] == '4')//폭탄
				printf("※");
			else if (PlayerPos->x == j && PlayerPos->y == i) //플레이어의 위치
			{
				printf("☆");
			}
			else if (Maze[i][j] == '0')//벽
			{
				printf("■");
			}
			else if (Maze[i][j] == '1')//길
			{
				printf("  ");

			}
			else if (Maze[i][j] == '2')//시작점
			{
				printf("★");
			}
			else if (Maze[i][j] == '3')//도착점
			{
				printf("♥");
			}

		}printf("\n");
	}
}

void MoveUp(char Maze[21][21], _tagPPoint PlayerPos)
{
	if (PlayerPos->y - 1 >= 0)//위로 이동 가능한 경우
	{
		//벽, 폭탄인지 확인
		if (Maze[PlayerPos->y - 1][PlayerPos->x] != '0' &&
			Maze[PlayerPos->y - 1][PlayerPos->x] != '4')
		{
			--PlayerPos->y;
		}
	}
}
void MoveDown(char Maze[21][21], _tagPPoint PlayerPos)
{
	if (PlayerPos->y + 1 < 21)//아래로 이동 가능한 범위
	{
		//벽, 폭탄인지 확인
		if (Maze[PlayerPos->y + 1][PlayerPos->x] != '0' &&
			Maze[PlayerPos->y + 1][PlayerPos->x] != '4')
		{
			++PlayerPos->y;
		}
	}
}
void MoveRight(char Maze[21][21], _tagPPoint PlayerPos)
{
	if (PlayerPos->x + 1 < 21)//오른쪽으로 이동 가능한 경우
	{
		//벽, 폭탄인지 확인
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
		//벽, 폭탄인지 확인
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
	if (*BombCnt == 5) //최대 다섯개까지 폭탄 설치 가능
		return;

	for (int i = 0; i < *BombCnt; ++i) //중복위치에 설치 불가능
	{
		if (Player->x == BombArr[i].x && Player->y == BombArr[i].y)
			return;
	}
	BombArr[*BombCnt] = *Player; //설치한 폭탄의 위치를 배열로 저장
	++(*BombCnt);

	Maze[Player->y][Player->x] = '4';
	++(*BombUsingCnt);
}

void Fire(char Maze[21][21], _tagPPoint Player, _tagPPoint BombArr, int* BombCnt)
{
	for (int i = 0; i < *BombCnt; ++i)
	{
		//터뜨린 폭탄은 없어짐
		Maze[BombArr[i].y][BombArr[i].x] = '1';

		if (BombArr[i].y + 1 < 20)
		{
			if (Maze[BombArr[i].y + 1][BombArr[i].x] == '0')//위의 벽이 깨짐
				Maze[BombArr[i].y + 1][BombArr[i].x] = '1';

			//플레이어가 폭탄에 맞으면 시작점으로 돌아감
			if (Player->x == BombArr[i].x && Player->y == BombArr[i].y + 1)
			{
				Player->x = 0;
				Player->y = 0;
			}
		}
		if (BombArr[i].y - 1 < 20)
		{
			if (Maze[BombArr[i].y - 1][BombArr[i].x] == '0')//아래 벽이 깨짐
				Maze[BombArr[i].y - 1][BombArr[i].x] = '1';

			if (Player->x == BombArr[i].x && Player->y == BombArr[i].y - 1)
			{
				Player->x = 0;
				Player->y = 0;
			}
		}
		if (BombArr[i].x - 1 >= 0)
		{
			if (Maze[BombArr[i].y][BombArr[i].x - 1] == '0')//왼쪽 벽이 깨짐
				Maze[BombArr[i].y][BombArr[i].x - 1] = '1';

			if (Player->x == BombArr[i].x - 1 && Player->y == BombArr[i].y)
			{
				Player->x = 0;
				Player->y = 0;
			}
		}
		if (BombArr[i].x + 1 < 20)
		{
			if (Maze[BombArr[i].y][BombArr[i].x + 1] == '0')//오른쪽 벽이 깨짐
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
int Winner(int PlayerCnt, int PlayerBombCnt[5], int minBomb, int winner)
{
	for (int i = 0; i < PlayerCnt; i++)
	{
		if (PlayerBombCnt[i] < minBomb)
		{
			minBomb = PlayerBombCnt[i];
			winner = i + 1;
		}
	}
	return winner;
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
	int PlayerCnt = 0;
	int minBomb = MAXBOMB;
	int winner = 0;

	printf("플레이어의 수를 입력하세요(최대 5명까지 가능합니다): ");
	scanf_s("%d", &PlayerCnt);
	const int Player_Cnt = PlayerCnt;

	int PlayerBombCnt[5] = { 0, };

	SetMaze(strMaze, &PlayerPos, &StartPos, &EndPos);
	for (int i = 0; i < PlayerCnt; i++)
	{
		if (i == 1)
		{
			SetMaze(strMaze, &PlayerPos, &StartPos, &EndPos);
		}
		while (1)
		{
			system("cls");
			//미로 출력
			Output(strMaze, &PlayerPos);

			if (PlayerPos.x == EndPos.x && PlayerPos.y == EndPos.y)
			{
				printf("도착했습니다\n");
				printf("사용하신 폭탄의 개수는 %d 입니다.\n", BombUsingCnt);
				PlayerBombCnt[i] = BombUsingCnt;
				BombUsingCnt = 0;
				Sleep(1000);
				break;
			}
			printf("b : 폭탄 설치, f : 폭탄 터뜨리기\n");
			printf("w : 위, s : 아래, a : 왼쪽, d : 오른쪽, q : 종료");
			char cinput = _getch(); //키보드 입력시 바로 반응
			if (cinput == 'q' || cinput == 'Q')
				break;
			else if (cinput == 'b' || cinput == 'B')
			{
				CreateBomb(strMaze, &PlayerPos, BombPos, &BombCnt, &BombUsingCnt);
			}
			else if (cinput == 'f' || cinput == 'F')
			{
				Fire(strMaze, &PlayerPos, BombPos, &BombCnt);
			}
			else
			{
				MovePlayer(strMaze, &PlayerPos, cinput);
			}
		}
		if (i == PlayerCnt - 1)
		{
			winner = Winner(PlayerCnt, PlayerBombCnt, minBomb, winner);
			printf("가장 폭탄을 적게 사용한 승자는 %d번째 플레이어입니다.", winner);
		}
	}

	return 0;
}