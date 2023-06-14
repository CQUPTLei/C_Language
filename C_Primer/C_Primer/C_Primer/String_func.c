#include<stdio.h>
#include<string.h>
#include<stdlib.h>



void strlen_test();
void strcat_test();
void strncat_test();
void  strcmp_test();
void strcpy_test();
void sprintf_test();
void strstr_test();
void str2num();
void str_sort(char *str[],int n);

int TEST;
TEST = 888;

int main_1()
{
	char *p[4] = { "Do your best this time.",
	"And i always believe in you.",
	"But you have not ",
	"What's the matter?" };

	//strlen_test();
	//strcat_test();
	//strncat_test();
	//strcmp_test();
	//strcpy_test();
	//sprintf_test();
	//strstr_test();
	//str2num();

	//puts("argv values are:");
	//for (int i = 0;i < argc;i++)
		//puts(*(argv+i));

	str_sort(p,4);
	return 0;
}


void strlen_test()
{
	char s1[] = "I am dog.";
	char* s2 = "I am dog.";
	char s3[] = {'H','e','l','l','0',' '};
	char s4[20] = "Hello, C.";   

	printf("%zd\n",strlen(s1));
	printf("%zd\n", sizeof(s1));

	printf("%zd\n", strlen(s2));
	printf("%zd\n", sizeof(s2));

	printf("%zd\n", strlen(s3));
	printf("%zd\n", sizeof(s3));

	printf("%zd\n", strlen(s4));
	printf("%zd\n", sizeof(s4));
	printf("%zd\n", sizeof(s1)/sizeof(char));
}


void strcat_test()
{
	char s1[100] = "In this world, ";
	char s2[] = "the car is far away and the horse is slow.";
	char* s3 = "In this world, ";

	strcat(s1,s2);
	puts(s1);
	puts(s2);
}


void strncat_test()
{
	char s1[20] = "Meet you, ";
	char s2[] = "love surge, see everything in the world, are romantic heart.";

	strncat(s1, s2, 20-strlen(s1)-1);
	puts(s1);
	puts(s2);
}


void  strcmp_test()
{
	char s1[20] = "Hello, Tom.";
	char s2[15] = "Hello, Jay.";

	printf("%d\n",strcmp(s1,s2));
	printf("%d\n", strcmp("OK", "OK"));
	printf("%d\n",strcmp("A","B"));
	printf("%d\n", strcmp("A", "C"));
	printf("%d\n", strcmp("B", "A"));
	printf("%d\n", strcmp("d", "a"));

	printf("%d\n", strncmp("Fighting", "Fight",5));
}


void strcpy_test()
{
	char s1[20];
	char s2[20];

	char s3[20] = "I am your dad";

	//fgets(s2,18,stdin);
	//gets_s(s2,18);
	if (!strncmp(s2, "I", 1))
		strcpy(s1,s2);

	//puts(s2);
	//puts(s1);

	puts(s3);
	printf("%s\n",strcpy(s3+10,"son"));
	printf("%s\n", s3);
}


void sprintf_test()		   
{
	char s1[50] = { "Hello, " };

	sprintf(s1+strlen(s1),"%sI am %d yesrs old. ","i am Tom. ",18);
	puts(s1);
}


void strstr_test()
{
	char *s1 = " The Panda has a big head.";

	//printf("%zd\n",strlen(s1)-strlen(strstr(s1,"a")));
	int i = 0;
	while (*(s1+i) != '\0')
	{
		if (strstr(s1 + i, "a") != NULL)
		{
			i = strlen(s1) - strlen(strstr(s1 + i, "a"));
			printf("%d\n",i);
		}
		i++;
	}
}


void str2num()
{
	char number[] = "7f";
	printf("%d  %d\n", atoi("123"),"123");
	printf("%d\n", atoi("30 days"));
	printf("%d\n", atoi("Five 23 days"));
	printf("%zd\n", sizeof(long long));
	printf("%d\n", strtol(number,number+2,16));
	printf("%d\n", strtol(number, number + 2, 10));
}


void str_sort(char *str[],int n)
{
	char *temp;
	
	for (int i = 0;i < n - 1;i++)
	{
		for (int j = i + 1;j < n;j++)
		{
			if (strncmp(str[i], str[j],1) > 0) //前比后大为正
			{
				temp = str[j];
				str[j] = str[i];
				str[i] = temp;
			}
		}
	}
	for (int k = 0;k < n;k++)
		puts(str[k]);
}