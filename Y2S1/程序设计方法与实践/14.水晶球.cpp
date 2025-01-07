#include <stdio.h>
#include <stdlib.h>

struct Ball{
	int x, y, z;
	int no;
} ball[100010];

int cmp(const void* a, const void* b)
{
    struct Ball* pa = (struct Ball*)a;
    struct Ball* pb = (struct Ball*)b;
    int num1 = pa->y;
    int num2 = pb->y;
    if(pa->y == pb->y){
    	if(pa->z == pb->z){
    		return (int)pa->x - pb->x;
		}
		else return (int)pa->z - pb->z;
	}
	else
    	return (int)num1 - num2;   // 从小到大，
}

int main(){
	int n, ans = -1, ans2 = -1, sum, min = 0, max = 0;
	int temp;
	int min2 = 0;
	int ans3 = 0, ans4 = 0;
	int flag = 1, flag2 = 1;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		scanf("%d %d %d", &ball[i].x, &ball[i].y, &ball[i].z);
		ball[i].no = i;
		if (ball[i].x >= ball[i].y && ball[i].x >= ball[i].z){
			if (ball[i].y >= ball[i].z){
				temp = ball[i].z;
				ball[i].z = ball[i].x;
				ball[i].x = temp;				
			}
			else{
				temp = ball[i].x;
				ball[i].x = ball[i].y;
				ball[i].y = ball[i].z;
				ball[i].z = temp;
			}
		}
		else if (ball[i].x >= ball[i].y){
			temp = ball[i].y;
			ball[i].y = ball[i].x;
			ball[i].x = temp;
		}
		else if (ball[i].x >= ball[i].z){
			temp = ball[i].y;
			ball[i].y = ball[i].x;
			ball[i].x = ball[i].z;
			ball[i].z = temp;
		}
		else if (ball[i].y >= ball[i].z){
			temp = ball[i].y;
			ball[i].y = ball[i].z;
			ball[i].z = temp;
		}
	}
	
	qsort(ball, n+1, sizeof(Ball), cmp);
	
	for (int i = 1; i <= n; i++){
		if(ball[i].x > max){
			ans = ball[i].no;
			max = ball[i].x;
		}
	}
	for (int i = n; i > 1; i--){
			
		if (ball[i].z == ball[i-1].z && ball[i].y == ball[i-1].y){
			sum = ball[i].x + ball[i-1].x;
			min = sum < ball[i].y ? sum : ball[i].y;
			if (min > max){
				ans = ball[i-1].no;
				ans2 = ball[i].no;
				flag = 2;
				break;
			}
		}
	}
	
	if (flag == 2){
		if (ans2 < ans)
			printf("2\n%d %d\n", ans2, ans);
		else
			printf("2\n%d %d\n", ans, ans2);
	}
	else{
		printf("%d\n", flag);
		printf("%d\n", ans);		
	}
	return 0;
}

//	printf("\n");
//	for (int i = 1; i <= n; i++)
//		printf("%d %d %d\n", ball[i].x, ball[i].y, ball[i].z);

//7
//10 9 3
//10 9 1
//8 9 3
//10 9 1
//8 9 2
//8 9 1
//8 9 2
