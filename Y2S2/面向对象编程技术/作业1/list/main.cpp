#include<iostream>
#include<string>
#include<conio.h>
#include"list.h"
//#include"draw.h"

using namespace std;

int main() {
	int n;
	int no;
	bool flag = false;
	string nodeName;
	int count = 0;
	LinkList ls = LinkList();
	do {
		if (flag) {
			cout << "�����������>>>";
			getch();
		}
		else {
			flag = true;
		}
		cout << endl;
		cout << "+------------------------+" << endl;
		cout << "|          ����          |" << endl;
		cout << "+------------------------+" << endl;
		cout << "| 1. ��ӽ��            |" << endl;
		cout << "+------------------------+" << endl;
		cout << "| 2. ɾ�����(β��)      |" << endl;
		cout << "+------------------------+" << endl;
		cout << "| 3. ɾ�����(���)      |" << endl;
		cout << "+------------------------+" << endl;
		cout << "| 4. ������(���)      |" << endl;
		cout << "+------------------------+" << endl;
		cout << "| 5. ���ҽ������(���)  |" << endl;
		cout << "+------------------------+" << endl;
		cout << "| 6. ���ҽ����(����)  |" << endl;
		cout << "+------------------------+" << endl;
		cout << "| 7. ���Ľ������(���)  |" << endl;
		cout << "+------------------------+" << endl;
		cout << "| 8. ��ȡ�������        |" << endl;
		cout << "+------------------------+" << endl;
		cout << "| 9. ��ӡ����            |" << endl;
		cout << "+------------------------+" << endl;
		cout << "| 0. �˳�                |" << endl;
		cout << "+------------------------+" << endl;
		cout << endl;
		cout << "����������: ";
		cin >> n;

		switch (n) {
		case 1:
			cout << "����������: ";
			cin >> nodeName;
			ls.insert(nodeName);
			ls.printList();
			break;
		case 2:
			ls.deleteNode();
			ls.printList();
			break;
		case 3:
			cout << "��������: ";
			cin >> no;
			ls.deleteNode(no);
			ls.printList();
			break;
		case 4:
			cout << "��������: ";
			cin >> no;
			cout << "����������: ";
			cin >> nodeName;
			ls.insert(nodeName, no);
			ls.printList();
			break;
		case 5:
			cout << "��������: ";
			cin >> no;
			cout << ls.find(no) << endl;
			break;
		case 6:
			cout << "����������: ";
			cin >> nodeName;
			cout << ls.find(nodeName) << endl;
			break;
		case 7:
			cout << "��������: ";
			cin >> no;
			cout << "����������: ";
			cin >> nodeName;
			ls.change(no, nodeName);
			ls.printList();
			break;
		case 8:
			cout << ls.getLength() << endl;
			break;
		case 9:
			ls.printList();
			break;
		case 0:
			break;
		default:
			cout << "no num " << n << endl;
			break;
		}
	} while (n != 0);
	return 0;
}