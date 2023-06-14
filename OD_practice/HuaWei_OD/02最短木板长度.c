#include <stdio.h>
#include <stdlib.h>

#define MAX_n 1000  // ���ľ�����

int a[MAX_n];       // ÿ��ľ�峤��

int main() {

    int n, m, i, j;
    // �ܳ����
    long long sum = 0, max_len = 0;  //long long��ģ�峤�ȿ��Դﵽ10^6

    scanf("%d %d", &n, &m);
    for (i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
        sum += a[i];
        if (max_len < a[i])
            max_len = a[i];
    }

    long long left = 1, right = sum + m;
    while (left <= right) {
        long long mid = (left + right) / 2;
        long long len = 0;
        for (i = 0; i < n; ++i)
            len += (a[i] > mid ? mid : a[i]);
        if (len + m >= mid * n)
            max_len = mid, left = mid + 1;
        else
            right = mid - 1;
    }

    printf("%lld\n", max_len);
    return 0;
}