#include<stdio.h>
#include<string.h>

int f(char *a, int i, int j);

int main(){
	char a[250];
	gets(a);
	int len = strlen(a);
	int i = 0, j = len - 1;
	int p = f(a, i, j);
	if(p == len / 2)
		printf("YES\n");
	else
		printf("NO\n");
	return 0;
}

int f(char *a, int i, int j){
	if(j <= i)
		return 0;
	else if(i + 1 == j || i + 2 == j){
		if(a[i] == a[j])
			return 1;
		else
			return 0;
	}
	else if(i + 2 < j){
		if(a[i] == a[j]){
			i++;
			j--;
			return 1 + f(a, i, j);
		}
		else{
			i++;
			j--;
			return f(a, i, j);
		}
	}
	else return 0;
}