// 封装业务函数
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "./门禁v3_业务.h"
#include "./门禁v3_工具.h"

#define Len 20

// 结构体数组，保存每个用户的信息
// User users[20] = {0, '0', '1', '0', "admin", "123qwe_", "管理员", "13000000000", "0-0-0"};
// int count = 1;           // 当前用户数量
// int current = -1;        // 当前登陆的用户索引
// char login_status = '0'; // 登陆状态 1登陆 0未登录
// char role = '1';         // 登陆角色 1普通 0管理

User *head = NULL;
User *current = NULL;
int count = 1;
char login_status = '0';
char role = '1';

/**
 * 检查用户名是否存在
 * @param char username[],用户名
 * @return  存在 索引 不存在 -1
 */
/*
int check_user_exists(char username[])
{
 for (int i = 0; i < count; i++)
 {
     if (strcmp(users[i].username, username) == 0)
     { // 传入函数的数据与结构数组数据对比
         return i;
     }
 }
 return -1;
}
*/

// 检查用户是否存在
int check_user_exists(char username[])
{
    User *p = head;

    for (int i = 0; p != NULL; i++)
    {
        if (strcmp(p->username, username) == 0)
        {
            return i;
        }
        p = p->next;
    }
    return -1;
}

// 使用索引从链表中查找用户
User *find(int index)
{
    User *p = head;
    for (int i = 0; i < index && p; i++)
        p = p->next;
    return p;
}

void login()
{
    if (head == NULL)
    {
        User *admin = malloc(sizeof(User));
        admin->lock_time = 0;
        admin->role = '0';
        admin->status = '1';
        admin->lock = '0';
        strcpy(admin->username, "admin");
        strcpy(admin->password, "123qwe_");
        strcpy(admin->realname, "管理员");
        strcpy(admin->phone, "13000000000");
        strcpy(admin->address, "0-0-0");
        admin->next = NULL;
        head = admin;
    }

    char username[20], passwd[20], flag = '1';
    int error = 0; // 连续密码错误次数

    while (flag == '1')
    {
        printf("用户名：");
        scanf("%s", username);
        printf("密码：");
        scanf("%s", passwd);
        int index = check_user_exists(username); // 调用函数检查用户名是否存在，获取其索引
        if (index == -1)
        {
            printf("用户名不存在, 请重新输入\n");
        }
        // else if (strcmp(passwd, users[index].password) != 0) // 检查密码是否正确
        // {
        else
        {
            User *u = find(index);
            if (strcmp(passwd, u->password) != 0)
            {
                // 三次锁定功能：
                error += 1; // 密码错误次数+1
                if (error == 3)
                {
                    printf("密码已经连续错误3次, 账号被锁定5分钟\n");
                    // users[index].lock = 1;                // 更新锁定状态为1
                    // users[index].lock_time = get_timec(); // 更新锁定时间
                    u->lock = '1';
                    u->lock_time = get_timec();

                    return; // 函数结束
                }
                printf("密码错误,请重新输入\n");
            }
            // else if (users[index].status != '1') // 检查账号状态
            else if (u->status != '1')
            {
                printf("账号状态异常, 请联系管理员\n");
                return;
            }
            // else if (users[index].lock == '1' && get_timec() - users[index].lock_time < 300) // 检查账号锁定状态&检查时间限制
            else if (u->lock == '1' && get_timec() - u->lock_time < 300)
            {
                printf("账号已经被锁定, 请稍后再试\n");
            }
            else
            {
                // 登录成功，清空限制
                error = 0;
                // users[index].lock == '0';
                // users[index].lock_time = 0;
                // current = index;          // 更新当前登录用户的索引
                u->lock = '0';
                u->lock_time = 0;
                current = u;
                login_status = '1'; // 保持登陆状态
                // role = users[index].role; // 赋值角色
                role = u->role;
                // current = index;
                return;
            }
        }
    }
}

void reg()
{
    char username[11]; // 用户名
    char passwrod[11]; // 密码
    char realname[20]; // 姓名
    char phone[12];    // 手机号
    char address[20];  // 门牌号
    char flag = '1';
    while (flag == '1')
    {
        printf("用户名: ");
        scanf("%s", username);
        printf("密码: ");
        scanf("%s", passwrod);
        printf("姓名: ");
        scanf("%s", realname);
        printf("手机号: ");
        scanf("%s", phone);
        printf("门牌号: ");
        scanf("%s", address);
        // 输入数据限制：
        if (check_string_length(username, 5, 10) == 0)
        {
            printf("用户名长度为5-10,请重新输入\n");
        }
        else if (check_string_1(username) == 0)
        {
            printf("用户名由字母或者数字组成,请重新输入\n");
        }
        else if (check_user_exists(username) != -1)
        {
            printf("用户名已存在,请重新输入\n");
        }
        else if (check_string_length(passwrod, 6, 10) == 0)
        {
            printf("密码长度为6-10,请重新输入\n");
        }
        else if (check_string_2(passwrod) == 0)
        {
            printf("密码必须同时包含字母、数字、下划线, 请重新输入\n");
        }
        else if (check_phone(phone) == 0)
        {
            printf("手机号非法,请重新输入\n");
        }
        else
        {

            // 检查通过，将新用户信息保存到数组中
            /*
            users[count].lock = '0';
            users[count].lock_time = 0;
            users[count].role = '1';
            users[count].status = '1';
            strcpy(users[count].username, username);
            strcpy(users[count].address, address);
            strcpy(users[count].password, passwrod);
            strcpy(users[count].phone, phone);
            strcpy(users[count].realname, realname);
            count += 1;                        // 用户数量+1
            printf("%s\n", users[1].username); // 输出测试
            */
            User *users = malloc(sizeof(User));
            users->lock = '0';
            users->lock_time = 0;
            users->role = '1';
            users->status = '1';
            strcpy(users->username, username);
            strcpy(users->address, address);
            strcpy(users->password, passwrod);
            strcpy(users->phone, phone);
            strcpy(users->realname, realname);
            users->next = NULL;

            if (head == NULL)
            {
                head = users;
            }
            else
            { // 填充月用户信息到链表尾部
                User *p = head;
                while (p->next != NULL)
                {
                    p = p->next;
                }
                p->next = users;
            }
            count += 1;
            printf("注册成功，当前用户共%d人\n", count);
            return;
        }
        printf("继续输入请按1, 结束请按其他键: ");
        scanf(" %c", &flag);
    }
}

// 日至模块

List logs = {0, 10, NULL};
//  创建
void create_list(List *p, int size)
{
    char **temp = (char **)malloc(sizeof(char *) * size); // 申请内存
    if (temp == NULL)
    {
        printf("内存分配失败\n");
        return;
    }
    // 内存分配成功，初始化顺序表基本信息
    p->cout = 0;
    p->size = size;
    p->head = temp;
}

// 扩容
void reset_size(List *p)
{
    char **temp = (char **)realloc(p->head, sizeof(char *) * p->size * 2);
    if (!temp)
    {
        printf("内存分配失败\n");
        return;
    }
    p->head = temp;
    p->size *= 2;
}
// char tim()
// {
//     long tc = time(NULL);
//     printf("当前时间戳：%ld\n", tc);
//     struct tm *tm = localtime(&tc);
//     char buf[1024];
//     //%Y-4位数的年，m-月，d-天，H-小时，%M-分钟，%S-秒
//     strftime(buf, 1023, "%Y-%m-%d %H:%M:%S", tm);
//     // printf("%s\n", buf);
//     return buf;
// }

// // 插入
// void add(List *p, char name[], char run[])
// {
//     if (p->cout == p->size)
//     {
//         reset_size(p);
//     }
//     char buf[1024];
//     snprintf(buf, 1023, "%d %s %s", tim(), name, run);
//     p->head[count] = buf;
//     p->cout++;

//     for (int i = 0; i < count + 1; i++)
//     {
//         printf(" %s", p->head[i]);
//     }
// }
void add_log(List *p, char *name, char *run)
{
    if (p->cout == p->size)
    {
        reset_size(p);
    }
    char timebuf[64];
    time_t tc = time(NULL);
    struct tm *tm_info = localtime(&tc);
    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", tm_info);

    // 合并日志
    int len = snprintf(NULL, 0, "%s %s %s", timebuf, name, run) + 1;
    char *log = (char *)malloc(len);
    if (!log)
    {
        printf("内存分配失败\n");
        exit(1);
    }
    snprintf(log, len, "%s %s %s", timebuf, name, run);

    // 存入顺序表
    p->head[p->cout++] = log;

    for (int i = 0; i < p->cout; i++)
    {
        printf("%s\n", p->head[i]);
    }
}
