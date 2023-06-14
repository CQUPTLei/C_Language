#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 500 //�������100�����ص㣬ÿ���������ռ3��char
#define PIX_NUM 100

void find_k(const char* line) {

    int k = 0;
    int img[PIX_NUM];          //���100�����ص�
    int pix_num = 0,sum=0;     //ʵ����������ص�����������ֵ�ĺ�
    char* p = strtok((char*)line, " "); //��������ַ�����ֳ�����Ԫ�أ��������ܺ�
    while (p != NULL) {
        sum += atoi(p);
        img[pix_num++] = atoi(p);
        p = strtok(NULL, " ");
    }

    int avg = sum / pix_num; //ԭ����ƽ������ֵ
    int diff = avg - 128;    //128��ƽ��ֵ�Ĳ�ֵ

    //int newImg[pix_num]; // �µ�img
    int* newImg = (int*)malloc(sizeof(int)*pix_num);
    memcpy(newImg, img, sizeof(int)*pix_num);

    if (diff > 0) { //��ֵ����0���ͼ�һ����ֵ
        while (avg > 127) { //���ڸ���k,Ҫ������С������������127
            k--;
            for (int i = 0; i < pix_num; i++) {
                if (newImg[i] - 1 < 0) { //��������Ϊ0
                    newImg[i] = 0;
                } else {
                    newImg[i] -= 1;
                }
            }
            sum = 0;
            for (int i = 0; i < pix_num; i++) {
                sum += newImg[i];
            }
            avg = sum / pix_num;
        }
    }

    if (diff < 0) {
        while (avg < 128) {
            k++;
            for (int i = 0; i < pix_num; i++) {
                if (newImg[i] + 1 > 255) {
                    newImg[i] = 255;
                } else {
                    newImg[i] += 1;
                }
            }
            sum = 0;
            for (int i = 0; i < pix_num; i++) {
                sum += newImg[i];
            }
            avg = sum / pix_num;
        }
    }
    printf("%d",k);
    free(newImg);
}

int main() {

    char* line;
    line = (char*)malloc(MAX_LEN*sizeof(char));
    fgets(line, sizeof(line), stdin); 
    line[strcspn(line, "\n")] = '\0'; //�ӻس�����ȡ
    
    find_k(line);

    free(line);
    return 0;
}
