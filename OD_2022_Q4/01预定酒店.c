#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

typedef struct {
	int a; //�Ƶ�۸�
	int b; //��ֵ
}Pair;


int compare_1(const void* x, const void* y) {
	const Pair* a = x;
	const Pair* b = y;
	return a->b - b->b;
}

int compare_2(const void* x, const void* y) {
	return *(const int*)x-*(const int*)y;
}


void Select(int* arr,int n,int k,int x) {

	Pair* sort_arr = (Pair*)malloc(n * sizeof(Pair));

	for (int i = 0; i < n; i++) {
		sort_arr[i].a = arr[i];
		sort_arr[i].b = abs(arr[i] - x);
	}
	 // �ȸ��ݲ������
	 qsort(sort_arr,n,sizeof(Pair),compare_1);
	 // �ٽ�ǰk���Ƶ�ļ۸�����
	 int* first_k = (int*)calloc(k * sizeof(int),sizeof(int));
	 // ���k��ż�������ܻ���2�������ͬ��,��Ҫ�Ƚ�k+1������
	 int c = (k % 2) == 0 ? k+1 : k;
	 for (int i = 0; i < c; i++)  first_k[i] = sort_arr[i].a;
	 qsort(first_k, c, sizeof(int), compare_2);

	 for (int j = 0; j < k; j++)
		 printf("%d ",first_k[j]);

	 free(first_k);
	 free(sort_arr);
}

int main() {
	int n, k, x;  //�Ƶ�����n��ѡk���������λx
	scanf("%d %d %d",&n,&k,&x);

	int* A = (int*)malloc(n * sizeof(int)); //n���Ƶ�ļ۸�
	for (int i = 0; i < n; i++) {
		scanf("%d", &A[i]);
	}
	Select(A,n,k,x);
	free(A);
	return 0;
}