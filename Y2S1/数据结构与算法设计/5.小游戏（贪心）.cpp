#include<iostream>
#include<cstdio> 
#include<cstring>
#include<algorithm>
using namespace std;
 
int dp[1505][2],v[1505]; 
int lk[1505][1505];
int n; 

void dfs(int x)
{
	v[x]=1;
	for(int i=0; lk[x][i]!=-1 ; ++i)
	{
		int m=lk[x][i];
		if(!v[m])
		{
			dfs(m);
			dp[x][1]+=dp[m][0];
			dp[x][0]+=min(dp[m][0],dp[m][1]);
		}
	}
	dp[x][0]++;
}
 
int main(){
	while(scanf("%d",&n)!=EOF)
	{
		memset(dp,0,sizeof(dp));
		memset(v,0,sizeof(v));
		memset(lk,0,sizeof(lk));
		int s,t,k,r;
		for(int i=0;i<n;i++)
		{
			scanf("%d:(%d)",&s,&t);
			if(!i) r=s;
			int nu=0;
			for(int j=0;j<t;++j)
			{
				cin>>k;
				
				lk[s][nu]=k; 
				nu++;
			} 
			lk[s][nu]=-1;
		}
		dfs(r);
		cout<<min(dp[r][0],dp[r][1])<<endl;
	} 
	return 0;
}