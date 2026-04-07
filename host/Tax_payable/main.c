#include <stdio.h>
#include <stdint.h>

void wait_for_user_input();
float calculate_payable_tax(float, int, int);

int main()
{
	float firstNumber = 0;

	printf("Write your income (integer): \n");
	if(scanf("%f", &firstNumber) == 0)
	{
		printf("Failed!\n Incorrect input\n");
		wait_for_user_input();
		return 0;
	}

	int32_t n1;

	n1 = firstNumber;

	if(n1 != firstNumber)
		printf("Warning! This app calculates only integers\n");

	float tax_payable = 0;

	if(n1 <= 9525)
		tax_payable = calculate_payable_tax(n1, 0, 0);
	else if(n1 >= 9526 && n1 <= 38700)
		tax_payable = calculate_payable_tax(n1, 12, 0);
	else if(n1 >= 38701 && n1 <= 82500)
		tax_payable = calculate_payable_tax(n1, 22, 0);
	else
		tax_payable = calculate_payable_tax(n1, 32, 1000);

	printf("You need to pay %.2f\n", tax_payable);

	wait_for_user_input();

	return 0;
}

float calculate_payable_tax(float income, int tax_rate, int fixed_tax)
{
	return income * ((float)tax_rate / 100) + fixed_tax;
}

void wait_for_user_input()
{
	printf("Press enter to exit app\n");
	while(getchar() != '\n')
	{

	}
	getchar();
}
