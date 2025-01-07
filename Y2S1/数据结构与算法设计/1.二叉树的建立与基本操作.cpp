#include<iostream>
#include<string>

using namespace std;

struct Tree{
	char data;
	Tree *lChild, *rChild;
};

char *c;
int cntLeaf;

Tree* CreateTree(Tree* p){
	if (*c == '#') {
		c++;
		return NULL;	
	}
	p = new Tree();
	p->data = *c;
	c++;
	p->lChild = CreateTree(p->lChild);
	p->rChild = CreateTree(p->rChild);
	
	if (p->lChild == NULL && p->rChild == NULL){
		cntLeaf++;
	}
	
	return p;
}

Tree* ChangeTree(Tree* p){
	Tree *q;
	q = p->lChild;
	p->lChild = p->rChild;
	p->rChild = q;	
	if (p->lChild != NULL){
		p->lChild = ChangeTree(p->lChild);
	}
	if (p->rChild != NULL){
		p->rChild = ChangeTree(p->rChild);
	}

	return p;
}

void prePrintTree(Tree* p){
	cout << p->data;
	if (p->lChild != NULL) prePrintTree(p->lChild);
	if (p->rChild != NULL) prePrintTree(p->rChild);
}
void inPrintTree(Tree* p){
	if (p->lChild != NULL) inPrintTree(p->lChild);
	cout << p->data;
	if (p->rChild != NULL) inPrintTree(p->rChild);
}
void postPrintTree(Tree* p){
	if (p->lChild != NULL) postPrintTree(p->lChild);
	if (p->rChild != NULL) postPrintTree(p->rChild);
	cout << p->data;
}

void inDrawing(Tree* p, int n){
	for (int i = 0; i < n; i++)
		cout << "    ";
	cout << p->data << endl;
	if (p->lChild != NULL) inDrawing(p->lChild, n+1);
	if (p->rChild != NULL) inDrawing(p->rChild, n+1);
}

int main(){
	string s;
	cin >> s;
	c = &s[0];
	Tree *root = new Tree();
	root = CreateTree(root);
	cout << "BiTree" << endl;
	inDrawing(root, 0);
	cout << "pre_sequence  : ";
	prePrintTree(root);
	cout << endl << "in_sequence   : ";
	inPrintTree(root);
	cout << endl << "post_sequence : ";
	postPrintTree(root);
	cout << endl;
	cout << "Number of leaf: " << cntLeaf << endl;
	
	root = ChangeTree(root);
	cout << "BiTree swapped" << endl;
	inDrawing(root, 0);
	cout << "pre_sequence  : ";
	prePrintTree(root);
	cout << endl << "in_sequence   : ";
	inPrintTree(root);
	cout << endl << "post_sequence : ";
	postPrintTree(root);
	cout << endl;
	return 0;
}