#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LIST_NUM 1000 // 最多1000个时刻的日志


int main()
{
	char* log_list;
	log_list = (char*)malloc(LIST_NUM * sizeof(char)); 

	fgets(log_list,LIST_NUM,stdin); //当然了这里没有严格设置边界

	char* tmp;
	tmp = log_list;
	char* p = strtok(tmp," ");
	char n = 0;
	while (p != NULL)  // 将输入的字符串分隔，并将数字保存到 log_list中
	{
		log_list[n++] = atoi(p);
		p = strtok(NULL, " ");
	}


	char sum = 0,score=0;
	int i;
	for (i = 0; i < n; i++)
	{
		sum += log_list[i];
	}
	i--;
	if (sum > 100)
	{
		score = 100 - (sum - log_list[i]);
		while (score < (sum - log_list[i]))
		{
			sum -= log_list[i];
			i--;
			if (sum >100)
				score = 100 - (sum - log_list[i]);
			else
				score = sum;
		}
	}
	else
		score = sum;

	printf("%d",score);
	free(log_list);
	return 0;
}