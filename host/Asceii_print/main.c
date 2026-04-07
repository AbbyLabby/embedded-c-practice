#include <stdio.h>

int main()
{
	int chars[6];

	printf("Enter 6 chars: \n");
	//for(int i = 0; i < 6; i++)
	//{
	//	chars[i] = getchar();
	//}

	scanf("%c %c %c %c %c %c", &chars);

	for(int i = 0; i < 6; i++)
	{
		printf("%d \n", chars[i]);
	}

	while(getchar() != '\n')
	{

	}
	getchar();

	return 0;
}
