#include<iostream>
#include<algorithm>
#include<string>

using namespace std;

struct GLNode{
	int tag;
	union{
		char data;
		struct {
			GLNode *hp;
		} ptr;
	};
	GLNode *next;
};
 
GLNode *ls = new GLNode();
GLNode *q = ls;
char *s;

void CreateGList(GLNode *p){
	while (*s != '\n'){
		s++;
		if (*s == ')') return;					//右括号退一层
		if (*s == ',') continue;				//逗号则处理下一个符号						
		if (*s == '('){							//左括号进入深一层
			GLNode *NewNode = new GLNode();		//开新内存给新节点
			NewNode->tag = 1;					
			NewNode->next = NULL;
			p->next = NewNode;
			p = p->next;
			CreateGList(p);
			NewNode->ptr.hp = NewNode->next;
			NewNode->next = NULL;
		}
		else{
			GLNode *NewNode = new GLNode();
			NewNode->tag = 0;
			NewNode->data = *s;
			NewNode->next = NULL;
			p->next = NewNode;
			p = p->next;
		}
	}
}

void PrintGList(GLNode *r){
	while (r != NULL){
		
		if (r->tag == 0){
			if (r->next != NULL)
				cout << r->data << ',';
			else
				cout << r->data;
		}
		else{
			cout << '(';
			PrintGList(r->ptr.hp);
			if (r->next != NULL)
				cout << "),";
			else
				cout << ')';
		}
		r = r->next;
	}
}

void Print(){
	q = ls;
	cout << "generic list: ";
	if (ls->next == NULL){
		cout << "()" << endl;
	}
	else if (ls->next->tag == 0 && ls->next->next == NULL){
		PrintGList(ls->next);
		cout << endl;
	}
	else {
		cout << '(';
		PrintGList(ls->next);
		cout << ')' << endl;			
	}
}

int main(){
	string str;
	cin >> str;
	s = &str[0];
	CreateGList(ls);
	
	Print();
	
	int x;
	while(ls->next != NULL){
		if (ls->next->tag == 0 && ls->next->next == NULL) break;
		cin >> x;
		if (x == 1){
			if (ls->next->tag == 1)
				ls->next = ls->next->ptr.hp;
			else
				ls->next->next = NULL;
				
			cout << "destroy tail" << endl;
			cout << "free list node" << endl;
			Print();
		}
		else if (x == 2){
			ls->next = ls->next->next;
			cout << "free head node" << endl;
			cout << "free list node" << endl;
			Print();
		}
	}
	
	return 0;
}