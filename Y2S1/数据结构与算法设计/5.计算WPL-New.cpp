#include<iostream>

using namespace std;

struct BTree{
	int weight;
	BTree *lchild, *rchild;
};

int WPL = 0;

BTree* CreateHuffTree(int n, int Weight[]){
	BTree *p[1000];
	BTree *q;
	for (int i = 0; i < n; i++){
		p[i] = new BTree();
		p[i]->weight = Weight[i];
		p[i]->lchild = p[i]->rchild = NULL;
	}
	
	for (int i = 1; i < n; i++){
		int min1 = -1, min2;
		for (int j = 0; j < n; j++){
			if (p[j] != NULL && min1 == -1){
				min1 = j;
				continue;
			}
			else if (p[j] != NULL){
				min2 = j;
				break;
			}
		}
		
		for (int j = min2; j < n; j++){
			if (p[j] != NULL){
				if (p[min1]->weight > p[j]->weight){
					min2 = min1;
					min1 = j;
				}
				else if (p[min2]->weight > p[j]->weight){
					min2 = j;
				}
			}
		}
		
		q = new BTree();
		q->weight = p[min1]->weight + p[min2]->weight;
		q->lchild = p[min1];
		q->rchild = p[min2];
		
		p[min1] = q;
		p[min2] = NULL;
	}
	
	return q;
}

void CountWPL(BTree *p, int deep){
	if (p->lchild == NULL && p->rchild == NULL){
		WPL += p->weight * deep;
		return;
	}
	
	if (p->lchild != NULL) CountWPL(p->lchild, deep + 1);
	if (p->rchild != NULL) CountWPL(p->rchild, deep + 1);
}

int main(){
	int n;
	int weight[1000] = {0};
	cin >> n;
	for (int i = 0; i < n; i++){
		cin >> weight[i];
	}
	BTree *root;
	root = CreateHuffTree(n, weight);
	CountWPL(root, 0);
	cout << "WPL=" << WPL << endl;
	return 0;
}