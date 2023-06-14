#include <stdio.h>
#include <string.h>

typedef struct {
    char unit[4];
    int rate;
} Rate_Tab;

// ���ʱ�1,Ԫ
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
    for (int i = 0; i < n; i++) //�ֱ����ÿ�����룬�����
    {
        char line_in[100];
        scanf("%s", line_in);
        int len = strlen(line_in);

        int num1 = 0, num2 = 0; //num1��ʾ��Ԫ����num2��ʾ���֣�
        int j = 0;
        while (j < len && line_in[j] >= '0' && line_in[j] <= '9') //�����һ�����ҵ�λǰ������
        {
            num1 = num1 * 10 + line_in[j] - '0';
            j++;
        }
        for (int k = 0; k < sizeof(Yuan_rate) / sizeof(Rate_Tab); k++) //����Ԫ��ǰ������ֻ��������ң�����sum��
        {
            if (strncmp(line_in + j, Yuan_rate[k].unit, 3) == 0) // ����ʱ��еĻ��ҵ�λ�Ƚ�
            {
                sum += num1 * 10000 / Yuan_rate[k].rate;  // ���ս����λ�ǣ�����ҵķ֣�
                j += 3;
                break;
            }
        }


        while (j < len && line_in[j] >= '0' && line_in[j] <= '9') //����ڶ������ҵ�λǰ������
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
    // ��Ŀ˵ֻ��������������û���������루���߿������޸ģ�
    printf("%d\n", sum);
    return 0;
}