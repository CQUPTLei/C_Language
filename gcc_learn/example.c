#include<stdio.h>
#include<string.h>
#include<stdlib.h> 

int max(int a,int b){
	return a>b? a:b;
}

 
int main()
{
	int i=0;
	for(i=0;i<5;i++){
		printf("* * *\n");
	}
	printf("%d is bigger between %d and %d\n",5,4,max(5,4));	
	puts("Done\n"); 
	return 0;
}

