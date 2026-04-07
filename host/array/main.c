#include <stdio.h>
#include <stdint.h>

void print_array(uint8_t const *const pArray, uint32_t arraySize);

int main()
{
	uint8_t somdeData[3] = {0xff, 0xff, 0xff};

	uint32_t arraySize = sizeof(somdeData) / sizeof(somdeData[0]);

	print_array(somdeData, arraySize);

	return 0;
}

void print_array(uint8_t const *const pArray, uint32_t arraySize)
{
	for(uint32_t i = 0; i < arraySize; i++)
	{
		//printf("%x\n", *(pArray + i));
		printf("%x\n", pArray[i]);
	}
}
