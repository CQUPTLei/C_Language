#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 1000

typedef struct {
	char str[10];
	int count;
}Word;

//��ÿ�����ʰ��ֵ������У���ascii������
int qks(const void* a, const void* b) {
	return *(char*)a - *(char*)b;
}
//���յ��ʳ��ִ�������
int qkc(const void* a, const void* b) {
	Word* x = a;
	Word* y = b;
	return y->count - x->count;
}
//��������
int qL(const void* a, const void* b) {
	Word* x = a;
	Word* y = b;
	return strlen(x->str) - strlen(y->str);
}
//�ֵ������
int qD(const void* a, const void* b) {
	Word* x = a;
	Word* y = b;
	return x->str[0] - y->str[0];
}
//�Գ��ִ�����ͬ�ĵ��ʣ����ݳ�������,����
void sort_L(Word* word,int start,int end) {
	qsort(word+2,end-start+1,sizeof(Word),qL);
}
//�Գ��ȡ�������ͬ�ĵ��ʣ����ֵ�������
void sort_D(Word* word, int start, int end) {
	qsort(word + 2, end - start + 1, sizeof(Word), qD);
}


// ͳ��ÿ�����ʳ��ֵĴ���
void word_count(char **arr, int num) {
	
	for (int i = 0; i < num; i++)
		qsort(arr[i],strlen(arr[i]),sizeof(char),qks);

	Word* word = (Word*)calloc(50,sizeof(Word));

	strcpy(word[0].str,arr[0]);
	word[0].count = 1;
	int index = 0, flag = 0;
	for (int i = 1; i < num; i++) {
		for (int j = 0; j < index+1; j++) {
			if (strcmp(arr[i], word[j].str) == 0) {
				word[j].count++;
				flag = 0;
				break;
			}
			else {
			flag = 1;
			}
		}
		if (flag == 1) {
			flag = 0;
 			strcpy(word[++index].str, arr[i]);
			word[index].count++;
		}
	}
	qsort(word, index + 1,sizeof(Word),qkc);
	for (int i = 0; i < index + 1; i++)printf("\nstr:%6s  scount:%2d",word[i].str,word[i].count);
	puts("\n");
	//���
	int f = 1;
	for (int i = 0; i < index; i++) {
		//int flag = 1;
		for (int j = i + 1; j < index + 1; j++) {

			if (word[i].count > word[j].count && f == 1) {
				for (int k = 0; k < word[i].count; k++)
					printf("%s ", word[i].str);
				i=j-1;  // �ȼ���i++
				break;
			}

			if (word[i].count==word[j].count) {
				f++;
				continue;
			}
		}
		if (f > 1) {
			//printf("\n%d",f);
			sort_L(word,i,i+f-1);
			for (int fuck = 0; fuck < f; fuck++) {
				for (int n = 0; n < word[i+fuck].count; n++) 
					printf("%s ", word[i+fuck].str); 
			}
			i = i + f - 1;
			f = 1;
		}
	}
}




int main() {

	char* input = (char*)malloc(MAX_LEN*sizeof(char));
	fgets(input,MAX_LEN,stdin);

	char** arr = (char**)malloc(50 * sizeof(char*));
	for (int i = 0; i < 50; i++) arr[i] = (char*)malloc(10 * sizeof(char));

	char* p = strtok(input," \n");
	int count = 0;
	while (p != NULL) {
		strcpy(arr[count++],p);
		p = strtok(NULL," \n");
	}
	free(input);

	for (int i = 0; i < count; i++)printf("%s,",arr[i]);
	//while (count > 0) { printf("%s,", arr[--count]); }

	word_count(arr,count);
	return 0;
}