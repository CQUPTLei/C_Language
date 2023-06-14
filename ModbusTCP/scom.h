#ifndef _SCOM_H_
#define _SCOM_H_

#include<windows.h>             //需要调用win32 API

extern HANDLE open_scom(char *serial_port,int baud_rate, int parity, int byte_size, int stop_bits);   //打开串口
extern int read_scom(HANDLE hcom, int data[]);          //读串口
extern void close_scom(HANDLE hcom);                                //关闭串口
static int setup_scom(HANDLE hcom, int baud_rate, int parity, int byte_size, int stop_bits); //设置串口
static int read_test(HANDLE hcom);                                  //读串口测试，用来寻找帧头
static void process_data(int temp[], int data[]);                   //处理数据，以data[]数组形式输出9轴数据


#endif


/****************************************************************

说明：以上函数只调用标注有extern的三个函数，在这三个函数中会自
动调用标注static的函数。
      具体工作流程为1.打开串口；2.读串口；3.关闭串口
一个典型的示例为：
int data[9];  //用来存放9轴的数据
HANDLE hcom;  //声明串口操作句柄
hcom = open_scom("COM1", 115200, NOPARITY, 8, 1);//打开串口
while(1)
{
	read_scom(hcom,  data);  //读串口
	// do someting;
	//break;
}
close_scom(hcom);         //关闭串口
****************************************************************/