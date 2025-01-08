#include<stdio.h>
#include<string.h>

int main(){
	char A[100]={0};
	while(~scanf("%s",&A)){
		getchar();
		int n=strlen(A);
		int sum=0;
		int max=0,min=0;
		max=A[0]-'0';
		min=A[0]-'0';
		for(int i=2;i<n-3;i+=2){
			if(max<A[i]-'0'){
				max=A[i]-'0';
			}
			if(min>A[i]-'0'){
				min=A[i]-'0';
			}
		}
		switch(A[n-3]){
			case '+':
				sum=max+min;
				printf("%d%c%d=%d\n",max,A[n-3],min,sum);
				break;
			case '-':
				sum=max-min;
				printf("%d%c%d=%d\n",max,A[n-3],min,sum);
				break;
			case '*':
				sum=max*min;
				printf("%d%c%d=%d\n",max,A[n-3],min,sum);
				break;
			case '/':
				if(min!=0) {
					sum=max/min;
					printf("%d%c%d=%d\n",max,A[n-3],min,sum);
				}
				else printf("Error!\n");
				break;
			case '%':
				sum=max%min;
				printf("%d%c%d=%d\n",max,A[n-3],min,sum);
				break;
		}
	}
}