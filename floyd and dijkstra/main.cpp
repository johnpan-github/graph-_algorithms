#include"Floyd.h"

//检验顶点和边的数值是否有效，可以自己推算
//顶点和边数的关系是：（vexnum*(vexnum-1)/2<edge
bool check(int vexnum, int edge)
{
	if (vexnum <= 0 || edge <= 0 || ((vexnum*(vexnum - 1)) / 2) < edge)
		return false;
	return true;
}
int main()
{
	int vexnum; int edge;
	cout << "输入图的种类：1表示有向图，2表示无向图" << endl;
	int kind;
	cin >> kind;
	while (1)
	{
		if (kind == 1 || kind == 2) break;
		else
		{
			cout << "输入的图的种类编号不合法，请重新输入" << endl;
			cin >> kind;
		}
	}
	cout << "输入顶点个数和边的条数" << endl;
	cin >> vexnum >> edge;
	while (!check(vexnum, edge))
	{
		cout << "输入的数值不合法，请重新输入" << endl;
		cin >> vexnum >> edge;
	}
	Graph_DG graph(vexnum, edge);
	graph.createGraph(kind);
	graph.print();
	graph.Floyd();
	graph.print_path();
	graph.Dijkstra(1);
	graph.print_path_Dij(1);
	system("pause");
	return 0;
}