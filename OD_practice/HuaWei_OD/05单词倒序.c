#include <stdio.h>
#include <string.h>

int main() {

    char sentence[101]; 
    fgets(sentence, 100, stdin); 

    int len = strlen(sentence); // ��ȡ�ַ�������

    int start = 0; // ���ʵ���ʼλ��
    int end = 0;   // ���ʵ���ֹλ��

    int i;
    for (i = 0; i < len; i++) {
        if (sentence[i] == ' ' || sentence[i] == ',' || sentence[i] == '.' || sentence[i] == '?') {
            // ��������ָ�������ǰ��ĵ����������
            end = i - 1; // ���ʵ���ֹλ��
            int j;
            for (j = end; j >= start; j--)
                printf("%c", sentence[j]);
            printf("%c", sentence[i]); // ����ָ���
            start = i + 1; // ��һ�����ʵ���ʼλ��
        }
    }
    return 0;
}