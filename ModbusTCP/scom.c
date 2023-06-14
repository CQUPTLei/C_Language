#include"scom.h"
#include<stdio.h>

/********************************************
函数：open_scom()
功能：打开串口。
说明：以同步方式打开串口，打开正常返回串口
      操作句柄，失败返回-1
********************************************/  
HANDLE open_scom(char *serial_port, int baud_rate, int parity, int byte_size, int stop_bits)
{
	HANDLE hcom;
	hcom = CreateFile(serial_port,          //串口名称
					 GENERIC_READ | GENERIC_WRITE,  //允许读和写
					 0,                             //独占方式
					 NULL,
					 OPEN_EXISTING,                //打开而不是创建
					 0,                            //同步方式
					 NULL);
	if (hcom == INVALID_HANDLE_VALUE)
	{
		//printf("打开串口失败");
		return -1;                                //失败则返回 -1
	}

	/*设置串口属性 如波特率、停止位、数据位、校验位；超时间隔*/
	setup_scom(hcom, baud_rate, parity, byte_size, stop_bits); 

	read_test(hcom);        //读串口，并测试数据以确定帧头
	return hcom;	
}

/************************************************
函数：setup_scom()
功能：配置串行口。
说明：hcom 为打开串口返回的串口操作句柄；
	  parity    奇偶校验  设置示例 EVENPARITY 偶校验; ODDPARITY 奇校验; NOPARITY 无校验
	  stop_bits 停止位    设置示例 ONESTOPBIT 1位;  ONESSTOPBITS 1.5位; TWOSTOPBIT 2位
	  byte_size 数据位    设置示例 4,5,6,7,8
	  baud_rate 波特率    设置示例 115200
	  失败返回-1，正常返回1。	  
************************************************/
int
setup_scom(HANDLE hcom, int baud_rate, int parity, int byte_size, int stop_bits)
{
	//声明设置用结构体
	COMMTIMEOUTS TimeOuts;
	DCB dcb;

	/*配置串口*/
	if (!SetupComm(hcom,4096,4096))               //输入缓冲区和输出缓冲区的大小都是4096
		return -1;
	/*设定读超时*/
	TimeOuts.ReadIntervalTimeout = MAXWORD;  //设置为最大值，表示如果没读到指定字节数，串口会一直等待
	TimeOuts.ReadTotalTimeoutMultiplier = 0;
	TimeOuts.ReadTotalTimeoutConstant = 0;   //此项和上项都设置为0，表示一旦读到数据马上返回。

	/*设定写超时*/
	TimeOuts.WriteTotalTimeoutMultiplier = 500;
	TimeOuts.WriteTotalTimeoutConstant = 2000;
	
	/*将超时设置写入串口寄存器*/
	if (!SetCommTimeouts(hcom, &TimeOuts))
		return -1;                          //失败返回-1
	
	GetCommState(hcom, &dcb);            //获得串行口当前属性信息

	//根据应用程序需要修串行端口参数
	dcb.BaudRate = baud_rate;
	dcb.ByteSize = byte_size;
	dcb.Parity = parity;
	dcb.StopBits = stop_bits;

	//将修改后的DCB结构重新写回串口寄存器
	if (!SetCommState(hcom, &dcb))
		return -1;                           //失败返回-1
	
	//清空缓冲区，为读写串口端口做准备
	PurgeComm(hcom, PURGE_TXCLEAR | PURGE_RXCLEAR);
	
	return 1;
}

/************************************************
函数：read_test()
功能：读串行口，并测试数据寻找帧头。
说明：hcom 为打开串口返回的串口操作句柄，函数碰到
      帧尾0Xbb就会返回。(第一帧的数据将会因为测试而
	  被丢弃)
	  正常返回1，错误返回 -1。
************************************************/
int
read_test(HANDLE hcom)
{
	DWORD bReadStat;          //读状态变量
	DWORD wCount;             //实际读取字节数变量
   unsigned	char buffer;      //数据暂存变量,声明为无符号型变量是方便和0xaa比较

	do
	{
		bReadStat = ReadFile(hcom,    //串口句柄
			                 &buffer, //数据暂存变量
							 1,		  //设定一次读取一个字节
							 &wCount, //存放实际读取字节数
							 NULL);	
		if (!bReadStat)
		{
			//printf("读串口失败");
			return -1;
		}
	}while (buffer != 0xbb); //如果没读到0Xbb就一直读取
	
	return 1;
} 

/************************************************
函数：read_scom()
功能：读串行口,获取数据。
说明：hcom 为串口操作句柄, 
	    data[]数组(至少含9个成员)含有处理后的9轴数据。
	    正常返回1，错误返回 -1。
************************************************/
int
read_scom(HANDLE hcom, int data[])
{ 
	DWORD bReadStat;                    //读状态变量
	DWORD wCount;                       //实际读取字节数变量
	int i;
	int temp[23];                       //存放从buffer取过来的原始数据 ,(数据格式为十六进制，高低字节暂分两个变量存放)
	char buffer[23];                    //定义存放从串口读取数据的原始缓存，原始数据带符号
	bReadStat = ReadFile(hcom,          //串口操作句柄
						buffer,                   //接收缓冲区
						23,                       //设定一次读取的字节数
						&wCount,                  //实际读取的字节数，由ReadFile返回
						NULL);			
	if (!bReadStat) //如果读串口失败
	{
		//printf("读串口失败");
		return -1;
	}

	/*0xaa为帧头，0xbb为帧尾。通过判断帧头和帧尾来确定数据格式是否正确。将16进制常量强制转换为char型*/
	if ( buffer[0] !=(char)0xaa && buffer[22] != (char)0xbb ) 
	{
		read_test(hcom);    //如果数据不正确，则重新调整读取位置
		return -1;          //而且退出函数，以免出现错误赋值
	}

	for (i = 0; i < 23; i++)
	{
		temp[i] = buffer[i];  //将从串口读到的数据赋值给temp数组(十六进制，高低字节暂分成了连个变量存放)
	}	
	process_data(temp, data); //处理数据，将temp里的原始数据，处理合成到data数组中
	
	return 1;
}

/************************************************
函数：close_scom()
功能：关闭串口。
说明：调用API函数关闭串口。	  
************************************************/
void 
close_scom(HANDLE hcom)
{
	CloseHandle(hcom);
}

/************************************************
函数：process_data()
功能：将高低字节分离的两个变量合成到一个变量中。
说明：temp[]数组(至少含有23个元素)为高低字节分离原
      始数据，data[]数组(至少含9个成员)含有处理后
	    的9轴数据。
************************************************/
void process_data(int temp[], int data[])
{
	int i;
	int step;
	int mask = 0; //掩膜变量，用来清零temp成员中的固定位
	mask |= 0xff; //将mask的第0-7位置1
	for (i = 0, step = 6; i < 3; i++)
	{
		//将x轴数据(加速度计，陀螺仪，地磁仪)
		temp[3 + step * i] <<= 8;                //将数据左移8位，表示高位数据
		temp[4 + step * i] &= mask;              //将0-7位外的其他位清零，消除包含低字节变量的符号干扰
		temp[3 + step * i] |= temp[4 + step * i]; //低字节与高字节相或，把数据整理到一个变量中

		 //y轴数据(加速度计，陀螺仪，地磁仪)
		temp[5 + step * i] <<= 8;                //将数据左移8位，表示高位数据
		temp[6 + step * i] &= mask;              //将0-7位外的其他位清零，消除包含低字节变量的符号干扰
		temp[5 + step * i] |= temp[6 + step * i];//低字节与高字节相或，把数据整理到一个变量中

		//z轴数据(加速度计，陀螺仪，地磁仪)
		temp[7 + step * i] <<= 8;                //将数据左移8位，表示高位数据
		temp[8 + step * i] &= mask;              //将0-7位外的其他位清零，消除包含低字节变量的符号干扰
		temp[7 + step * i] |= temp[8 + step * i]; //低字节与高字节相或，把数据整理到一个变量中)
	}
	for (i = 0; i < 9; i++)
	{
		data[i] = temp[3 + 2 * i]; //temp数组中下标值为3,5,7,9,11,13,15,17,19的成员含有处理后的值
	}
}

