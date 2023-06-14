#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ARR_LEN 1001

typedef struct {
	int value;
	int count;
}Pair;


int qk_s(const void* a, const void* b) { //降序排序
	Pair* x = a;
	Pair* y = b;
	return y->count - x->count;
}

//求某个误码的最短子串
int err_len(int* arr,int num,Pair* pair, int x) {
	int min_len = 0, st = 0, find = 0;
	for (int i = 0; i < num; i++) {
		if (arr[i] == pair[x].value) {
			min_len++;
			st =1; //开始计数
			find++;
			continue;
		}
		if (st > 0 && find < pair[x].count)
		{
			min_len++;
			continue;
		}
		else {
			st = 0;
			continue;
		}	
	}
	return min_len;
}


//统计每个误码出现的次数,并返最短...
void max_err(int* arr,int num) {
	Pair* err_count = (Pair*)calloc(num,sizeof(Pair));
	err_count[0].value = arr[0];
	err_count[0].count = 1;
	int index = 0,flag=0;
	for (int i = 1; i < num; i++) {   //统计各个误码数量
		for (int j = 0; j < index + 1; j++) {
			if (arr[i] == err_count[j].value) {
				err_count[j].count++;
				flag = 0;
				break;
			}
			else {
				flag = 1;
			}
		}
		if (flag == 1) {
			flag = 0;
			err_count[++index].value = arr[i];
			err_count[index].count++;
			//break;
		}
	}
	//根据数量排序，降序
	qsort(err_count,index+1,sizeof(Pair),qk_s);

	int minL = err_len(arr,num,err_count,0),mark=0;
	for (int i = 0; i < index + 1; i++) {
		if (err_count[i].count == err_count[0].count) {
			minL = minL > err_len(arr, num, err_count, i) ? err_len(arr, num, err_count, i) : minL;
		}
		else
			break;
	}
	printf("%d", minL);
	free(err_count);
}


int main() {
	int num;
	int* arr = (int*)calloc(ARR_LEN,sizeof(int));

	scanf("%d\n",&num);
	for (int i = 0; i < num; i++)
		scanf("%d", &arr[i]);

	max_err(arr,num);

	free(arr);
	return 0;
}