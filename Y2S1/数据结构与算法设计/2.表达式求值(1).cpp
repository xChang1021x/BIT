#include <iostream>
#include <cstring>
#include <string>
#include <stack>

using namespace std;

#define INF 2147483647

int isOp(char op){
	if (op == '+' || op == '-' || op == '*' || op == '/' || op == '^' || op == '%'){
		return 1;
	}
	else return 0;
}

int isp(char op){
    if (op == '^') return 6;
    if (op == '*' || op == '/' || op == '%') return 5;
    if (op == '+' || op == '-') return 3;
    return 0;
}

int icp(char op){
    if (op == '^') return 7;
    if (op == '*' || op == '/' || op == '%') return 4;
    if (op == '+' || op == '-') return 2;
    return 0;
}

int pow(int a, int b){
	int sum = 1;
	for (int i = 0; i < b; i++){
		sum *= a;
	}
	return sum;
}

int operation(char op, int a, int b){
	switch(op){
		case '+':
			return a+b;
		case '-':
			return a-b;
		case '*':
			return a*b;
		case '/':
			if (b == 0) return INF;
			return a/b;
		case '^':
			if (b < 0) return INF - 1;
			return pow(a, b);
		case '%':
			return a%b;
		default:
			return INF - 1;
	}
	return 0;
}

int main() {
    
        stack<char> op;
        stack<int> num;
        string A;
		int length;
        int x = 0;
        int cntOp = 0, cntNum = 0;
        int number = 0;
        int a = 0, b = 0, c = 0;
        cin >> A;
        length = A.length();
        while (x < length) {
            
            if ((A[x] >= '0' && A[x] <= '9')){
            	number = A[x] - '0';
            	x++;
				while (A[x] >= '0' && A[x] <= '9'){
					number *= 10;
					number += A[x] - '0';
					x++;
				}
				num.push(number);
				cntNum++;
				continue;
			}
			
			if (A[x] == '-'){
				if (x == 0 || isOp(A[x-1])){
					
					x++;
					number = A[x] - '0';
					x++;
					while (A[x] >= '0' && A[x] <= '9'){
						number *= 10;
						number += A[x] - '0';
						x++;
					}
					number = -number;
					num.push(number);
					cntNum++;
					continue;
				} 
			}
			
			if (op.empty() || icp(A[x]) > isp(op.top())){
				op.push(A[x]);
				if (A[x] != '('){
					cntOp++;	
				}
				else{
					cntLeft++;
				}
				x++;
				continue;
			}
			else if (icp(A[x]) < isp(op.top())){
				if (num.size() < 2){
					Error = 1;
					printf("error.\n");
					break;
				}
				
				while (!op.empty() && isp(op.top()) > icp(A[x])){
		        	a = num.top();
		        	num.pop();
		        	b = num.top();
		        	num.pop();
		        	c = operation(op.top(), b, a);
		        	op.pop();
					num.push(c);
					cntOp--;
					cntNum--;
				}
				
				char abcde = op.top();
				if (!op.empty() && icp(A[x]) == isp(op.top())){
					op.pop();
				}
				else{
					op.push(A[x]);
					cntOp++;
				}
				x++;
			}
			else if (icp(A[x]) == isp(op.top())){
				op.pop();
				cntLeft--;
				x++;
				continue;
			}
        }
        
        while (op.size() != 0 && num.size() >= 2){
        	a = num.top();
        	num.pop();
        	b = num.top();
        	num.pop();
        	c = operation(op.top(), b, a);
        	op.pop();
			num.push(c);
		}
		
		if (op.size() == 0 && num.size() == 1){
			printf("%d\n", num.top());
			continue;
		}
		
    
    return 0;
} 