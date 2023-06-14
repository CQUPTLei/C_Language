#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")  //���� socket��̬��
 
#define BUF_SIZE 1024  // ��������С
#define PORT 8888      // �˿ں�

int main() {
    // ��ʼ�� Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {   //�����winsock�汾��winsock2
        printf("WSAStartup failed.\n");
        return 1;
    }

    SOCKET serverSocket;                        // ����ˡ��ͻ����׽��־��
    struct sockaddr_in serverAddr, clientAddr;  // ipv4��ַ�ṹ��
    int clientAddrLen = sizeof(clientAddr);     // �ͻ��˵�ַ�ṹ�峤��
    char buffer[BUF_SIZE];                      // ������

    // �����׽���
    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);    // ipv4��ַ�����ݱ��׽��֣������׽����Զ�ѡ��Э�����ͣ���UDP��
    if (serverSocket == INVALID_SOCKET) {
        printf("Failed to create socket.\n");
        WSACleanup();
        return 1;
    }

    // ���÷�������ַ�Ͷ˿�
    memset(&serverAddr, 0, sizeof(serverAddr));  //ÿ���ֽڶ���0���
    serverAddr.sin_family = AF_INET;             // Э��
   // serverAddr.sin_addr.s_addr = INADDR_ANY;     // ��ַ����0.0.0.0����������������������д�ɣ���127.0.0.1��Ҳ����
    serverAddr.sin_addr.s_addr = inet_addr("192.168.31.39");
    serverAddr.sin_port = htons(PORT);           // �˿�

    // ���׽���
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Failed to bind socket.\n");
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    printf("UDP server started. Waiting for data...\n");

    // ���պͷ�������
    while (1) {
        int recvLen = recvfrom(serverSocket, buffer, BUF_SIZE, 0, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (recvLen == SOCKET_ERROR) {
            printf("Failed to receive data.\n");
            break;
        }

        // ������յ�������
        buffer[recvLen] = '\0';
        printf("Received data from client: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0) break;  // �յ�exitʱ�˳�

        // ���ͻ�Ӧ���ݸ��ͻ���
        const char* response = "I've got it.";
        if (sendto(serverSocket, response, (int)strlen(response), 0, (struct sockaddr*)&clientAddr, clientAddrLen) == SOCKET_ERROR) {
            printf("Failed to send response.\n");
            break;
        }
    }

    // �ر��׽��ֺ����� Winsock
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}