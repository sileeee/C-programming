#include <stdio.h>
#include<conio.h>
#include<string.h>
#include<windows.h>
#define MAXBOMB 100

/*
0: 벽, 1: 길, 2: 시작점, 3: 도착점
*/
typedef struct _tagPoint { //플레이어의 위치를 나타내는 구조체
    int x;
    int y;

} _tagPoint, * _tagPPoint;

void SetMaze(char Maze[21][21], _tagPPoint PlayerPos, _tagPPoint pStartPos, _tagPPoint pEndPos);
void Output(char Maze[21][21], _tagPPoint PlayerPos);
void MoveRight(char Maze[21][21], _tagPPoint PlayerPos);
void MoveLeft(char Maze[21][21], _tagPPoint PlayerPos);
void MoveLeft(char Maze[21][21], _tagPPoint PlayerPos);
void MoveDown(char Maze[21][21], _tagPPoint PlayerPos);
void MovePlayer(char Maze[21][21], _tagPPoint PlayerPos, char cintput);
int CreateBomb(char Maze[21][21], const _tagPPoint Player, _tagPPoint BombArr, int* BombCnt, int* BombUsingCnt);
void Fire(char Maze[21][21], _tagPPoint Player, _tagPPoint BombArr, int* BombCnt);
int Winner(int PlayerCnt, int PlayerBombCnt[5], int minBomb, int winner);

int main() {

    int BombCnt = 0; //폭탄 개수 초기화
    char strMaze[21][21] = { 0, };
    int PlayerBombCnt[5] = { 0, }; //각 플레이어가 사용한 폭탄 개수 저장하는 배열
    int BombUsingCnt = 0; //사용한 폭탄의 개수
    int PlayerCnt = 0;
    int minBomb = MAXBOMB;
    int winner = 0;

    _tagPoint BombPos[5];
    _tagPoint PlayerPos;
    _tagPoint StartPos;
    _tagPoint EndPos;

    printf("플레이어의수를입력하세요(최대5명까지가능합니다): ");
    scanf_s("%d", &PlayerCnt);
    const int Player_Cnt = PlayerCnt;

    // 20x20크기의 미로 설정
    SetMaze(strMaze, &PlayerPos, &StartPos, &EndPos);

    for (int i = 0; i < Player_Cnt; i++) { //플레이어의 수만큼 게임을 반복시킴
        if (i == 1) {
            SetMaze(strMaze, &PlayerPos, &StartPos, &EndPos);
        }
        while (1) {
            system("cls");

            //미로출력
            Output(strMaze, &PlayerPos);

            if (PlayerPos.x == EndPos.x && PlayerPos.y == EndPos.y) { //종료시 출력
                printf("도착했습니다\n");
                printf("사용하신폭탄의개수는 %d 입니다.\n", BombUsingCnt);
                PlayerBombCnt[i] = BombUsingCnt;
                BombUsingCnt = 0;
                Sleep(1000);
                break;
            }

            char cinput = _getch(); //키보드입력시바로반응
            if (cinput == 'q' || cinput == 'Q') {
                break;
            }
            else if (cinput == 'b' || cinput == 'B') {
                CreateBomb(strMaze, &PlayerPos, BombPos, &BombCnt, &BombUsingCnt); //폭탄 설치
            }
            else if (cinput == 'f' || cinput == 'F') { //폭탄 터뜨림
                Fire(strMaze, &PlayerPos, BombPos, &BombCnt);
            }
            else {
                MovePlayer(strMaze, &PlayerPos, cinput); //플레이어 이동시킴
            }
        }
        if (i == PlayerCnt - 1) {
            winner = Winner(PlayerCnt, PlayerBombCnt, minBomb, winner);
            printf("가장폭탄을적게사용한승자는%d번째플레이어입니다.", winner);
        }
    }
    return 0;
}

void SetMaze(char Maze[21][21], _tagPPoint PlayerPos, _tagPPoint pStartPos, _tagPPoint pEndPos) { //미로를 설정하는 함수
    pStartPos->x = 0;
    pStartPos->y = 0;

    pEndPos->x = 19; //종료 지점
    pEndPos->y = 19;

    *PlayerPos = *pStartPos; //시작점에서플레이어시작

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

void Output(char Maze[21][21], _tagPPoint PlayerPos) { //미로를 출력시키는 함수
    for (int i = 0; i < 21; ++i) {
        for (int j = 0; j < 21; ++j) {
            if (Maze[i][j] == '4') { //폭탄
                printf("※");
            }
            else if (PlayerPos->x == j && PlayerPos->y == i) { //플레이어의위치
                printf("☆");
            }
            else if (Maze[i][j] == '0') {//벽
                printf("■");
            }
            else if (Maze[i][j] == '1') {//길
                printf("  ");
            }
            else if (Maze[i][j] == '2') {//시작점
                printf("★");
            }
            else if (Maze[i][j] == '3') { //도착점
                printf("♥");
            }

        }printf("\n");
    }
}

void MoveRight(char Maze[21][21], _tagPPoint PlayerPos) {//플레이어를 오른쪽으로 이동시키는 함수
    if (PlayerPos->x + 1 < 21) { //오른쪽으로이동가능한경우

        //벽인지확인
        if (Maze[PlayerPos->y][PlayerPos->x + 1] != '0') {
            ++PlayerPos->x; //오른쪽으로 이동시킴
        }
    }
}

void MoveLeft(char Maze[21][21], _tagPPoint PlayerPos) {//플레이어를 왼쪽으로 이동시키는 함수
    if (PlayerPos->x - 1 < 21) {
        //벽인지확인
        if (Maze[PlayerPos->y][PlayerPos->x - 1] != '0') {
            --PlayerPos->x;
        }
    }
}
void MoveUp(char Maze[21][21], _tagPPoint PlayerPos) {//플레이어를 위쪽으로 이동시키는 함수
    if (PlayerPos->y - 1 >= 0) {//위로이동가능한경우

        //벽인지확인
        if (Maze[PlayerPos->y - 1][PlayerPos->x] != '0') {
            --PlayerPos->y;
        }
    }
}
void MoveDown(char Maze[21][21], _tagPPoint PlayerPos) {//플레이어를 아래쪽으로 이동시키는 함수
    if (PlayerPos->y + 1 < 21) {//아래로이동가능한범위

        //벽인지확인
        if (Maze[PlayerPos->y + 1][PlayerPos->x] != '0') {
            ++PlayerPos->y;
        }
    }
}


void MovePlayer(char Maze[21][21], _tagPPoint PlayerPos, char cintput) {// 플레이어를 움직이는 함수
    switch (cintput) {
    case'w'://키보드 'w'를 눌렀을 경우
    case'W':
        MoveUp(Maze, PlayerPos);// 플레이어 위쪽으로 이동
        break;
    case's'://키보드 's'를 눌렀을 경우
    case'S':
        MoveDown(Maze, PlayerPos);// 플레이어 아래쪽으로 이동
        break;
    case'a'://키보드 'a'를 눌렀을 경우
    case'A':
        MoveLeft(Maze, PlayerPos);// 플레이어 왼쪽으로 이동
        break;
    case'd':
    case'D': //키보드 'D'를 눌렀을 경우
        MoveRight(Maze, PlayerPos); // 플레이어 오른쪽으로 이동
        break;
    }
}
int CreateBomb(char Maze[21][21], const _tagPPoint Player, _tagPPoint BombArr, int* BombCnt, int* BombUsingCnt) { //폭탄 생성하는 함수

    if (*BombCnt == 5) { //최대다섯개까지폭탄설치가능
        return 0;
    }
    for (int i = 0; i < *BombCnt; ++i) { //중복위치에설치불가능
        if (Player->x == BombArr[i].x && Player->y == BombArr[i].y) {
            return 0;
        }
    }
    BombArr[*BombCnt] = *Player; //설치한폭탄의위치를배열로저장
    ++(*BombCnt);

    Maze[Player->y][Player->x] = '4';
    ++(*BombUsingCnt);
}
void Fire(char Maze[21][21], _tagPPoint Player, _tagPPoint BombArr, int* BombCnt) { //폭탄을 터뜨리는 함수
    for (int i = 0; i < *BombCnt; ++i) {
        //터뜨린폭탄은없어짐
        Maze[BombArr[i].y][BombArr[i].x] = '1';

        if (BombArr[i].y + 1 < 20) {
            if (Maze[BombArr[i].y + 1][BombArr[i].x] == '0') {//위의벽이깨짐
                Maze[BombArr[i].y + 1][BombArr[i].x] = '1';
            }
            //플레이어가폭탄에맞으면시작점으로돌아감
            if (Player->x == BombArr[i].x && Player->y == BombArr[i].y + 1) {
                Player->x = 0;
                Player->y = 0;
            }
        }
        if (BombArr[i].y - 1 < 20) {
            if (Maze[BombArr[i].y - 1][BombArr[i].x] == '0') { //아래벽이깨짐
                Maze[BombArr[i].y - 1][BombArr[i].x] = '1';
            }
            if (Player->x == BombArr[i].x && Player->y == BombArr[i].y - 1) {
                Player->x = 0;
                Player->y = 0;
            }
        }
        if (BombArr[i].x - 1 >= 0) {
            if (Maze[BombArr[i].y][BombArr[i].x - 1] == '0') { //왼쪽벽이깨짐
                Maze[BombArr[i].y][BombArr[i].x - 1] = '1';
            }
            if (Player->x == BombArr[i].x - 1 && Player->y == BombArr[i].y) {
                Player->x = 0;
                Player->y = 0;
            }
        }
        if (BombArr[i].x + 1 < 20) {
            if (Maze[BombArr[i].y][BombArr[i].x + 1] == '0') {//오른쪽벽이깨짐
                Maze[BombArr[i].y][BombArr[i].x + 1] = '1';
            }
            if (Player->x == BombArr[i].x + 1 && Player->y == BombArr[i].y) {
                Player->x = 0;
                Player->y = 0;
            }
        }
    }
    *BombCnt = 0;
}
int Winner(int PlayerCnt, int PlayerBombCnt[5], int minBomb, int winner) { //승리한 플레이어를 찾아내는 함수
    for (int i = 0; i < PlayerCnt; i++) {
        if (PlayerBombCnt[i] < minBomb) {
            minBomb = PlayerBombCnt[i];
            winner = i + 1;
        }
    }
    return winner;
}