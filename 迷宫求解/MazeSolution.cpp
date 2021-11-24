#include "LocStack.h"									//位置栈相关头文件
#include <Windows.h>									//实现部分简单动画

int Row;												//全局变量 迷宫行数
int Col;												//全局变量 迷宫列数

void anim();											//动画函数
void printMaze(int** m, xYLoc* enter, xYLoc* final);	//打印迷宫
int** mazeRead(); 										//从文件中读取迷宫
int isPass(int** m, xYLoc loc);							//判断该点是否可以通过
int isExit(xYLoc loc, xYLoc* enter, xYLoc* final);		//判断该点是否是终点
int isValidEnter(int** m, xYLoc* enter, xYLoc* final);	//判断入口是否非法
int passMaze(int** m, xYLoc* enter, xYLoc* final);		//走迷宫函数


int main()
{	
	int** maze;
	int choice;
	maze = mazeRead();
	xYLoc* enter = (xYLoc*)malloc(sizeof(xYLoc));
	xYLoc* final = (xYLoc*)malloc(sizeof(xYLoc));
	enter->x = -1; enter->y = -1;
	final->x = -1; final->y = -1;
	printMaze(maze, enter, final);

	printf("行数：%d 列数：%d\n", Row, Col);
	printf("请进行选择，默认情况下左上起点，右下终点\n");
	printf("开始请输入1\t");
	printf("修改请输入2\n");
	scanf_s("%d", &choice);
	if (choice == 1)
	{
		enter->x = 0; enter->y = 0;
		final->x = Row - 1; final->y = Col - 1;		//初始化默认值
		if (passMaze(maze, enter, final) == -1)
		{
			choice = 2;
			printf("警告：默认模式不适应，即将转入手动模式\n");
			system("CLS");
			enter->x = -1; enter->y = -1;
			final->x = -1; final->y = -1;
			printMaze(maze, enter, final);
		}
	}
	if (choice == 2)
	{
		
		while (1)
		{
			printf("请输入起点的X Y\n");
			scanf_s("%d %d", &enter->x, &enter->y);
			printf("请输入终点的X Y\n");
			scanf_s("%d %d", &final->x, &final->y);

			if (passMaze(maze, enter, final) == -1)
			{
				printf("起点/终点非法，请重新输入\n\n");
				Sleep(1000);
				continue;
			}
			else
				break;

		}
	}
	return 0;
}

int** mazeRead()
{
	FILE* fp;
	int amount_all = 0, amount_row = 1;
	char a;

	if ((fp = fopen("Maze.txt", "r")) == NULL)
	{
		printf("读取文件失败，程序终止\n");
		exit(0);
	}
	while(!feof(fp))
	{
		a = fgetc(fp);
		//printf("%c", a);
		if (a == '1' || a == '0')
			amount_all++;
		else if (a == '\n')
			amount_row++;
	}
	fclose(fp);
	printf("%d行 %d列\n", amount_row, amount_all / amount_row);


	int** temp_map = (int**)malloc(sizeof(int*) * amount_row);//为二维数组分配3行
	for (int i = 0; i < amount_row; i++)//为每列分配4个大小空间
		temp_map[i] = (int*)malloc(sizeof(int) * (amount_all / amount_row));

	int i = 0; int j = 0;
	if ((fp = fopen("Maze.txt", "r")) == NULL)
	{
		printf("读取文件失败，程序终止\n");
		exit(0);
	}
	while (!feof(fp))
	{
		a = fgetc(fp);
		//printf("%c", a);
		if (a == '1' || a == '0')
		{
			temp_map[i][j] = a - '0';
			j++;
		}
		else if (a == '\n')
		{
			i++;
			j = 0;
		}
	}
	fclose(fp);
	Row = amount_row; Col = amount_all / amount_row;
	return temp_map;
}

int isValidEnter(int** m, xYLoc* enter, xYLoc* final)
{
	assert(m != NULL);
	if ((enter->x >= 0 && enter->x < Row) && (enter->y >= 0 && enter->y < Col))
		if ((final->x >= 0 && final->x < Row) && (final->y >= 0 && final->y < Col))
			if ((m[enter->x][enter->y] != 0) && (m[final->x][final->y] != 0))
				return 0;
	return 1;
}

void printMaze(int** m, xYLoc* enter, xYLoc* final)
{
	assert(m != NULL);
	Sleep(200);
	anim();
	int i = 0, j = 0;
	for (i = 0; i < Row; i++)
	{
		for (j = 0; j < Col; j++)
		{
			if (i == enter->x && j == enter->y)
			{
				printf("☆");
			}
			else if (i == final->x && j == final->y)
			{
				printf("★");
			}
			else if (m[i][j] == 1)
			{
				printf("  ");
			}
			else if (m[i][j] == 0)
			{
				printf("■");
			}
			else if (m[i][j] == 3)
			{
				printf("▲");
			}
			else
			{
				printf("* ");
			}
		}
		printf("\n");
	}
	printf("\n");
}

void anim()
{
	HANDLE handle;
	COORD coord;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	coord.X = 0;
	coord.Y = 0;
	SetConsoleCursorPosition(handle, coord);
}

int isExit(xYLoc loc, xYLoc* enter, xYLoc* final)
{
	if ((loc.x == final->x) && (loc.y == final->y))
		return 1;
	return 0;
}

int isPass(int** m, xYLoc loc)
{
	assert(m != NULL);
	if (loc.x < 0 || loc.y < 0 || loc.x >= Row || loc.y >= Col)
	{
		return 0;
	}
	if (m[loc.x][loc.y] == 1)
	{
		return 1;
	}
	return 0;
}

int passMaze(int** m, xYLoc* enter, xYLoc* final)
{
	if (isValidEnter(m, enter, final))		//判断入口是否合法
	{
		printf("入口/出口不合法！！！\n");
		return -1;
	}
	else 
	{
		assert(m != NULL);
		locStack s;
		initStack(&s);
		pushStack(&s, enter);
		while (!isStackEmpty(&s))		//当栈不空时
		{
			xYLoc loc;
			xYLoc next;
			loc = stackTopElement(&s);
			m[loc.x][loc.y] = 2;		//将走过的路标记为2
			printMaze(m, enter, final);
			if (isExit(loc, enter, final))		//判断是不是出口
				return 0;
			else
			{
				//上
				next = loc;
				next.x -= 1;
				if (isPass(m, next))		//判断是否可以走通，只有为1时才可以走通
				{
					pushStack(&s, &next);
					continue;
				}
				//左
				next = loc;
				next.y -= 1;
				if (isPass(m, next))
				{
					pushStack(&s, &next);
					continue;
				}
				//右
				next = loc;
				next.y += 1;
				if (isPass(m, next))
				{
					pushStack(&s, &next);
					continue;
				}
				//下
				next = loc;
				next.x += 1;
				if (isPass(m, next))
				{
					pushStack(&s, &next);
					continue;
				}

				m[loc.x][loc.y] = 3;
				popStack(&s);
			}
		}
	}
	return 0;
}