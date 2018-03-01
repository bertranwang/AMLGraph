//main.cpp
#include<iostream>
#include"Graph.h"

using namespace std;
int main()
{
	cout<<"0.����ͼ���˳�"<<endl;
	cout<<"1.�ý�����ʽ����ͼ"<<endl;
	cout<<"2.���ı�����ͼ"<<endl;
	cout<<"3.�޸Ķ����ֵ"<<endl;
	cout<<"4.�����¶�������ر�"<<endl;
	cout<<"5.�����±�"<<endl;
	cout<<"6.ɾ����"<<endl;
	cout<<"7.ɾ����������ر�"<<endl;
	cout<<"8.������ȱ���"<<endl;
	cout<<"9.������ȱ���"<<endl;
	AMLGraph G;
	VertexType v1,v2;
	int n;
	int k;
	int num;
	cout<<"���������"<<endl;
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
				cout<<"�������ļ���"<<endl;
				cin>>name;
				CreateGraphFromFile(name);
				Translate(G);
				Display(G);
				break;
			} 
			case 3:{
				cout<<"�޸Ľ���ֵ"<<endl;
				cout<<"ԭֵ"<<endl;
				cin>>v1;
				cout<<"��ֵ"<<endl;
				cin>>v2;
				PutVex(&G,v1,v2);
				Display(G);
				break;
			}
			case 4:{
				cout<<"�����¶���,�����붥���ֵ"<<endl;
				cin>>v1;
				InsertVex(&G,v1);
				cout<<"�����붥���йصı�,�������"<<endl;
				cin>>n;
				for(k = 0;k < n;k++)
				{
					cout<<"��������һ�����ֵ"<<endl;
					cin>>v2;
					InsertArc(&G,v1,v2);
				}
				Display(G);
				break;
			}
			case 5:{
				cout<<"�������һ�������ֵ"<<endl;
				cin>>v1;
				cout<<"������ڶ��������ֵ"<<endl;
				cin>>v2;
				InsertArc(&G,v1,v2);
				Display(G);
				break;
			}
			case 6:{
				cout<<"ɾ���ߣ�������ߵ���������"<<endl;
				cin>>v1>>v2;
				DeleteArc(&G,v1,v2);
				Display(G);
				break;
			}
			case 7:{
				cout<<"ɾ����"<<endl;
				cin>>v1;
				DeleteVex(&G,v1);
				Display(G);
				break;
			}
			case 8:{
				cout<<"������ȱ���"<<endl;
				DFSTraverse(G);
				break;
			}
			case 9:{
				cout<<"������ȱ���"<<endl;
				BFSTraverse(G);
				break;
			}
			default:{
				break;
			} 
		}
	cout<<"0.����ͼ���˳�"<<endl;
	cout<<"1.�ý�����ʽ����ͼ"<<endl;
	cout<<"2.���ı�����ͼ"<<endl;
	cout<<"3.�޸Ķ����ֵ"<<endl;
	cout<<"4.�����¶�������ر�"<<endl;
	cout<<"5.�����±�"<<endl;
	cout<<"6.ɾ����"<<endl;
	cout<<"7.ɾ����������ر�"<<endl;
	cout<<"8.������ȱ���"<<endl;
	cout<<"9.������ȱ���"<<endl;
	cout<<"���������"<<endl;
	cin>>num;	
	}
	DestroyGraph(&G);
	
}

