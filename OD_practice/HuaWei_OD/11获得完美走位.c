#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define MAX_NUM 100000

typedef struct{
    char letter[4] ;
    int count[4] ;
}Tab;

Tab table = { {'A','S','W','D'},{0,0,0,0} };

int main() {
    char* s;
    s = (char*)malloc(MAX_NUM * sizeof(char));

    scanf("%s", s);
    int len = strlen(s);

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < 4; j++) {
            if (s[i] == table.letter[j])
                table.count[j]++;
        }
    }

    int count = 0;
    for (int i = 0; i < 4; i++) {
        count += abs(table.count[i] -len / 4);
    }

    printf("%d",count/2);
    free(s);
    return 0;
}