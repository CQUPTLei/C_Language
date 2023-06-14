#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")  //���� socket��̬��

#define BUF_SIZE 1024
#define SERVER_IP "192.168.31.39"   // ��������Ҫ���ӵķ���˵�ip��ַ�Ͷ˿ں�
#define PORT 8888

int main() {
    WSADATA wsaData;
    // ��ʼ�� Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed.\n");
        return 1;
    }

    SOCKET clientSocket;
    struct sockaddr_in serverAddr;  // �����ӵķ���˵�ip��ַ�ṹ��
    char buffer[BUF_SIZE];

    // �����׽���
    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        printf("Failed to create socket.\n");
        WSACleanup();
        return 1;
    }

    // ���÷�������ַ�Ͷ˿�
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    serverAddr.sin_port = htons(PORT);


    while (1) {
        printf("\nEnter message to send (max %d characters, exit to close):", BUF_SIZE);
        fgets(buffer, BUF_SIZE, stdin);
        buffer[strlen(buffer) - 1] = '\0';

        // �������ݵ�������
        if (sendto(clientSocket, buffer, (int)strlen(buffer), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            printf("Failed to send data.\n");
            closesocket(clientSocket);
            WSACleanup();
            return 1;
        }

        if (strcmp(buffer, "exit") == 0)break;

        // ���շ������Ļ�Ӧ����
        int serverAddrLen = sizeof(serverAddr);
        int recvLen = recvfrom(clientSocket, buffer, BUF_SIZE, 0, (struct sockaddr*)&serverAddr, &serverAddrLen);
        if (recvLen == SOCKET_ERROR) {
            printf("Failed to receive response.\n");
            closesocket(clientSocket);
            WSACleanup();
            return 1;
        }

        // ������յ�������
        buffer[recvLen] = '\0';
        printf("Received response from server: %s\n", buffer);
    }

    // �ر��׽��ֺ����� Winsock
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}