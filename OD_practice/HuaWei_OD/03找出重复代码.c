#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

int dp[MAX_LENGTH + 1][MAX_LENGTH + 1];   // 动态规划数组

int main()
{
    char text1[MAX_LENGTH + 1];
    char text2[MAX_LENGTH + 1];

    fgets(text1, MAX_LENGTH + 1, stdin);
    fgets(text2, MAX_LENGTH + 1, stdin);

    int len1 = strlen(text1) - 1, len2 = strlen(text2) - 1; // 长度不算回车符
    int max_len = 0, end_index = 0;    // 最长公共子串长度及其在text1中的结束位置

    // 初始化第0行和第0列
    for (int i = 0; i <= len1; i++)
        dp[i][0] = 0;
    for (int j = 0; j <= len2; j++)
        dp[0][j] = 0;


    // 动态规划求解(记录最后一个相同的字符的位置以及最大长度)
    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (text1[i - 1] == text2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] >= max_len) {  // 更新最长公共子串长度及其在text1中的结束位置
                    max_len = dp[i][j];
                    end_index = i - 1;
                }
            }
            else {
                dp[i][j] = 0;
            }
        }
    }

    // 结果输出
    if (max_len == 0) {   // 不存在公共子串
        printf("空字符串\n");
    }
    else {
        printf("%.*s\n", max_len, text1 + end_index - max_len + 1); // 输出公共子串（在text1中的位置）
        // `%.*s`是C语言中`printf`函数的一个转换说明符，它用于输出字符串的一部分，其中`.*`表示用后面传递的参数指定字符串的长度。
    }

    return 0;
}