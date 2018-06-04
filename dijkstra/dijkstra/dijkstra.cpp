#include<iostream>
#include<vector>
#define MAX 100 //������������
#define INF INT_MAX
using namespace std;
//�ڽӾ���
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

	// ����"������"��"����"
	if ((pG = (Graph*)malloc(sizeof(Graph))) == NULL)
		return NULL;
	memset(pG, 0, sizeof(Graph));

	// ��ʼ��"������"
	pG->vexnum = vlen;
	// ��ʼ��"����"
	for (i = 0; i < pG->vexnum; i++)
		pG->vexs[i] = vexs[i];

	// ��ʼ��"��"
	for (i = 0; i < pG->vexnum; i++)
	for (j = 0; j < pG->vexnum; j++)
		pG->matrix[i][j] = matrix[i][j];

	// ͳ�Ʊߵ���Ŀ
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
	int flag[MAX];  //flag[i]=1 ��ʾ��ʼ���㵽����i�����·���Ѿ��ɹ���ȡ��
	
	//initialization
	for (i = 0; i < G.vexnum; i++)
	{
		flag[i] = 0;
		prev[i] = 0;
		dist[i] = G.matrix[vs][i]; //����i�����·��Ϊ����vs������i��Ȩ��
	}
	//�Զ���vs������г�ʼ��
	flag[vs] = 1;
	dist[vs] = 0;
	//����G.vexnum-1�Σ�ÿ���ҵ�һ����������·��
	for (i = 1; i < G.vexnum; i++)
	{
		//Ѱ�ҵ�ǰ�����·��
		//Ҳ����˵����δ��ȡ���·���Ķ����У��ҵ���vs����Ķ���k
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
		//������ǰ���·����ǰ������
		//Ҳ���ǣ����Ѿ���ö���K�����·��֮�󣬸��¡�δ��ȡ���·���Ķ�������·����ǰ����㡱
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