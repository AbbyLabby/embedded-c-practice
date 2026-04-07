#include <stdio.h>
#include <stdint.h>

void wait_for_user_input();

int main()
{
	int value = 0;
	int maxValue = 20;

	while(value <= maxValue)
	{
		printf("Value %d\n", value);
		value++;
	}

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
