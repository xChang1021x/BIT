#include<stdio.h>
#include<math.h>

int main(){
	int T;
	scanf("%d", &T);
	while (T--){
		int n, m;
		int next, count, flag;
		scanf("%d %d", &n, &m);
		n -= m + 1;
		
		if (n < 0){
			printf("0\n");
			continue;
		}
		if (n == 0){
			printf("1\n");
			continue;
		}
		next = 1;
		count = 1;
		flag = 1;
		while (n > 0){
			if (next > m || n == 0)	break;
			int need = (int)pow(2, next) - 1;
			
			if (n - need > 0){
				count += pow(2, next-1);
				if(flag) next++;
				n -= need;
			}
			else if (n - need == 0){
				count += pow(2, next-1);
				break;
			}
			else if (n - need < 0){
				flag = 0;
				next--;
				n--;
			}	
		}
		printf("%lld\n", count);		
	}
}