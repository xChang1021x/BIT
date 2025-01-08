#include<stdio.h>

int main(){
	int n;
	while(~scanf("%d",&n)){
		int A[100]={0};
		int length[100][5]={0};
		int k=0,x=0,y=0;
		int panduan=0,max=0;
		for(int i=0;i<n;i++){
			scanf("%d",&A[i]);
		}
		for(int i=0;i<n-1;i++){
			if(A[i]==A[i+1]){
				panduan=1;
				length[x][1]=i;
				while(A[i]==A[i+1]){
					length[x][0]+=1;
					i++;
				}
				length[x][2]=i;
				x++;
			}
		}
		max=length[0][0];
		for(int i=0;i<x;i++){
			if(max<length[i][0]) max=length[i][0];
		}
		for(int i=0;i<x;i++){
			if(max==length[i][0]){
				y=i;
				break;
			}
		}
		if(panduan)printf("The longest equal number list is from %d to %d.\n",length[y][1],length[y][2]);
		else printf("No equal number list.\n");
	}
}