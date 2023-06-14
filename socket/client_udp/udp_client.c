#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")  //加载 socket静态库

#define BUF_SIZE 1024
#define SERVER_IP "192.168.31.39"   // 这里是他要连接的服务端的ip地址和端口号
#define PORT 8888

int main() {
    WSADATA wsaData;
    // 初始化 Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed.\n");
        return 1;
    }

    SOCKET clientSocket;
    struct sockaddr_in serverAddr;  // 它连接的服务端的ip地址结构体
    char buffer[BUF_SIZE];

    // 创建套接字
    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        printf("Failed to create socket.\n");
        WSACleanup();
        return 1;
    }

    // 设置服务器地址和端口
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    serverAddr.sin_port = htons(PORT);


    while (1) {
        printf("\nEnter message to send (max %d characters, exit to close):", BUF_SIZE);
        fgets(buffer, BUF_SIZE, stdin);
        buffer[strlen(buffer) - 1] = '\0';

        // 发送数据到服务器
        if (sendto(clientSocket, buffer, (int)strlen(buffer), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            printf("Failed to send data.\n");
            closesocket(clientSocket);
            WSACleanup();
            return 1;
        }

        if (strcmp(buffer, "exit") == 0)break;

        // 接收服务器的回应数据
        int serverAddrLen = sizeof(serverAddr);
        int recvLen = recvfrom(clientSocket, buffer, BUF_SIZE, 0, (struct sockaddr*)&serverAddr, &serverAddrLen);
        if (recvLen == SOCKET_ERROR) {
            printf("Failed to receive response.\n");
            closesocket(clientSocket);
            WSACleanup();
            return 1;
        }

        // 处理接收到的数据
        buffer[recvLen] = '\0';
        printf("Received response from server: %s\n", buffer);
    }

    // 关闭套接字和清理 Winsock
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}