#include <stdio.h>

typedef struct{
    char early_aalbum [2][20];
}Album;

typedef struct{
    char first[10];
    char last[10];
    int age;
    Album album;
}Name;

int main(){
    Name singer[2]={
        {"Jay","Chou",18,{"《Jay》","《Fantasy》"}},
        {"David","Tao",888,{"《David Tao》","《I'm OK》"}},
    };
    
    Album *p = &singer[0].album;

    for(int i=0;i<2;i++)printf("%s %s,  %d,  Album:  %s, %s\n", singer[i].first,singer[i].last,singer[i].age,
                               singer[i].album.early_aalbum[0],singer[i].album.early_aalbum[1]);

    printf("His first albul is: %s\n",p->early_aalbum[0]);
    printf("His first albul is: %s\n",singer[0].album.early_aalbum[0]);
    printf("His first albul is: %s\n",(*p).early_aalbum[0]);

    printf("%zd\n",sizeof(singer));

    return 0;
}
