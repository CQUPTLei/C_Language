#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>

#define RECORD_LEN 1000

typedef struct {
	int id;
	int time;
	int dis;
	char id1[5];
	char id2[5];
	bool out;
}Records;

void Isnormal(Records *rec,int  num) {
	char count = 0;
	for (int i = 0; i < num; i++) { //设备号与注册号是否相同
		if (strncmp(rec[i].id1, rec[i].id2, 4) != 0) {
			rec[i].out = true;      //已经输出标志
			count++;
		}	
	}
	for (int i = 0; i < num-1; i++) { //距离、时间
		for (int j = 1; j < num; j++) {
			if ((rec[i].id == rec[j].id)) {
				if ((abs((rec[i].time - rec[j].time)) < 60) && (abs(rec[i].dis - rec[j].dis) > 5)) {
					if (rec[i].out == false) {
						rec[i].out = true;
						count++;
					}
					if (rec[j].out == false) {
						rec[j].out = true;
						count++;
					}
				}
			} 
		}
	}
	if (count == 0)
		puts("null");
	else
		for (int k = 0; k < num; k++) {
			if (rec[k].out == true) {
				if (k > 0 && k < count)
					printf(";");
				printf("%d,%d,%d,%s,%s", rec[k].id, rec[k].time, rec[k].dis, rec[k].id1, rec[k].id2);
			}
		}

}

int main() {
	int N; //打卡记录条数
	scanf("%d",&N);

	Records* record = (Records*)malloc(N * sizeof(Records));

	for (int i = 0; i < N; i++) {  //输入打卡记录
		char clockrecords[RECORD_LEN];
		scanf("%s",clockrecords);
		char(*tmp)[7];
		tmp = (char(*)[7])malloc(5 * 7 * sizeof(char));
		int n = 0;
		char* p = strtok(clockrecords,",");
		while (p != NULL) {
			strcpy(tmp[n++],p);
			p = strtok(NULL,",");
		}
		record[i].id = atoi(tmp[0]);
		record[i].time = atoi(tmp[1]);
		record[i].dis = atoi(tmp[2]);
		strcpy(record[i].id1,tmp[3]);
		strcpy(record[i].id2, tmp[4]);
		record[i].out = false;
		free(tmp);
	}

	Isnormal(record,N);
	free(record);
	return 0;
}