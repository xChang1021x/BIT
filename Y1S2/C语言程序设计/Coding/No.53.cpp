#include <stdio.h>
 
int main() {
	int y, m, d, sum_d = 0, shang, yu, i, a[20] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	scanf("%d %d %d", &y, &m, &d);
	for (i = 2012; i < y; i++) {
		if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0)
			sum_d = sum_d + 366;
		else
			sum_d = sum_d + 365;
	}
	if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0)
		a[2] = 29;
	for (i = 1; i < m; i++) {
		sum_d = sum_d + a[i];
	}
	sum_d = sum_d + d - 99;
	shang = sum_d / 7, yu = sum_d % 7;
	if (yu == 6 || yu == 0)
		printf("Free.\n");
	else {
		int p = (shang / 13) % 5, j = 2;
		for (; j - p + yu <= 0;)
			p = p - 5;
		for (; j - p + yu > 5;)
			j = j - 5;
		switch (yu) {
			case 1:
				printf("%d and %d.\n", j - p + 1, (j - p + 1 + 5) % 10);
				break;
			case 2:
				printf("%d and %d.\n", j - p + 2, (j - p + 2 + 5) % 10);
				break;
			case 3:
				printf("%d and %d.\n", j - p + 3, (j - p + 3 + 5) % 10);
				break;
			case 4:
				printf("%d and %d.\n", j - p + 4, (j - p + 4 + 5) % 10);
				break;
			case 5:
				printf("%d and %d.\n", j - p + 5, (j - p + 5 + 5) % 10);
				break;
		}
	}
	return 0;
}