#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib") 

#define ip "192.168.0.5"
#define PORT 8080
#define BUF_SIZE 1024

int main() {
    WSADATA wsaData;
    // ��ʼ��Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("�޷���ʼ��Winsock\n");
        return 1;
    }

    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddress;
    char buffer[BUF_SIZE];

    // �����������׽���
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        printf("�޷������׽���\n");
        return 1;
    }

    // ���÷�������ַ�Ͷ˿�
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
   // serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_addr.s_addr = inet_addr(ip);
    serverAddr.sin_port = htons(PORT);

    // ���׽��ֵ�ָ���ĵ�ַ�Ͷ˿�
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("��ʧ��\n");
        return 1;
    }

    // �������������
    if (listen(serverSocket, 1) == SOCKET_ERROR) {
        printf("����ʧ��\n");
        return 1;
    }

    printf("���������ڼ����˿� %d\n", PORT);

    // ���ܴ��������
    int clientAddressSize = sizeof(clientAddress);
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressSize);
    if (clientSocket == INVALID_SOCKET) {
        printf("��������ʧ��\n");
        return 1;
    }

    printf("�Ѿ���ͻ��˽�������\n");

    while (1) {      
        // �������Կͻ��˵�����
        memset(buffer, 0, sizeof(buffer));
        int recvLen = recv(clientSocket, buffer, BUF_SIZE, 0);
        if (recvLen == SOCKET_ERROR) {
            printf("��������ʧ��\n");
            return 1;
        }

        buffer[recvLen] = '\0';
        printf("�ӿͻ��˽��յ������ݣ�%s\n", buffer);
        if (strcmp(buffer, "exit") == 0) break;

        if (send(clientSocket, buffer, (int)strlen(buffer), 0) == SOCKET_ERROR) {
            printf("������Ӧʧ��\n");
            return 1;
        }    
    }

    // �ر�����
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
