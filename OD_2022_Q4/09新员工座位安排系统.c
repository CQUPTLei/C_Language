#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX 100000

typedef struct {
	int idx;
	int value;
	int num;
}Pair;

int sort_arr(const void* a, const void* b) {
	const Pair* x = a;
	const Pair* y = b;
	return y->num -x->num;
}

void max_friend(int *arr,int n) {
	int count = 0;
	for (int i = 0; i < n; i++) {
		if ((arr[i] == 0)||(arr[i]==2))
			count++;
	}
	Pair* pos = (Pair*)calloc(count , sizeof(Pair));
	int index = 0;
	for (int i = 0; i < n; i++) {
		if ((arr[i] == 0) || (arr[i] == 2)) {
			pos[index].idx = i;
			pos[index++].value = arr[i];
		}	
	}

	for (int i = 0; i < count; i++) {
		if (pos[i].value == 0) {
			if (i == 0)
				pos[i].num = pos[i + 1].idx -1;
			if (i > 0 && i < count - 1)
				pos[i].num =  pos[i + 1].idx-  pos[i - 1].idx -2;
			if (i == count - 1)
				pos[i].num = pos[i].idx - pos[i - 1].idx + count-i-2;
		}
	}
	qsort(pos,count,sizeof(Pair), sort_arr);
	printf("%d",pos[0].num);
	free(pos);
}


int main() {

	int* seat = (int*)malloc(MAX*sizeof(int));
	char* input = (char*)malloc(MAX * sizeof(char));
	fgets(input,MAX,stdin);
	int count = 0;
	char* p = strtok(input," ");
	while (p != NULL) {
		seat[count++] = atoi(p);
		p = strtok(NULL," ");
	}
	free(input);
	max_friend(seat,count);
	return 0;
}