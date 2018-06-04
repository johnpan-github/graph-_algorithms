#include"Floyd.h"

//���캯��
Graph_DG::Graph_DG(int vexnum, int edge)
{
	//��ʼ������ͱ���
	this->vexnum = vexnum;
	this->edge = edge;
	//Ϊ�ڽӾ��󿪱ٿռ�͸���ֵ
	arc = new int *[this->vexnum];
	disi = new int *[this->vexnum];
	path = new int *[this->vexnum];
	dis = new Dis[this->vexnum];
	for (int i = 0; i < this->vexnum; i++)
	{
		arc[i] = new int[this->vexnum];
		disi[i] = new int[this->vexnum];
		path[i] = new int[this->vexnum];
		for (int k = 0; k < this->vexnum; k++)
		{
			//�ڽӾ����ʼ��Ϊ�����
			arc[i][k] = INT_MAX;
		}
	}
}
//��������
Graph_DG::~Graph_DG()
{
	delete[] dis;
	for (int i = 0; i < this->vexnum; i++)
	{
		delete this->arc[i];
		delete this->disi[i];
		delete this->path[i];
	}
	delete disi;
	delete arc;
	delete path;
}
//�ж�����ÿ������ıߵ���Ϣ�Ƿ�Ϸ�
//�����1��ʼ���
bool Graph_DG::check_edge_value(int start, int end, int weight)
{
	if (start < 1 || end < 1 || start>vexnum || end>vexnum || weight < 0)
		return false;
	return true;
}
void Graph_DG::createGraph(int kind) //kind���������ǰͼ������ͼ��������ͼ
{
	cout << "������ÿ���ߵ������ص㣨�����Ŵ�1��ʼ���Լ�Ȩ��" << endl;
	int start;
	int end;
	int weight;
	int count = 0;
	while (count != this->edge)
	{
		cin >> start >> end >> weight;
		//�����жϱߵ���Ϣ�Ƿ�Ϸ�
		while (!this->check_edge_value(start, end, weight))
		{
			cout << "����ıߵ���Ϣ���Ϸ�������������" << endl;
			cin >> start >> end >> weight;
		}
		//���ڽӾ����Ӧ�ĵ㸳ֵ
		arc[start - 1][end - 1] = weight;
		//����ͼ��˵��kindȡֵ��2
		if (kind == 2)
			arc[end - 1][start - 1] = weight;
		++count;
	}
}
//��ӡ�ڽӾ���
void Graph_DG::print()
{
	cout << "ͼ���ڽӾ���Ϊ��" << endl;
	int count_row = 0;//��ӡ�еı�ǩ
	int count_col = 0;//��ӡ�еı�ǩ
	//��ʼ��ӡ
	while (count_row != this->vexnum)
	{
		count_col = 0;
		while (count_col != this->vexnum)
		{
			if (arc[count_row][count_col] == INT_MAX)
				cout << "��" << " ";
			else
				cout << arc[count_row][count_col] << " ";
			++count_col;
		}
		cout << endl;
		++count_row;
	}

}
void Graph_DG::Floyd()
{
	int row = 0;
	int col = 0;
	for (row = 0; row < this->vexnum; row++)
	{
		for (col = 0; col < this->vexnum; col++)
		{
			//�Ѿ����ʼ��Ϊ�ڽӾ����ֵ
			this->disi[row][col] = this->arc[row][col];
			//����p�ĳ�ֵ��Ϊ�����ߵ��յ㶥����±�
			this->path[row][col] = col;
		}	
	}
	//����ѭ�������ڼ���ÿ����Ե����·��
	int temp = 0;
	int select = 0;
	for (temp = 0; temp < this->vexnum; temp++)
	{
		for (row = 0; row < this->vexnum; row++)
		{
			for (col = 0; col < this->vexnum; col++)
			{
				//Ϊ�˷�ֹ�������������һ��selectֵ
				select = (disi[row][temp] == INT_MAX || disi[temp][col] == INT_MAX) ? INT_MAX : disi[row][temp] + disi[temp][col];
				if (this->disi[row][col]>select)
					//�������ǵľ���
				{
					this->disi[row][col] = select;
					this->path[row][col] = path[row][temp];
				}
			}
		}
	}
}
void Graph_DG::print_path()
{
	cout << "������������·����" << endl;
	int row = 0;
	int col = 0;
	int temp = 0;
	for (row = 0; row < this->vexnum; row++)
	{
		for (col = row + 1; col < this->vexnum; col++)
		{
			if (this->disi[row][col] != INT_MAX)
			{
				cout << "v" << to_string(row + 1) << "----" << "v" << to_string(col + 1) << " weight: " << this->disi[row][col] << "  " << "path:" << "v" << to_string(row + 1);
				temp = path[row][col];
				//ѭ�����;����ÿ��·��
				while (temp != col)
				{
					cout << "--->" << "v" << to_string(temp + 1);
					temp = path[temp][col];
				}
				cout << "--->" << "v" << to_string(col + 1) << endl;
			}
		}
	}
}
void Graph_DG::Dijkstra(int begin){
	//���ȳ�ʼ�����ǵ�dis����
	int i;
	for (i = 0; i < this->vexnum; i++) {
		//���õ�ǰ��·��
		dis[i].pathi = "v" + to_string(begin) + "-->v" + to_string(i + 1);
		dis[i].value = arc[begin - 1][i];
	}
	//�������ĵ�����·��Ϊ0
	dis[begin - 1].value = 0;
	dis[begin - 1].visit = true;

	int count = 1;
	//����ʣ��Ķ�������·����ʣ��this->vexnum-1�����㣩
	while (count != this->vexnum) {
		//temp���ڱ��浱ǰdis��������С���Ǹ��±�
		//min��¼�ĵ�ǰ����Сֵ
		int temp = 0;
		int min = INT_MAX;
		for (i = 0; i < this->vexnum; i++) {
			if (!dis[i].visit && dis[i].value<min) {
				min = dis[i].value;
				temp = i;
			}
		}
		//cout << temp + 1 << "  "<<min << endl;
		//��temp��Ӧ�Ķ�����뵽�Ѿ��ҵ������·���ļ�����
		dis[temp].visit = true;
		++count;
		for (i = 0; i < this->vexnum; i++) {
			//ע�����������arc[temp][i]!=INT_MAX����ӣ���Ȼ�����������Ӷ���ɳ����쳣
			if (!dis[i].visit && arc[temp][i] != INT_MAX && (dis[temp].value + arc[temp][i]) < dis[i].value) {
				//����µõ��ı߿���Ӱ������Ϊ���ʵĶ��㣬�Ǿ;͸����������·���ͳ���
				dis[i].value = dis[temp].value + arc[temp][i];
				dis[i].pathi = dis[temp].pathi + "-->v" + to_string(i + 1);
			}
		}
	}

}
void Graph_DG::print_path_Dij(int begin) {
	string str;
	str = "v" + to_string(begin);
	cout << "��" << str << "Ϊ����ͼ�����·��Ϊ��" << endl;
	for (int i = 0; i != this->vexnum; i++) {
		if (dis[i].value != INT_MAX)
			cout << dis[i].pathi << "=" << dis[i].value << endl;
		else {
			cout << dis[i].pathi<< "�������·����" << endl;
		}
	}
}