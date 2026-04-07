#include <stdio.h>
#include <stdint.h>

void wait_for_user_input();

int main()
{
	float n1 = 0, n2 = 0;

	printf("Write two numbers(integer): \n");

	if(scanf("%f\n%f", &n1, &n2) == 0)
	{
		printf("Failed!\n Incorrect input\n");
		wait_for_user_input();
		return 0;
	}

	uint32_t val1 = 0, val2 = 0;

	val1 = n1;
	val2 = n2;

	if(val1 != n1 || val2 != n2)
		printf("Warning! This app works only with integers\n");

	printf("Bitwise operation &: %d\n", val1 & val2);
	printf("Bitwise operation |: %d\n", val1 | val2);
	printf("Bitwise operation ^: %d\n", val1 ^ val2);
	printf("Bitwise operation ~ for first value: %d\n", ~val1);
	printf("Bitwise operation ~ for second value: %d\n", ~val2);

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
