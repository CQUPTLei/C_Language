#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> // linux下socket头文件
#include <arpa/inet.h>  // ip地址转换、字节序转换

#define ip INADDR_ANY  // 主机ip地址，表示监听主机所有网卡
//#define ip "0.0.0.0"
#define port 8087      // 端口号
#define BUF_SIZE 1024  //缓冲区大小

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    char buffer[BUF_SIZE]; //缓冲区

    // 创建套接字
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        printf("无法创建套接字\n");
        return -1;
    }

    // 设置服务器地址和端口
    memset(&server_address,0,sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = ip;
     //server_address.sin_addr.s_addr=inet_addr(ip);
    server_address.sin_port = htons(port);

    // 绑定套接字到指定的地址和端口
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        printf("绑定失败\n");
        return -1;
    }

    // 监听传入的连接
    if (listen(server_socket, 1) < 0) {
        printf("监听失败\n");
        return -1;
    }

    printf("服务器正在监听端口 %d\n", port);

    // 接受传入的连接
    socklen_t client_address_length = sizeof(client_address);    //注意这里的长度的类型是：socklen_t
    client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_length);
    if (client_socket < 0) {
        printf("接受连接失败\n");
        return -1;
    }

    printf("与客户端建立连接成功\n");

    // 循环接受客户端请求，收到exit时关闭套接字
    while(1){
        memset(buffer, 0, sizeof(buffer));
         ssize_t recvLen=recv(client_socket,buffer ,sizeof(buffer), 0); 
        if(recvLen<0){
            puts("接收数据失败");
            return -1;
        }
        buffer[recvLen]='\0';
        printf("从客户端接收到的数据：%s\n",buffer);
        if(strcmp(buffer,"exit")==0) break;

        // 将收到的数据回送给客户端
        if(send(client_socket,buffer,sizeof(buffer),0)<0){
            puts("发送响应失败");
            return -1;
        }
    }

    // 关闭连接
    close((int)client_socket);
    close((int)server_socket);

    return 0;
}
