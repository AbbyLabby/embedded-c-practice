#include <stdio.h>

int main()
{
	int a, b, c;

	printf("Enter 3 numbers: \n");
	scanf("%d %d %d", &a, &b, &c);

	int avg = 0;

	avg = (a + b + c) / 3;
	printf("Average number: %d\n", avg);

	while(getchar() != '\n')
	{

	}
	getchar();
	return 0;
}
