#include<stdio.h>

int main(){
	int A[3][4]={0};
	float max[3]={0};
	float temp;
	float avg[3]={0};
	for(int i=0;i<3;i++){
		for(int j=0;j<4;j++){
			scanf("%d",&A[i][j]);
			avg[i]+=A[i][j];
		}
		avg[i]/=4.0;
	}
	max[0]=avg[0];
	max[1]=avg[1];
	max[2]=avg[2];
	for(int i=0;i<2;i++){
		for(int j=i+1;j<3;j++){
			if(max[i]<max[j]){
				temp = max[i];
				max[i] = max[j];
				max[j] = temp;
			}
		}
	}
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(max[i]==avg[j]) max[i]=j;
		}
	}
	for(int i=0;i<3;i++){
		for(int j=0;j<4;j++){
			printf("%d",A[(int)max[i]][j]);
			if(j!=3) printf(",");
		}
		printf("\n");
	}
}