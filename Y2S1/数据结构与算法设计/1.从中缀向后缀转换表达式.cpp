#include <iostream>
#include <stack>

using namespace std;

int isp(char op){
    if (op == '^') return 6;
    if (op == '*' || op == '/') return 5;
    if (op == '+' || op == '-') return 3;
    if (op == '(') return 1;
    if (op == ')') return 8;
    return 0;
}

int icp(char op){
    if (op == '^') return 7;
    if (op == '*' || op == '/') return 4;
    if (op == '+' || op == '-') return 2;
    if (op == '(') return 8;
    if (op == ')') return 1;
    return 0;
}

int main() {
    int N;
    scanf("%d", &N);
    while (N--) {
        stack<char> op;
        char ch = 0;
        char A[1000] = {0};
        int x = 0;
        scanf("%s", A);
        ch = A[0];
        op.push('#');
        while (ch != '#') {
            ch = A[x++];
            
            if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')){
            	printf("%c", ch);
            	continue;
			}
			else if (icp(ch) > isp(op.top())){
				op.push(ch);
				continue;
			}
			else if (icp(ch) < isp(op.top())){
				while (isp(op.top()) > icp(ch)){
					printf("%c", op.top());
					op.pop();	
				}
				if (icp(ch) == isp(op.top())){
					op.pop();
				}
				else{
					op.push(ch);
				}
			}
			else if (icp(ch) == isp(op.top())){
				op.pop();
			}
        }
        printf("\n");
    }

    return 0;
}