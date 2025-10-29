#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8888

// 车辆进入
void car_run_client(char *card, int type)
{
    // 创建套接字
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("socket");
        exit(1);
    }
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // 连接服务端
    if (connect(fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("connect");
        exit(1);
    }
    char buf[1024];
    // 发送车牌号和类型
    sprintf(buf, "%s %d", card, type);
    write(fd, buf, strlen(buf));
    int nbytes = read(fd, buf, sizeof(buf) - 1);
    buf[nbytes] = '\0';
    printf(">> 服务端返回: %s\n", buf); // 返回车位号或错误信息
    close(fd);
}

// 车辆离开
void car_out_client(char *card)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("socket");
        exit(1);
    }
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("connect");
        exit(1);
    }
    char buf[1024];
    // 向服务器发送离场数据
    sprintf(buf, "%s exit", card);
    write(fd, buf, strlen(buf));
    int nbytes = read(fd, buf, sizeof(buf) - 1);
    buf[nbytes] = '\0';
    printf(">> 服务端返回费用: %s\n", buf);
    close(fd);
}

int main()
{
    char card[16];
    int type;
    printf("模拟道闸系统\n");
    printf("请输入车牌号: ");
    fgets(card, sizeof(card), stdin);
    int n = strcspn(card, "\n");
    card[n] = 0;
    printf("请输入车辆类型 1-月租 2-长期 3-临停: ");
    scanf("%d", &type);
    printf("请输入操作：(1入场2离场)");
    int op;
    scanf("%d", &op);
    if (op == 1)
    {
        car_run_client(card, type);
    }
    else
    {
        car_out_client(card);
    }
}
