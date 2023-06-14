#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")  //加载 socket静态库
 
#define BUF_SIZE 1024  // 缓冲区大小
#define PORT 8888      // 端口号

int main() {
    // 初始化 Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {   //请求的winsock版本是winsock2
        printf("WSAStartup failed.\n");
        return 1;
    }

    SOCKET serverSocket;                        // 服务端、客户端套接字句柄
    struct sockaddr_in serverAddr, clientAddr;  // ipv4地址结构体
    int clientAddrLen = sizeof(clientAddr);     // 客户端地址结构体长度
    char buffer[BUF_SIZE];                      // 缓冲区

    // 创建套接字
    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);    // ipv4地址，数据报套接字，根据套接字自动选择协议类型（即UDP）
    if (serverSocket == INVALID_SOCKET) {
        printf("Failed to create socket.\n");
        WSACleanup();
        return 1;
    }

    // 设置服务器地址和端口
    memset(&serverAddr, 0, sizeof(serverAddr));  //每个字节都用0填充
    serverAddr.sin_family = AF_INET;             // 协议
   // serverAddr.sin_addr.s_addr = INADDR_ANY;     // 地址（即0.0.0.0，监听本机所有网卡），写成：“127.0.0.1”也可以
    serverAddr.sin_addr.s_addr = inet_addr("192.168.31.39");
    serverAddr.sin_port = htons(PORT);           // 端口

    // 绑定套接字
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Failed to bind socket.\n");
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    printf("UDP server started. Waiting for data...\n");

    // 接收和发送数据
    while (1) {
        int recvLen = recvfrom(serverSocket, buffer, BUF_SIZE, 0, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (recvLen == SOCKET_ERROR) {
            printf("Failed to receive data.\n");
            break;
        }

        // 处理接收到的数据
        buffer[recvLen] = '\0';
        printf("Received data from client: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0) break;  // 收到exit时退出

        // 发送回应数据给客户端
        const char* response = "I've got it.";
        if (sendto(serverSocket, response, (int)strlen(response), 0, (struct sockaddr*)&clientAddr, clientAddrLen) == SOCKET_ERROR) {
            printf("Failed to send response.\n");
            break;
        }
    }

    // 关闭套接字和清理 Winsock
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}