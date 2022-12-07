#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

#define GAMESTART 1
#define LEVEL 2
#define EXIT 3
#define WIDTH 10
#define HEIGHT 20
#define Y 0
#define X 1
#define NULL 0
#define WALL 1
#define PLAYER 2
#define STAR 3
#define BEAM 4
#define ITEM 5
#define false 0
#define true 1

struct Player
{
    int x  ;
    int y  ;
}player;


int level = 3;
int run = 1;
int score = 0;
int gNumOfBeams = 0;

int GameMenu()
{
    int Select;
    printf("====별동별 피하기====\n");

    printf("  1.게임 시작\n\n");

    printf("  2.난이도 조절\n\n");

    printf("  3.종료\n\n");

    printf("  B777000 전승권\n\n");

    printf("  B777000 송우주\n\n");

    printf("  B877000 신우성\n\n");

    scanf("%d", &Select);

    return Select;
}

void Init(int map[][WIDTH])
{
    player.x = WIDTH - 5;
    player.y = HEIGHT - 1;
}

void StarCreate(int map[HEIGHT][WIDTH])
{
    int lv, i, x;
    for (lv = 0; lv < level; lv++)
    {
        x = rand() % 8 + 1;

        if (map[0][x] == STAR)
        {
            lv--;
        }
        else
        {
            map[0][x] = STAR;
        }
    }
}

void ItemCreate(int map[HEIGHT][WIDTH])
{
    srand(time(NULL));
    int ran = rand() % 4; // 25% 확률
    if (ran == 1) {
        srand(time(NULL));
        ran = rand() % 8 + 1;
        if (ran > 1 && ran < WIDTH - 1) {
            if (map[0][ran] != STAR) {
                map[0][ran] = ITEM;
            }
        }
    }
}
void gotoxy(int x, int y)
{
    COORD Pos = { x - 1, y - 1 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void map_reset(int map[HEIGHT][WIDTH])
{
    int y, x;
    for (y = 0; y < HEIGHT; y++)
    {
        for (x = 0; x < WIDTH; x++)
        {
            map[y][0] = WALL;
            map[y][WIDTH - 1] = WALL;
        }
    }
    StarCreate(map);
}

void BeamDraw()
{
    printf("├────────────────┤\n");
    switch (gNumOfBeams) {
    case 0:
        printf("│ Beams = □□□ │\n");
        break;
    case 1:
        printf("│ Beams = ■□□ │\n");
        break;
    case 2:
        printf("│ Beams = ■■□ │\n");
        break;
    case 3:
        printf("│ Beams = ■■■ │\n");
    }
    printf("┗────────────────┘\n");
}

void MapDraw(int map[HEIGHT][WIDTH])
{
    system("cls");
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            if (player.y == y && player.x == x)
                printf("옷");
            else if (map[y][x] == WALL)
                printf("│");
            else if (map[y][x] == STAR)
                printf("☆");
            else if (map[y][x] == ITEM)
                printf("ㅇ");
            else if (map[y][x] == BEAM)
                printf("↑");
            else
                printf("  ");
        }
        printf("\n");
    }
    BeamDraw();
    printf("   Score : %d\n", score);
    printf("     P   : 일시정지\n ");
}

void GameOverDraw(int map[HEIGHT][WIDTH])
{
    system("cls");
    int aspectRatio = 0;
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            if (player.y== y && player.x == x)
                printf("※");
            else if (map[y][x] == WALL)
                printf("│");
            else if (map[y][x] == STAR)
                printf("☆");
            else if (map[y][x] == ITEM)
                printf("ㅇ");
            else if (map[y][x] == BEAM)
                printf("↑");
            else if (x == 3 && y == 10) {
                aspectRatio = 4;
                printf("GAME OVER!");
            }
            else if (aspectRatio == 0)
                printf("  ");
            else
                --aspectRatio;
        }
        printf("\n");
    }
    BeamDraw();
    printf("   Score : %d\n", score);
}
void Star_Update(int map[HEIGHT][WIDTH])
{
    for (int y = HEIGHT - 1; y >= 0; y--)
    {
        for (int x = 1; x < WIDTH - 1; x++)
        {
            if (map[y][x] == STAR &&
                map[y + 1][x] != BEAM)
            {
                map[y][x] = 0;
                if (y + 1 >= HEIGHT)
                {
                    map[HEIGHT - 1][1] = 0;
                    map[HEIGHT - 1][2] = 0;
                    map[HEIGHT - 1][3] = 0;
                    map[HEIGHT - 1][4] = 0;
                    map[HEIGHT - 1][5] = 0;
                    map[HEIGHT - 1][6] = 0;
                    map[HEIGHT - 1][7] = 0;
                    map[HEIGHT - 1][8] = 0;
                    StarCreate(map);
                    ItemCreate(map);
                    return;
                }
                else //이부분을 건들면 좌우로 와리가리 칠수있다.
                {
                        map[y + 1][x] = STAR;
                        //map[y+1[x]]= STAR;

                }
            }
            else if (map[y][x] == ITEM &&
                map[y + 1][x] != BEAM)
            {
                map[y][x] = 0;
                map[y + 1][x] = ITEM;
            }
        }
    }
}

void Star1_Update(int map[HEIGHT][WIDTH])
{
    for (int y = HEIGHT - 1; y >= 0; y--)
    {
        for (int x = 1; x < WIDTH - 1; x++)
        {
            if (map[y][x] == STAR &&
                map[y + 1][x] != BEAM)
            {
                map[y][x] = 0;
                if (y + 1 >= HEIGHT)
                {
                    map[HEIGHT - 1][1] = 0;
                    map[HEIGHT - 1][2] = 0;
                    map[HEIGHT - 1][3] = 0;
                    map[HEIGHT - 1][4] = 0;
                    map[HEIGHT - 1][5] = 0;
                    map[HEIGHT - 1][6] = 0;
                    map[HEIGHT - 1][7] = 0;
                    map[HEIGHT - 1][8] = 0;
                    StarCreate(map);
                    ItemCreate(map);
                    return;
                }
                else //이부분을 건들면 좌우로 와리가리 칠수있다.
                {
                    int ran = rand() % 3+1;
                    int randNum = rand() % 2 + 1;
                    switch (ran)
                    {
                    case 1:
                        map[y + 1][x - 1] = STAR;//모니터 기준 왼쪽 아래로 대각선 이동
                        if (map[y][0] == STAR) // 해당좌표에서 스타가 갈경우
                        {
                            map[y][0] = WALL; // wall로 값을 다시 초기화
                            map[y + 1][WIDTH - 2] = STAR;   // 건너편 으로 스타를 값 이동
                        }
                        else if (map[y][WIDTH - 1] == STAR)// 해당 좌표에서 스타가 갈경우
                        {
                            map[y][WIDTH - 1] = WALL;   // wall 로 값을 다시 초기화
                            map[y + 1][1] = STAR; // 건너편으로 스타를 값 이동 
                        }
                        break;
                    case 2:
                        map[y + 1][x + 1] = STAR;//모니터 기준 오른쪽 아래로 대각선 이동
                        if (map[y][0] == STAR) // 해당좌표에서 스타가 갈경우
                        {
                            map[y][0] = WALL; // wall로 값을 다시 초기화
                            map[y + 1][WIDTH - 2] = STAR;   // 건너편 으로 스타를 값 이동
                        }
                        else if (map[y][WIDTH - 1] == STAR)// 해당 좌표에서 스타가 갈경우
                        {
                            map[y][WIDTH - 1] = WALL;   // wall 로 값을 다시 초기화
                            map[y + 1][1] = STAR; // 건너편으로 스타를 값 이동 
                        }
                        break;
                    case 3:
                        if (randNum == 1)
                            randNum = -1;
                        else
                            randNum = 1;
                        if (randNum == -1)
                        {
                            map[y + 1][x + randNum] = STAR;
                            if (map[y][0] == STAR) // 해당좌표에서 스타가 갈경우
                            {
                                map[y][0] = WALL; // wall로 값을 다시 초기화
                                map[y + 1][WIDTH - 2] = STAR;   // 건너편 으로 스타를 값 이동
                            }
                            else if (map[y][WIDTH - 1] == STAR)// 해당 좌표에서 스타가 갈경우
                            {
                                map[y][WIDTH - 1] = WALL;   // wall 로 값을 다시 초기화
                                map[y + 1][1] = STAR; // 건너편으로 스타를 값 이동 
                            }
                        }
                        else
                        {
                            map[y + 1][x + randNum] = STAR;
                            if (map[y][0] == STAR) // 해당좌표에서 스타가 갈경우
                            {
                                map[y][0] = WALL; // wall로 값을 다시 초기화
                                map[y + 1][WIDTH - 2] = STAR;   // 건너편 으로 스타를 값 이동
                            }
                            if (map[y][WIDTH - 1] == STAR)
                            {
                                map[y][WIDTH - 1] = WALL;   // wall 로 값을 다시 초기화
                                map[y + 1][1] = STAR; // 건너편으로 스타를 값 이동 
                            }
                        }
                        break;
                    }
                    // 기존 좌우로 이동 하는 코드 정리 전승권
                   /* 
                   map[y + 1][x - 1] = STAR; //좌측으로 대각선 그리면서 내려감
                    map[y + 1][x+1] = STAR; // 우측으로 대각선 그리면서 내려감
                    if (map[y][0] == STAR) // 해당좌표에서 스타가 갈경우
                    {
                        map[y][0] = WALL; // wall로 값을 다시 초기화
                        map[y+1][8] = STAR;   // 건너편 으로 스타를 값 이동
                    }
                    else if (map[y][9] == STAR)
                    {
                        map[y][9] = WALL;   // wall 로 값을 다시 초기화
                        map[y + 1][1] = STAR; // 건너편으로 스타를 값 이동 
                    }
                    */

                }
            }
            else if (map[y][x] == ITEM &&
                map[y + 1][x] != BEAM)
            {
                map[y][x] = 0;
                map[y + 1][x] = ITEM;
            }
        }
    }
}

void BEAM_Update(int map[HEIGHT][WIDTH])
{
    for (int y = 0; y < HEIGHT - 1; ++y) {
        for (int x = 1; x < WIDTH - 1; ++x) {
            if (map[y][x] == BEAM &&
                map[y - 1][x] != STAR) {
                map[y][x] = 0;
                map[y - 1][x] = BEAM;
            }
        }
    }
}

int cheak_hit(int map[HEIGHT][WIDTH])
{
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            if (map[y][x] == STAR)
            {
                if (player.y == y && player.x == x)
                {
                    return 1;
                }
            }
            if (map[y][x] == ITEM)
            {
                if (player.y == y && player.x == x)
                {
                    if (gNumOfBeams < 3) {
                        ++gNumOfBeams;
                    }
                }
            }
            if (map[y][x] == STAR &&
                map[y + 1][x] == BEAM) {
                map[y][x] = 0;
                map[y + 1][x] = 0;
            }
        }
    }

    return 0;
}

void pause(int map[HEIGHT][WIDTH])    // 정지시 일시정지 메세지 출력
{

    int i;

    int x = 5;
    int y = 5;

    for (i = 1; i < WIDTH - 2; i++) {
        gotoxy(x - 1, y + 0); printf("───────");
        gotoxy(x - 1, y + 1); printf("|일 시 정 지 |");
        gotoxy(x - 1, y + 2); printf("───────");
    }
}

void PlayerMove(int map[HEIGHT][WIDTH])
{
    char ch;
    //map[player[Y]][player[X]] = NULL;
    if (_kbhit())
    {
        ch = _getch();
        if (ch == 'a' || ch == 'A')
            if (map[player.y][player.x - 1] != WALL)
                player.x--;
        if (ch == 'd' || ch == 'D')
            if (map[player.y][player.x + 1] != WALL)
                player.x++;
        if (ch == 'p' || ch == 'P')
        {
            pause(map);
            system("pause");
        }



        if (ch == ' ') {
            if (gNumOfBeams > 0) {
                if (map[player.y - 1][player.x] == STAR)
                    map[player.y - 1][player.x] = 0;
                else
                    map[player.y - 1][player.x] = BEAM;
                --gNumOfBeams;
            }
        }
    }
    //map[player[Y]][player[X]] = PLAYER;

    if (cheak_hit(map) == 1)
    {
        run = 0;
    }
    else
    {
        score++;
    }
}


void main()
{
    int map[HEIGHT][WIDTH] = { 0 };
    int x;

    while (run)
    {
        switch (GameMenu())
        {
        case GAMESTART:
            map_reset(map);
            Init(map);
            srand((unsigned)time(NULL));
            while (run)
            {
                if (level == 4)
                    Star1_Update(map);
                else 
                    Star_Update(map);
                BEAM_Update(map);
                MapDraw(map);
                PlayerMove(map);
                Sleep(33);
            }
            if (run == 0) {
                GameOverDraw(map);
            }
            break;
        case LEVEL:
            printf("----selet level----\n");
            printf("1.easy 2.normal 3.hard 4.swift\n");
            printf(">");
            scanf("%d", &x);

            switch (x)
            {
            case 1:
                level = 3;
                break;
            case 2:
                level = 5;
                break;
            case 3:
                level = 7;
                break;
            case 4:
                level = 4;
                break;
            }

            break;
        case EXIT:
            return;
        }
    }
}