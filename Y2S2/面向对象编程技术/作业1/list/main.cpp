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
			cout << "输入任意继续>>>";
			getch();
		}
		else {
			flag = true;
		}
		cout << endl;
		cout << "+------------------------+" << endl;
		cout << "|          操作          |" << endl;
		cout << "+------------------------+" << endl;
		cout << "| 1. 添加结点            |" << endl;
		cout << "+------------------------+" << endl;
		cout << "| 2. 删除结点(尾部)      |" << endl;
		cout << "+------------------------+" << endl;
		cout << "| 3. 删除结点(编号)      |" << endl;
		cout << "+------------------------+" << endl;
		cout << "| 4. 插入结点(编号)      |" << endl;
		cout << "+------------------------+" << endl;
		cout << "| 5. 查找结点数据(编号)  |" << endl;
		cout << "+------------------------+" << endl;
		cout << "| 6. 查找结点编号(数据)  |" << endl;
		cout << "+------------------------+" << endl;
		cout << "| 7. 更改结点数据(编号)  |" << endl;
		cout << "+------------------------+" << endl;
		cout << "| 8. 获取结点数量        |" << endl;
		cout << "+------------------------+" << endl;
		cout << "| 9. 打印链表            |" << endl;
		cout << "+------------------------+" << endl;
		cout << "| 0. 退出                |" << endl;
		cout << "+------------------------+" << endl;
		cout << endl;
		cout << "输入操作编号: ";
		cin >> n;

		switch (n) {
		case 1:
			cout << "输入结点名称: ";
			cin >> nodeName;
			ls.insert(nodeName);
			ls.printList();
			break;
		case 2:
			ls.deleteNode();
			ls.printList();
			break;
		case 3:
			cout << "输入结点编号: ";
			cin >> no;
			ls.deleteNode(no);
			ls.printList();
			break;
		case 4:
			cout << "输入结点编号: ";
			cin >> no;
			cout << "输入结点名称: ";
			cin >> nodeName;
			ls.insert(nodeName, no);
			ls.printList();
			break;
		case 5:
			cout << "输入结点编号: ";
			cin >> no;
			cout << ls.find(no) << endl;
			break;
		case 6:
			cout << "输入结点名称: ";
			cin >> nodeName;
			cout << ls.find(nodeName) << endl;
			break;
		case 7:
			cout << "输入结点编号: ";
			cin >> no;
			cout << "输入结点名称: ";
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