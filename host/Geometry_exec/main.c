#include <stdio.h>
#include <stdint.h>

float triangle_calculation();
float trapezoid_calculation();
float circle_calculation();
float square_calculation();
float rectangle_calculation();

void wait_for_user_input();

int main()
{
	int8_t opCode = 0;

	printf("To calculate area of a geometrical figures enter a figure code: \n");
	printf("Triangle ==> t\n");
	printf("Trapezoid ==> z\n");
	printf("Circle ==> c\n");
	printf("Square ==> s\n");
	printf("Rectangle ==> r\n");

	if(scanf("%c", &opCode) == 0)
	{
		printf("Failed!\n Incorrect input\n");
		wait_for_user_input();
		return 0;
	}

	float result = 0;

	switch(opCode){
	case 't':
		result = triangle_calculation();
		break;
	case 'z':
		result = trapezoid_calculation();
		break;
	case 'c':
		result = circle_calculation();
		break;
	case 's':
		result = square_calculation();
		break;
	case 'r':
		result = rectangle_calculation();
		break;
	default:
		printf("Failed!\n Incorrect input\n");
		wait_for_user_input();
		return 0;
		break;
	}

	printf("Result: %.2f\n", result);

	wait_for_user_input();

	return 0;
}

float triangle_calculation()
{
	float base = 0, height = 0;

	printf("Triangle calculation area\n");
	printf("Enter base(b): \n");

	if(scanf("%f", &base) == 0)
	{
		printf("Failed!\n Incorrect input\n");
		wait_for_user_input();
		return 0;
	}

	printf("Enter height(h): \n");

	if(scanf("%f", &height) == 0)
	{
		printf("Failed!\n Incorrect input\n");
		wait_for_user_input();
		return 0;
	}

	return (base * height) / 2;
}

float trapezoid_calculation()
{
	float a_base = 0, b_base = 0, height = 0;

	printf("Trapezoid calculation area\n");
	printf("Enter a base(a): \n");

	if(scanf("%f", &a_base) == 0)
	{
		printf("Failed!\n Incorrect input\n");
		wait_for_user_input();
		return 0;
	}

	printf("Enter b base(b): \n");

	if(scanf("%f", &b_base) == 0)
	{
		printf("Failed!\n Incorrect input\n");
		wait_for_user_input();
		return 0;
	}

	printf("Enter height(h): \n");

	if(scanf("%f", &height) == 0)
	{
		printf("Failed!\n Incorrect input\n");
		wait_for_user_input();
		return 0;
	}

	return ((a_base + b_base) / 2) * height;
}

float circle_calculation()
{
	float radius = 0;

	printf("Circle calculation area\n");
	printf("Enter radius(r): \n");

	if(scanf("%f", &radius) == 0)
	{
		printf("Failed!\n Incorrect input\n");
		wait_for_user_input();
		return 0;
	}

	return 3.14 * radius;
}

float square_calculation()
{
	float side = 0;

	printf("Square calculation area\n");
	printf("Enter side(a): \n");

	if(scanf("%f", &side) == 0)
	{
		printf("Failed!\n Incorrect input\n");
		wait_for_user_input();
		return 0;
	}

	return side * side;
}

float rectangle_calculation()
{
	float length = 0, width = 0;

	printf("Rectangle calculation area\n");
	printf("Enter length(l): \n");

	if(scanf("%f", &length) == 0)
	{
		printf("Failed!\n Incorrect input\n");
		wait_for_user_input();
		return 0;
	}

	printf("Enter width(w): \n");

	if(scanf("%f", &width) == 0)
	{
		printf("Failed!\n Incorrect input\n");
		wait_for_user_input();
		return 0;
	}

	return length * width;
}

void wait_for_user_input()
{
	printf("Press enter to exit app\n");
	while(getchar() != '\n')
	{

	}
	getchar();
}
