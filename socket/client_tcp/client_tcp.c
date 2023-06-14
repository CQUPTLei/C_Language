#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib") 

#define server_ip "192.168.31.39"
#define PORT 8080
#define BUF_SIZE 1024


int main() { 

    // ��ʼ��Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("�޷���ʼ��Winsock\n");
        return 1;
    }

    SOCKET clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[BUF_SIZE];

    // �����ͻ����׽���
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        printf("�޷������׽���\n");
        return 1;
    }

    // ���÷�������ַ�Ͷ˿�
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(server_ip);


    // ���ӷ�����
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("���ӷ�����ʧ��\n");
        return 1;
    }

    printf("��������������ӳɹ�\n");

    while (1) {
        // �������ݸ�������
        memset(buffer, 0, sizeof(buffer));
        printf("\n����Ҫ���͵����ݣ�exit�˳���");
        fgets(buffer,BUF_SIZE,stdin);
        buffer[strlen(buffer) - 1] = '\0';

        if (send(clientSocket, buffer, (int)strlen(buffer), 0) == SOCKET_ERROR) {
            printf("��������ʧ��\n");
            return 1;
        }

        if (strcmp(buffer, "exit") == 0)break;

        // ���շ���������Ӧ
        memset(buffer, 0, BUF_SIZE);
        if (recv(clientSocket, buffer, BUF_SIZE, 0) == SOCKET_ERROR) {
            printf("������Ӧʧ��\n");
            return 1;
        }
        printf("�ӷ��������յ�����Ӧ��%s\n", buffer);
    
    }

    // �ر�����
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}