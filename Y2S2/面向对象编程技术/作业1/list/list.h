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
	int dataCount;				//���ֵΪ20

public:
	LinkList();		//���캯��
	void insert(string data);		//β��
	void insert(string data, int location);		//��ĳ��Ų��� // ����
	void deleteNode(int location);		//ɾ��ĳ���λ���
	void deleteNode();		//ɾ��ָ������
	void change(int location, string data);	//����ĳλ������
	string find(int location);
	int find(string data);		//�������ݣ�������λ��,ֻ���ص�һ���ҵ���
	void printList();
	int getLength();
};
#endif