#include"Floyd.h"

//构造函数
Graph_DG::Graph_DG(int vexnum, int edge)
{
	//初始化顶点和边数
	this->vexnum = vexnum;
	this->edge = edge;
	//为邻接矩阵开辟空间和赋初值
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
			//邻接矩阵初始化为无穷大
			arc[i][k] = INT_MAX;
		}
	}
}
//析构函数
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
//判断我们每次输入的边的信息是否合法
//顶点从1开始编号
bool Graph_DG::check_edge_value(int start, int end, int weight)
{
	if (start < 1 || end < 1 || start>vexnum || end>vexnum || weight < 0)
		return false;
	return true;
}
void Graph_DG::createGraph(int kind) //kind传入参数当前图是有向图还是无向图
{
	cout << "请输入每条边的起点和重点（顶点编号从1开始）以及权重" << endl;
	int start;
	int end;
	int weight;
	int count = 0;
	while (count != this->edge)
	{
		cin >> start >> end >> weight;
		//首先判断边的信息是否合法
		while (!this->check_edge_value(start, end, weight))
		{
			cout << "输入的边的信息不合法，请重新输入" << endl;
			cin >> start >> end >> weight;
		}
		//对邻接矩阵对应的点赋值
		arc[start - 1][end - 1] = weight;
		//无向图来说，kind取值是2
		if (kind == 2)
			arc[end - 1][start - 1] = weight;
		++count;
	}
}
//打印邻接矩阵
void Graph_DG::print()
{
	cout << "图的邻接矩阵为：" << endl;
	int count_row = 0;//打印行的标签
	int count_col = 0;//打印列的标签
	//开始打印
	while (count_row != this->vexnum)
	{
		count_col = 0;
		while (count_col != this->vexnum)
		{
			if (arc[count_row][count_col] == INT_MAX)
				cout << "∞" << " ";
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
			//把矩阵初始化为邻接矩阵的值
			this->disi[row][col] = this->arc[row][col];
			//矩阵p的初值则为各个边的终点顶点的下标
			this->path[row][col] = col;
		}	
	}
	//三重循环，用于计算每个点对的最短路径
	int temp = 0;
	int select = 0;
	for (temp = 0; temp < this->vexnum; temp++)
	{
		for (row = 0; row < this->vexnum; row++)
		{
			for (col = 0; col < this->vexnum; col++)
			{
				//为了防止溢出，所以引入一个select值
				select = (disi[row][temp] == INT_MAX || disi[temp][col] == INT_MAX) ? INT_MAX : disi[row][temp] + disi[temp][col];
				if (this->disi[row][col]>select)
					//更新我们的矩阵
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
	cout << "各个顶点的最短路径：" << endl;
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
				//循环输出途径的每条路径
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
	//首先初始化我们的dis数组
	int i;
	for (i = 0; i < this->vexnum; i++) {
		//设置当前的路径
		dis[i].pathi = "v" + to_string(begin) + "-->v" + to_string(i + 1);
		dis[i].value = arc[begin - 1][i];
	}
	//设置起点的到起点的路径为0
	dis[begin - 1].value = 0;
	dis[begin - 1].visit = true;

	int count = 1;
	//计算剩余的顶点的最短路径（剩余this->vexnum-1个顶点）
	while (count != this->vexnum) {
		//temp用于保存当前dis数组中最小的那个下标
		//min记录的当前的最小值
		int temp = 0;
		int min = INT_MAX;
		for (i = 0; i < this->vexnum; i++) {
			if (!dis[i].visit && dis[i].value<min) {
				min = dis[i].value;
				temp = i;
			}
		}
		//cout << temp + 1 << "  "<<min << endl;
		//把temp对应的顶点加入到已经找到的最短路径的集合中
		dis[temp].visit = true;
		++count;
		for (i = 0; i < this->vexnum; i++) {
			//注意这里的条件arc[temp][i]!=INT_MAX必须加，不然会出现溢出，从而造成程序异常
			if (!dis[i].visit && arc[temp][i] != INT_MAX && (dis[temp].value + arc[temp][i]) < dis[i].value) {
				//如果新得到的边可以影响其他为访问的顶点，那就就更新它的最短路径和长度
				dis[i].value = dis[temp].value + arc[temp][i];
				dis[i].pathi = dis[temp].pathi + "-->v" + to_string(i + 1);
			}
		}
	}

}
void Graph_DG::print_path_Dij(int begin) {
	string str;
	str = "v" + to_string(begin);
	cout << "以" << str << "为起点的图的最短路径为：" << endl;
	for (int i = 0; i != this->vexnum; i++) {
		if (dis[i].value != INT_MAX)
			cout << dis[i].pathi << "=" << dis[i].value << endl;
		else {
			cout << dis[i].pathi<< "是无最短路径的" << endl;
		}
	}
}