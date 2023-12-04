#include<iostream>
using namespace std;

const int MAXV = 100;
const int INF = 0;

struct ArcNode
{
	int adjvex;
	int weight;
	string name;
	string information;
	ArcNode* nextarc;
};
   
struct HNode
{
	string info;
	ArcNode* firstarc;
};

class AdjGragh
{
public:
	HNode adjlist[MAXV];
	int n, e;

	AdjGragh()
	{
		for (int i = 0; i < MAXV; i++)
		{
			adjlist[i].firstarc = NULL;
		}
	}

	void CreatAdjGragh(int a[][MAXV], string name[], string information[], int n, int e)
	{
		ArcNode* p;
		this->n = n; this->e = e;
		for (int i = 0; i < n; i++)
			for (int j = n - 1; j >= 0; j--)
				if (a[i][j] != 0 && a[i][j] != INF)
				{
					p = new ArcNode();
					p->adjvex = j;
					p->weight = a[i][j];
					p->name = name[j];
					p->information = information[j];
					p->nextarc = adjlist[i].firstarc;
					adjlist[i].firstarc = p;
				}
	}

	void DispAdjGragh()                           //����ڽӱ�
	{
		ArcNode* p;
		for (int i = 0; i < n; i++)
		{
			cout << " " << i;
			p = adjlist[i].firstarc;
			while (p != NULL)
			{
				cout << "->";
				cout << "(" << p->adjvex << "," << p->weight << ")";
				p = p->nextarc;

			}
			cout << endl;
		}
	}
};

//��������㷨
 
void DFS(AdjGragh& G, int v)                                         //��Ϊ�����Ŀ�У�ѧУ�ĵص��γɵ�ͼΪ��ͨͼ�������ֱ��ʹ��DFS��������Ȼ����Ҫ�޸�һ��
{
	int visited[MAXV];                                         //C++����Ĭ��ֵΪ0
	visited[v] = 1;
	ArcNode* p = G.adjlist[v].firstarc;
	while (p != NULL)
	{

		int w = p->adjvex;

		if (visited[w] == 0)
		{
			DFS(G, w);
		}
		p = p->nextarc;
	}
	cout << endl;

}

void DFSA(AdjGragh& G)
{
	int visited[MAXV];
	for (int i = 0; i < G.n; i++)
		if (visited[i] == 0)
			DFS(G, i);
}

ArcNode* DFS_FUN(AdjGragh& G, int v,string function_var)       //DFS for search using names    DFS_FUN  ��󷵻���Ӧָ��
{
	int visited[MAXV];
	
	visited[v] = 1;
	ArcNode* p = G.adjlist[v].firstarc;
	while (p != NULL)                                          //�����p���ж�������Ҫ��if�����return���ǹؼ�
	{
		
		int w = p->adjvex;
		if (function_var == p->name)
		{
			return p;                                                        //����ָ��
		}
		if (visited[w] == 0)
		{  
			DFS_FUN(G, w,function_var);
		}
		p = p->nextarc;
	}
	return NULL;                                                          //δ�������򷵻�NULL

}

//������������������������·������


int DFS_fl (AdjGragh&G, int start,int end)  // ������ ��Ŀ�ĵ� �����        ��������ŷ���main����DFS_FUN
{
	int visited[MAXV];

	visited[start] = 1;
	ArcNode* p = G.adjlist[start].firstarc;
	
	
	while (p != NULL)                                             //����p���ж���DFS_FUN��һ��������Ҫ
	{
		
		int w = p->adjvex;
		int path_len = 0;    //path for length
		path_len += p->weight;
		if (end == p->adjvex)
		{
			return path_len;                                                  //����·������
		}
		
		if (visited[w] == 0)
		{
			DFS_fl(G,start,end);
		}
		p = p->nextarc;
	}
	
}



int main()
{

	int array1[][MAXV] = { {0,1,INF,5,INF},{1,0,2,1,3},{INF,2,0,INF,0},{INF,1,0,0,3},{INF,3,INF,3,0} };
	int num = 5;  //num�����������ܹ��ĵص����Ƶ������ģ� ���Ҫɾ�������Ӿ���Ļ��ǵö�num�����޸�
	string name[20] = { "����","����¥","һ��","����","��¥" };               //������ֵ������Ϊ�˷�����ɾ
	string information[20] = { "�ϱߵĴ���","��������","һ�ڵ�ʳ��","���ڵ�ʳ��","�׽�ѧ¥" };
	AdjGragh tu1;
	tu1.CreatAdjGragh(array1, name, information, 5, 5);

	//������еص�����ƣ��Է����οͲ�ѯ
	cout << "��������";
	for (int i = 0; i < 5; i++)
	{
		cout << ',' << name[i];
	}
	cout << endl;

	


	//p for search using name p_fsun
	ArcNode* p_fsun = NULL;
	int time = 0;
	string function_var;
	cout << "�����������ѯ��Ϣ�ĵص������\n";
	cin >> function_var;
	while (p_fsun == NULL||time<5)
	{  
		p_fsun = DFS_FUN(tu1, time,function_var);
		if (p_fsun != NULL)                                       //��DFS_FUN��������Ӧ�Ľ�㣬�򷵻�һ���ǿ�ָ�룬������������ж�����
		{
			break;
		}
		time = time + 1;
	}
	cout << p_fsun->information;
	cout << endl;

	//���������뿪ʼ�غ�Ŀ�ĵ�
	string start_place, end_place;
	cout << "��������ʼ�أ�";
	cin >> start_place;
	cout<< "������Ŀ�ĵأ�";
	cin >> end_place;


	//������������whileѭ�����������ʼ�ء�Ŀ�ĵص���ţ� ͨ��DFS_FUN
	int start, end;
	p_fsun = NULL;
	time = 0;
	while (p_fsun == NULL || time < 5)
	{
		p_fsun = DFS_FUN(tu1, time, start_place);
		if (p_fsun != NULL)                                      
		{
			break;
		}
		time = time + 1;
	}
	start = p_fsun->adjvex;

	p_fsun = NULL;
	time = 0;
	while (p_fsun == NULL || time < 5)
	{
		p_fsun = DFS_FUN(tu1, time, end_place);
		if (p_fsun != NULL)
		{
			break;
		}
		time = time + 1;
	}
	end = p_fsun->adjvex;

	cout <<"����Ϊ" << DFS_fl(tu1, start, end) << endl;

	tu1.DispAdjGragh();

}