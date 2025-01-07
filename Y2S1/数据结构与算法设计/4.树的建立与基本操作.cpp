#include<iostream>
#include<string>

using namespace std;

char *c;
int degree;
int level[100] = {0};
int num = 0;

void PrintTree(int n, int x){
	while (*c != '\n'){
		if (*c == '('){
			c++;
			degree = max(degree, n+1);
			PrintTree(n+1, 0);
		}
		else if (*c == ')'){
			c++;
			degree = degree > x ? degree : x;
			return;
		}
		else if (*c == ','){
			c++;
			x++;
			continue;
		}	
		else{
			for(int i = 0; i < n; i++)
				cout << "    ";
			cout << *c << endl;
			c++;
			level[num] = n;
			num++;
		}
	}
}

int main(){
	int Degree[100] = {0};
	int totalDegree[100] = {0};
	string s;
	cin >> s;
	c = &s[1];
	PrintTree(0, 0);
	cout << "Degree of tree: " << degree << endl;
	for (int i = 0; i < num; i++){
		for (int j = i + 1; j < num; j++){
			if (level[i] == level[j]) break;
			if (level[i] + 1 == level[j]) Degree[i]++;
		}
	}
	for (int i = 0; i < num; i++) totalDegree[Degree[i]]++;
	for (int i = 0; i <= degree; i++){
		cout << "Number of nodes of degree " << i << ": " << totalDegree[i] << endl;
	}
}