#include<stdio.h>

struct result{
	int xuehao;
	int chengji1,chengji2,chengji3;
};

int main(){
	struct result man[3]= {{1,90,80,70},
							{2,85,75,95},
							{3,88,84,65},
							};
	char A[10]={0};
	float avg[3]={0};
	float max;
	int n;
	scanf("%s",A);
	if(A[0]=='m' && A[1] == 'a' && A[2] == 'x'){
		for(int i=0;i<3;i++){
			avg[i]=(man[i].chengji1 + man[i].chengji2 + man[i].chengji3)/3.0;
		}
		max=avg[0];
		for(int i=0;i<3;i++){
			if(max<avg[i]) max=avg[i];
		}
		for(int i=0;i<3;i++){
			if(max==avg[i]) printf("%d\n",i+1);
		}
	}
	else{
		n = A[0]-'0'-1;
		if(n<3) printf("%g",(man[n].chengji1+man[n].chengji2+man[n].chengji3)/3.0 );
		else printf("0\n");
	}
}