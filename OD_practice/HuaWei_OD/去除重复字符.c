#include <stdio.h>
#include <string.h>

// ȥ���ַ������ظ��ַ�
//����ͳ�����ַ�����ÿ����ĸ���ֵĴ�����Ȼ�󽫳��ִ���Ϊ 1 ���ַ��ŵ��ַ�����ǰ�棬
//����ַ����ضϡ������Ϳ���ȥ���ַ����е��ظ��ַ��ˡ�
//ʹ�� `cnt` ������ͳ���ַ����ֵĴ������� `pos` ����¼û���ظ��ַ���λ�á�


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

        cnt[idx]++;  //ͳ��ÿ���ַ����ֵĴ���

        if (cnt[idx] == 1) {   //�ѳ���һ�εķ���ǰ��
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