#include <stdio.h>
#include <string.h>

// 去除字符串中重复字符
//首先统计了字符串中每个字母出现的次数，然后将出现次数为 1 的字符放到字符串的前面，
//最后将字符串截断。这样就可以去除字符串中的重复字符了。
//使用 `cnt` 数组来统计字符出现的次数，用 `pos` 来记录没有重复字符的位置。


void remove_duplicates(char* s) {

    int len = strlen(s);

    int cnt[26] = { 0 }, pos = 0;

    for (int i = 0; i < len; i++) {
        //int idx = s[i] - 'a';
        int idx = 0;
        if (s[i] >= 'A' && s[i] <= 'Z')
            idx = s[i] - 'A';
        else
            idx = s[i] - 'a';

        cnt[idx]++;  //统计每个字符出现的次数

        if (cnt[idx] == 1) {   //把出现一次的放在前面
            s[pos] = s[i];
            pos++;
        }
    }
    //printf("%d %d\n", cnt[0],cnt[1]);
    s[pos] = '\0';
}

//int main() {
//    char s[1005];
//    scanf("%s",s);
//
//    remove_duplicates(s);
//    printf("%s\n", s);
//
//    return 0;
//}