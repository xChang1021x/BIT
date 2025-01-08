#include<stdio.h>
#include<stdlib.h>

struct ren{
	char name[100];
	int result[5];
	float avg;
};

struct result{
	float avg;
}kemu[4];

int main(){
	struct ren people[4] = {"wanglei",{78,90,87,92},0,
							"lihong",{88,91,89,78},0,
							"zhangli",{84,76,83,75},0,
							"liuming",{88,90,71,83},0
							};
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			people[i].avg += people[i].result[j]; 	
			kemu[i].avg += people[j].result[i];
		}
		people[i].avg /= 4.0;
		kemu[i].avg /= 4.0;
	}

	for(int i=0;i<4;i++){
		printf("%s,",people[i].name);
		if(people[i].avg == (int)people[i].avg) printf("%d\n",(int)people[i].avg);
		else printf("%.2f\n",people[i].avg );
	}
	printf("AVERAGE:");
	for(int i=0;i<4;i++){
		if(kemu[i].avg == (int)kemu[i].avg) printf("%d",(int)kemu[i].avg);
		else printf("%.2f",kemu[i].avg );
		if(i!=3) printf(",");
	}
	printf("\n");
}