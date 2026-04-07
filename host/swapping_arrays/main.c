#include <stdio.h>
#include <stdint.h>

void swap_arrays(uint32_t *array1, uint32_t *array2, uint32_t size_array0, uint32_t size_array1);
void print_array(uint32_t const *const pArray, uint32_t arraySize);
void wait_for_user_input();

int main()
{
	uint32_t array_size0, array_size1;

	printf("Enter size for 1 array: \n");
	scanf("%d", &array_size0);

	printf("Enter size for 2 array: \n");
	scanf("%d", &array_size1);

	uint32_t array0[array_size0];

	for(int i = 0; i < array_size0; i++)
	{
		printf("Enter %d element of 1 array: \n", i + 1);
		scanf("%d", &array0[i]);
	}

	uint32_t array1[array_size1];

	for(int i = 0; i < array_size1; i++)
	{
		printf("Enter %d element of 2 array: \n", i + 1);
		scanf("%d", &array1[i]);
	}

	swap_arrays(array0, array1, array_size0, array_size1);

	print_array(array0, array_size0);
	print_array(array1, array_size1);

	wait_for_user_input();

	return 0;
}

void swap_arrays(uint32_t *array1, uint32_t *array2, uint32_t size_array0, uint32_t size_array1)
{
	for(int i = 0; i < (size_array0 > size_array1 ? size_array1 : size_array0); i++)
	{
		uint32_t temp = array1[i];
		array1[i] = array2[i];
		array2[i] = temp;
	}
}

void print_array(uint32_t const *const pArray, uint32_t arraySize)
{
	for(uint32_t i = 0; i < arraySize; i++)
	{
		//printf("%x\n", *(pArray + i));
		printf("%d", pArray[i]);
	}

	printf("\n");
}

void wait_for_user_input()
{
	printf("Press enter to exit app\n");
	while(getchar() != '\n')
	{

	}
	getchar();
}
