#include<stdio.h>
#include<string.h>

int main(){
	char numA[10000]={0};
	char numB[10000]={0};
	char total[10000]={0};
	int lenA,lenB,lenTotal,dcpA=-2,dcpB=-2,dcpTotal=-1;
	int max,max2,max3,max4;
	int qianMian=0,houMian=0;
	int lenIntA,lenIntB,lenDcmA,lenDcmB,lenDcmTotal;
	int k=0,a=0,b=0,c=0,x=0,y=0,z=0,flag=0,flag2=0,flag3=0;
	int tailA=-1,tailB=-1;
	scanf("%s",numA);
	scanf("%s",numB);
	lenA=strlen(numA);
	lenB=strlen(numB);
	tailA=lenA-1;
	tailB=lenB-1;
	max = lenA>lenB?lenA:lenB;
	
	for(int i=0;i<lenA;i++){
		if(numA[i]!='0') a=i;
	}
	for(int i=0;i<lenB;i++){
		if(numB[i]!='0') b=i;
	}
	for(int i=0;i<lenA;i++){
		if(numA[i]=='.'){
			dcpA=i;
		}
	}
	for(int i=0;i<lenB;i++){
		if(numB[i]=='.'){
			dcpB=i;
		}
	}

	if(dcpA==-2 && dcpB==-2){
		lenDcmA=-1;
		lenDcmB=-1;
		lenIntA=lenA-a;
		lenIntB=lenB-b;
		c = max;
	}
	else if(dcpA == -2){
		lenDcmA = -1;
		lenDcmB = tailB - dcpB;
		lenIntA = lenA - a;
		lenIntB = dcpB - b;
		c = lenA>dcpB?lenA:dcpB;
		c += lenDcmB + 1;
	}
	else if(dcpB == -2){
		lenDcmA = tailA - dcpA;
		lenDcmB = -1;
		lenIntA = dcpA - a;
		lenIntB = lenB - b;
		c = lenB>dcpA?lenB:dcpA;
		c += lenDcmA + 1;
	}
	else{
		lenDcmA = tailA - dcpA;
		lenDcmB = tailB - dcpB;
		lenIntA = dcpA - a;
		lenIntB = dcpB - b;
		c = dcpA>dcpB?dcpA:dcpB;
		c += lenDcmA>lenDcmB?lenDcmA:lenDcmB;
		c++;
		flag3 = 1;
	}

	lenTotal = c;
	max2 = lenDcmA>lenDcmB?lenDcmA:lenDcmB; 
	max3 = lenIntA+a>lenIntB+b?lenIntA+a:lenIntB+b;
	max4 = dcpA>dcpB?dcpA:dcpB;
	
	x=lenDcmB-lenDcmA;
	y=lenDcmA-lenDcmB;
	if(x<0) x=0;
	if(y<0) y=0;
	
	while(c>=0){
		if(k==max2 && (dcpA != -1 || dcpB != -1)){
			dcpTotal=c;
			total[c] += '.';
			if(total[c]!='.'){
				total[c]--;
				total[c-1]++;
			}
			
		}
		else if(numA[tailA+x-k]==0 || numB[tailB+y-k]==0){
			total[c] += numA[tailA+x-k] + numB[tailB+y-k];
		}
		else{
			total[c] += numA[tailA+x-k] + numB[tailB+y-k] -'0';
		}
		
		
		
		if(total[c]>'9'){
			total[c]-=10;
			total[c-1]++;
		}
		c--;
		k++;
	}
	flag2=0;
	if(total[c+1]==1){
		total[c+1]='1';
		flag2=1;
	}

	if(dcpA==-2 && dcpB==-2){
		dcpA = lenA;
		dcpB = lenB;
	}
	else if(dcpA == -2){
		dcpA = lenA;
	}
	else if(dcpB == -2){
		dcpB = lenB;
	}

	printf("   ");
	if(flag2)
		printf(" ");
	for(int i=0;i<max3-dcpA;i++){
		printf(" ");
	}
	printf("%s",numA);
	for(int i=0;i<max2-lenDcmA;i++){
		printf(" ");
	}
	printf("\n");
	
	printf("+  ");
	if(flag2)
		printf(" ");
	for(int i=0;i<max3-dcpB;i++){
		printf(" ");
	}
	printf("%s",numB);
	for(int i=0;i<max2-lenDcmB;i++){
		printf(" ");
	}
	printf("\n");
	
	if(flag2)
		printf("-");
	for(int i=0;i<max2+max3+4;i++){
		printf("-");
	}
	printf("\n");
	
	flag = 0;
	

	printf("  ");
	if(flag2)
		printf(" ");
	for(int i=0;i<lenTotal+1;i++){
		if(total[i]>'0' && total[i]<='9' && flag==0 || i==dcpTotal-1 || i==lenTotal-1){
			printf("%c",total[i]);
			flag=1;
		}
		else if((total[i]>='0' && total[i]<='9' || total[i] == '.') && flag==1){
			printf("%c",total[i]);
		}
		else
			printf(" ");
	}
	printf("\n");

	return 0;
}