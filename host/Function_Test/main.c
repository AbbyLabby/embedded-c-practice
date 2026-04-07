#include <stdio.h>

int main()
{
	int a, b, c;

	printf("Enter number a: \n");
	scanf("%d", &a);
	printf("Enter number b: \n");
	scanf("%d", &b);
	printf("Enter number c: \n");
	scanf("%d", &c);

	int avg = 0;

	avg = (a + b + c) / 3;
	printf("Average number: %d\n", avg);

	while(getchar() != '\n')
	{

	}
	getchar();
	return 0;
}
