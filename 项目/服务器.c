#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "工具.h"
#include "业务.h"
#define PORT 8888

// 客户端处理
void *client(void *arg)
{
    int client_fd = *(int *)arg;
    char buf[256];
    while (1)
    {
        int nbytes = read(client_fd, buf, sizeof(buf) - 1);
        if (nbytes <= 0)
        {
            break;
        }
        buf[nbytes] = '\0';
        if (strstr(buf, "exit"))
        { // 离场
            char card[16];
            sscanf(buf, "%s", card);
            int fee = car_out(card); // 传参车牌号调用离场函数
            if (fee >= 0)
            {
                sprintf(buf, "离场成功，费用 %d 元", fee);
            }
            else if (fee == -1)
            {
                sprintf(buf, "车辆未在场");
            }
            else
            {
                sprintf(buf, "离场失败");
            }
        }
        else
        { // 入场
            char card[16];
            int type;
            sscanf(buf, "%s %d", card, &type);
            int ret = car_run(card, type); // 调用入场函数
            if (ret == 0)
            {
                char *rec = search("cars_now.txt", card);
                char card[16], num[16];
                sscanf(rec, "%s %s", card, num);
                sprintf(buf, "%s入场成功,车位：%s", card, num);
            }
            else if (ret == -1)
            {
                sprintf(buf, "车牌号非法");
            }
            else if (ret == -2)
            {
                sprintf(buf, "没有空闲车位，入场失败");
            }
            else if (ret == -3)
            {
                sprintf(buf, "月租车不存在");
            }
            else if (ret == -4)
            {
                sprintf(buf, "月租已到期，请续费或按照临时车入场");
            }
            else if (ret == -5)
            {
                sprintf(buf, "长期车不存在");
            }
        }

        write(client_fd, buf, strlen(buf));
    }
    close(client_fd);
    return NULL;
}

int main()
{
    // 创建
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        perror("socket");
        exit(1);
    }
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("bind");
        exit(1);
    }
    // 监听
    if (listen(server_fd, 5) < 0)
    {
        perror("listen");
        exit(1);
    }
    printf(">> 服务端已就绪，监听端口 %d\n", PORT);

    while (1)
    {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int *client_fd = malloc(sizeof(int));
        *client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
        if (*client_fd < 0)
        {
            perror("accept");
            free(client_fd);
            continue;
        }
        printf(">> 客户端连接: %s:%d\n",
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        // 创建线程处理客户端请求
        pthread_t tid;
        pthread_create(&tid, NULL, client, client_fd);
        pthread_detach(tid);
    }
    // 关闭套接字
    close(server_fd);
    return 0;
}
