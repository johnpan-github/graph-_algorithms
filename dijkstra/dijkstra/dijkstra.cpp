#include<iostream>
#include<vector>
#define MAX 100 //矩阵的最大容量
#define INF INT_MAX
using namespace std;
//邻接矩阵
typedef struct _graph
{
	char vexs[MAX];   //vertex set
	int vexnum;       //the number of vertexs
	int edgnum;       //the number of edges
	int matrix[MAX][MAX];    //the adjacent matrix
}Graph, *PGraph;

//the edge struct
typedef struct _EdgeData
{
	char start; //the start point of edge
	char end;  //the end point of edge
	int weight; //the weight of the edge
}EData;
Graph* create_example_graph()
{
	vector<char> vexs= { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
	int matrix[][9] = {
		/*A*//*B*//*C*//*D*//*E*//*F*//*G*/
		/*A*/{ 0, 12, INF, INF, INF, 16, 14 },
		/*B*/{ 12, 0, 10, INF, INF, 7, INF },
		/*C*/{ INF, 10, 0, 3, 5, 6, INF },
		/*D*/{ INF, INF, 3, 0, 4, INF, INF },
		/*E*/{ INF, INF, 5, 4, 0, 2, 8 },
		/*F*/{ 16, 7, 6, INF, 2, 0, 9 },
		/*G*/{ 14, INF, INF, INF, 8, 9, 0 } };
	int vlen = vexs.size();
	int i, j;
	Graph* pG;

	// 输入"顶点数"和"边数"
	if ((pG = (Graph*)malloc(sizeof(Graph))) == NULL)
		return NULL;
	memset(pG, 0, sizeof(Graph));

	// 初始化"顶点数"
	pG->vexnum = vlen;
	// 初始化"顶点"
	for (i = 0; i < pG->vexnum; i++)
		pG->vexs[i] = vexs[i];

	// 初始化"边"
	for (i = 0; i < pG->vexnum; i++)
	for (j = 0; j < pG->vexnum; j++)
		pG->matrix[i][j] = matrix[i][j];

	// 统计边的数目
	for (i = 0; i < pG->vexnum; i++)
	for (j = 0; j < pG->vexnum; j++)
	if (i != j && pG->matrix[i][j] != INF)
		pG->edgnum++;
	pG->edgnum /= 2;

	return pG;
}
void dijkstra(Graph G, int vs, int prev[], int dist[])
{
	int i, j, k;
	int min;
	int tmp;
	int flag[MAX];  //flag[i]=1 表示起始顶点到顶点i的最短路径已经成功获取。
	
	//initialization
	for (i = 0; i < G.vexnum; i++)
	{
		flag[i] = 0;
		prev[i] = 0;
		dist[i] = G.matrix[vs][i]; //顶点i的最短路径为顶点vs到顶点i的权。
	}
	//对顶点vs自身进行初始化
	flag[vs] = 1;
	dist[vs] = 0;
	//遍历G.vexnum-1次，每次找到一个顶点的最短路径
	for (i = 1; i < G.vexnum; i++)
	{
		//寻找当前的最短路径
		//也就是说，在未获取最短路径的顶点中，找到离vs最近的顶点k
		min = INF;
		for (j = 0; j < G.vexnum; j++)
		{
			if (flag[j] == 0 && dist[j] < min)
			{
				min = dist[j];
				k = j;
			}
		}
		flag[k] = 1;
		//修正当前最短路径和前驱顶点
		//也就是，当已经获得顶点K的最短路径之后，更新“未获取最短路径的顶点的最短路径和前驱结点”
		for (j = 0; j < G.vexnum; j++)
		{
			tmp = (G.matrix[k][j] == INT_MAX ? INT_MAX : (min + G.matrix[k][j]));
			if (flag[j] == 0 && (tmp < dist[j]))
			{
				dist[j] = tmp;
				prev[j] = k;
			}
		}
	}
	printf("dijkstra(%c):\n", G.vexs[vs]);
	for (i = 0; i < G.vexnum; i++)
		printf("shortest(%c,%c)=%d\n", G.vexs[vs], G.vexs[i], dist[i]);
}
int main()
{
	int prev[MAX] = { 0 };
	int dist[MAX] = { 0 };
	Graph* pG;
	pG = create_example_graph();
	dijkstra(*pG, 3, prev, dist);
	system("pause");
	return 0;
}