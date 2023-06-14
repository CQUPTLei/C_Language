#include <stdio.h>

typedef struct{
    int num1;
    int num2;
}Num;

// 只传递结构体成员
int func_1(int a,int b){
    return a>b? a:b;
}

// 传递结构体指针
int func_2(const Num *tmp){
    return tmp->num1 > tmp->num2? tmp->num1 : tmp->num2;
}

// 传递结构体 
int func_3(const Num tmp){
    return tmp.num1 > tmp.num2? tmp.num1 : tmp.num2;
}

int main(){
    Num num = {888,999};
    Num *p = &num;
    printf("%d\n",func_1(num.num1,num.num2));
    printf("%d\n",func_2(p));
    printf("%d\n",func_3(num));

    printf("%zd\n",sizeof(num));
    return 0;
}

