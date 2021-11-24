#include "LocStack.h"

void initStack(locStack* p)
{
	if (p == NULL)
		return;
	p->capacity = stackCapacity;
	p->size = 0;
	p->loc = (xYLoc*)malloc(sizeof(xYLoc) * stackCapacity);
}

void pushStack(locStack* p, xYLoc* data)		//压栈
{
	if (p == NULL)	//栈是否存在 
		return;
	stackMemoryChange(p);
	p->loc[p->size] = *data;
	p->size++;
}

void popStack(locStack* p)
{
	if (p == NULL)	//栈是否存在
		return;
	stackMemoryChange(p);

	if (p->size == 0)
	{		//是否空栈
		printf("栈已空\n");
		return;
	}

	p->size--;
	//需要补充出栈操作内容
}

int isStackEmpty(locStack* s)
{
	assert(s != NULL);
	if (s->size == 0)
		return 1;//栈空
	return 0;
}

void stackMemoryChange(locStack* p)
{
	if (p->size == p->capacity) 
	{	//栈满则扩大一倍 
		p->capacity = 2 * p->capacity;
		p->loc = (xYLoc*)realloc(p->loc, sizeof(xYLoc) * p->capacity);		//扩大一倍
		return;
	}

	else if (p->size <= p->capacity / 4)
	{		//栈占用不足四分之一，缩小一倍 
		if (p->capacity / 4 < stackCapacity)
		{
			//printf("栈容量预期缩减会小于初始大小，缩减终止\n");
			return;
		}
		else {
			//printf("栈容量缩减一倍\n");
			p->capacity = p->capacity / 2;
			p->loc = (xYLoc*)realloc(p->loc, sizeof(xYLoc) * p->capacity);		//缩小一倍
			return;
		}
	}
}

xYLoc stackTopElement(locStack* p)			//栈顶元素查询 
{
	//printf("顶栈数据:%d\n", p->loc[p->size - 1]);
	return p->loc[p->size - 1];

}
