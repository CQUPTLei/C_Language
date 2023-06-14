#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 500 //最多输入100个像素点，每个像素最多占3个char
#define PIX_NUM 100

void find_k(const char* line) {

    int k = 0;
    int img[PIX_NUM];          //最多100个像素点
    int pix_num = 0,sum=0;     //实际输入的像素点数量、像素值的和
    char* p = strtok((char*)line, " "); //将输入的字符串拆分成数组元素，并计算总和
    while (p != NULL) {
        sum += atoi(p);
        img[pix_num++] = atoi(p);
        p = strtok(NULL, " ");
    }

    int avg = sum / pix_num; //原来的平均像素值
    int diff = avg - 128;    //128和平均值的差值

    //int newImg[pix_num]; // 新的img
    int* newImg = (int*)malloc(sizeof(int)*pix_num);
    memcpy(newImg, img, sizeof(int)*pix_num);

    if (diff > 0) { //差值大于0，就加一个负值
        while (avg > 127) { //对于负数k,要尽可能小，所以这里是127
            k--;
            for (int i = 0; i < pix_num; i++) {
                if (newImg[i] - 1 < 0) { //负数设置为0
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
    line[strcspn(line, "\n")] = '\0'; //从回车符截取
    
    find_k(line);

    free(line);
    return 0;
}
