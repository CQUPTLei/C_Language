/*
* File_name：server.c
* Author：dahu
* Description：modbus tcp socket主要实现源文件
* Time：2021-04-21
* encoding：UTF-8
* Version：1.0
*/


/*********************************************************************
*                          Modbus-TCP报文帧格式
* |-----------------MBAP报头------------------|-----PDU-----|
* 
* 事务处理标识箱    协议表示符    长度    单元标识符   功能码   数据     
* 
    2Bytes          2Bytes    2Bytes    1Bytes    1Bytes  nBytes
exp:00 00         00  00      00 06     01         03     00 00   00 0A
**********************************************************************/


#include<stdio.h>
//#include<winsock2.h>
//#include"scom.h"
#include<sys/socket.h>
#include"respond.h"

#pragma comment(lib,"ws2_32.lib")                //使用静态链接库

#define BUF_SIZE 20                              //缓冲区大小
#define Request_Queue_len 20                     //请求队列最大长度 

const char *server_addr = "172.20.10.3";       //服务器IP地址
short port = 502;                                //服务器端口号  

void TCP_server(short port,const char *p);       //TCP服务器函数声明
void STM32_IO(void);                             //与STM32通信，有点问题，没使用到，用的模拟方法实现
void init();                                     //从站状态检查，本来应该是STM32开机自检，由于用的是模曲线拟，基本上没什么用



int main() {
	//初始化 DLL
	WSADATA wsaData;   
	WSAStartup(MAKEWORD(2, 2), &wsaData);        //初始化，以指明 WinSock 规范的版本

	init();
	TCP_server(port,server_addr);
	//STM32_IO();

	WSACleanup();                                 //终止 DLL 的使用
	return 0;
}


/*********************************************************************************************
* 名称：main(short port,const char* p)
* 功能：创建tcp服务器，与client通信
* 入口参数：port：端口号；p：ip地址，本机ipv4地址
* 返回参数：无
* 说明：无
**********************************************************************************************/
void TCP_server(short port,const char* p) {
	/*Windows下的socket函数原型:
	SOCKET socket(int af, int type, int protocol);
	Windows 不把套接字作为普通文件对待，而是返回 SOCKET 类型的句柄,如：
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	*/
	SOCKET server_socket;                                     //创建一个套接字，参数（地址簇，socket类型，使用的协议） 
	server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);


	struct sockaddr_in server_addr;                            //sockaddr_in结构体，可在ws2def.h中查看原型
	/*memset()函数原型是:extern void* memset(void* buffer, int c, int count)
	buffer：为指针或是数组, c：是赋给buffer的值,count：是buffer的长度.
	这个函数在socket中多用于清空数组.如:原型是memset(buffer, 0, sizeof(buffer))*/
	memset(&server_addr, 0, sizeof(server_addr));              //每个字节都用0填充
	server_addr.sin_family = AF_INET;                          //使用IPv4地址
	server_addr.sin_addr.s_addr = inet_addr(p);                //具体的IP地址,inet_addr是比较老的定义，要取消SDL检查。或者用inet_pton()函数
	server_addr.sin_port = htons(port);                        //端口

	/*Windows下的bind()函数原型:
	int bind(SOCKET sock, const struct sockaddr* addr, int addrlen);
	*/
	int bind_status = -1;
	bind_status = bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));           //将套接字与特定的IP地址和端口绑定起来

	if (bind_status == -1) {                                     //绑定状态监测，成功返回0，失败返回-1
		printf("绑定失败\n");
		exit(1);
	}
	else printf("套接字与IP地址、端口绑定成功\n");

	/*Windows下listeb()函数原型:
	int listen(SOCKET sock, int backlog);
	backlog 为请求队列的最大长度当套接字正在处理客户端请求时，如果有新的请求进来，套接字是没法处理的，只能把它放进缓冲区，待当前请求处理完毕后，再从缓冲区中读取出来处理。
	如果不断有新的请求进来，它们就按照先后顺序在缓冲区中排队，直到缓冲区满。这个缓冲区，就称为请求队列。
	*/
	int listen_status = -1;
	listen_status = listen(server_socket, Request_Queue_len);      //让套接字处于监听状态(并没有接收请求。接收请求需要使用 accept() 函数)

	if (listen(server_socket, 5) == -1) {                          //监听状态监测
		printf("监听失败\n");
		exit(1);
	}
	else printf("创建TCP服务器成功\nTCP连接正常，开始监听\n\n");

	/*Windows下accept()函数原型：
	SOCKET accept(SOCKET sock, struct sockaddr *addr, int *addrlen);
	accept() 返回一个新的套接字来和客户端通信，addr 保存了客户端的IP地址和端口号。后面和客户端通信时，要使用这个新生成的套接字，而不是原来服务器端的套接字。
	accept() 会阻塞程序执行（后面代码不能被执行），直到有新的请求到来
	*/
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	//char buff[BUF_SIZE] = { 0 };                                                   //缓冲区

	byte buff[BUF_SIZE] = {0};
	SOCKET clntSock = accept(server_socket, (SOCKADDR*)&clntAddr, &nSize);          //接收客户端请求
	printf("%d Link successfull\n", clntSock);


	while (1) {     

		//int recv(SOCKET sock, char *buf, int len, int flags);
		//int send(SOCKET sock, const char *buf, int len, int flags);

		int strLen = recv(clntSock, buff, BUF_SIZE, 0);         //接收客户端发来的数据,recv返回的是字节数

		if (strLen = 0)
			printf("客户端连接关闭\n\n");
		else if (strLen < 0) 
			printf("Linking Error");

		printf("\n\n**************************************************************************************************\n");
		//int length = buff[5];                                  //MBAP报文头，2+2+2+1   功能码1+起始地址2+数量2
		printf("收到报文为：\n");
		for (int i = 0;i < 12;i++)printf("0x0%x ", buff[i]);     //显示主站的请求报文
		printf("\n");

		solve_all(clntSock,buff);                                //根据功能码进行相应处理，从站返回相应报文

		memset(buff, 0, BUF_SIZE);                               //重置缓冲区
		//Sleep(1000);
	}

	closesocket(server_socket);                                   //关闭套接字
}




/*********************************************************************************************
* 名称：init()
* 功能：服务器端（从机）开机自检，但我没连接stm32，所以这个函数暂时是个空壳子
* 入口参数：无
* 返回参数：无
* 说明：无
**********************************************************************************************/
void init(void) {
	printf("从站状态检查...");
	printf("\n从站状态正常\n");
}




/*********************************************************************************************
* 名称： STM32_IO()
* 功能：与32通信，实现modbus tcp的AI、AO等
* 入口参数：无
* 返回参数：无
* 说明：调试不成功，暂时没使用
**********************************************************************************************/
void STM32_IO(void) {
	int data[9];  //
	HANDLE hcom;  //声明串口操作句柄
	hcom = open_scom("COM3", 9600, NOPARITY, 8, 1);//打开串口
	while (1)
	{
		read_scom(hcom, data);  //读串口
		// do someting;
		//break
		//printf("%d\n", data);
	}
	
	close_scom(hcom);         //关闭串口
}
