#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
	int value;  //数字
	int count;  //出现的次数
	int pos[10];//出现的下标
}Pair;

int qk_s(const void* a, const void* b) {
	return *(int*)a - *(int*)b;
}

void solve(int* arr,int num) {
	int* res = (int*)calloc(num, sizeof(int));
	Pair* pair = (Pair*)calloc(num,sizeof(Pair));

	int index = 0,flag = 0;
	pair[0].value = *arr;
	pair[0].count = 1;
	for (int i = 1; i < num; i++) {
		flag = 0;
		for (int j = 0; j < index+1; j++) {
			if (arr[i] == pair[j].value) {
				pair[j].count++;
				pair[j].pos[pair[j].count - 1] = i;//记录下标
				break;
			}
			else flag = 1;
		}
		if (flag == 1) {
			index++;
			pair[index].value = arr[i];
			pair[index].count++;
			pair[index].pos[pair[index].count - 1] = i;
		}
		else continue;
	} //数量是index+1

	int* sort_out = (int*)malloc((index + 1) * sizeof(int));
	//int sort_out[index+1] = { 0 };
	for (int i = 0; i < index + 1; i++) {
		sort_out[i] = pair[i].pos[pair[i].count-1] - pair[i].pos[0];//计算最大下标差（下标已经是升序的了）
	}

	//对下表差排序
	qsort(sort_out,index+1,sizeof(int),qk_s);
	if (sort_out[index] == 0)
		printf("-1");
	else
		printf("%d",sort_out[index]);
	
	free(sort_out);
	free(res);
	free(pair);
}

int main() {
	int N;
	scanf("%d",&N);
	int* arr = (int*)malloc(N * sizeof(int));

	for (int i = 0; i < N; i++)
		scanf("%d",&arr[i]);
	solve(arr,N);
}