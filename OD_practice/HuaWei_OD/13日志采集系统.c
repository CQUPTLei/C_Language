#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LIST_NUM 1000 // ���1000��ʱ�̵���־


int main()
{
	char* log_list;
	log_list = (char*)malloc(LIST_NUM * sizeof(char)); 

	fgets(log_list,LIST_NUM,stdin); //��Ȼ������û���ϸ����ñ߽�

	char* tmp;
	tmp = log_list;
	char* p = strtok(tmp," ");
	char n = 0;
	while (p != NULL)  // ��������ַ����ָ����������ֱ��浽 log_list��
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