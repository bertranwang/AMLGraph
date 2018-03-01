#include<iostream> 
#include"queue.h"
#include <string.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
# define OVERFLOW -2

#define MAX_VERTEX_NUM 30  // 最大顶点数目 

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
int LocateVex(AMLGraph G,VertexType u)		//给定值，获取顶点在图中的序号 
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

VertexType GetVex(AMLGraph G,int v)		//给定序号，获取图中某个顶点的内容 
{
	if(v >= G.vexnum || v < 0)
	{
		exit(ERROR);
	}
	return G.Nodelist[v].data;
}

Status PutVex(AMLGraph *G,VertexType v,VertexType value)			//给定值求序号，对此结点赋新值
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

Status CreateGraph(AMLGraph *G)			//创建无向图 
{
	int i,j,k,l;
	VertexType va,vb;
	EBox *p;
	
	cout<<"请输入无向图的顶点数"<<endl;
	cin>>(*G).vexnum;
	cout<<"请输入无向图的边数"<<endl;
	cin>>(*G).edgenum;
	
	
	for(i = 0;i < (*G).vexnum;i++)		//构建顶点向量 
	{
		cout<<"请输入第"<<i+1<<"个顶点的值"<<endl;
		cin>>(*G).Nodelist[i].data;
		(*G).Nodelist[i].firstedge = NULL;
	}
	
	for(k = 0;k < (*G).edgenum;++k)		//构造表结点链表 
	{
		cout<<"请顺序输入第"<<k+1<<"条边两个端点(以空格作为间隔：)"<<endl;
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

void MarkUnvizited(AMLGraph *G)		//置所有的边访问标记为未访问 
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

void Display(AMLGraph G)		//输出图的邻接多重表 
{

	int i;
	int k;
	EBox *p;
	MarkUnvizited(&G);
	cout<<"顶点个数为"<<G.vexnum<<endl;
	for(i = 0;i < G.vexnum;i++)
	{
		cout<<G.Nodelist[i].data<<"  ";
	}
	cout<<endl;
	cout<<"边的个数为"<<G.edgenum<<endl;
	
	for(k = 0;k < G.vexnum;k++)
	{
		p = G.Nodelist[k].firstedge;

		while(p)
		{	
			if(p->ivex == k)
			{
				if(p->mark == unvisited)		//未访问 
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

int FirstAdjVex(AMLGraph G,VertexType v)		//给定值，求结点的第一条边的另一个结点的序号。 
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

int NextAdjVex(AMLGraph G,VertexType v,VertexType w)		//给定两个值，求结点一相对另一结点的下一个结点的序号。 
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

Status InsertVex(AMLGraph *G,VertexType v)		//给定顶点值，图中添加新顶点。 
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

Status InsertArc(AMLGraph *G,VertexType v,VertexType w)		//给定两个顶点的值，在两个顶点间增加新边。 
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

Status DeleteArc(AMLGraph *G,VertexType v,VertexType w)			//给定两顶点值，删除两点之间边。 
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

Status DeleteVex(AMLGraph *G,VertexType v)		//给定顶点值，删除顶点及与其相关的边 
{
	int i;
	int j;
	VertexType w;
	EBox *p;
	
	i = LocateVex(*G,v);		//i为待删除顶点序号 
	if(i < 0)
	{
		return ERROR;
	}
	for(j = 0;j < (*G).vexnum;j++)		//删除与顶点v相连的边 
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

void DestroyGraph(AMLGraph *G)		//删除图 
{
	int i;
	for(i = (*G).vexnum-1; i >= 0; i--)
	{
		DeleteVex(G,(*G).Nodelist[i].data);
	}
	cout<<"图成功销毁"<<endl;
}

void DFS(AMLGraph G,int v)		//深度优先遍历 
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

void DFSTraverse(AMLGraph G)		//从第一个顶点起，深度优先遍历 
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
	FILE *pFile;		//定义文件指针 
	char str[1000];		//存放读出一行文本的字符串 
	char strTemp[10];	//判断是否是注释行
	
	pFile = fopen(fileName,"r");
	if(! pFile){
		cout<<"错误,文件"<<fileName<<"打开错误"<<endl;
		return false;
	}
	
	if((fgets(str,1024,pFile))!=NULL)  	//读取标志 
    {  
        if(str == "Graph")
		{
			cout<<"错误,打开文件格式错误!"<<endl;
			fclose(pFile);
			return false;
    	}
	}
										
	if((fgets(str,1024,pFile))!=NULL)   //读取点边
    {  
                  char *token = strtok(str," ");
                  int va = atoi(token);
                  Nodenum[0] = va;
                  token = strtok(NULL," ");
                  int vb = atoi(token);

                Nodenum[1] = vb;

    } 
    
    if((fgets(str,1024,pFile)) != NULL)		//读取顶点
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
	
    
    int num = Nodenum[0]+2;					//读取边的两顶点
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
	cout<<"文件打开成功"<<endl;
	fclose(pFile);
}
Status Translate(AMLGraph &G)
{
	int num = Nodenum[0]+2;
	G.vexnum = Nodenum[0];
	G.edgenum = Nodenum[1];
	
	for(int i = 0;i < G.vexnum;i++)		//构建顶点向量 
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

