#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define ip "198.52.97.228"
#define port 8087
#define BUF_SIZE 1024


int main() {
    int client_socket;
    struct sockaddr_in server_address;
    char buffer[BUF_SIZE];

    // 创建套接字
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        printf("无法创建套接字\n");
        return -1;
    }

    // 设置服务器地址和端口
    memset(&server_address,0,sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr=inet_addr(ip);
    server_address.sin_port = htons(port);

    // 连接服务器
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address))<0){
        puts("与服务器建立连接失败");
        return -1;
    }
    puts("与服务器建立连接成功");

    while(1){
        memset(buffer, 0, BUF_SIZE);
        printf("输入要发送的数据(exit关闭两侧链接)：");
        fgets(buffer,BUF_SIZE,stdin);
        buffer[strlen(buffer)-1]='\0';

        if(send(client_socket,buffer,strlen(buffer),0)<0){
            puts("发生数据失败");
            return -1;
        }

        if(strcmp(buffer, "exit")==0) break;

        memset(buffer, 0, BUF_SIZE);
        if(recv(client_socket,buffer,sizeof(buffer),0)<0){
            puts("从服务器接收响应失败");
            return -1;
        }
        printf("从服务器接收响应为：%s\n",buffer);
    }
    // 关闭连接
    close((int)client_socket);
    return 0; 
}
