    #include<stdio.h>
    #include<string.h>

    #define WORD_NUM 100
    #define WORD_LEN 20

    // �ж������ַ�������ĸȥ�غ��Ƿ���ͬ��ÿ���ַ��Ƿ���ֵ����һ����
    int cmp(char* a, char* b) {

        int ha[26] = { 0 }, hb[26] = { 0 };
        int lena = strlen(a), lenb = strlen(b);

        for (int i = 0; i < lena; i++) 
            ha[a[i] - 'a'] = 1;
        for (int i = 0; i < lenb; i++)
            hb[b[i] - 'a'] = 1;

        for (int i = 0; i < 26; i++) {
            if (ha[i] != hb[i]) 
                return 0;
        }
        return 1;
    }

    // �ж������ַ����Ƿ����ͨ���任˳��õ�(ÿ���ַ����ִ�����ȫһ��)
    int check(char* a, char* b) {

        int lena = strlen(a), lenb = strlen(b);

        if (lena != lenb) 
            return 0;

        int cnta[26] = { 0 }, cntb[26] = { 0 };

        for (int i = 0; i < lena; i++) {
            cnta[a[i] - 'a']++;
            cntb[b[i] - 'a']++;
        }
        for (int i = 0; i < 26; i++) {
            if (cnta[i] != cntb[i]) 
                return 0;
        }
        return 1;
    }
    
    // ��ȡ�յ׺�����
    int read_input(char out[][WORD_LEN+1])
    {
        char in[WORD_NUM*(WORD_LEN+1)+1+1] = {0};           // ��һά�����ȡ����

        fgets(in, WORD_NUM * (WORD_LEN + 1) + 1+1,stdin); // ����+1����ά����ÿ���ַ�����β\0��һά����ʱ��β\0��fgets�Ļ��з�
        in[strlen(in)-1] = '\0';  // gets�����Ὣ�ַ�����β�Ļ��з�������������ȥ��

        char str1[WORD_NUM * (WORD_LEN + 1) + 1] = { 0 };
        strcpy(str1, in);        // ����һ�ݣ���ֹԭ�ַ������޸�

        int n = 0;
        char* p = NULL;
        for (p = strtok(str1, ","); p != NULL; p = strtok(NULL, ",")) {
            strcpy(out[n++],p);
        }
        return n; //���ص�������
    }



    int main() {
        
        static char guess[WORD_NUM][WORD_LEN + 1]; // ����
        static char dict[WORD_NUM][WORD_LEN + 1];  // �յ�
        int count_g,count_d; // ���ʼ�����

        count_g = read_input(guess); // ��ȡ����
        count_d = read_input(dict);  // ��ȡ�յ�


        char flag = 0;
        for (int i = 0; i < count_g; i++) {
            for (int j = 0; j < count_d; j++) {
                if (check(guess[i], dict[j]) || cmp(guess[i], dict[j])) {
                    flag = 1;
                    printf("%s,", dict[j]); // �������ö��ŷָ��������޸�ʵ��
                }
            }
        }
        if (!flag)
            printf("not found");
        return 0;
    }