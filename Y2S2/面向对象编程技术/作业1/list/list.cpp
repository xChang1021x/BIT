#include <iostream>
#include "list.h"
using namespace std;

LinkList::LinkList():dataCount(0) {		//构造函数
	head = new Node();
	head->next = NULL;
	tail = head;
}

void LinkList::insert(string data) {		//尾插
	if (dataCount == 20) {
		cout << "链表已满" << endl;
		return;
	}
	Node* p = new Node();
	p->data = data;
	p->next = NULL;
	tail->next = p;
	tail = p;
	dataCount++;
}

void LinkList::insert(string data, int location) {		//在某序号插入 // 重载
	if (dataCount == 20) {		//最大值20
		cout << "链表已满" << endl;
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
		cout << "超出范围" << endl;
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
		cout << "没有数据了!!";
		return;
	}
	else {
		cout << "删出范围了";
		return;
	}
}

void LinkList::deleteNode() {	
	bool found = false;
	Node* p = head;
	if (p->next == NULL) {
		cout << "未找到相应数据" << endl;
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

void LinkList::change(int location, string data) {	//更改某位置数据
	if (location > 0 && location <= dataCount) {
		Node* p = head;
		while (location--) {
			p = p->next;
		}
		p->data = data;
	}
	else {
		cout << "超出范围了" << endl;
	}
}

string LinkList::find(int location) {   // 查找结点，若超出范围则返回最后一个元素
	Node* p = head;
	while (location--) {
		p = p->next;
		if (p == NULL) {
			return "超出范围了";
		}
	}
	return p->data;
}

int LinkList::find(string data) {		//查找数据，并返回位置,只返回第一查找到的
	Node* p = head;
	int location = -1;
	int temp = 0;		//记录当前位置
	while (p->next != NULL) {
		p = p->next;
		temp++;
		if (p->data == data) {
			location = temp;
			break;
		}
	}
	if (location == -1) {
		cout << "数据不存在";
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