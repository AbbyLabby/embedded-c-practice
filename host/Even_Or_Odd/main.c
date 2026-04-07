#include <stdio.h>
#include <stdint.h>

void wait_for_user_input();

int main()
{
	float n1 = 0;

	printf("Write a number(integer): \n");

	if(scanf("%f", &n1) == 0)
	{
		printf("Failed!\n Incorrect input\n");
		wait_for_user_input();
		return 0;
	}

	uint32_t val1 = 0;

	val1 = n1;

	if(val1 != n1)
		printf("Warning! This app works only with integers\n");

	if(val1 & 1)
		printf("number is odd\n");
	else
		printf("number is even\n");

	wait_for_user_input();

	return 0;
}

void wait_for_user_input()
{
	printf("Press enter to exit app\n");
	while(getchar() != '\n')
	{

	}
	getchar();
}
