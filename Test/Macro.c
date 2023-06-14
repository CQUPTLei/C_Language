#include <stdio.h>

fmax(int b[], int t)
{
    int i, imax;
    imax = b[0];
    for (i = 1; i < t; i++)
        if (b[i] > imax) imax = b[i];
    return (imax);
}


main()
{
    int a[10], i, jmax;
    for (i = 0; i < 10; ++i)
        scanf("%d" , &a[i]);
    jmax = fmax(a, 10);
    printf("%d" , jmax);
}
