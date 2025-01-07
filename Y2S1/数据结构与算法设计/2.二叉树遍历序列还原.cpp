#include<iostream>
#include<string>
#include<queue>

using namespace std;

struct Tree{
	char data;
	Tree *lChild, *rChild;
};

Tree* Recover(string sin, string spost){
	if(sin[0] == 0)
		return NULL;
	
	int locate = sin.find(spost[spost.size() - 1], 0);
	Tree *p =  new Tree();
	p->data = spost[spost.size() - 1];
	p->lChild = Recover(sin.substr(0, locate), spost.substr(0,locate));
	p->rChild = Recover(sin.substr(locate + 1, sin.size() - locate), spost.substr(locate, spost.size() - locate - 1));
	
	return p;
}


void PrintTree(Tree *root){
	queue< Tree*> q;
	q.push(root);
	
	while (q.size()){
		Tree *p = q.front();
		cout << p->data;
		if (p->lChild != NULL) q.push(p->lChild);
		if (p->rChild != NULL) q.push(p->rChild);
		q.pop();
	}
}

int main(){

	string ins, posts;
	cin >> ins;
	cin >> posts;
	Tree *root = new Tree();
	root = Recover(ins, posts);
	PrintTree(root);
	cout << endl;
}