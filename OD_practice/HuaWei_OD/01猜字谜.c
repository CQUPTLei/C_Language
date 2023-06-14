    #include<stdio.h>
    #include<string.h>

    #define WORD_NUM 100
    #define WORD_LEN 20

    // 判断两个字符串的字母去重后是否相同（每个字符是否出现的情况一样）
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

    // 判断两个字符串是否可以通过变换顺序得到(每个字符出现次数完全一样)
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
    
    // 读取谜底和谜面
    int read_input(char out[][WORD_LEN+1])
    {
        char in[WORD_NUM*(WORD_LEN+1)+1+1] = {0};           // 用一维数组获取输入

        fgets(in, WORD_NUM * (WORD_LEN + 1) + 1+1,stdin); // 三个+1：二维数组每行字符串结尾\0，一维输入时结尾\0，fgets的换行符
        in[strlen(in)-1] = '\0';  // gets函数会将字符串结尾的换行符读进来，这里去掉

        char str1[WORD_NUM * (WORD_LEN + 1) + 1] = { 0 };
        strcpy(str1, in);        // 拷贝一份，防止原字符串被修改

        int n = 0;
        char* p = NULL;
        for (p = strtok(str1, ","); p != NULL; p = strtok(NULL, ",")) {
            strcpy(out[n++],p);
        }
        return n; //返回单词数量
    }



    int main() {
        
        static char guess[WORD_NUM][WORD_LEN + 1]; // 谜面
        static char dict[WORD_NUM][WORD_LEN + 1];  // 谜底
        int count_g,count_d; // 单词计数器

        count_g = read_input(guess); // 读取谜面
        count_d = read_input(dict);  // 读取谜底


        char flag = 0;
        for (int i = 0; i < count_g; i++) {
            for (int j = 0; j < count_d; j++) {
                if (check(guess[i], dict[j]) || cmp(guess[i], dict[j])) {
                    flag = 1;
                    printf("%s,", dict[j]); // 这里，输出用逗号分隔，自行修改实现
                }
            }
        }
        if (!flag)
            printf("not found");
        return 0;
    }