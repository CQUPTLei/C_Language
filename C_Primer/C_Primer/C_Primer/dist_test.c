#include<stdio.h>

int test()
{
	char a = 10;
	char* p = &a;
	//变量的值
	printf("变量a的值是：%d\n", a);
	//变量的地址
	printf("a的地址是：%p\n",&a);
	//指针的值即地址处存放的值
	printf("指针p指向地址存储的值是：%d\n", *p);
	//指针的值是变量地址
	printf("指针的值（即变量地址）是：%p\n", p);
	//变量的地址处存放的是变量的值
	printf("a的地址存放的值是a的值：%d\n",*(&a));
	//指针的地址
	printf("指针p的地址是：%p\n",&p);
	//指针的地址处存放的是a的地址；
	printf("指针的地址处存放的是a的地址：%p\n",*(&p));
	return 0;
}