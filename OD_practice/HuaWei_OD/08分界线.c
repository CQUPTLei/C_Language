#include <stdio.h>
#include <string.h>
#include<stdlib.h>

#define MAX_LEN 10005

// ����һ���ṹ�壬�����洢ÿ��������ÿ����ĸ���ֵĴ���
typedef struct LetterCnt {
    int cnt[26];
} LetterCnt;


// ͳ���ַ�����ÿ����ĸ������
LetterCnt countLetter(char* s, int len) {
    LetterCnt cnt = { 0 };
    for (int i = 0; i < len; i++) {
        cnt.cnt[s[i] - 'a']++;
    }
    return cnt;
}

int main() {

    char* newspaper, * anonymousLetter;
    newspaper = (char*)malloc(MAX_LEN * sizeof(char));
    anonymousLetter = (char*)malloc(MAX_LEN * sizeof(char));

    fgets(newspaper, MAX_LEN, stdin);
    fgets(anonymousLetter, MAX_LEN, stdin);


    char ok = 0; //ƥ��ɹ���־
    char* pl = strtok(anonymousLetter," "); //��letter��ÿ�����ʣ����newspaper���Ƿ������������ĵ���
    while (pl != NULL) {
        int n = strlen(pl);
        LetterCnt cntLetter = countLetter(pl, n);

        char* news = newspaper;        //����
        char* ptr = strtok(news, " "); // �Ƚϵ�ǰ��������ĸ�������Ƿ���anonymousLetter��ÿ�������е�������ͬ
        while (ptr != NULL) {
            int len = strlen(ptr);
            LetterCnt curCnt = countLetter(ptr, len);

            int flag = 1;
            for (int i = 0; i < 26; i++) {
                // ע�⣬ÿ����ĸֻ�ܳ���һ�Σ���������ÿ�������в������ظ���ĸ�룩
                // ���Ҫ�������������в������ظ�����ĸ�����������ж�һ�¾�����
                // �����Ѿ�ȫ��ͨ���ˣ�������û��ȫ��ͨ�����ͼ������������
                if ((curCnt.cnt[i] != cntLetter.cnt[i])||cntLetter.cnt[i]>1) {
                    flag = 0;
                    break;
                }
            }

            if (flag) {
                ok++;
            }

            ptr = strtok(NULL, " ");
        }
        pl = strtok(NULL, " ");
    }

    if (ok > 0)
        puts("true");
    else
        puts("false");

    free(newspaper);
    free(anonymousLetter);
    return 0;
}