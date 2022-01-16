#include<iostream>
#include<stdlib.h>
#include<time.h>
#include <graphics.h>
#include<conio.h>

#ifndef LOVELYBOY
#define LOVELYBOY
#include "function.h"
#endif

#include <chrono>
#include <future>

#define single_square 30
extern SYSTEMTIME start;


using namespace std;

enum visit { gray, yellow, red };

const int speed = 2;

IMAGE timing[10];

position stack[MAZE_MAX_LEN * MAZE_MAX_LEN] = {};
int pointer = 0;
int vis[5];

void Timing(position ending);

/*使迷宫成为独立不互通的隔间*/
void initial_maze(int maze[MAZE_MAX_LEN][MAZE_MAX_LEN], position& dig, position ending)
{
	int i, j;
	srand((unsigned)time(NULL));
	for (i = 0; i < MAZE_MAX_LEN; i++)
		for (j = 0; j < MAZE_MAX_LEN; j++)
		{
			if (i % 2 != 0 && j % 2 != 0)
				maze[i][j] = yellow;
		}
	i = rand() % (ending.x / 2 - 1);//5/2-1=0,1 2*i+1
	j = rand() % (ending.y / 2 - 1);//5/2=0,1
	dig.x = 2 * i + 1;
	dig.y = ending.y - 2;
	maze[dig.y][dig.x] = red;
	stack[pointer] = dig;
}

/*ending.x,ending.y是迷宫本身大小，且为奇数*/
void generate_maze(int maze[MAZE_MAX_LEN][MAZE_MAX_LEN], position& dig, position ending)
{
	int direction;
	enum dict { left, up, right, down };
	int go_through = 0;
	int verdict = 0;
	if (dig.x >= ending.x || dig.y >= ending.y)
		cout << "waring" << endl;
	while (1)
	{
		direction = rand() % 4;
		/*检查是否通路*/
		switch (direction)
		{
			/*左*/
			case(left):
				if (dig.x - 2 > 0 && maze[dig.y][dig.x - 2] == yellow)
				{
					maze[dig.y][dig.x - 2] = red;
					maze[dig.y][dig.x - 1] = red;
					dig.x = dig.x - 2;
					go_through++;
				}
				break;
				/*上*/
			case(up):
				if (dig.y - 2 > 0 && maze[dig.y - 2][dig.x] == yellow)
				{
					maze[dig.y - 2][dig.x] = red;
					maze[dig.y - 1][dig.x] = red;
					dig.y = dig.y - 2;
					go_through++;
				}
				break;
				/*右*/
			case(right):
				if (dig.x + 2 < ending.x && maze[dig.y][dig.x + 2] == yellow)
				{
					maze[dig.y][dig.x + 2] = red;
					maze[dig.y][dig.x + 1] = red;
					dig.x = dig.x + 2;
					go_through++;
				}
				break;
				/*下*/
			case(down):
				if (dig.y + 2 < ending.y && maze[dig.y + 2][dig.x] == yellow)
				{
					maze[dig.y + 2][dig.x] = red;
					maze[dig.y + 1][dig.x] = red;
					dig.y = dig.y + 2;
					go_through++;
				}
				break;
		}
		if (go_through > 0)
			break;
		verdict = (dig.x - 2 > 0 && maze[dig.y][dig.x - 2] == yellow)
			|| (dig.y - 2 > 0 && maze[dig.y - 2][dig.x] == yellow)
			|| (dig.x + 2 < ending.x && maze[dig.y][dig.x + 2] == yellow)
			|| (dig.y + 2 < ending.y && maze[dig.y + 2][dig.x] == yellow);
		if (verdict == 0)
			break;
	}

	int ergodic = 0;
	int i, j;
	if (go_through > 0)
	{
		pointer++;
		stack[pointer] = dig;
		generate_maze(maze, dig, ending);
	}
	else if (verdict == 0)
	{
		for (i = 0; i < ending.x; i++)
			for (j = 0; j < ending.y; j++)
			{
				if (maze[j][i] == yellow)
					ergodic++;
			}
		if (ergodic == 0)
		{
			return;
		}
		else
		{
			pointer--;
			dig = stack[pointer];
			generate_maze(maze, dig, ending);
		}
	}
}

/*绘制迷宫*/
void print_maze(int maze[MAZE_MAX_LEN][MAZE_MAX_LEN], position ending)      //画迷宫的函数，map为指向储存迷宫数组的指针，n为迷宫大小
{
	maze[1][0] = red;
	maze[ending.y - 2][ending.x - 1] = red;

	// 初始化图形模式
	initgraph(ending.x * single_square, ending.y * single_square);
	IMAGE JIQINGREN;
	IMAGE STONE;
	loadimage(&JIQINGREN, _T("人物.jpg"));
	loadimage(&STONE, _T("stone_0.jpg"));

	IMAGE JIQINGREN_negative;
	loadimage(&JIQINGREN_negative, _T("人物1.jpg"));

	BeginBatchDraw();
	//画图，棕色为墙，绿色为通路
	for (int x = 0; x < ending.x; x++) {
		for (int y = 0; y < ending.y; y++) {
			if (maze[y][x] == red) {
				//putimage(x * single_square, y * single_square,single_square,single_square, &JIQINGREN,0,0);
				setfillcolor(GREEN);
				solidrectangle(x * single_square, y * single_square, x * single_square + single_square, y * single_square + single_square);
			}
			else
			{
				//Sleep(10);
				//setfillcolor(YELLOW);
				//solidrectangle(x * single_square, y * single_square, x * single_square + single_square, y * single_square + single_square);
				putimage(x * single_square, y * single_square, single_square, single_square, &STONE, 0, 0);
			}
		}
	}
	FlushBatchDraw();
	//int c=getchar();              
}

void cartoon(int where_to_x, int where_to_y, int where_from_x, int where_from_y)
{
	IMAGE JIQINGREN;
	IMAGE JIQINGREN_negative;
	const int up = 72, down = 80, left = 75, right = 77;
	loadimage(&JIQINGREN, _T("人物.jpg"));
	loadimage(&JIQINGREN_negative, _T("人物1.jpg"));
	solidrectangle(where_to_x, where_to_y, where_to_x + single_square, where_to_y + single_square);
	putimage(where_to_x, where_to_y, single_square, single_square, &JIQINGREN_negative, where_from_x + single_square, where_from_y, NOTSRCERASE);
	putimage(where_to_x, where_to_y, single_square, single_square, &JIQINGREN, where_from_x + single_square, where_from_y, SRCINVERT);
	FlushBatchDraw();
	Sleep(speed);
	putimage(where_to_x, where_to_y, single_square, single_square, &JIQINGREN_negative, where_from_x + single_square * 2, where_from_y, NOTSRCERASE);
	putimage(where_to_x, where_to_y, single_square, single_square, &JIQINGREN, where_from_x + single_square * 2, where_from_y, SRCINVERT);
	FlushBatchDraw();
	Sleep(speed);
	putimage(where_to_x, where_to_y, single_square, single_square, &JIQINGREN_negative, where_from_x, where_from_y, NOTSRCERASE);
	putimage(where_to_x, where_to_y, single_square, single_square, &JIQINGREN, where_from_x, where_from_y, SRCINVERT);
	FlushBatchDraw();
	Sleep(speed);
}


/*绘制小人并控制移动*/
void get_move(position& NPC, int maze[MAZE_MAX_LEN][MAZE_MAX_LEN], position ending, position diamond[])
{
	IMAGE JIQINGREN;
	IMAGE JIQINGREN_negative;
	NPC.x = 0;
	NPC.y = 1;
	int k = 0;
	int number=0;
	const int up = 72, down = 80, left = 75, right = 77;
	loadimage(&JIQINGREN, _T("人物.jpg"));
	loadimage(&JIQINGREN_negative, _T("人物1.jpg"));
	setfillcolor(GREEN);
	putimage(NPC.x * single_square, NPC.y * single_square, single_square, single_square, &JIQINGREN_negative, 0, 0, NOTSRCERASE);
	putimage(NPC.x * single_square, NPC.y * single_square, single_square, single_square, &JIQINGREN, 0, 0, SRCINVERT);
	FlushBatchDraw();
	thread t(Timing, ending);
	t.detach();
	while (1)
	{
		
		
		if (k = _getch() == 224)
		{
			k = _getch();
			if (k == up && NPC.y - 1 >= 0 && maze[NPC.y - 1][NPC.x] == red)
			{
				for (int i = 0; i < single_square; i++)
				{
					cartoon(NPC.x * single_square, NPC.y * single_square - i, 0, single_square);
				}
				NPC.y--;
			}
			else if (k == down && NPC.y + 1 < ending.y && maze[NPC.y + 1][NPC.x] == red)
			{
				for (int i = 0; i < single_square; i++)
				{
					cartoon(NPC.x * single_square, NPC.y * single_square + i, 0, 0);
				}
				NPC.y++;
			}
			else if (k == left && NPC.x - 1 >= 0 && maze[NPC.y][NPC.x - 1] == red)
			{
				for (int i = 0; i < single_square; i++)
				{
					cartoon(NPC.x * single_square - i, NPC.y * single_square, 0, 2 * single_square);
				}
				NPC.x--;
			}
			else if (k == right && NPC.x + 1 < ending.x && maze[NPC.y][NPC.x + 1] == red)
			{
				for (int i = 0; i < single_square; i++)
				{
					cartoon(NPC.x * single_square + i, NPC.y * single_square, 0, 5 * single_square);
				}
				NPC.x++;
			}
		}
		if (NPC.x == ending.x - 1 && NPC.y == ending.y - 2 && number == 5)
		{
			return;
		}
		for (int i = 0; i < 5; ++i)
			if (NPC.x == diamond[i].x && NPC.y == diamond[i].y && !vis[i])
			{
				number++;
				vis[i] = 1;
			}
	}
	
}

void random_place(int maze[MAZE_MAX_LEN][MAZE_MAX_LEN], position ending, position diamond[])
{
	IMAGE treasure;
	loadimage(&treasure, _T("宝石.jpg"));

	for (int i = 0; i < 5; i++)
	{
		diamond[i].x = rand() % ending.x;
		diamond[i].y = rand() % ending.y;
		if (maze[diamond[i].y][diamond[i].x] != red && !(diamond[i].x == 0 && diamond[i].y == 1))//不在开始处，也不在石头里
		{
			i--;

		}
		else
		{
			putimage(diamond[i].x * single_square, diamond[i].y * single_square, &treasure);
		}
	}
	FlushBatchDraw();
}

void picture_time()
{
	loadimage(&timing[0], _T("t0.bmp"));
	loadimage(&timing[1], _T("t1.bmp"));
	loadimage(&timing[2], _T("t2.bmp"));
	loadimage(&timing[3], _T("t3.bmp"));
	loadimage(&timing[4], _T("t4.bmp"));
	loadimage(&timing[5], _T("t5.bmp"));
	loadimage(&timing[6], _T("t6.bmp"));
	loadimage(&timing[7], _T("t7.bmp"));
	loadimage(&timing[8], _T("t8.bmp"));
	loadimage(&timing[9], _T("t9.bmp"));
}
void Timing(position ending)
{
	picture_time();
	int t1, t2;
	int i, j;
	int a, b;
	int sum;
	while (1)
	{
		SYSTEMTIME ti;
		sum = 0;
		GetLocalTime(&ti);		// 获取当前时间
		sum += ti.wHour - start.wHour;
		sum *= 60;
		sum += ti.wMinute - start.wMinute;
		sum *= 60;
		sum += ti.wSecond - start.wSecond;
		i = 0;
		j = 0;
		t1 = sum;
		t2 = sum / 60;//对时间分钟和秒数的换算
		while (i != 2)
		{
			if (i == 0)
			{
				t1 = sum % 60;
			}
			a = t1 % 10;
			putimage((ending.x - 1 - i) * single_square, (ending.y - 1) * single_square, &timing[a]);//显示秒数
			t1 = t1 / 10;
			i++;
		}
		while (j != 2)
		{
			b = t2 % 10;
			putimage((ending.x - 3 - j) * single_square, (ending.y - 1) * single_square, &timing[b]);//显示分钟
			t2 = t2 / 10;
			j++;
		}
		FlushBatchDraw();
		this_thread::sleep_for(chrono::microseconds(1000));
		//if (NPC.x == ending.x - 1 && NPC.y == ending.y - 2 && number == 5)
			//return sum;
	}
}

void Maze_cord()
{
	int maze[MAZE_MAX_LEN][MAZE_MAX_LEN] = {};
	int isvisited[MAZE_MAX_LEN][MAZE_MAX_LEN] = {};
	position ending, dig, NPC, diamond[5];
	dig.x = 0;
	dig.y = 0;

	ending.x = 37;
	ending.y = 21;

	GetLocalTime(&start);
	initial_maze(maze, dig, ending);
	generate_maze(maze, dig, ending);
	print_maze(maze, ending);

	random_place(maze, ending, diamond);
	get_move(NPC, maze, ending, diamond);

	return;
}