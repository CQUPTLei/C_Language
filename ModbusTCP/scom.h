#ifndef _SCOM_H_
#define _SCOM_H_

#include<windows.h>             //��Ҫ����win32 API

extern HANDLE open_scom(char *serial_port,int baud_rate, int parity, int byte_size, int stop_bits);   //�򿪴���
extern int read_scom(HANDLE hcom, int data[]);          //������
extern void close_scom(HANDLE hcom);                                //�رմ���
static int setup_scom(HANDLE hcom, int baud_rate, int parity, int byte_size, int stop_bits); //���ô���
static int read_test(HANDLE hcom);                                  //�����ڲ��ԣ�����Ѱ��֡ͷ
static void process_data(int temp[], int data[]);                   //�������ݣ���data[]������ʽ���9������


#endif


/****************************************************************

˵�������Ϻ���ֻ���ñ�ע��extern�������������������������л���
�����ñ�עstatic�ĺ�����
      ���幤������Ϊ1.�򿪴��ڣ�2.�����ڣ�3.�رմ���
һ�����͵�ʾ��Ϊ��
int data[9];  //�������9�������
HANDLE hcom;  //�������ڲ������
hcom = open_scom("COM1", 115200, NOPARITY, 8, 1);//�򿪴���
while(1)
{
	read_scom(hcom,  data);  //������
	// do someting;
	//break;
}
close_scom(hcom);         //�رմ���
****************************************************************/