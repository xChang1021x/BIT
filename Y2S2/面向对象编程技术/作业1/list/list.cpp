#include <iostream>
#include "list.h"
using namespace std;

LinkList::LinkList():dataCount(0) {		//���캯��
	head = new Node();
	head->next = NULL;
	tail = head;
}

void LinkList::insert(string data) {		//β��
	if (dataCount == 20) {
		cout << "��������" << endl;
		return;
	}
	Node* p = new Node();
	p->data = data;
	p->next = NULL;
	tail->next = p;
	tail = p;
	dataCount++;
}

void LinkList::insert(string data, int location) {		//��ĳ��Ų��� // ����
	if (dataCount == 20) {		//���ֵ20
		cout << "��������" << endl;
		return;
	}
	else if (location > 0 && location <= dataCount + 1) {
		Node* p = head;
		Node* q = new Node();
		location--;
		while (location--) {
			p = p->next;
		}
		q->data = data;
		q->next = p->next;
		p->next = q;
		if (location == dataCount + 1) {
			tail = q;
		}
		dataCount++;
	}
	else {
		cout << "������Χ" << endl;
	}
}

void LinkList::deleteNode(int location) {
	if (location > 0 && location <= dataCount) {
		Node* p = head;
		location--;
		while (location--) {
			p = p->next;
		}
		if (p->next->next == NULL) {
			tail = p;
		}
		Node* q = p->next;
		p->next = q->next;
		delete(q);
		dataCount--;
	}
	else if (dataCount == 0) {
		cout << "û��������!!";
		return;
	}
	else {
		cout << "ɾ����Χ��";
		return;
	}
}

void LinkList::deleteNode() {	
	bool found = false;
	Node* p = head;
	if (p->next == NULL) {
		cout << "δ�ҵ���Ӧ����" << endl;
		return;
	}
	while(p->next->next) {
		p = p->next;
	}
	tail = p;
	p = p->next;
	tail->next = NULL;
	delete(p);
	dataCount--;
}

void LinkList::change(int location, string data) {	//����ĳλ������
	if (location > 0 && location <= dataCount) {
		Node* p = head;
		while (location--) {
			p = p->next;
		}
		p->data = data;
	}
	else {
		cout << "������Χ��" << endl;
	}
}

string LinkList::find(int location) {   // ���ҽ�㣬��������Χ�򷵻����һ��Ԫ��
	Node* p = head;
	while (location--) {
		p = p->next;
		if (p == NULL) {
			return "������Χ��";
		}
	}
	return p->data;
}

int LinkList::find(string data) {		//�������ݣ�������λ��,ֻ���ص�һ���ҵ���
	Node* p = head;
	int location = -1;
	int temp = 0;		//��¼��ǰλ��
	while (p->next != NULL) {
		p = p->next;
		temp++;
		if (p->data == data) {
			location = temp;
			break;
		}
	}
	if (location == -1) {
		cout << "���ݲ�����";
	}
	return location;
}

void LinkList::printList() {
	for (int i = 0; i < 2; ++i) {
		cout << endl;
	}
	Node* p = head;
	while (p->next != NULL) {
		p = p->next;
		cout << p->data << " ";
		if (p->next != NULL) {
			cout << "-->" << " ";
		}
	}
	for (int i = 0; i < 3; ++i) {
		cout << endl;
	}
}

int LinkList::getLength() {
	return dataCount;
}