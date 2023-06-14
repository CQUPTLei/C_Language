#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib") 

#define server_ip "192.168.31.39"
#define PORT 8080
#define BUF_SIZE 1024


int main() { 

    // 初始化Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("无法初始化Winsock\n");
        return 1;
    }

    SOCKET clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[BUF_SIZE];

    // 创建客户端套接字
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        printf("无法创建套接字\n");
        return 1;
    }

    // 设置服务器地址和端口
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(server_ip);


    // 连接服务器
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("连接服务器失败\n");
        return 1;
    }

    printf("与服务器建立连接成功\n");

    while (1) {
        // 发送数据给服务器
        memset(buffer, 0, sizeof(buffer));
        printf("\n输入要发送的数据，exit退出：");
        fgets(buffer,BUF_SIZE,stdin);
        buffer[strlen(buffer) - 1] = '\0';

        if (send(clientSocket, buffer, (int)strlen(buffer), 0) == SOCKET_ERROR) {
            printf("发送数据失败\n");
            return 1;
        }

        if (strcmp(buffer, "exit") == 0)break;

        // 接收服务器的响应
        memset(buffer, 0, BUF_SIZE);
        if (recv(clientSocket, buffer, BUF_SIZE, 0) == SOCKET_ERROR) {
            printf("接收响应失败\n");
            return 1;
        }
        printf("从服务器接收到的响应：%s\n", buffer);
    
    }

    // 关闭连接
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}