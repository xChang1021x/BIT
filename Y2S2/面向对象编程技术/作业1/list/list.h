#pragma once
#include <string>
using namespace std;

#ifndef _LINKLIST_H_
#define _LINKLIST_H_

class Node {
public:
	string data;
	Node* next;
};

class LinkList {
private:
	Node* head;
	Node* tail = new Node();
	int dataCount;				//最大值为20

public:
	LinkList();		//构造函数
	void insert(string data);		//尾插
	void insert(string data, int location);		//在某序号插入 // 重载
	void deleteNode(int location);		//删除某序号位结点
	void deleteNode();		//删除指定数据
	void change(int location, string data);	//更改某位置数据
	string find(int location);
	int find(string data);		//查找数据，并返回位置,只返回第一查找到的
	void printList();
	int getLength();
};
#endif