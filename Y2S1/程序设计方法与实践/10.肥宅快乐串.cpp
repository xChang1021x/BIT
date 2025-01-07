#include<stdio.h>
#include<string.h>

int main(){
	int t;
	scanf("%d",&t);
	getchar();
	while(t--){
		char word[20010]={0};
		char A[100]="fattyhappy";
		char *p=NULL;
		char temp;
		int len,flag=0,flag2=0,flag3=0;
		int x=0,y=0,z=0,ans1=-1,ans2=-1,start=0,end=0;
		gets(word);
		p = word;
		len = strlen(word);
		end = len;
		for(p;p!=NULL;p++){
			char panDuanQu[10010]={0};
			x=0;
			flag=0;
			flag2=0;
			end=start+9;
			strncpy(panDuanQu,p,10);
		
			for(int j=0;j<10;j++){
				if(panDuanQu[j]!=A[j]){
					x+=1;
					if(flag2==0){
						y=j;
						flag2=1;
					}
					else{
						z=j;
					}
				}
				if(x>2) break;
			}
			if(x==0){
				ans1=start+3;
				ans2=start+4;
			}
			else if(x==1){
				for(int i=0;i<len;i++){
					if(i<start || i>end){
						if(word[i]==A[y]){
							ans1=i+1;
							ans2=start+y+1;
							flag3=1;
						}
					}
					if(flag3) break;
				}
			}
			else if(x==2){
				temp=panDuanQu[y];
				panDuanQu[y]=panDuanQu[z];
				panDuanQu[z]=temp;
				if(strcmp(panDuanQu,"fattyhappy")==0){
					ans1 = start+y+1;
					ans2 = start+z+1;
				}
			}
			
			if(ans1!=-1){
				break;
			}
			
			start++;
			if(len-start<10) break;
		}
		if(ans1!=-1){
			if(ans1>ans2)
				printf("%d %d\n",ans2,ans1);
			else
				printf("%d %d\n",ans1,ans2);
		}
		else printf("-1\n");
	}
}