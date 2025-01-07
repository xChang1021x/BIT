#include<iostream>
#include<queue>

using namespace std;

struct Node {
    int data;
    Node* next;
};

int main() {
    int x = 0;
    char A[10010] = {0};
    Node* p, *Datas[10010];

    while (1) {
        char data;
        scanf("%c", &data);
        getchar();
        if (data == '*') {
            break;
        }
        A[x++] = data;
    }

    for (int i = 0; i < x; i++) {
        p = new Node();
        p->data = i;
        p->next = NULL;
        Datas[i] = p;
    }

    while (1) {
        int a, b;
        scanf("%d,%d", &a, &b);
        if (a == -1 && b == -1) break;

        p = new Node();
        p->data = b;
        p->next = Datas[a]->next;
        Datas[a]->next = p;

        p = new Node();
        p->data = a;
        p->next = Datas[b]->next;
        Datas[b]->next = p;
    }

    cout << "the ALGraph is" << endl;
    for (int i = 0; i < x; i++) {
        p = Datas[i]->next;
        cout << A[i];
        while (p != NULL) {
            cout << " " << p->data;
            p = p->next;
        }
        cout << endl;
    }

    cout << "the Breadth-First-Seacrh list:";
    int hash[10010] = {0};
    int flag = 0;
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int vertex = q.front();
        p = Datas[vertex]->next;
        cout << A[vertex];
        hash[vertex] = 1;
        q.pop();
        while (p != NULL) {
            if (!hash[p->data]) {
                hash[p->data] = 1;
                q.push(p->data);
            }
            p = p->next;
        }
        if (q.empty()){
	        for (int i = 0; i < x; i++){
	        	if (hash[i] == 0){
	        		q.push(i);
	        		break;
				}
			}        	
		}

    }
    cout << endl;

    return 0;
}