#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static union { char c[4]; unsigned long l; }endian_test = { { 'l', '?', '?', 'b' } };
#define ENDIANNESS ((char)endian_test.l)

#define LEN 30

void file_copy(const char *file_in);
void fp_s();
void fseek_tell();

int main()
{
	//file_copy("origin.txt");
	//fp_s();
	//fseek_tell();
	printf("%c\n",ENDIANNESS);

	return 0;
}


void file_copy(const char *file_in)
{
	FILE *in, *out;
	char name[LEN];
	int ch;

	// ����ļ�����
	if ((in = fopen(file_in, "r")) == NULL)
	{
		fprintf(stderr,"The file: %s is not exit.\n",file_in);
		exit(EXIT_FAILURE);
	}


	strncpy(name, file_in, LEN - 9);
	name[LEN - 5] = '\0';
	strcat(name,".new.txt");

	if ((out = fopen(name, "w+")) == NULL)
	{
		fprintf(stderr, "Can't creat output file.\n");
		exit(EXIT_FAILURE);
	}



	while ((ch = getc(in)) != EOF)
	{
		putc(ch, out);
	}

	if (fclose(in) != 0 || fclose(out) != 0)
	{
		fprintf(stderr, "Error with closing files.\n");
		exit(EXIT_FAILURE);
	}

	puts("Processing success!");

}


void fp_s()
{
	FILE* fp;
	char words[30];

	if ((fp = fopen("word.txt", "a+")) == NULL)
	{
		fprintf(stderr, "���ļ�ʧ�ܡ�\n");
		exit(EXIT_FAILURE);
	}

	puts("���뵥�ʣ�q��ʾ����\n");
	while ((fscanf(stdin, "%s", words) == 1) && words[0] != 'q')
	{
		fprintf(fp, "%s\n", words);
	}

	rewind(fp); //��ָ���Ƶ���ͷ

	puts("�����������µ��ʣ�");

	while ((fscanf(fp, "%s\n", words)) == 1)
		puts(words);

	if ((fclose(fp)) != NULL)
		fprintf(stderr,"�ر��ļ�ʧ�ܡ�\n");
}


void fseek_tell()
{
	FILE* pt;
	long count;
	int ch;

	pt = fopen("sort.txt","a+");

	fseek(pt,0L,SEEK_END);
	count = ftell(pt);

	fprintf(pt,"%s","\n"); //����

	while (count != -1)
	{
		fseek(pt,count,SEEK_SET);
		ch = getc(pt);

		count--;

		fseek(pt, 0L, SEEK_END);
		fprintf(pt, "%c", ch);
	}

	fclose(pt);
}