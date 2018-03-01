//main.cpp
#include<iostream>
#include"Graph.h"

using namespace std;
int main()
{
	cout<<"0.销毁图并退出"<<endl;
	cout<<"1.用交互方式构造图"<<endl;
	cout<<"2.从文本构建图"<<endl;
	cout<<"3.修改顶点的值"<<endl;
	cout<<"4.插入新顶点与相关边"<<endl;
	cout<<"5.插入新边"<<endl;
	cout<<"6.删除边"<<endl;
	cout<<"7.删除顶点与相关边"<<endl;
	cout<<"8.深度优先遍历"<<endl;
	cout<<"9.广度优先遍历"<<endl;
	AMLGraph G;
	VertexType v1,v2;
	int n;
	int k;
	int num;
	cout<<"请输入序号"<<endl;
	cin>>num;
	while(num)
	{
		switch(num)
		{
			case 1:{
				CreateGraph(&G);
				Display(G);
				break;
			}
			case 2:{
				char name[100];
				cout<<"请输入文件名"<<endl;
				cin>>name;
				CreateGraphFromFile(name);
				Translate(G);
				Display(G);
				break;
			} 
			case 3:{
				cout<<"修改结点的值"<<endl;
				cout<<"原值"<<endl;
				cin>>v1;
				cout<<"新值"<<endl;
				cin>>v2;
				PutVex(&G,v1,v2);
				Display(G);
				break;
			}
			case 4:{
				cout<<"插入新顶点,请输入顶点的值"<<endl;
				cin>>v1;
				InsertVex(&G,v1);
				cout<<"插入与顶点有关的边,输入边数"<<endl;
				cin>>n;
				for(k = 0;k < n;k++)
				{
					cout<<"请输入另一顶点的值"<<endl;
					cin>>v2;
					InsertArc(&G,v1,v2);
				}
				Display(G);
				break;
			}
			case 5:{
				cout<<"请输入第一个顶点的值"<<endl;
				cin>>v1;
				cout<<"请输入第二个顶点的值"<<endl;
				cin>>v2;
				InsertArc(&G,v1,v2);
				Display(G);
				break;
			}
			case 6:{
				cout<<"删除边，请输入边的两个顶点"<<endl;
				cin>>v1>>v2;
				DeleteArc(&G,v1,v2);
				Display(G);
				break;
			}
			case 7:{
				cout<<"删除点"<<endl;
				cin>>v1;
				DeleteVex(&G,v1);
				Display(G);
				break;
			}
			case 8:{
				cout<<"深度优先遍历"<<endl;
				DFSTraverse(G);
				break;
			}
			case 9:{
				cout<<"广度优先遍历"<<endl;
				BFSTraverse(G);
				break;
			}
			default:{
				break;
			} 
		}
	cout<<"0.销毁图并退出"<<endl;
	cout<<"1.用交互方式构造图"<<endl;
	cout<<"2.从文本构建图"<<endl;
	cout<<"3.修改顶点的值"<<endl;
	cout<<"4.插入新顶点与相关边"<<endl;
	cout<<"5.插入新边"<<endl;
	cout<<"6.删除边"<<endl;
	cout<<"7.删除顶点与相关边"<<endl;
	cout<<"8.深度优先遍历"<<endl;
	cout<<"9.广度优先遍历"<<endl;
	cout<<"请输入序号"<<endl;
	cin>>num;	
	}
	DestroyGraph(&G);
	
}

