#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

int dp[MAX_LENGTH + 1][MAX_LENGTH + 1];   // ��̬�滮����

int main()
{
    char text1[MAX_LENGTH + 1];
    char text2[MAX_LENGTH + 1];

    fgets(text1, MAX_LENGTH + 1, stdin);
    fgets(text2, MAX_LENGTH + 1, stdin);

    int len1 = strlen(text1) - 1, len2 = strlen(text2) - 1; // ���Ȳ���س���
    int max_len = 0, end_index = 0;    // ������Ӵ����ȼ�����text1�еĽ���λ��

    // ��ʼ����0�к͵�0��
    for (int i = 0; i <= len1; i++)
        dp[i][0] = 0;
    for (int j = 0; j <= len2; j++)
        dp[0][j] = 0;


    // ��̬�滮���(��¼���һ����ͬ���ַ���λ���Լ���󳤶�)
    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (text1[i - 1] == text2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] >= max_len) {  // ����������Ӵ����ȼ�����text1�еĽ���λ��
                    max_len = dp[i][j];
                    end_index = i - 1;
                }
            }
            else {
                dp[i][j] = 0;
            }
        }
    }

    // ������
    if (max_len == 0) {   // �����ڹ����Ӵ�
        printf("���ַ���\n");
    }
    else {
        printf("%.*s\n", max_len, text1 + end_index - max_len + 1); // ��������Ӵ�����text1�е�λ�ã�
        // `%.*s`��C������`printf`������һ��ת��˵����������������ַ�����һ���֣�����`.*`��ʾ�ú��洫�ݵĲ���ָ���ַ����ĳ��ȡ�
    }

    return 0;
}