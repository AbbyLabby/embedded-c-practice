#include <stdio.h>

int main()
{
	int age = 0;

	printf("Write your age: \n");
	scanf("%d", &age);

	if(age >= 18)
		printf("You can vote\n");
	else
		printf("You can`t vote\n");

	while(getchar() != '\n')
	{

	}
	getchar();

	return 0;
}
