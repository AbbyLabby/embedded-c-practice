#include <stdio.h>

int main()
{
	char var = 100;
	printf("Address of var variable: %p\n", &var);
	printf("Value of var variable: %d\n", var);

	char* var_address = &var;

	char read_data = *var_address;

	printf("Read data %d from address %p\n", read_data, var_address);

	*var_address = 65;

	printf("New data of var variable: %d\n", var);

	getchar();

	return 0;
}
