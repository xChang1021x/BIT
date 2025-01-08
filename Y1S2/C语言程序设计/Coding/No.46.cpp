#include<stdio.h>
#include<math.h>

double Area(int x1,int y1,int x2,int y2,int x3,int y3){
	double area;
	area=fabs(x1*y2+x2*y3+x3*y1-y1*x2-y2*x3-y3*x1)/2.0;
	return area;
}

int main(){
	int n;
	float a;
	while(~scanf("%d",&n)){
		int m,z=0;
		int X[100]={0};
		int Y[100]={0};
		float max;
		for(int i=0;i<n;i++){
			float area[100]={0};
			scanf("%d",&m);
			for(int j=0;j<m;j++){
				scanf("%d %d",&X[j],&Y[j]);
			}
			for(int j=0;j<m-2;j++){
				for(int k=j+1;k<m-1;k++){
					for(int l=k+1;l<m;l++){
						area[z++]=Area(X[j],Y[j],X[k],Y[k],X[l],Y[l]);
						if(z==2 && area[z-1]>area[z-2]){
							area[z-2]=area[z-1];
							z=1;
						}
						else if(z==2) z=1;
					}
				}
			}
			max=area[0];
			for(int j=1;j<z;j++){
				if(max<area[j]) max=area[j];
			}
			printf("%.1f\n",max);
		}
	}
}