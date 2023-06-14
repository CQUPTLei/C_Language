#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_NUM 100 

typedef struct {
	int r; //0
	int g; //1
	int b; //2
	int max;//次数最多的颜色
}Color;

//求每个窗口内颜色最多的
void pair_sort(Color* color) {
	color->max = (color->r > color->g ? color->r : color->g) > color->b ? (color->r > color->g ? color->r : color->g) : color->b;
}

//对所有窗口最大值进行排序
int qk_s(const void* a, const void* b) {
	const Color* x = a;
	const Color* y = b;
	return y->max-x->max;
}


void find_color(int *arr,int window,int num) {
	Color* color = (Color*)calloc((num+1-window),sizeof(Color));
	int index = 0;
	for (int i = 0; i < num-window; i++) {
		 for(int j = 0; j < window; j++) {
			if (arr[i + j] == 0)color[i].r++;
			if (arr[i + j] == 1)color[i].g++;
			if (arr[i + j] == 2)color[i].b++;
		}
	}
	for (int i = 0; i < num - window; i++)
		pair_sort(&color[i]);
	qsort(color, num - window + 1, sizeof(Color), qk_s);
	printf("%d",color[0].max);
	//for (int i = 0; i < num - window;i++)printf("\n%d %d %d max:%d", color[i].r, color[i].g, color[i].b,color[i].max);
	free(color);
}



int main() {
	int window;
	char* car_color=(char*)calloc(MAX_NUM,sizeof(char));
	fgets(car_color,MAX_NUM,stdin);
	scanf("%d", &window);

	int* car = (int*)malloc(MAX_NUM * sizeof(int));

	char* p = strtok(car_color," ");
	int count = 0;
	while (p != NULL) {
		car[count++] = atoi(p);
		p = strtok(NULL," ");
	}
	find_color(car,window,count+1);

	free(car_color);
	free(car);
	return 0;
}