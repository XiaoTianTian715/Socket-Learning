#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <stdio.h> 
#include <string.h> 
#include <unistd.h>
#include <stdbool.h>
#include <malloc.h>

#define BUFSZ	1024
#define SERVER_IPADDR "192.168.1.115"


static const char send_data[] = "Client from FH8830"; /* 发送用到的数据 */
int main(int argc,char*argv[])
{
	char* server_ip = SERVER_IPADDR;
	int port = 5000;
    char *recv_data;
    //struct hostent *host;
    int sock, bytes_received;
    struct sockaddr_in server_addr;


    /* 分配用于存放接收数据的缓冲 */
    recv_data = malloc(BUFSZ);
    if (recv_data == NULL)
    {
        printf("No memory\n");
        return -1;
    }

    /* 创建一个socket，类型是SOCKET_STREAM，TCP类型 */
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        /* 创建socket失败 */
        printf("Socket error\n");

        /* 释放接收缓冲 */
        free(recv_data);
        return -2;
    }

    /* 初始化预连接的服务端地址 */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    //server_addr.sin_addr = *((struct in_addr *)host->h_addr);
	server_addr.sin_addr.s_addr = inet_addr(server_ip);
    memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));

    /* 连接到服务端 */
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
    {
        /* 连接失败 */
        printf("Connect fail!\n");
        close(sock);

        /*释放接收缓冲 */
        free(recv_data);
        return -3;
    }

    while(1)
    {
#if 0
        /* 从sock连接中接收最大BUFSZ - 1字节数据 */
        bytes_received = recv(sock, recv_data, BUFSZ - 1, 0);
        if (bytes_received <= 0)
        {
            /* 接收失败，关闭这个连接 */
            close(sock);

            /* 释放接收缓冲 */
            free(recv_data);
            break;
        }

        /* 有接收到数据，把末端清零 */
        recv_data[bytes_received] = '\0';

        if (strcmp(recv_data , "q") == 0 || strcmp(recv_data , "Q") == 0)
        {
            /* 如果是首字母是q或Q，关闭这个连接 */
            close(sock);

            /* 释放接收缓冲 */
            free(recv_data);
            break;
        }
        else
        {
            /* 在控制终端显示收到的数据 */
            printf("\nReceived data = %s " , recv_data);
        }
#endif
        /* 发送数据到sock连接 */
        send(sock,send_data,strlen(send_data), 0);
		sleep(20);
		printf("send by FH8830 every 2 seconds\n");
    }

    return 0;
}
