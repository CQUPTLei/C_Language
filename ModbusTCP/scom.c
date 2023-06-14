#include"scom.h"
#include<stdio.h>

/********************************************
������open_scom()
���ܣ��򿪴��ڡ�
˵������ͬ����ʽ�򿪴��ڣ����������ش���
      ���������ʧ�ܷ���-1
********************************************/  
HANDLE open_scom(char *serial_port, int baud_rate, int parity, int byte_size, int stop_bits)
{
	HANDLE hcom;
	hcom = CreateFile(serial_port,          //��������
					 GENERIC_READ | GENERIC_WRITE,  //�������д
					 0,                             //��ռ��ʽ
					 NULL,
					 OPEN_EXISTING,                //�򿪶����Ǵ���
					 0,                            //ͬ����ʽ
					 NULL);
	if (hcom == INVALID_HANDLE_VALUE)
	{
		//printf("�򿪴���ʧ��");
		return -1;                                //ʧ���򷵻� -1
	}

	/*���ô������� �粨���ʡ�ֹͣλ������λ��У��λ����ʱ���*/
	setup_scom(hcom, baud_rate, parity, byte_size, stop_bits); 

	read_test(hcom);        //�����ڣ�������������ȷ��֡ͷ
	return hcom;	
}

/************************************************
������setup_scom()
���ܣ����ô��пڡ�
˵����hcom Ϊ�򿪴��ڷ��صĴ��ڲ��������
	  parity    ��żУ��  ����ʾ�� EVENPARITY żУ��; ODDPARITY ��У��; NOPARITY ��У��
	  stop_bits ֹͣλ    ����ʾ�� ONESTOPBIT 1λ;  ONESSTOPBITS 1.5λ; TWOSTOPBIT 2λ
	  byte_size ����λ    ����ʾ�� 4,5,6,7,8
	  baud_rate ������    ����ʾ�� 115200
	  ʧ�ܷ���-1����������1��	  
************************************************/
int
setup_scom(HANDLE hcom, int baud_rate, int parity, int byte_size, int stop_bits)
{
	//���������ýṹ��
	COMMTIMEOUTS TimeOuts;
	DCB dcb;

	/*���ô���*/
	if (!SetupComm(hcom,4096,4096))               //���뻺����������������Ĵ�С����4096
		return -1;
	/*�趨����ʱ*/
	TimeOuts.ReadIntervalTimeout = MAXWORD;  //����Ϊ���ֵ����ʾ���û����ָ���ֽ��������ڻ�һֱ�ȴ�
	TimeOuts.ReadTotalTimeoutMultiplier = 0;
	TimeOuts.ReadTotalTimeoutConstant = 0;   //������������Ϊ0����ʾһ�������������Ϸ��ء�

	/*�趨д��ʱ*/
	TimeOuts.WriteTotalTimeoutMultiplier = 500;
	TimeOuts.WriteTotalTimeoutConstant = 2000;
	
	/*����ʱ����д�봮�ڼĴ���*/
	if (!SetCommTimeouts(hcom, &TimeOuts))
		return -1;                          //ʧ�ܷ���-1
	
	GetCommState(hcom, &dcb);            //��ô��пڵ�ǰ������Ϣ

	//����Ӧ�ó�����Ҫ�޴��ж˿ڲ���
	dcb.BaudRate = baud_rate;
	dcb.ByteSize = byte_size;
	dcb.Parity = parity;
	dcb.StopBits = stop_bits;

	//���޸ĺ��DCB�ṹ����д�ش��ڼĴ���
	if (!SetCommState(hcom, &dcb))
		return -1;                           //ʧ�ܷ���-1
	
	//��ջ�������Ϊ��д���ڶ˿���׼��
	PurgeComm(hcom, PURGE_TXCLEAR | PURGE_RXCLEAR);
	
	return 1;
}

/************************************************
������read_test()
���ܣ������пڣ�����������Ѱ��֡ͷ��
˵����hcom Ϊ�򿪴��ڷ��صĴ��ڲ����������������
      ֡β0Xbb�ͻ᷵�ء�(��һ֡�����ݽ�����Ϊ���Զ�
	  ������)
	  ��������1�����󷵻� -1��
************************************************/
int
read_test(HANDLE hcom)
{
	DWORD bReadStat;          //��״̬����
	DWORD wCount;             //ʵ�ʶ�ȡ�ֽ�������
   unsigned	char buffer;      //�����ݴ����,����Ϊ�޷����ͱ����Ƿ����0xaa�Ƚ�

	do
	{
		bReadStat = ReadFile(hcom,    //���ھ��
			                 &buffer, //�����ݴ����
							 1,		  //�趨һ�ζ�ȡһ���ֽ�
							 &wCount, //���ʵ�ʶ�ȡ�ֽ���
							 NULL);	
		if (!bReadStat)
		{
			//printf("������ʧ��");
			return -1;
		}
	}while (buffer != 0xbb); //���û����0Xbb��һֱ��ȡ
	
	return 1;
} 

/************************************************
������read_scom()
���ܣ������п�,��ȡ���ݡ�
˵����hcom Ϊ���ڲ������, 
	    data[]����(���ٺ�9����Ա)���д�����9�����ݡ�
	    ��������1�����󷵻� -1��
************************************************/
int
read_scom(HANDLE hcom, int data[])
{ 
	DWORD bReadStat;                    //��״̬����
	DWORD wCount;                       //ʵ�ʶ�ȡ�ֽ�������
	int i;
	int temp[23];                       //��Ŵ�bufferȡ������ԭʼ���� ,(���ݸ�ʽΪʮ�����ƣ��ߵ��ֽ��ݷ������������)
	char buffer[23];                    //�����ŴӴ��ڶ�ȡ���ݵ�ԭʼ���棬ԭʼ���ݴ�����
	bReadStat = ReadFile(hcom,          //���ڲ������
						buffer,                   //���ջ�����
						23,                       //�趨һ�ζ�ȡ���ֽ���
						&wCount,                  //ʵ�ʶ�ȡ���ֽ�������ReadFile����
						NULL);			
	if (!bReadStat) //���������ʧ��
	{
		//printf("������ʧ��");
		return -1;
	}

	/*0xaaΪ֡ͷ��0xbbΪ֡β��ͨ���ж�֡ͷ��֡β��ȷ�����ݸ�ʽ�Ƿ���ȷ����16���Ƴ���ǿ��ת��Ϊchar��*/
	if ( buffer[0] !=(char)0xaa && buffer[22] != (char)0xbb ) 
	{
		read_test(hcom);    //������ݲ���ȷ�������µ�����ȡλ��
		return -1;          //�����˳�������������ִ���ֵ
	}

	for (i = 0; i < 23; i++)
	{
		temp[i] = buffer[i];  //���Ӵ��ڶ��������ݸ�ֵ��temp����(ʮ�����ƣ��ߵ��ֽ��ݷֳ��������������)
	}	
	process_data(temp, data); //�������ݣ���temp���ԭʼ���ݣ�����ϳɵ�data������
	
	return 1;
}

/************************************************
������close_scom()
���ܣ��رմ��ڡ�
˵��������API�����رմ��ڡ�	  
************************************************/
void 
close_scom(HANDLE hcom)
{
	CloseHandle(hcom);
}

/************************************************
������process_data()
���ܣ����ߵ��ֽڷ�������������ϳɵ�һ�������С�
˵����temp[]����(���ٺ���23��Ԫ��)Ϊ�ߵ��ֽڷ���ԭ
      ʼ���ݣ�data[]����(���ٺ�9����Ա)���д����
	    ��9�����ݡ�
************************************************/
void process_data(int temp[], int data[])
{
	int i;
	int step;
	int mask = 0; //��Ĥ��������������temp��Ա�еĹ̶�λ
	mask |= 0xff; //��mask�ĵ�0-7λ��1
	for (i = 0, step = 6; i < 3; i++)
	{
		//��x������(���ٶȼƣ������ǣ��ش���)
		temp[3 + step * i] <<= 8;                //����������8λ����ʾ��λ����
		temp[4 + step * i] &= mask;              //��0-7λ�������λ���㣬�����������ֽڱ����ķ��Ÿ���
		temp[3 + step * i] |= temp[4 + step * i]; //���ֽ�����ֽ���򣬰���������һ��������

		 //y������(���ٶȼƣ������ǣ��ش���)
		temp[5 + step * i] <<= 8;                //����������8λ����ʾ��λ����
		temp[6 + step * i] &= mask;              //��0-7λ�������λ���㣬�����������ֽڱ����ķ��Ÿ���
		temp[5 + step * i] |= temp[6 + step * i];//���ֽ�����ֽ���򣬰���������һ��������

		//z������(���ٶȼƣ������ǣ��ش���)
		temp[7 + step * i] <<= 8;                //����������8λ����ʾ��λ����
		temp[8 + step * i] &= mask;              //��0-7λ�������λ���㣬�����������ֽڱ����ķ��Ÿ���
		temp[7 + step * i] |= temp[8 + step * i]; //���ֽ�����ֽ���򣬰���������һ��������)
	}
	for (i = 0; i < 9; i++)
	{
		data[i] = temp[3 + 2 * i]; //temp�������±�ֵΪ3,5,7,9,11,13,15,17,19�ĳ�Ա���д�����ֵ
	}
}

