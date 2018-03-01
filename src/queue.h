#include<iostream>

using namespace std;

typedef int elementType;

typedef struct LNode
{
	elementType data;
	struct LNode *next;
}node;

typedef struct
{
	node * front;
	node * rear;
}Queue;

void initQueue(Queue &Q)		//初始化队列 
{
	Q.front = new node;
	Q.rear = Q.front;
	Q.front->next = NULL;
}

bool queueEmpty(Queue &Q)		//判断队空 
{
	return (Q.front == Q.rear);
}

void enQueue(Queue &Q,elementType x)		//入队 
{
	node *P = new node;
	P->data = x;
	P->next = NULL;
	Q.rear->next = P;
	Q.rear = P;
}

void outQueue(Queue &Q,elementType &x)		//出队 
{
	node * u;
	if(!queueEmpty(Q))
	{
		x = Q.front->next->data;
		u = Q.front->next;
		Q.front->next = u->next;
		delete u;
		if(Q.front->next == NULL)
		{
			Q.rear = Q.front;
		}
	}
}

