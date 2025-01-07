#include<stdio.h>

int main(){
	int n,v,a,b,max,temp;
	int total=0;
	int dayFruit[5000]={0};
	scanf("%d %d",&n,&v);
	for(int i=0;i<n;i++){
		scanf("%d %d",&a,&b);
		max=a>max?a:max;
		dayFruit[a]+=b;
	}
	temp=v;
	for(int i=1;i<=max+1;i++){
		v=temp;
		if(dayFruit[i-1]>=v){
			total+=v;
			dayFruit[i-1]-=v;
			continue;
		}
		else{
			total+=dayFruit[i-1];
			v-=dayFruit[i-1];
			dayFruit[i-1]=0;
		}
		
		if(dayFruit[i]>=v){
			total+=v;
			dayFruit[i]-=v;
		}
		else{
			total+=dayFruit[i];
			dayFruit[i]=0;
		}
	}
	printf("%d\n",total);
}