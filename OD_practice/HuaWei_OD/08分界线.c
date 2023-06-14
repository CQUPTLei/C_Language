#include <stdio.h>
#include <string.h>
#include<stdlib.h>

#define MAX_LEN 10005

// 定义一个结构体，用来存储每个单词中每个字母出现的次数
typedef struct LetterCnt {
    int cnt[26];
} LetterCnt;


// 统计字符串中每个字母的数量
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


    char ok = 0; //匹配成功标志
    char* pl = strtok(anonymousLetter," "); //对letter中每个单词，检查newspaper中是否有满足条件的单词
    while (pl != NULL) {
        int n = strlen(pl);
        LetterCnt cntLetter = countLetter(pl, n);

        char* news = newspaper;        //备份
        char* ptr = strtok(news, " "); // 比较当前单词中字母的数量是否与anonymousLetter中每个单词中的数量相同
        while (ptr != NULL) {
            int len = strlen(ptr);
            LetterCnt curCnt = countLetter(ptr, len);

            int flag = 1;
            for (int i = 0; i < 26; i++) {
                // 注意，每个字母只能出现一次（我这里是每个单词中不能有重复字母与）
                // 如果要求整个匿名信中不能有重复的字母，在外面先判断一下就行了
                // 例子已经全部通过了，考试若没有全部通过，就加上上面的条件
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