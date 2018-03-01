#include<iostream> 
#include"queue.h"
#include <string.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
# define OVERFLOW -2

#define MAX_VERTEX_NUM 30  // ��󶥵���Ŀ 

using namespace std;

typedef int Status;

enum VisitIf
{
	unvisited = 0,visited
};

typedef int VertexType; 
typedef struct EBox
{
	VisitIf mark;
	int ivex,jvex;
	struct EBox *ilink;
	struct EBox *jlink;
	
}EBox;

typedef struct
{
	VertexType data;
	EBox *firstedge;
}VerBox;

typedef struct
{
	VerBox Nodelist[MAX_VERTEX_NUM];
	int vexnum;
	int edgenum;
}AMLGraph;

int VisitNode[MAX_VERTEX_NUM] = {0};
int Nodenum[100] = {0};
int LocateVex(AMLGraph G,VertexType u)		//����ֵ����ȡ������ͼ�е���� 
{
	int i;
	
	for(i = 0; i < G.vexnum; i++)
	{
		if(G.Nodelist[i].data == u)
		{
			return i;
		}
	}
	return -1;
}

VertexType GetVex(AMLGraph G,int v)		//������ţ���ȡͼ��ĳ����������� 
{
	if(v >= G.vexnum || v < 0)
	{
		exit(ERROR);
	}
	return G.Nodelist[v].data;
}

Status PutVex(AMLGraph *G,VertexType v,VertexType value)			//����ֵ����ţ��Դ˽�㸳��ֵ
{
	int i;
	i = LocateVex(*G,v);
	if(i < 0)
	{
		return ERROR;
	}
	(*G).Nodelist[i].data = value;
	
	return OK;
}

Status CreateGraph(AMLGraph *G)			//��������ͼ 
{
	int i,j,k,l;
	VertexType va,vb;
	EBox *p;
	
	cout<<"����������ͼ�Ķ�����"<<endl;
	cin>>(*G).vexnum;
	cout<<"����������ͼ�ı���"<<endl;
	cin>>(*G).edgenum;
	
	
	for(i = 0;i < (*G).vexnum;i++)		//������������ 
	{
		cout<<"�������"<<i+1<<"�������ֵ"<<endl;
		cin>>(*G).Nodelist[i].data;
		(*G).Nodelist[i].firstedge = NULL;
	}
	
	for(k = 0;k < (*G).edgenum;++k)		//����������� 
	{
		cout<<"��˳�������"<<k+1<<"���������˵�(�Կո���Ϊ�����)"<<endl;
		cin>>va>>vb;
		i = LocateVex(*G,va);
		j = LocateVex(*G,vb);
		
		if(i < 0 || j < 0)
		{
			return ERROR;
		}
		
		p = new EBox;
		
		p->mark = unvisited;
		
		p->ivex = i;
		p->jvex = j;
		
		
		p->ilink = (*G).Nodelist[i].firstedge;
		p->jlink = (*G).Nodelist[j].firstedge;
		(*G).Nodelist[i].firstedge = p;
		(*G).Nodelist[j].firstedge = p;
		
		
	}
	cout<<"OK"<<endl; 
	return OK;
}

void MarkUnvizited(AMLGraph *G)		//�����еı߷��ʱ��Ϊδ���� 
{
	int i;
	EBox *p;
	for(i = 0;i < (*G).vexnum;i++)
	{
		p = (*G).Nodelist[i].firstedge;
		while(p)
		{
			p->mark = unvisited;
			if(p->ivex == i)
			{
				p = p->ilink;
			}
			else
			{
				p = p->jlink;
			}
		}
	}
}

void Display(AMLGraph G)		//���ͼ���ڽӶ��ر� 
{

	int i;
	int k;
	EBox *p;
	MarkUnvizited(&G);
	cout<<"�������Ϊ"<<G.vexnum<<endl;
	for(i = 0;i < G.vexnum;i++)
	{
		cout<<G.Nodelist[i].data<<"  ";
	}
	cout<<endl;
	cout<<"�ߵĸ���Ϊ"<<G.edgenum<<endl;
	
	for(k = 0;k < G.vexnum;k++)
	{
		p = G.Nodelist[k].firstedge;

		while(p)
		{	
			if(p->ivex == k)
			{
				if(p->mark == unvisited)		//δ���� 
				{
					cout<<G.Nodelist[p->ivex].data<<"-"<<G.Nodelist[p->jvex].data<<endl;
					p->mark = visited;
				}
				p = p->ilink;
			}
			else
			{
				if(p->mark == unvisited)
				{	
					cout<<G.Nodelist[p->ivex].data<<"-"<<G.Nodelist[p->jvex].data<<endl;
					p->mark = visited;
				}
				p = p->jlink;
			}
			
		}
		cout<<endl;
	}
		
} 

int FirstAdjVex(AMLGraph G,VertexType v)		//����ֵ������ĵ�һ���ߵ���һ��������š� 
{
	int i;
	EBox *p;
	i = LocateVex(G,v);
	if(i < 0)
	{
		return -1;
	}
	
	p = G.Nodelist[i].firstedge;
	
	if(p)
	{
		if(p->ivex == i)
		{
			return p->jvex;
		}
		else
		{
			return p->ivex; 
		}
	}
	else
	{
		return -1;
	}
}

int NextAdjVex(AMLGraph G,VertexType v,VertexType w)		//��������ֵ������һ�����һ������һ��������š� 
{
	int i;
	int j;
	EBox *p;
	i = LocateVex(G,v);
	j = LocateVex(G,w);
	if(i < 0 || j < 0)
	{
		return -1;
	} 
	p = G.Nodelist[i].firstedge;
	while(p)
	{
		if(p->ivex == i && p->jvex != j)
		{
			p = p->ilink;
		}
		else if(p->jvex == i && p->ivex != j)
		{
			p = p->jlink;
		}
		else
		{
			break;
		}
	}
	
	if(p && p->ivex == i && p->jvex == j)
	{
		p = p->ilink;
		if(p && p->ivex == i)
		{
			return p->jvex;
		}
		else if(p && p->jvex == i)
		{
			return p->ivex;
		}
	}
	
	if(p && p->ivex == j && p->jvex == i)
	{
		p = p->jlink;
		if(p && p->ivex == i)
		{
			return p->jvex;
		}
		else if(p && p->jvex == i)
		{
			return p->ivex;
		}
	}
	
	return -1;
}

Status InsertVex(AMLGraph *G,VertexType v)		//��������ֵ��ͼ������¶��㡣 
{
	int i;
	if((*G).vexnum == MAX_VERTEX_NUM)
	{
		return ERROR;
	}
	if(LocateVex(*G,v) >= 0)
	{
		return ERROR;
	}
	
	i = (*G).vexnum;
	
	(*G).Nodelist[i].data = v;
	(*G).Nodelist[i].firstedge = NULL;
	(*G).vexnum++;
	
	return OK;
}

Status InsertArc(AMLGraph *G,VertexType v,VertexType w)		//�������������ֵ������������������±ߡ� 
{
	int i;
	int j;
	int l;
	int info;
	EBox *p;
	
	i = LocateVex(*G,v);
	j = LocateVex(*G,w);
	if(i < 0 || j < 0)
	{
		return ERROR;
	}
	p = new EBox;
	p->mark = unvisited;
	p->ivex = i;
	p->jvex = j;
	p->ilink = (*G).Nodelist[i].firstedge;
	(*G).Nodelist[i].firstedge = p;
	p->jlink = (*G).Nodelist[j].firstedge;
	(*G).Nodelist[j].firstedge = p;
	
	(*G).edgenum++;
	return OK;
}

Status DeleteArc(AMLGraph *G,VertexType v,VertexType w)			//����������ֵ��ɾ������֮��ߡ� 
{
	int i;
	int j;
	EBox *p;
	EBox *q;
	
	i = LocateVex(*G,v);
	j = LocateVex(*G,w);
	
	if(i < 0 ||  j < 0 || i == j)
	{
		return ERROR;
	}
	
	p = (*G).Nodelist[i].firstedge;
	if(p && p->jvex == j)
	{
		(*G).Nodelist[i].firstedge = p->jlink;
	}
	else if(p && p->ivex == j)
	{
		(*G).Nodelist[i].firstedge = p->jlink;
	}
	else
	{
		while(p)
		{
			if(p->ivex == i && p->jvex != j)
			{
				q = p;
				p = p->ilink;
			}
			else if(p->jvex == i && p->ivex != j)
			{
				q = p;
				p = p->jlink;
			}
			else
			{
				break;
			}
		}
		if(!p)
		{
			return ERROR;
		}
		if(p->ivex == i && p->jvex == j)
		{
			if(q->ivex == i)
			{
				q->ilink = p->ilink;
			}
			else
			{
				q->jlink = p->ilink;
			}
		}
		else if(p->ivex == j && p->jvex == i)
		{
			if(q->ivex = i)
			{
				q->ilink = p->jlink;
			}
			else
			{
				q->jlink = p->jlink;
			}
		} 
	}
	
	p = (*G).Nodelist[j].firstedge;
	if(p->jvex == i)
	{
		(*G).Nodelist[j].firstedge = p->ilink;
	}
	else if(p->ivex == i)
	{
		(*G).Nodelist[j].firstedge = p->jlink;
	}
	else
	{
		while(p)
		{
			if(p->ivex == j && p->jvex != i)
			{
				q = p;
				p = p->ilink;
			}
			else if(p->jvex == j && p->ivex != i)
			{
				q = p;
				p = p->jlink;
			}
			else
			{
				break;
			}
		}
		if(p->ivex == i && p->jvex == j)
		{
			if(q->ivex == j)
			{
				q->ilink = p->jlink;
			}
			else
			{
				q->jlink = p->jlink;
			}
		}
		else if(p->ivex == j && p->jvex == i)
		{
			if(q->ivex == j)
			{
				q->ilink = p->ilink;
			}
			else
			{
				q->jlink = p->ilink;
			}
		}
	}
	(*G).edgenum--;
	return OK;
}

Status DeleteVex(AMLGraph *G,VertexType v)		//��������ֵ��ɾ�����㼰������صı� 
{
	int i;
	int j;
	VertexType w;
	EBox *p;
	
	i = LocateVex(*G,v);		//iΪ��ɾ��������� 
	if(i < 0)
	{
		return ERROR;
	}
	for(j = 0;j < (*G).vexnum;j++)		//ɾ���붥��v�����ı� 
	{
		if(j == i)
		{
			continue;
		}
		w = GetVex(*G,j);
		DeleteArc(G,v,w);
	}
	
	for(j = i+1;j < (*G).vexnum;j++)
	{
		(*G).Nodelist[j-1] = (*G).Nodelist[j];
	}
	(*G).vexnum--;
	
	for(j = i; j < (*G).vexnum;j++)
	{
		p = (*G).Nodelist[j].firstedge;
		if(p)
		{
			if(p->ivex == j+1)
			{
				p->ivex--;
				p = p->ilink;
			}
			else
			{
				p->jvex--;
				p = p->jlink;
			}
		} 
	}
	return OK;
}

void DestroyGraph(AMLGraph *G)		//ɾ��ͼ 
{
	int i;
	for(i = (*G).vexnum-1; i >= 0; i--)
	{
		DeleteVex(G,(*G).Nodelist[i].data);
	}
	cout<<"ͼ�ɹ�����"<<endl;
}

void DFS(AMLGraph G,int v)		//������ȱ��� 
{
	int j;
	EBox *p;
	
	cout<<G.Nodelist[v].data<<endl; 
	VisitNode[v] = TRUE;
	
	p = G.Nodelist[v].firstedge;
	
	while(p)
	{
		j = p->ivex == v ? p->jvex : p->ivex;
		if(!VisitNode[j])
		{
			DFS(G,j);
		}
		p = p->ivex == v ? p->ilink : p->jlink;
	}
}

void DFSTraverse(AMLGraph G)		//�ӵ�һ��������������ȱ��� 
{
	int v;
	for(v = 0; v < G.vexnum;v++)
	{
		VisitNode[v] = FALSE;
	}
	
	for(v = 0; v < G.vexnum; v++)
	{
		if(!VisitNode[v])
		{
			DFS(G,v);
		}
	}
}

void BFS(AMLGraph G,int v)
{
	int w;
	int u;
	Queue Q;
	EBox *p;
	initQueue(Q);
	
	u = G.Nodelist[v].data;
	VisitNode[v] = TRUE;
	p = G.Nodelist[v].firstedge;

	enQueue(Q,u);
	
	while(!queueEmpty(Q))
	{
		outQueue(Q,u);
		cout<<u<<endl;
		w = FirstAdjVex(G,u);
		while(w != -1)
		{
			if(VisitNode[w] == FALSE)
			{
				VisitNode[w] = TRUE;
				w = G.Nodelist[w].data;
				enQueue(Q,w);
			}
			w = NextAdjVex(G,u,w);
		}
	}
	
}

void BFSTraverse(AMLGraph G)
{
	int v;
	for(v = 0; v < G.vexnum;v++)
	{
		VisitNode[v] = FALSE;
	}
	for(v = 0;v < G.vexnum;v++)
	{
		if(VisitNode[v] == FALSE)
		{
			BFS(G,v);
		}
	}
}

int CreateEdge(AMLGraph &G,int va,int vb)
{
	int i,j;
	EBox *p;
	i = LocateVex(G,va);
	j = LocateVex(G,vb);
		
	if(i < 0 || j < 0)
	{
		return ERROR;
	}

		
	p = new EBox;
		
	p->mark = unvisited;
		
	p->ivex = i;
	p->jvex = j;
		
		
	p->ilink = (G).Nodelist[i].firstedge;
	p->jlink = (G).Nodelist[j].firstedge;
	(G).Nodelist[i].firstedge = p;
	(G).Nodelist[j].firstedge = p;
}

int CreateGraphFromFile(char fileName[])
{
	int i = 0;
	int va,vb,vc,vd;
	FILE *pFile;		//�����ļ�ָ�� 
	char str[1000];		//��Ŷ���һ���ı����ַ��� 
	char strTemp[10];	//�ж��Ƿ���ע����
	
	pFile = fopen(fileName,"r");
	if(! pFile){
		cout<<"����,�ļ�"<<fileName<<"�򿪴���"<<endl;
		return false;
	}
	
	if((fgets(str,1024,pFile))!=NULL)  	//��ȡ��־ 
    {  
        if(str == "Graph")
		{
			cout<<"����,���ļ���ʽ����!"<<endl;
			fclose(pFile);
			return false;
    	}
	}
										
	if((fgets(str,1024,pFile))!=NULL)   //��ȡ���
    {  
                  char *token = strtok(str," ");
                  int va = atoi(token);
                  Nodenum[0] = va;
                  token = strtok(NULL," ");
                  int vb = atoi(token);

                Nodenum[1] = vb;

    } 
    
    if((fgets(str,1024,pFile)) != NULL)		//��ȡ����
	{
		char *token = strtok(str," ");
		int va = atoi(token);
		Nodenum[2] = va;

			for(int i = 1;i < va-1;i++)
			{
                  token = strtok(NULL," ");
                  if(token != 0)
                  {
                  	int vb = atoi(token);

    				Nodenum[i+2] = vb;

				  }
                  
			}
	}
	
    
    int num = Nodenum[0]+2;					//��ȡ�ߵ�������
	while((fgets(str,1024,pFile)) != NULL)
	{
		
		char *token = strtok(str," ");
        int va = atoi(token);
        Nodenum[num] = va;
        num++;

        token = strtok(NULL," ");
       	int vb = atoi(token);
       	Nodenum[num] = vb;

        num++;

	}
	cout<<"�ļ��򿪳ɹ�"<<endl;
	fclose(pFile);
}
Status Translate(AMLGraph &G)
{
	int num = Nodenum[0]+2;
	G.vexnum = Nodenum[0];
	G.edgenum = Nodenum[1];
	
	for(int i = 0;i < G.vexnum;i++)		//������������ 
	{
		G.Nodelist[i].data = Nodenum[i+2]; 
		G.Nodelist[i].firstedge = NULL;
	}
	for(int j = 0;j < G.edgenum;j++)
	{
		int va = Nodenum[num+j*2];
		int vb = Nodenum[num+j*2+1];
		CreateEdge(G,va,vb);
	}
}

