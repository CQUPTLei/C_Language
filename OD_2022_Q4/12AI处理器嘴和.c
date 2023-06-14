#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LEN 20

typedef struct {
	int value[4]; //存放可用处理器编号
	int count;   //可用处理器的数量
}Pair;

//打印链路1的n个数字
void left_n(Pair* pair, int n) {
	printf("[");
	for (int i = 0; i < n; i++) {
		if (i < n - 1)
			printf("%d,", pair[0].value[i]);
		else
			printf("%d", pair[0].value[i]);
	}
	printf("]");
}
//链路2
void right_n(Pair* pair, int n) {
	printf("[");
	for (int i = 0; i < n; i++) {
		if (i < n - 1)
			printf("%d,", pair[1].value[i]);
		else
			printf("%d", pair[1].value[i]);
	}
	printf("]");

}
// 两个都打印
void both_n(Pair* pair,int n) {
	printf("[");
	left_n(pair, n);
	printf(",");
	right_n(pair, n);
	printf("]");
}

int select(Pair* pair, int order) {
	if (pair[0].count == order && pair[1].count == order) {
		both_n(pair,order);
		return 1;
	}	
	if (pair[0].count == order && pair[1].count != order) {
		left_n(pair,order);
		return 1;
	}
	if (pair[1].count == order && pair[0].count != order) {
		right_n(pair, order);
		return 1;
	}
	else 
		return -1;
}


void pr_2(Pair* pair){
	int flag = 0;
	flag = select(pair, 2);
	if (flag != 1) flag = select(pair, 4);
	if (flag != 1) flag = select(pair, 3);
}

void pr_1(Pair* pair) {
	int flag = 0;
	flag = select(pair, 1);
	if (flag != 1) flag = select(pair, 3);
	if (flag != 1) flag = select(pair, 2);
	if (flag != 1) flag = select(pair, 4);
}

void solve(Pair* pair,int num) {
	switch (num) {
	case 8:
		select(pair, 8/2);
		break;
	break;
	case 4:
		select(pair,4);
		break;
	case 2:
		pr_2(pair);
		break;
	case 1:;
		pr_1(pair);
		break;
	}
}

int main() {
	
	int number;
	char* arr = (char*)malloc(MAX_LEN*sizeof(char));
	scanf("%s", arr);
	scanf("%d", &number);

	Pair* pair = (Pair*)calloc(2,sizeof(Pair));//两个链路结构体数组

	char* p = strtok(arr,"[], ");
	while (p != NULL) {
		
		if (atoi(p) < 4) {
			//puts(p);
			pair[0].value[pair[0].count] = atoi(p);
			pair[0].count++;
		}
		else {
			//puts(p);
			pair[1].value[pair[1].count] = atoi(p);
			pair[1].count++;
		}
		p = strtok(NULL,"[], ");
	}
	free(arr);
	//scanf(" %d", &number);
	solve(pair,number);
	free(pair);
	return 0;
}
