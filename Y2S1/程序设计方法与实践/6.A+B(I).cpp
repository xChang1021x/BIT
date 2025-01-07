#include<stdio.h>
#include<string.h>

int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		char numA[100010]={0};
		char numB[100010]={0};
		char reverseA[100010]={0};
		char reverseB[100010]={0};
		char total[100010]={0};
		char temp;
		int lenA,lenB,lenTotal,minLen,maxLen;
		scanf("%s",numA);
		scanf("%s",numB);
		lenA=strlen(numA);
		lenB=strlen(numB);
		minLen=lenA<lenB?lenA:lenB;
		maxLen=lenA>lenB?lenA:lenB;
		for(int i=0;i<lenA;i++){
			reverseA[i]=numA[lenA-i-1];
		}
		for(int i=0;i<lenB;i++){
			reverseB[i]=numB[lenB-i-1];
		}
		for(int i=0;i<maxLen;i++){
			if(i<minLen)
				total[i]+=reverseA[i]+reverseB[i]-'0';
			else
				total[i]+=reverseA[i]+reverseB[i];
				
			if(total[i]>='2'){
				total[i]-=2;
				total[i+1]+=1;
			}
		}
		if(total[maxLen]!=0)
			total[maxLen]+='0';
		if(total[maxLen]>='2'){
			total[maxLen+1]+='1';
			total[maxLen]-=2;
		}
		lenTotal=strlen(total);
		printf(" ");
		for(int i=0;i<lenTotal-lenA+1;i++){
			printf(" ");
		}
		printf("%s\n",numA);
		printf("+");
		
		for(int i=0;i<lenTotal-lenB+1;i++){
			printf(" ");
		}
		printf("%s\n",numB);
		for(int i=0;i<lenTotal+2;i++){
			printf("-");			
		}
		printf("\n");
		printf("  ");
		for(int i=0;i<lenTotal;i++){
			printf("%c",total[lenTotal-1-i]);
		}
		printf("\n");
	}
}