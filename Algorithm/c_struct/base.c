#include <stdio.h>

typedef struct{
    char first[10];
    char last[10];
    int age;
}Name;

int main(){
    Name singer[2]={
        {"Jay","Chou",18},
        {"David","Tao",888},
    };

    for(int i=0;i<2;i++)printf("%s %s,%d\n",singer[i].first,singer[i].last,singer[i].age);

    return 0;
}
