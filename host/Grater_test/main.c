#include <stdio.h>
#include <stdint.h>

void wait_for_user_input();

int main()
{
	float firstNumber = 0, secondNumber = 0;

	printf("Write two (integer)numbers: \n");
	if(scanf("%f\n%f", &firstNumber, &secondNumber) == 0)
	{
		printf("Failed!\n Incorrect input\n");
		wait_for_user_input();
		return 0;
	}

	int32_t n1, n2;

	n1 = firstNumber;
	n2 = secondNumber;

	if(n1 != firstNumber || n2 != secondNumber)
		printf("Warning! This app calculates only integers\n");

	if(n1 == n2)
		printf("Numbers are equal\n");
	else if(n1 > n2)
		printf("Number %d are greater\n", n1);
	else
		printf("Number %d are greater\n", n2);


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
