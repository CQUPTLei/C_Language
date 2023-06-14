#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LEN 1000

typedef struct {
	int value; //��ֵ
	int count; //���ֵĴ���
}Poke;


//������ͬ��������
int qk_s(const void* a, const void* b) {
	Poke* x = b; 
	Poke* y = a;
	return x->count - y->count;
}
//�������ƴӴ�С����
int p_s(const void* a, const void* b) {
	return *(int*)b - *(int*)a;
}

//��count��ͬ���ƣ�����value��������
int qk_v(const void* a, const void* b) {
	Poke* x = b;
	Poke* y = a;
	return x->value - y->value;
}

void solve(int* arr,int count) {
	Poke* poke = (Poke*)calloc(count,sizeof(Poke)); //��¼ÿ���Ƶ�����

	int index = 0;
	poke[0].value = arr[0]; //ͳ��ÿ���Ƴ��ֵĴ���
	poke[0].count = 1;
	for (int i = 1; i < count; i++) {
		int flag = 0;
		for (int j = 0; j < index+1; j++) {
			if (arr[i] == poke[j].value) {
				poke[j].count++;
				flag = 0;
				break; 
			}
			else {
				flag = 1;
			}
		}	
		if (flag == 1) {
			poke[++index].value = arr[i];
			poke[index].count++;
		}
	}//����index���±꣬��������1
	//for (int i = 0; i < index+1; i++)printf("\nvalue:%d  count:%d", poke[i].value, poke[i].count);
	// 
	// �����ɶൽ������
	qsort(poke,index+1,sizeof(Poke),qk_s);

	for (int i = 0; i < index + 1;) {
		for (int j = i+1; j < index+2 ; j++) {
			if (poke[i].count == poke[j].count)
				continue;
			else {
				qsort(poke+i,j-i,sizeof(Poke),qk_v);
				i +=j;
				break;
			}
		}
	}
	puts("\n");
	for (int i = 0; i < index + 1; i++)printf("\nvalue:%d  count:%d", poke[i].value, poke[i].count);
	puts("\n");

	//�ٽ������ƴӴ�С����
	qsort(arr,count,sizeof(int),p_s);
	//for (int i = 0; i < count; i++)printf("%d  ", arr[i]);

	int flag_2 = 0, flag_3 = 0;
	for (int i = 0; i < index + 1; i++) {

		//������ڵ���4�ţ�ֱ�����
		if (poke[i].count >= 4) {
			for (int j = 0; j < count; j++) {
				if (poke[i].value == arr[j])
					printf("%d ", arr[j]);
			}
		}
		//�����3�ţ���Ҫ���2��
		if (poke[i].count == 3) {
			//�����3��
			for (int j = 0; j < count; j++) { 
				if (poke[i].value == arr[j]) {
					printf(" %d",arr[j]);
				}
			}
			//�����2��
			for (int j = i + 1; j < index + 1; j++) {
				if (poke[j].count == 2) {
					for (int k = 0; k < count; k++) {
						if (poke[j].value == arr[k]) {
							printf(" %d",arr[k]);
							poke[j].count = 0;//���ϲ��ظ����
						}
					}
					break; //ֻ���1��
				}
			}
		}

		//ʣ�µ�2���������
		if (poke[i].count == 2) {
			for (int j = 0; j < count; j++) {
				if (poke[i].value == arr[j])
					printf(" %d",arr[j]);
			}
		}

		if (poke[i].count == 1) {
			for (int j = 0; j < count; j++) {
				if (poke[i].value == arr[j])
					printf(" %d",arr[j]);
			}
		}

	}
}




int main() {

	char* arr = (char*)malloc(MAX_LEN*sizeof(char));
	fgets(arr,MAX_LEN-2,stdin);

	int* poke = (int*)calloc(MAX_LEN, sizeof(int));
	char* p = strtok(arr," \n");
	int count = 0;
	while (p != NULL) {
		poke[count++] = atoi(p);
		p = strtok(NULL," \n");
	}
	free(arr);
	solve(poke,count);
	free(poke);
	return 0;
}