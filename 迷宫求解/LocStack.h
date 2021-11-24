#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#define stackCapacity 2

typedef struct xYLoc	//���ڼ�¼��ǰ���λ�ã������Զ������������
{
	int x;
	int y;
}xYLoc;

typedef struct locStack	//���ڼ�¼λ�õ�ջ
{
	xYLoc* loc;			//��ջ��λ����Ϣ
	int capacity;		//ջ������
	int size;			//ջ����ЧԪ�ظ���������ջ��
}locStack;

void initStack(locStack* p);
void pushStack(locStack* p, xYLoc* data);
void popStack(locStack* p);
void stackMemoryChange(locStack* p);
int isStackEmpty(locStack* s);
xYLoc stackTopElement(locStack* p);