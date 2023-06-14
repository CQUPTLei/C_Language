#include <stdio.h>
#include <string.h>

int main() {

    char sentence[101]; 
    fgets(sentence, 100, stdin); 

    int len = strlen(sentence); // 获取字符串长度

    int start = 0; // 单词的起始位置
    int end = 0;   // 单词的终止位置

    int i;
    for (i = 0; i < len; i++) {
        if (sentence[i] == ' ' || sentence[i] == ',' || sentence[i] == '.' || sentence[i] == '?') {
            // 如果遇到分隔符，则将前面的单词逆序输出
            end = i - 1; // 单词的终止位置
            int j;
            for (j = end; j >= start; j--)
                printf("%c", sentence[j]);
            printf("%c", sentence[i]); // 输出分隔符
            start = i + 1; // 下一个单词的起始位置
        }
    }
    return 0;
}