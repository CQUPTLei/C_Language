#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib") 

#define ip "192.168.0.5"
#define PORT 8080
#define BUF_SIZE 1024

int main() {
    WSADATA wsaData;
    // 初始化Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("无法初始化Winsock\n");
        return 1;
    }

    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddress;
    char buffer[BUF_SIZE];

    // 创建服务器套接字
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        printf("无法创建套接字\n");
        return 1;
    }

    // 设置服务器地址和端口
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
   // serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_addr.s_addr = inet_addr(ip);
    serverAddr.sin_port = htons(PORT);

    // 绑定套接字到指定的地址和端口
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("绑定失败\n");
        return 1;
    }

    // 监听传入的连接
    if (listen(serverSocket, 1) == SOCKET_ERROR) {
        printf("监听失败\n");
        return 1;
    }

    printf("服务器正在监听端口 %d\n", PORT);

    // 接受传入的连接
    int clientAddressSize = sizeof(clientAddress);
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressSize);
    if (clientSocket == INVALID_SOCKET) {
        printf("接受连接失败\n");
        return 1;
    }

    printf("已经与客户端建立连接\n");

    while (1) {      
        // 接收来自客户端的数据
        memset(buffer, 0, sizeof(buffer));
        int recvLen = recv(clientSocket, buffer, BUF_SIZE, 0);
        if (recvLen == SOCKET_ERROR) {
            printf("接收数据失败\n");
            return 1;
        }

        buffer[recvLen] = '\0';
        printf("从客户端接收到的数据：%s\n", buffer);
        if (strcmp(buffer, "exit") == 0) break;

        if (send(clientSocket, buffer, (int)strlen(buffer), 0) == SOCKET_ERROR) {
            printf("发送响应失败\n");
            return 1;
        }    
    }

    // 关闭连接
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
