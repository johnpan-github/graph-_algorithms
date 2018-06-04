/**************************************/
/*        �������ߣ�Lintao            */
/*        �������ʱ�䣺2018/6/2      */
/*   ���κ�������ϵ��330263730@qq.com */
/**************************************/
//@����д�������ĳ���

#pragma once
//pragma once ��һ�ֳ�����C/C++��ע
//ֻҪ��ͷ�ļ����ʼ����������ע�����ܱ�֤ͷ�ļ�ֻ������һ��

/*
ʹ���ڽӾ�����ʵ��Floyd�㷨
*/
#include<iostream>
#include<string>
using namespace std;

//��¼��㵽ÿ����������·������Ϣ
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
	int vexnum;//ͼ�Ķ������
	int edge; //ͼ�ı���
	int **arc; //�ڽӾ���
	int **disi; //��¼������������·��
	int **path; //��¼�������·������Ϣ
	Dis * dis;   //��¼�����������·������Ϣ
public:
	//���캯��
	Graph_DG(int vexnum, int edge);
	//��������
	~Graph_DG();
	//�ж�����ÿ������ıߵ���Ϣ�Ƿ�Ϸ�
	//�����1��ʼ���
	bool check_edge_value(int start, int end, int weight);
	//����ͼ
	void createGraph(int);
	//��ӡ�ڽӾ���
	void print();
	//�����·��
	void Floyd();
	//��ӡ���·��
	void print_path();
	//Dijkstra�㷨
	void Dijkstra(int begin);
	void print_path_Dij(int begin);
};