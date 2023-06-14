#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int * static_test();
int* auto_test();

extern int TEST;

int main()
{
	const int a = 9;
	int arr[a];

	int* pa = &a;
	*pa = 10;
	printf("%d\n",a);

	srand((unsigned int)time(0));
	for (int i = 0; i < 4; i++)
	{
		printf("%d\n", rand()%5);
	}
		
	//int* pa;

	//printf("%d\n\n", TEST);

	//pa = static_test();

	//

	//printf("用指针访问局部静态变量：%d\n\n", *pa);

	//*pa += 6;
	//static_test();

	//printf("用指针访问自动变量：%d\n\n", *auto_test());

	//for (int i = 1; i < 4; i++)
	//{
	//	static_test();
	//	auto_test();
	//}

	return 0;
}

int *static_test()
{
	static int a;
	printf("局部静态变量的值：%d\n", a++);
	return &a;
}

int *auto_test()
{
	int b=2;
	printf("自动变量的值：%d\n", b++);
	return &b;
}
