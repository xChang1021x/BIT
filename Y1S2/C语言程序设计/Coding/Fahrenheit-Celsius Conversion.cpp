#include<stdio.h>

int main(){
	int x;
	float wendu,zhuan;
	for(int i=0;i<3;i++){
		scanf("%d %f",&x,&wendu);
		if(x==1){
			zhuan=(wendu-32)/1.8;
			printf("The Centigrade is %.2f\n",zhuan);
		}
		else if(x==2){
			zhuan=wendu*1.8+32;
			printf("The Fahrenheit is %.2f\n",zhuan);
		}
		else printf("Wrong input!\n");
	}
	return 0;
}