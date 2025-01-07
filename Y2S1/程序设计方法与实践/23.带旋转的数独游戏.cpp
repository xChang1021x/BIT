#include<iostream>
#include<algorithm>
#include<cstring>
#include<utility>
#include<queue>

using namespace std;

char Sudoku[20][20] = {0};
int ans = 2147483647;
int step[4][4] = {0};
int check[20] = {0};
int check2[20] = {0};
int check3[20] = {0};

int CheckSudoku(){
		for (int j = 0; j < 16; j++){
			if (Sudoku[i][j] == '1'){
				check[0]++;
				if (check[0] > 1) {
					memset(check, 0, sizeof(check));
					return 0;	
				}
			}
			else if (Sudoku[i][j] == '2'){
				check[1]++;
				if (check[1] > 1) {
					memset(check, 0, sizeof(check));
					return 0;	
				}
			}
			else if (Sudoku[i][j] == '3'){
				check[2]++;
				if (check[2] > 1) {
					memset(check, 0, sizeof(check));
					return 0;	
				}
			}
			else if (Sudoku[i][j] == '4'){
				check[3]++;
				if (check[3] > 1) {
					memset(check, 0, sizeof(check));
					return 0;	
				}
			}
			else if (Sudoku[i][j] == '5'){
				check[4]++;
				if (check[4] > 1) {
					memset(check, 0, sizeof(check));
					return 0;	
				}
			}
			else if (Sudoku[i][j] == '6'){
				check[5]++;
				if (check[5] > 1) {
					memset(check, 0, sizeof(check));
					return 0;	
				}
			}
			else if (Sudoku[i][j] == '7'){
				check[6]++;
				if (check[6] > 1) {
					memset(check, 0, sizeof(check));
					return 0;	
				}
			}
			else if (Sudoku[i][j] == '8'){
				check[7]++;
				if (check[7] > 1) {
					memset(check, 0, sizeof(check));
					return 0;	
				}
			}
			else if (Sudoku[i][j] == '9'){
				check[8]++;
				if (check[8] > 1) {
					memset(check, 0, sizeof(check));
					return 0;	
				}
			}
			else if (Sudoku[i][j] == 'A'){
				check[9]++;
				if (check[9] > 1) {
					memset(check, 0, sizeof(check));
					return 0;	
				}
			}
			else if (Maze[i][j] == 'B'){
				check[10]++;
				if (check[10] > 1) {
					memset(check, 0, sizeof(check));
					return 0;	
				}
			}
			else if (Maze[i][j] == 'C'){
				check[11]++;
				if (check[11] > 1) {
					memset(check, 0, sizeof(check));
					return 0;	
				}
			}
			else if (Maze[i][j] == 'D'){
				check[12]++;
				if (check[12] > 1) {
					memset(check, 0, sizeof(check));
					return 0;	
				}
			}
			else if (Maze[i][j] == 'E'){
				check[13]++;
				if (check[13] > 1) {
					memset(check, 0, sizeof(check));
					return 0;	
				}
			}
			else if (Maze[i][j] == 'F'){
				check[14]++;
				if (check[14] > 1) {
					memset(check, 0, sizeof(check));
					return 0;	
				}
			}
			else if (Maze[i][j] == '0'){
				check[15]++;
				if (check[15] > 1) {
					memset(check, 0, sizeof(check));
					return 0;	
				}
			}
			

		}
		memset(check, 0, sizeof(check));
		memset(check2, 0, sizeof(check2));
	}
	
	return 1;
}

void spin(int n, int x, int y){
	char temp1, temp2, temp3, temp4;
	for (int i = 0; i < n; i++){
		temp1 = Maze[0+(x-1)*4][0+(y-1)*4];
		temp2 = Maze[0+(x-1)*4][1+(y-1)*4];
		temp3 = Maze[0+(x-1)*4][2+(y-1)*4];
		temp4 = Maze[0+(x-1)*4][3+(y-1)*4];
		
		Maze[0+(x-1)*4][0+(y-1)*4] = Maze[0+(x-1)*4][3+(y-1)*4];
		Maze[0+(x-1)*4][1+(y-1)*4] = Maze[1+(x-1)*4][3+(y-1)*4];
		Maze[0+(x-1)*4][2+(y-1)*4] = Maze[2+(x-1)*4][3+(y-1)*4];
		Maze[0+(x-1)*4][3+(y-1)*4] = Maze[3+(x-1)*4][3+(y-1)*4];
		
		Maze[0+(x-1)*4][3+(y-1)*4] = Maze[3+(x-1)*4][3+(y-1)*4];
		Maze[1+(x-1)*4][3+(y-1)*4] = Maze[3+(x-1)*4][2+(y-1)*4];
		Maze[2+(x-1)*4][3+(y-1)*4] = Maze[3+(x-1)*4][1+(y-1)*4];
		Maze[3+(x-1)*4][3+(y-1)*4] = Maze[3+(x-1)*4][0+(y-1)*4];
		
		Maze[3+(x-1)*4][3+(y-1)*4] = Maze[3+(x-1)*4][0+(y-1)*4];
		Maze[3+(x-1)*4][2+(y-1)*4] = Maze[2+(x-1)*4][0+(y-1)*4];
		Maze[3+(x-1)*4][1+(y-1)*4] = Maze[1+(x-1)*4][0+(y-1)*4];
		Maze[3+(x-1)*4][0+(y-1)*4] = Maze[0+(x-1)*4][0+(y-1)*4];
		
		Maze[3+(x-1)*4][0+(y-1)*4] = temp1;
		Maze[2+(x-1)*4][0+(y-1)*4] = temp2;
		Maze[1+(x-1)*4][0+(y-1)*4] = temp3;
		Maze[0+(x-1)*4][0+(y-1)*4] = temp4;		
	}
}

void Dfs(int y, int move){
	int flag = 0;
	if (y != 3){					//判断是否进入到最后的方阵
		Dfs(x, y+1, move);			
	}
	
	flag = CheckSudoku(); 					//该方阵无旋转时检查一次

	if (flag){
		ans = move;
		exit(0);
	}
	FlipSudoku(x, y); 					//旋转方阵
	step[x][y]++;
	move++;
	
	flag = CheckSudoku();
	if (flag){
		ans = move;
		exit(0);
	}
	if (y != 3){				
		Dfs(x, y+1, move);			
	}
	else if(x != 3){
		Dfs(x+1, 0, move);
	}
		
	FlipSudoku(x,y);
	step[x][y]++;
	move++;			
	flag = CheckSudoku();
	if (flag){
		ans = move;
		exit(0);
	}
				
	if (y != 3){				
		Dfs(x, y+1, move);			
	}
	else if(x != 3){
		Dfs(x+1, 0, move);
	}
	
	FlipSudoku(x,y);
	step[x][y]++;
	move++;				
	flag = CheckSudoku();
	if (flag){
		ans = move;
		exit(0);
	}			
	if (y != 3){				
		Dfs(x, y+1, move);			
	}
	else if(x != 3){
		Dfs(x+1, 0, move);
	}
	
	FlipSudoku(x,y);
	step[x][y]-=3;
	move-=3;				
	flag = CheckSudoku();
	if (flag){
		ans = move;
		exit(0);
	}			
	
}

int main(){
	int n;
	scanf("%d", &n);
	getchar();
	while(n--){
		memset(Sudoku, 0, sizeof(Sudoku));
		ans = 0;
		for (int i = 0; i < 16; i++){
			for (int j = 0; j < 16; j++){
				scanf("%c", &Sudoku[i][j]);
			}
			getchar();
		}	
		Dfs(0,0,0);
		
		printf("%d\n", ans);
	}
}



/*
			if (Sudoku[j][i] == '1'){
				check2[0]++;
				if (check2[0] > 1) {
					memset(check2, 0, sizeof(check2));
					return 0;	
				}
			}
			else if (Sudoku[j][i] == '2'){
				check2[1]++;
				if (check2[1] > 1) {
					memset(check2, 0, sizeof(check2));
					return 0;	
				}
			}
			else if (Sudoku[j][i] == '3'){
				check2[2]++;
				if (check2[2] > 1) {
					memset(check2, 0, sizeof(check2));
					return 0;	
				}
			}
			else if (Sudoku[j][i] == '4'){
				check2[3]++;
				if (check2[3] > 1) {
					memset(check2, 0, sizeof(check2));
					return 0;	
				}
			}
			else if (Sudoku[j][i] == '5'){
				check2[4]++;
				if (check2[4] > 1) {
					memset(check2, 0, sizeof(check2));
					return 0;	
				}
			}
			else if (Sudoku[j][i] == '6'){
				check2[5]++;
				if (check2[5] > 1) {
					memset(check2, 0, sizeof(check2));
					return 0;	
				}
			}
			else if (Sudoku[j][i] == '7'){
				check2[6]++;
				if (check2[6] > 1) {
					memset(check2, 0, sizeof(check2));
					return 0;	
				}
			}
			else if (Sudoku[j][i] == '8'){
				check2[7]++;
				if (check2[7] > 1) {
					memset(check2, 0, sizeof(check2));
					return 0;	
				}
			}
			else if (Sudoku[j][i] == '9'){
				check2[8]++;
				if (check2[8] > 1) {
					memset(check2, 0, sizeof(check2));
					return 0;	
				}
			}
			else if (Sudoku[j][i] == 'A'){
				check2[9]++;
				if (check2[9] > 1) {
					memset(check2, 0, sizeof(check2));
					return 0;	
				}
			}
			else if (Sudoku[j][i] == 'B'){
				check2[10]++;
				if (check2[10] > 1) {
					memset(check2, 0, sizeof(check2));
					return 0;	
				}
			}
			else if (Sudoku[j][i] == 'C'){
				check2[11]++;
				if (check2[11] > 1) {
					memset(check2, 0, sizeof(check2));
					return 0;	
				}
			}
			else if (Sudoku[j][i] == 'D'){
				check2[12]++;
				if (check2[12] > 1) {
					memset(check2, 0, sizeof(check2));
					return 0;	
				}
			}
			else if (Sudoku[j][i] == 'E'){
				check2[13]++;
				if (check2[13] > 1) {
					memset(check2, 0, sizeof(check2));
					return 0;	
				}
			}
			else if (Sudoku[j][i] == 'F'){
				check2[14]++;
				if (check2[14] > 1) {
					memset(check2, 0, sizeof(check2));
					return 0;	
				}
			}
			else if (Sudoku[j][i] == '0'){
				check2[15]++;
				if (check2[15] > 1) {
					memset(check2, 0, sizeof(check2));
					return 0;	
				}
			}
*/