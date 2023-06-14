#include <stdio.h>
#include <string.h>

typedef struct {
    char unit[4];
    int rate;
} Rate_Tab;

// 汇率表1,元
Rate_Tab Yuan_rate[] = {
    {"CNY", 100},
    {"JPY", 1825},
    {"HKD", 123},
    {"EUR", 14},
    {"GBP", 12}
};

Rate_Tab Fen_rate[] = {
    {"fen",100},
    {"cen",123},
    {"sen",1825},
    {"eur",14},
    {"pen",12}
};


int main()
{
    int n;
    scanf("%d", &n);

    int sum = 0;
    for (int i = 0; i < n; i++) //分别计算每行输入，并求和
    {
        char line_in[100];
        scanf("%s", line_in);
        int len = strlen(line_in);

        int num1 = 0, num2 = 0; //num1表示（元），num2表示（分）
        int j = 0;
        while (j < len && line_in[j] >= '0' && line_in[j] <= '9') //计算第一个货币单位前的数字
        {
            num1 = num1 * 10 + line_in[j] - '0';
            j++;
        }
        for (int k = 0; k < sizeof(Yuan_rate) / sizeof(Rate_Tab); k++) //将（元）前面的数字换算成人民币，加在sum上
        {
            if (strncmp(line_in + j, Yuan_rate[k].unit, 3) == 0) // 与汇率表中的货币单位比较
            {
                sum += num1 * 10000 / Yuan_rate[k].rate;  // 最终结果单位是（人民币的分）
                j += 3;
                break;
            }
        }


        while (j < len && line_in[j] >= '0' && line_in[j] <= '9') //计算第二个货币单位前的数字
        {
            num2 = num2 * 10 + line_in[j] - '0';
            j++;
        }
        for (int m = 0; m < sizeof(Fen_rate) / sizeof(Rate_Tab); m++) 
        {
            if (strncmp(line_in + j, Fen_rate[m].unit, 3) == 0)
            {
                sum += num2 * 100 / Fen_rate[m].rate; 
                break;
            }
        
        }
    }
    // 题目说只保留整数，所以没有四舍五入（读者可自行修改）
    printf("%d\n", sum);
    return 0;
}