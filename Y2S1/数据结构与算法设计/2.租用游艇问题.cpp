#include<iostream>
#define Ma_x 99999
#define Mi_x 0 
#define min(a,b) a<b?a:b
#define max(a,b) a>b?a:b 

using namespace std;

int n,w[200],dp[200][200],dq[200][200];

int sum(int i,int t){
    int k,s=0,k1;
    for(k=i;k<i+t;k++){
        k1=k%n;
        if(k1==0) k1=n;
        s=s+w[k1];  
    }
    return s;
}

int main(){
    int i,t,k;
    scanf("%d",&n);
    for(i=1;i<=n;i++){
        scanf("%d",&w[i]);
        dp[i][1]=0;
       
	}

    for(t=2;t<=n;t++){
        for(i=1;i<=n;i++){
            dp[i][t]=Ma_x;
            dq[i][t]=Mi_x; 
            for(k=1;k<t;k++){
                dp[i][t]=min(dp[i][t],dp[i][k]+dp[(i+k-1)%n+1][t-k]+sum(i,t));
                dq[i][t]=max(dq[i][t],dq[i][k]+dq[(i+k-1)%n+1][t-k]+sum(i,t));
			}
        }
    }
    int mini=Ma_x;
	int maxi=Mi_x; 
    for(i=1;i<=n;i++){
        mini=min(mini,dp[i][n]);  
		maxi=max(maxi,dq[i][n]); 
    }
    cout << mini << endl; 
    cout << maxi << endl; 
}

