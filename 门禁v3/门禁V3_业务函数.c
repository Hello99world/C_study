// 封装门禁系统相关的业务函数，如的恩登陆函数、重置密码函数等
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "./门禁V3_工具.h"

Node *head = NULL;       // 头指针
mlog *mylog = NULL;      // 日志指针
Node *current = NULL;    // 当前登录的用户所在节点
char login_status = '0'; // 登录状态，1-已登录，0-未登录

void login()
{
    printf("- - - - - - - - - - - - - 登录操作 - - - - - - - - - - - - -\n");
    char username[20], passwd[20], flag = '1';
    int error = 0; // 密码连续错误次数
    while (flag == '1')
    {
        printf("用户名: ");
        scanf("%s", username);
        printf("密 码: ");
        scanf("%s", passwd);
        current = search(head, username); // 检查用户名是否存在，获取其索引
        if (current == NULL)
        {
            printf("用户名不存在, 请重新输入\n");
        }
        else if (strcmp(passwd, current->user->passwrod) != 0)
        {
            error += 1; // 密码错误次数+1
            if (error == 3)
            {
                printf("密码已经连续错误3次, 账号被锁定5分钟\n");
                current->user->lock = 1;                // 更新锁定状态为1
                current->user->lock_time = get_timec(); // 更新锁定时间
                return;                                 // 函数结束
            }
            printf("密码错误,请重新输入\n");
        }
        else if (current->user->status != '1')
        {
            printf("账号状态异常, 请联系管理员\n");
            return; // 函数结束
        }
        else if (current->user->lock == '1' && get_timec() - current->user->lock_time < 300)
        {
            printf("账号已经被锁定, 请稍后再试\n");
        }
        else
        {
            // 登录成功
            error = 0;
            current->user->lock == '0';
            current->user->lock_time = 0;
            login_status = '1';
            // 记录日志
            char *buf = (char *)malloc(1024); // 申请内存保存日志内容
            get_dt();                         // 获取当前日期时间
            snprintf(buf, 1023, "%s\t%s\t%s\n", dt, username, "登录成功");
            log_add(mylog, buf);
            return; // 函数结束
        }
        printf("继续输入请按1, 结束请按其他键: ");
        scanf(" %c", &flag);
    }
}

void logout()
{
    printf("- - - - - - - - - - - - - 登出操作 - - - - - - - - - - - - -\n");
    // 登出成功后记录日志
    char *buf = (char *)malloc(1024); // 申请内存保存日志内容
    get_dt();                         // 获取当前日期时间
    snprintf(buf, 1023, "%s\t%s\t%s\n", dt, current->user->username, "登出成功");
    login_status = '0';
}

void add()
{
    printf("- - - - - - - - - - - - - 添加用户 - - - - - - - - - - - - -\n");
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
        if (check_string_length(username, 5, 10) == 0)
        {
            printf("用户名长度为5-10,请重新输入\n");
        }
        else if (check_string_1(username) == 0)
        {
            printf("用户名由字母或者数字组成,请重新输入\n");
        }
        else if (search(head, username) != NULL)
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
            User *info = (User *)malloc(sizeof(User));
            info->lock = '0';
            info->lock_time = 0;
            info->role = '1';
            info->status = '1';
            strcpy(info->username, username);
            strcpy(info->address, address);
            strcpy(info->passwrod, passwrod);
            strcpy(info->phone, phone);
            strcpy(info->realname, realname);
            if (add_node(head, info) == 1)
            {
                printf("添加用户成功\n");
                // 记录日志
                char *buf = (char *)malloc(1024); // 申请内存保存日志内容
                get_dt();                         // 获取当前日期时间
                snprintf(buf, 1023, "%s\t%s\t%s\n", dt, "添加用户", username);
                log_add(mylog, buf);
            }

            return;
        }
        printf("继续输入请按1, 结束请按其他键: ");
        scanf(" %c", &flag);
    }
}

void user_list()
{
    printf("- - - - - - - - - - - - - 用户列表 - - - - - - - - - - - - -\n");
    Node *temp = head->next;
    if (temp == NULL)
    {
        printf("暂无用户数据\n");
        return;
    }
    printf("用户名列表：\n");
    while (temp != NULL)
    {
        printf("%s\n", temp->user->username);
        temp = temp->next;
    }
    // 记录日志
    char *buf = (char *)malloc(1024);
    get_dt();
    snprintf(buf, 1023, "%s\t%s\t查看用户列表\n", dt, current->user->username);
    log_add(mylog, buf);
}

void user_detail()
{
    printf("- - - - - - - - - - - - - 用户详情 - - - - - - - - - - - - -\n");
    char username[11];
    Node *node = current; // 普通用户默认查看自己的详情
    if (current->user->role == '0')
    { // 管理员可指定查看用户
        printf("请输入要查看的用户名：");
        scanf("%s", username);
        node = search(head, username);
        if (node == NULL)
        {
            printf("用户名不存在\n");
            return;
        }
    }
    // 打印用户详情
    printf("用户名：%s\n", node->user->username);
    printf("姓名：%s\n", node->user->realname);
    printf("手机号：%s\n", node->user->phone);
    printf("门牌号：%s\n", node->user->address);
    printf("角色：%s\n", node->user->role == '0' ? "管理员" : "普通用户");
    printf("状态：%s\n", node->user->status == '1' ? "正常" : "异常");
    printf("锁定状态：%s\n", node->user->lock == '1' ? "已锁定" : "未锁定");
    // 记录日志
    char *buf = (char *)malloc(1024);
    get_dt();
    snprintf(buf, 1023, "%s\t%s\t查看用户%s详情\n", dt, current->user->username, node->user->username);
    log_add(mylog, buf);
}

void del_user()
{
    printf("- - - - - - - - - - - - - 删除用户 - - - - - - - - - - - - -\n");
    // 输入需要删除的用户名并检查用户名是否存在
    // 删除完成后记录日志
    char username[11];
    printf("请输入要删除的用户名：");
    scanf("%s", username);
    if (strcmp(username, "admin") == 0)
    { // 保护管理员账号
        printf("禁止删除管理员账号\n");
        return;
    }
    Node *node = search(head, username);
    if (node == NULL)
    {
        printf("用户名不存在\n");
        return;
    }
    del_node(head, username); // 调用工具函数删除节点
    printf("删除用户成功\n");
    // 记录日志
    char *buf = (char *)malloc(1024);
    get_dt();
    snprintf(buf, 1023, "%s\t%s\t删除用户%s\n", dt, current->user->username, username);
    log_add(mylog, buf);
}

void modify_status()
{
    printf("- - - - - - - - - - - - - 修改状态 - - - - - - - - - - - - -\n");
    // 修改用户状态
    char username[11], status[2];
    printf("请输入用户名：");
    scanf("%s", username);
    Node *node = search(head, username);
    if (node == NULL)
    {
        printf("用户名不存在\n");
        return;
    }
    printf("当前状态：%s（1-正常，0-异常）\n", node->user->status == '1' ? "正常" : "异常");
    printf("请输入新状态（1-正常，0-异常）：");
    scanf("%s", status);
    if (status[0] != '0' && status[0] != '1')
    {
        printf("输入无效，状态只能是0或1\n");
        return;
    }
    node->user->status = status[0];
    printf("修改状态成功\n");
    // 记录日志
    char *buf = (char *)malloc(1024);
    get_dt();
    snprintf(buf, 1023, "%s\t%s\t修改用户%s状态为%s\n", dt, current->user->username, username, status);
    log_add(mylog, buf);
}

void unlock()
{
    printf("- - - - - - - - - - - - - 解锁用户 - - - - - - - - - - - - -\n");
    // 解锁用户
    char username[11];
    printf("请输入要解锁的用户名：");
    scanf("%s", username);
    Node *node = search(head, username);
    if (node == NULL)
    {
        printf("用户名不存在\n");
        return;
    }
    if (node->user->lock == '0')
    {
        printf("该用户未被锁定，无需解锁\n");
        return;
    }
    // 强制解锁（忽略锁定时间）
    node->user->lock = '0';
    node->user->lock_time = 0;
    printf("解锁用户成功\n");
    // 记录日志
    char *buf = (char *)malloc(1024);
    get_dt();
    snprintf(buf, 1023, "%s\t%s\t解锁用户%s\n", dt, current->user->username, username);
    log_add(mylog, buf);
}

void reset_passwd()
{
    printf("- - - - - - - - - - - - - 重置密码 - - - - - - - - - - - - -\n");
    char *u = current->user->username;
    // 检查当前登录用户是否为管理员
    if (current->user->role != '1')
    {
        // 输入需要在在设置秘密的用户名
        char username[11];
        printf("请输入需要修改密码的用户名: ");
        scanf("%s", username);
        // 检查用户名是否存在
        Node *node = search(head, username);
        if (node == NULL)
        {
            printf("用户名不存在\n");
            return;
        }
        u = username;
    }
    else
    {
        // 普通用户需要输入原密码，验证通过后才能设置新密码
        char password[11];
        printf("请输入原密码: ");
        scanf("%s", password);
        if (strcmp(password, current->user->passwrod) != 0)
        {
            printf("原密码错误\n");
            return;
        }
    }
    // 输入新密码、确认密码，检查通过后更新用户信息，记录日志
    char new_password[11], confirm_password[11];
    printf("请输入新密码: ");
    scanf("%s", new_password);
    printf("请输入确认密码: ");
    scanf("%s", confirm_password);
    if (strcmp(new_password, confirm_password) != 0)
    {
        printf("两次密码不一致\n");
    }
    else if (check_string_length(new_password, 6, 10) == 0)
    {
        printf("密码长度为6-10,请重新输入\n");
    }
    else if (check_string_2(new_password) == 0)
    {
        printf("密码必须同时包含字母、数字、下划线, 请重新输入\n");
    }
    else
    {
        strcpy(current->user->passwrod, new_password);
        printf("修改密码成功\n");
        // 记录日志
        char *buf = (char *)malloc(1024); // 申请内存保存日志内容
        get_dt();                         // 获取当前日期时间
        if (current->user->role != '1')
        {
            snprintf(buf, 1023, "%s\tadmin\t重置用户%s的密码\n", dt, u);
        }
        else
        {
            snprintf(buf, 1023, "%s\t%s\t%s\n", dt, u, "修改密码");
        }
        log_add(mylog, buf);
    }
}

void modify_phone()
{
    printf("- - - - - - - - - - - - - 修改手机号 - - - - - - - - - - - - -\n");
    char username[11], new_phone[12];
    Node *node = current; // 普通用户默认修改自己的手机号
    if (current->user->role == '0')
    { // 管理员可指定用户
        printf("请输入要修改的用户名：");
        scanf("%s", username);
        node = search(head, username);
        if (node == NULL)
        {
            printf("用户名不存在\n");
            return;
        }
    }
    printf("请输入新手机号：");
    scanf("%s", new_phone);
    if (check_phone(new_phone) == 0)
    {
        printf("手机号非法（11位数字，以13/15/17/18/19开头）\n");
        return;
    }
    strcpy(node->user->phone, new_phone);
    printf("修改手机号成功\n");
    // 记录日志
    char *buf = (char *)malloc(1024);
    get_dt();
    snprintf(buf, 1023, "%s\t%s\t修改用户%s手机号\n", dt, current->user->username, node->user->username);
    log_add(mylog, buf);
}

void modify_address()
{
    printf("- - - - - - - - - - - - - 修改门牌号 - - - - - - - - - - - - -\n");
    char username[11], new_address[20];
    Node *node = current; // 普通用户默认修改自己的门牌号
    if (current->user->role == '0')
    { // 管理员可指定用户
        printf("请输入要修改的用户名：");
        scanf("%s", username);
        node = search(head, username);
        if (node == NULL)
        {
            printf("用户名不存在\n");
            return;
        }
    }
    printf("请输入新门牌号：");
    scanf("%s", new_address);
    strcpy(node->user->address, new_address);
    printf("修改门牌号成功\n");
    // 记录日志
    char *buf = (char *)malloc(1024);
    get_dt();
    snprintf(buf, 1023, "%s\t%s\t修改用户%s门牌号\n", dt, current->user->username, node->user->username);
    log_add(mylog, buf);
}