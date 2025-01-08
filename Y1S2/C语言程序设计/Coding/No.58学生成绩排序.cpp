#include<stdio.h>
#include<string.h>

struct ren
{
	char name[30]={0};
	int result;
};

int main(){
	struct ren man[20];
	int max,panduan;
	int maxtomin[100]={0};
	int n;
	int x=0,count=0;
	scanf("%d",&n);
	getchar();
	for(int i=0;i<n;i++){
		x=0;
		do{
			scanf("%c",&man[i].name[x]);
		}
		while(man[i].name[x++] != ',');
		scanf("%d",&man[i].result);
		getchar();
	}
	while(count != n){
		max=0;
		for(int i=n-1;i>=0;i--){
			panduan=0;
			if(max<=man[i].result){
				for(int j=0;j<=count;j++){
					if(i==maxtomin[j]) panduan=1;
				}
				if(panduan==0){
					max=man[i].result ;
					maxtomin[count] = i;	
				}
			}
		}
		count++;
	}
	for(int i=0;i<n;i++){
		printf("%s",man[maxtomin[i]].name);
		printf("%d\n",man[maxtomin[i]].result);
	}
}