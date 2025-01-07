#include <stdio.h>

int n, m, min = 2147483647;
int flag = 0;

void OpenOrClose(int iCopyQuestion[20][20], int y, int x){
	if(x > 1){
		iCopyQuestion[y][x - 1] = !iCopyQuestion[y][x - 1];
	}
	if(x < m){
		iCopyQuestion[y][x + 1] = !iCopyQuestion[y][x + 1];
	}
	if(y > 1){
		iCopyQuestion[y - 1][x] = !iCopyQuestion[y - 1][x];
	}
	if(y < n){
		iCopyQuestion[y + 1][x] = !iCopyQuestion[y + 1][x];		
	}
	iCopyQuestion[y][x] = !iCopyQuestion[y][x];
	
}


void Solve(int iQuestion[20][20], int iLoopDeep, int x, int iPressTime){
	iLoopDeep++;
	int iCopyQuestion[20][20] = {0};
	int sum = 0, temp = 0;
	
	OpenOrClose(iQuestion, 1, x);							//按下x位置的灯
	iPressTime++;												//次数+1
	if(iLoopDeep != m){											//不是最深层就再进一层
		Solve(iCopyQuestion, iLoopDeep, x + 1, iPressTime);
	}
	
	//拷贝一份按下后的灯，然后对每一行进行改变
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			iCopyQuestion[i][j] = iQuestion[i][j];
		}
	}
	//在每一行对应位置按下灯
	for(int i = 2; i <= n; i++){
		for (int j = 1; j <= m; j++){
			if(iCopyQuestion[i-1][j] == 1){
				OpenOrClose(iCopyQuestion, i, j);
				temp++;	
			}
		}
	}
	//判断最后一行是否全为0
	sum = 0;
	for (int j = 1; j <= m; j++){
		if(iCopyQuestion[n][j] == 0)
			sum += 1;
	}
	if (sum == m){
		iPressTime += temp;
		min = min < iPressTime ? min : iPressTime;
		flag = 1;
	}
		
	OpenOrClose(iQuestion, 1, x);  //把刚刚按下的x位置的灯关掉
	iPressTime--;						//关掉只是复原，所以次数要减1
	
	if(iLoopDeep != m){
		Solve(iQuestion, iLoopDeep, x + 1, iPressTime);
	}
	
	if(iLoopDeep == 1){
		iPressTime = 0;
		//在每一行对应位置按下灯
		for(int i = 2; i <= n; i++){
			for (int j = 1; j <= m; j++){
				if(iQuestion[i-1][j] == 1){
					OpenOrClose(iQuestion, i, j);
					iPressTime++;	
				}
			}
		}
		sum = 0;
		for (int j = 1; j <= m; j++){
			if(iQuestion[n][j] == 0)
				sum += 1;
		}
		if (sum == m){
			min = min < iPressTime ? min : iPressTime;
			flag = 1;
		}		
	}
		
}

int main(){
	int iQuestion[20][20] = {0};
	char a;
	scanf("%d %d", &n, &m);
	getchar();
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			scanf("%c", &a);
			iQuestion[i][j] = a - '0';
		}
		getchar();
	}
	Solve(iQuestion, 0, 1, 0);	
	
	if(flag)
		printf("%d\n",min);
	else
		printf("0\n");
	
	return 0;
}