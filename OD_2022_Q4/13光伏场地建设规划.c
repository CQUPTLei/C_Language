#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int cacul_len(int** arr,int len,int x,int y) {

	int sum = 0;
	for (int i = x; i < x+len; i++) {
		for (int j = y; j < y+len; j++)
			sum += arr[i][j];
	}
	return sum;
}


int main() {

	int row, col, len, ele;
	scanf("%d %d %d %d",&row,&col,&len,&ele);
	//int* arr = (int*)malloc(row*col*sizeof(int));
	int** arr = (int**)malloc(row * sizeof(int)) ;
	for (int i = 0; i < row; i++) {
		 arr[i] = (int*)malloc(col * sizeof(int));
		 for (int j = 0; j < col; j++)
			 scanf("%d",&arr[i][j]);
	}

	int count = 0;
	for (int i = 0; i < row - len + 1; i++) { 
		for (int j = 0; j < col - len + 1; j++) {
			int power = cacul_len(arr,len,i,j);
			if (power >= ele)
				count++;
		}
	}
	printf("%d",count);

	for (int i = 0; i < row;i++)
		free(arr[i]);
	free(arr);
	return 0;
}