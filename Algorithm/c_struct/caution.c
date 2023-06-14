#include <stdio.h>

typedef struct{
    int a;
    int b;
    char arr[10];
    char *p;
}Test;

int main(){
    //char str[20]="Hello,C language.";
    Test var = {11,22,{[5]='B'},"Hello,C language."};
    puts("The content of var:");
    printf("a: %d\nb: %d\narr: ",var.a,var.b);
    for(int i=0;i<10;i++)printf("%c ",var.arr[i]);
    printf("\n*p: %s\n",var.p);

    printf("Size of var is: %zd\n",sizeof(var));
    printf("成员变量的地址：\na:   %p\nb:   %p\narr:  %p\narr+10:   %p\np:   %p\n",&var.a,&var.b,var.arr,var.arr+10,&var.p);
    
    return 0;
}
