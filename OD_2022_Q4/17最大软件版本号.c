#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define LEN 50

typedef struct {
	int num[3];
	char str[10];
}Version;


void To_struct(Version* version,char* ver,int n) {
	char* p = strtok(ver, ". -\n");
	for (int i = 0; i < 3; i++) {
		version[n].num[i] = atoi(p);
		p = strtok(NULL,". -\n");
	}
	strcpy(version[n].str, p);
}

void Ver_cmp(Version* version,char* ver1,char* ver2) {
	int flag = 0;
	for (int i = 0; i < 3; i++) {
		if (version[0].num[i] > version[1].num[i]) {
			printf("%s",ver1);
			flag = 1;
			break;
		}
	}
	//如果数字部分相同，判断字符串
	if (flag == 0) {
		//取字符串的最小长度
		int minL = strlen(version[0].str) > strlen(version[1].str) ? strlen(version[1].str) : strlen(version[0].str);
		for (int i = 0; i < minL; i++) {
			if (version[0].str[i] > version[1].str[i]) {
				printf("%s",ver1);
				flag = 1;
				break;
			}
		}
	}
	if (flag == 0)printf("%s",ver2);
}


int main() {
	 
	char* ver1 = (char*)malloc(LEN*sizeof(char));
	char* ver2 = (char*)malloc(LEN*sizeof(char));

	fgets(ver1, LEN, stdin);
	fgets(ver2, LEN, stdin);
	char* v1 = (char*)malloc(LEN * sizeof(char)); strcpy(v1, ver1); //备份
	char* v2 = (char*)malloc(LEN * sizeof(char)); strcpy(v2, ver2);

	Version* version = (Version*)malloc(2*sizeof(Version));
	
	To_struct(version, ver1,0);
	To_struct(version, ver2, 1);


	Ver_cmp(version,v1,v2);

	free(ver1); free(ver2);
	free(v1); free(v2);
	free(version);
	return 0;
}
//2.5.1 - C
//1.4.2 - D
