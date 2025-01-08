#include<stdio.h>
#include<string.h>

int main(){
	int Num[100]={0};
	int Count[100][2]={0};
	int n,x;
	scanf("%d %d",&n,&x);
		int flag=0;
		for(int i=0;i<n;i++){
			scanf("%d",&Num[i]);
			for(int j=0;j<i+1;j++){
				if(Num[i]==Count[j][0]){
					break;
				}
				else if(j==i) Count[j][0]=Num[i];
			}
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(Num[i]==Count[j][0]){
					Count[j][1]++;
				}
			}
		}
		for(int i=0;i<n;i++){
			if(Count[i][1]>x){
				printf("%d\n",Count[i][0]);
				flag=1;
			}
		}
		if(flag==0) printf("No such element.\n");
}