#include "LocStack.h"

void initStack(locStack* p)
{
	if (p == NULL)
		return;
	p->capacity = stackCapacity;
	p->size = 0;
	p->loc = (xYLoc*)malloc(sizeof(xYLoc) * stackCapacity);
}

void pushStack(locStack* p, xYLoc* data)		//ѹջ
{
	if (p == NULL)	//ջ�Ƿ���� 
		return;
	stackMemoryChange(p);
	p->loc[p->size] = *data;
	p->size++;
}

void popStack(locStack* p)
{
	if (p == NULL)	//ջ�Ƿ����
		return;
	stackMemoryChange(p);

	if (p->size == 0)
	{		//�Ƿ��ջ
		printf("ջ�ѿ�\n");
		return;
	}

	p->size--;
	//��Ҫ�����ջ��������
}

int isStackEmpty(locStack* s)
{
	assert(s != NULL);
	if (s->size == 0)
		return 1;//ջ��
	return 0;
}

void stackMemoryChange(locStack* p)
{
	if (p->size == p->capacity) 
	{	//ջ��������һ�� 
		p->capacity = 2 * p->capacity;
		p->loc = (xYLoc*)realloc(p->loc, sizeof(xYLoc) * p->capacity);		//����һ��
		return;
	}

	else if (p->size <= p->capacity / 4)
	{		//ջռ�ò����ķ�֮һ����Сһ�� 
		if (p->capacity / 4 < stackCapacity)
		{
			//printf("ջ����Ԥ��������С�ڳ�ʼ��С��������ֹ\n");
			return;
		}
		else {
			//printf("ջ��������һ��\n");
			p->capacity = p->capacity / 2;
			p->loc = (xYLoc*)realloc(p->loc, sizeof(xYLoc) * p->capacity);		//��Сһ��
			return;
		}
	}
}

xYLoc stackTopElement(locStack* p)			//ջ��Ԫ�ز�ѯ 
{
	//printf("��ջ����:%d\n", p->loc[p->size - 1]);
	return p->loc[p->size - 1];

}
