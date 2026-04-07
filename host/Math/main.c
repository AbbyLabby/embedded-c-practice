#include <stdio.h>
#include "math.h"

int main()
{
	printf("sum = %d\n", math_sum(6, 5));
	printf("sub = %d\n", math_sub(6, 5));
	printf("mul = %lld\n", math_mul(6, 5));
	printf("div = %0.2f\n", math_div(6, 5));

	getchar();
}
