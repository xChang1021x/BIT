#include<stdio.h>
#include<string.h>

int main(){
	char A[10][5]={0};
	char B[10][5]={0};
	int temp;
	while(~scanf("%s %s %s",A[0],A[1],A[2])){
		int a[10]={0};
		int b[10]={0};
		int a2[10]={0};
		int b2[10]={0};	
		getchar();
		scanf("%s %s %s",B[0],B[1],B[2]);
		getchar();
		int panduan=0;
		A[3][0]=A[0][0];
		A[3][1]=A[0][1];
		A[3][2]=A[0][2];
		B[3][0]=B[0][0];
		B[3][1]=B[0][1];
		B[3][2]=B[0][2];
		for(int i=0;i<3;i++){
			if(A[i][0]==A[i+1][0] && A[i][1]==A[i+1][1] && A[i][2]==A[i+1][2]){
				printf("Input Error!\n");
				panduan=1;
			}
			if(B[i][0]==B[i+1][0] && B[i][1]==B[i+1][1] && B[i][2]==B[i+1][2]){
				printf("Input Error!\n");
				panduan=1;
			}
		}
		for(int i=0;i<3;i++){
			switch(A[i][0]){
				case 'H':
					a[i]+=100000;
					break;
				case 'S':
					a[i]+=10000;
					break;
				case 'D':
					a[i]+=1000;
					break;
				case 'C':
					a[i]+=100;
					break;
				default :
					printf("Input Error!\n");
					panduan=1;
					break;
			}
			if(strlen(A[i])==3 && A[i][1]=='1' && A[i][2]=='0'){
				a[i]+=10;
			}
			else switch(A[i][1]){
				case 'A':
					a[i]+=14;
					break;
				case '2':
					a[i]+=2;
					break;
				case '3':
					a[i]+=3;
					break;
				case '4':
					a[i]+=4;
					break;
				case '5':
					a[i]+=5;
					break;
				case '6':
					a[i]+=6;
					break;
				case '7':
					a[i]+=7;
					break;
				case '8':
					a[i]+=8;
					break;
				case '9':
					a[i]+=9;
					break;
				case 'J':
					a[i]+=11;
					break;
				case 'Q':
					a[i]+=12;
					break;
				case 'K':
					a[i]+=13;
					break;
				default:
					printf("Input Error!\n");
					panduan=1;
					break;
			}
		}
		for(int i=0;i<3;i++){
			switch(B[i][0]){
				case 'H':
					b[i]+=100000;
					break;
				case 'S':
					b[i]+=10000;
					break;
				case 'D':
					b[i]+=1000;
					break;
				case 'C':
					b[i]+=100;
					break;
				default :
					printf("Input Error!\n");
					panduan=1;
					break;
			}
			if(strlen(B[i])==3 && B[i][1]=='1' && B[i][2]=='0'){
				b[i]+=10;
			}
			else switch(B[i][1]){
				case 'A':
					b[i]+=14;
					break;
				case '2':
					b[i]+=2;
					break;
				case '3':
					b[i]+=3;
					break;
				case '4':
					b[i]+=4;
					break;
				case '5':
					b[i]+=5;
					break;
				case '6':
					b[i]+=6;
					break;
				case '7':
					b[i]+=7;
					break;
				case '8':
					b[i]+=8;
					break;
				case '9':
					b[i]+=9;
					break;
				case 'J':
					b[i]+=11;
					break;
				case 'Q':
					b[i]+=12;
					break;
				case 'K':
					b[i]+=13;
					break;
				default:
					printf("Input Error!\n");
					panduan=1;
					break;
			}
		}
		if(panduan==1){
			continue;
		}
		if(a[0]>=a[1]){
			if(a[1]>=a[2]){
				a2[0]=0;
				a2[1]=1;
				a2[2]=2;	
			}
			else if(a[2]<=a[0]){
				a2[0]=0;
				a2[1]=2;
				a2[2]=1;
			}
			else{
				a2[0]=2;
				a2[1]=0;
				a2[2]=1;
			}
		}
		else if(a[1]>=a[2]){
			if(a[0]>a[2]){
				a2[0]=1;
				a2[1]=0;
				a2[2]=2;
			}
			else{
				a2[0]=1;
				a2[1]=2;
				a2[2]=0;
			}
		}
		else{
			a2[0]=2;
			a2[1]=1;
			a2[2]=0;
		}
		if(b[0]>=b[1]){
			if(b[1]>=b[2]){
				b2[0]=0;
				b2[1]=1;
				b2[2]=2;	
			}
			else if(b[2]<=b[0]){
				b2[0]=0;
				b2[1]=2;
				b2[2]=1;
			}
			else{
				b2[0]=2;
				b2[1]=0;
				b2[2]=1;
			}
		}
		else if(b[1]>=b[2]){
			if(b[0]>b[2]){
				b2[0]=1;
				b2[1]=0;
				b2[2]=2;
			}
			else{
				b2[0]=1;
				b2[1]=2;
				b2[2]=0;
			}
		}
		else{
			b2[0]=2;
			b2[1]=1;
			b2[2]=0;
		}
		for(int i=0;i<3;i++){
			if(a[a2[i]]>b[b2[i]]){
				printf("Winner is A!\n");
				break;
			}
			else if(a[a2[i]]<b[b2[i]]){
				printf("Winner is B!\n");
				break;
			}
			else if(i==2){
				printf("Winner is X!\n");
			}
		}
		printf("A: %s %s %s\n",A[a2[0]],A[a2[1]],A[a2[2]]);
		printf("B: %s %s %s\n",B[b2[0]],B[b2[1]],B[b2[2]]);
	}
}