#include<stdio.h>

int hh()
{
	char a = 10;
	int arr[4] = { 5,2,3,4 };
	int b = 20;
	char* pa = &a;
	int* pb = &b;

	printf("a = %d\n",a);
	printf("*pa = %d\n\n", *pa);

	printf("b = %d\n",b );
	printf("*pb = %d\n\n", *pb);

	printf("&a = %p\n",&a );
	printf("pa = %p\n\n",pa );

	printf("&b = %p\n", &b);
	printf("pb = %p\n\n", pb);

	printf("pa = %p\n",pa);
	printf("pa+1 = %p\n", ++pa);
	printf("pb = %p\n",pb);
	printf("pb+1 = %p\n\n", ++pb);


	printf("*arr = %d = arr[0] = %d\n",*arr,arr[0]);
	printf("*(arr+1) = %d = arr[1]=%d\n", *(arr+1),arr[1]);
	printf("*arr+1 = %d = arr[0]+1 = %d\n\n",*arr+1,arr[0]+1);


	//printf("pa!=pb的结果是：%d\n",pa!=pb);
}