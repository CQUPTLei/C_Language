#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LEN 1000

typedef struct {
	int value; //数值
	int count; //出现的次数
}Poke;


//根据相同张数排序
int qk_s(const void* a, const void* b) {
	Poke* x = b; 
	Poke* y = a;
	return x->count - y->count;
}
//对所有牌从大到小排序
int p_s(const void* a, const void* b) {
	return *(int*)b - *(int*)a;
}

//对count相同的牌，根据value降序排列
int qk_v(const void* a, const void* b) {
	Poke* x = b;
	Poke* y = a;
	return x->value - y->value;
}

void solve(int* arr,int count) {
	Poke* poke = (Poke*)calloc(count,sizeof(Poke)); //记录每种牌的张数

	int index = 0;
	poke[0].value = arr[0]; //统计每张牌出现的次数
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
	}//这里index是下标，比总数少1
	//for (int i = 0; i < index+1; i++)printf("\nvalue:%d  count:%d", poke[i].value, poke[i].count);
	// 
	// 张数由多到少排序
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

	//再将所有牌从大到小排序
	qsort(arr,count,sizeof(int),p_s);
	//for (int i = 0; i < count; i++)printf("%d  ", arr[i]);

	int flag_2 = 0, flag_3 = 0;
	for (int i = 0; i < index + 1; i++) {

		//如果大于等于4张，直接输出
		if (poke[i].count >= 4) {
			for (int j = 0; j < count; j++) {
				if (poke[i].value == arr[j])
					printf("%d ", arr[j]);
			}
		}
		//如果是3张，还要输出2张
		if (poke[i].count == 3) {
			//先输出3张
			for (int j = 0; j < count; j++) { 
				if (poke[i].value == arr[j]) {
					printf(" %d",arr[j]);
				}
			}
			//再输出2张
			for (int j = i + 1; j < index + 1; j++) {
				if (poke[j].count == 2) {
					for (int k = 0; k < count; k++) {
						if (poke[j].value == arr[k]) {
							printf(" %d",arr[k]);
							poke[j].count = 0;//保障不重复输出
						}
					}
					break; //只输出1次
				}
			}
		}

		//剩下的2张依次输出
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