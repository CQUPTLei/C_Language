#include <stdio.h>

int main()
{
	double a, b, c;
	printf("Type in two numbers:\n");
	scanf("%f %f", &a, &b);
	printf("%f %f\n", a, b);
	c = a / b;
	printf("%.1f\n", c);
	printf("%.1f is %.2f  of %.1f", a, c, b);
	return 0;
}