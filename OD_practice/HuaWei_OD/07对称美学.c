#include <stdio.h>
#include<stdlib.h>

char find(int n, long long k) {
    if (n == 1) 
        return 'R';
    if (k < (1LL << (n - 2))) 
        return find(n - 1, k) == 'R' ? 'B' : 'R'; //ǰһ����ȡ��
    else 
        return find(n - 1, k - (1LL << (n - 2))); //��һ������ǰһ���ַ�������
}

int main() {
    int T;
    scanf("%d", &T);

    int* n;
    long long* k;
    n = (int*)malloc(T * sizeof(int));
    k = (long long*)malloc(T * sizeof (long long));

    int count = T;
    while (count--)
        scanf("%d %lld", &n[T-count], &k[T-count]);
    count = T;
    while(count--)
        printf("%s\n", find(n[T-count], k[T-count]) == 'R' ? "red" : "blue");

    return 0;
}