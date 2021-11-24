#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#define stackCapacity 2

typedef struct xYLoc	//用于记录当前点的位置，这是自定义的数据类型
{
	int x;
	int y;
}xYLoc;

typedef struct locStack	//用于记录位置的栈
{
	xYLoc* loc;			//入栈点位置信息
	int capacity;		//栈的容量
	int size;			//栈的有效元素个数，代表栈顶
}locStack;

void initStack(locStack* p);
void pushStack(locStack* p, xYLoc* data);
void popStack(locStack* p);
void stackMemoryChange(locStack* p);
int isStackEmpty(locStack* s);
xYLoc stackTopElement(locStack* p);