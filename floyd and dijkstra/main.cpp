#include"Floyd.h"

//���鶥��ͱߵ���ֵ�Ƿ���Ч�������Լ�����
//����ͱ����Ĺ�ϵ�ǣ���vexnum*(vexnum-1)/2<edge
bool check(int vexnum, int edge)
{
	if (vexnum <= 0 || edge <= 0 || ((vexnum*(vexnum - 1)) / 2) < edge)
		return false;
	return true;
}
int main()
{
	int vexnum; int edge;
	cout << "����ͼ�����ࣺ1��ʾ����ͼ��2��ʾ����ͼ" << endl;
	int kind;
	cin >> kind;
	while (1)
	{
		if (kind == 1 || kind == 2) break;
		else
		{
			cout << "�����ͼ�������Ų��Ϸ�������������" << endl;
			cin >> kind;
		}
	}
	cout << "���붥������ͱߵ�����" << endl;
	cin >> vexnum >> edge;
	while (!check(vexnum, edge))
	{
		cout << "�������ֵ���Ϸ�������������" << endl;
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