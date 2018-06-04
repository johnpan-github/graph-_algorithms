/**************************************/
/*        程序作者：Lintao            */
/*        程序完成时间：2018/6/2      */
/*   有任何问题联系：330263730@qq.com */
/**************************************/
//@尽量写出完美的程序

#pragma once
//pragma once 是一种常见的C/C++杂注
//只要在头文件的最开始加入这条杂注，就能保证头文件只被编译一次

/*
使用邻接矩阵来实现Floyd算法
*/
#include<iostream>
#include<string>
using namespace std;

//记录起点到每个顶点的最短路径的信息
struct Dis {
	string pathi;
	int value;
	bool visit;
	Dis() {
		visit = false;
		value = 0;
		pathi = "";
	}
};

class Graph_DG
{
private:
	int vexnum;//图的顶点个数
	int edge; //图的边数
	int **arc; //邻接矩阵
	int **disi; //记录各个顶点的最短路径
	int **path; //记录各个最短路径的信息
	Dis * dis;   //记录各个顶点最短路径的信息
public:
	//构造函数
	Graph_DG(int vexnum, int edge);
	//析构函数
	~Graph_DG();
	//判断我们每次输入的边的信息是否合法
	//顶点从1开始编号
	bool check_edge_value(int start, int end, int weight);
	//创建图
	void createGraph(int);
	//打印邻接矩阵
	void print();
	//求最短路径
	void Floyd();
	//打印最短路径
	void print_path();
	//Dijkstra算法
	void Dijkstra(int begin);
	void print_path_Dij(int begin);
};