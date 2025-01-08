#include<stdio.h>

int main(){
	int n, m, temp;
	int A[100]={0};
	int B[100]={0};
	while(~scanf("%d %d", &n, &m)){
		int x=0, count=0, total=0;
		for(int i=0;i<n;i++){
			scanf("%d",&A[i]);
		}
		for(int i=0;i<m;i++){
			scanf("%d",&B[i]);
		}
		for(int i=0;i<n-1;i++){
			for(int j=i+1;j<n;j++){
				if(A[i]>A[j]){
					temp = A[i];
					A[i] = A[j];
					A[j] = temp;
				}
			}
		}
		for(int i=0;i<m-1;i++){
			for(int j=i+1;j<m;j++){
				if(B[i]>B[j]){
					temp = B[i];
					B[i] = B[j];
					B[j] = temp;
				}
			}
		}
		for(int i=0;i<n;i++){
			for( x ; x<m ; x++){
				if(B[x]>=A[i]){
					total += B[x];
					count += 1;
					x++;
					break;
				}
			}
		}
		if(count==n) printf("%d\n",total);
		else printf("bit is doomed!\n");
	}
}