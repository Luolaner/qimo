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

	void DispAdjGragh()                           //输出邻接表
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

//深度优先算法
 
void DFS(AdjGragh& G, int v)                                         //因为这次项目中，学校的地点形成的图为连通图，因而我直接使用DFS函数，当然，还要修改一下
{
	int visited[MAXV];                                         //C++数组默认值为0
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

ArcNode* DFS_FUN(AdjGragh& G, int v,string function_var)       //DFS for search using names    DFS_FUN  最后返回相应指针
{
	int visited[MAXV];
	
	visited[v] = 1;
	ArcNode* p = G.adjlist[v].firstarc;
	while (p != NULL)                                          //这里的p的判定并不重要，if里面的return才是关键
	{
		
		int w = p->adjvex;
		if (function_var == p->name)
		{
			return p;                                                        //返回指针
		}
		if (visited[w] == 0)
		{  
			DFS_FUN(G, w,function_var);
		}
		p = p->nextarc;
	}
	return NULL;                                                          //未遍历到则返回NULL

}

//接下来的这个函数用来解决求路径问题


int DFS_fl (AdjGragh&G, int start,int end)  // 出发地 和目的地 的序号        这两个序号放在main里用DFS_FUN
{
	int visited[MAXV];

	visited[start] = 1;
	ArcNode* p = G.adjlist[start].firstarc;
	
	
	while (p != NULL)                                             //这里p的判定和DFS_FUN的一样，不重要
	{
		
		int w = p->adjvex;
		int path_len = 0;    //path for length
		path_len += p->weight;
		if (end == p->adjvex)
		{
			return path_len;                                                  //返回路径长度
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
	int num = 5;  //num是用来计算总共的地点名称的数量的， 如果要删除或增加景点的话记得对num进行修改
	string name[20] = { "南门","银杏楼","一期","二期","甲楼" };               //这里数值调高是为了方便增删
	string information[20] = { "南边的大门","男生宿舍","一期的食堂","二期的食堂","甲教学楼" };
	AdjGragh tu1;
	tu1.CreatAdjGragh(array1, name, information, 5, 5);

	//输出所有地点的名称，以方便游客查询
	cout << "景点名称";
	for (int i = 0; i < 5; i++)
	{
		cout << ',' << name[i];
	}
	cout << endl;

	


	//p for search using name p_fsun
	ArcNode* p_fsun = NULL;
	int time = 0;
	string function_var;
	cout << "请输入你想查询信息的地点的名称\n";
	cin >> function_var;
	while (p_fsun == NULL||time<5)
	{  
		p_fsun = DFS_FUN(tu1, time,function_var);
		if (p_fsun != NULL)                                       //若DFS_FUN遍历到对应的结点，则返回一个非空指针，因而这里用作判定条件
		{
			break;
		}
		time = time + 1;
	}
	cout << p_fsun->information;
	cout << endl;

	//接下来输入开始地和目的地
	string start_place, end_place;
	cout << "请输入起始地：";
	cin >> start_place;
	cout<< "请输入目的地：";
	cin >> end_place;


	//接下来这两个while循环用来求出起始地、目的地的序号， 通过DFS_FUN
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

	cout <<"距离为" << DFS_fl(tu1, start, end) << endl;

	tu1.DispAdjGragh();

}