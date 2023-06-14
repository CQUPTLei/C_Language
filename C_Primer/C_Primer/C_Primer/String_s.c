#include<stdio.h>


void string_array();
void string_io();
void my_input(char string[]);
void my_output(const char* string);

int test1()
{
	char test_str[30];
	//string_array();
	//string_io();
	my_input(test_str);
	my_output(test_str);

	return 0;
}


// 字符串数组、指针输出测试
void string_array()
{
	char s1[30] = "This is" " Visual Studio.";
	char s2[30] = "This is Visual Studio.";

	char s3[20] = { 'H','e','l','l','o' };
	char s4[20] = { 'H','e','l','l','o','\0'};

	char s5[] = "I love you more than i can say.";
	const char *ps5= "I love you more than i can say.";

	char* ps6[3] = { "你说我比大笨钟还笨要怎么比",
					"吵架我太安静，",
					 "钟至少还有声音" };

	char s6[3][30] = {"街灯下的橱窗，",
		             "有一种落寞的温暖，",
		             "吐气在玻璃上..."};

	puts(s1);
	puts(s2);
	puts("这是一个双引号\"\".");

	puts(s3);
	puts(s4);

	printf("s5 = %p = &s5[0] = %p\n",s5,&s5[0]);
	printf("*s5 = %c = s5[0] = %c\n",*s5,s5[0]);
	printf("*(s5+3) = %c = s5[3] = %c\n\n", *(s5+3), s5[3]);


	for (int i = 0;i < 3;i++)
		printf("%-36s %-25s\n", ps6[i], s6[i]);

	printf("\nsize of ps6 = %zd, size of s6 = %zd\n",sizeof(ps6),sizeof(s6));
}


// 字符串输出函数测试
void string_io()
{
	char str1[] = "The stars change, but the mind remains the same.";
	char* str2 = "Refrain from excess.";

	puts("There is always a better way.");
	puts(str1);
	puts(str2);
	puts(str1+4);
	puts(&str1[4]);
	puts(str2+8);
	puts(&str2[8]);
}


// 自定义输入函数
void my_input(char string[])
{
	int i=0;
	int j = 0;

	while((string[i] = getchar())!= '\n')
		i++;

	while (string[j] != '\n')
		j++;
	string[j] = '\0';
}


// 自定义输出函数
void my_output(const char* string)
{
	while (*string)
		putchar(*string++);
}