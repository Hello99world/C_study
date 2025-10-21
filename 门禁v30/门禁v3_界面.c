#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "./门禁v3_业务.h"
#include "./门禁v3_工具.h"

int main()
{
    int index;
    char opt;
    reset_size(&logs);
    add_log(&logs, "系统", "启动");
    char info[100];
    while (1)
    {
        char flag = '1';
        while (flag == '1')
        {

            printf("---------------一级界面--------------\n");
            printf("1-登陆\n2-注册\n0-退出\n");
            printf("请选择需要的服务：");
            scanf(" %c", &opt);
            switch (opt)
            {
            case '1':
                printf("---------------登录操作---------------\n");
                login();
                if (login_status == '1')
                {
                    flag = '0';
                    add_log(&logs, current->username, "登录系统");
                } // 进入下一级
                // index = current;
                break;
            case '2':
                printf("注册操作\n");
                reg();
                add_log(&logs, "新用户", "注册账户");
                break;
            default:
                printf("谢谢使用，再见！\n");
                add_log(&logs, current->username, "退出系统");
                return 0;
                break;
            }
        }
        while (login_status == '1')
        {
            printf("---------------二级界面--------------\n");
            char pwd[20], repwd[20], phe[20];
            if (role == '0') // 判断是否为管理员
            {
                char user[20];
                char user_exists = '0'; // 表示用户名是否存在
                printf("1-用户列表\n2-用户详情\n3-添加用户\n4-删除用户\n5-重置密码\n6-修改手机号\n7-修改门牌号\n8-修改状态\n9-解除锁定\n-0注销\n");
                printf("请选择需要的服务：");
                scanf(" %c", &opt);
                User *p, *tmp;

                switch (opt)
                {
                case '1':
                    p = head;
                    printf("---------------用户列表--------------\n");
                    // for (int i = 0; i < count; i++)
                    // {
                    //     printf("%s\n", users[i].username);
                    // }
                    while (p)
                    {
                        printf("%s\n", p->username);
                        p = p->next;
                    }
                    add_log(&logs, current->username, "用户列表");
                    break;
                case '2':
                    printf("---------------用户详情--------------\n");
                    // printf("用户名\t密码\t姓名\t手机号\t门牌号\t角色\t状态\t锁定状态\t锁定时间\n");
                    printf("用户名         密码            姓名        手机号           门牌号     角色      状态      锁定状态      锁定时间\n");
                    // for (int i = 0; i < count; i++)
                    // {
                    //     printf("%s\t%s\t%s\t%s\t%s\t%d\t%d\t%d\t%ld\t", users[i].username, users[i].password, users[i].realname, users[i].phone, users[i].address, users[i].role, users[i].status, users[i].lock, users[i].lock_time);
                    //     printf("\n");
                    // }
                    p = head;
                    while (p)
                    {
                        printf("%s\t%s\t%s\t%s\t%s\t%c\t%c\t%c\t%ld\n", p->username, p->password, p->realname, p->phone, p->address, p->role, p->status, p->lock, p->lock_time);
                        p = p->next;
                    }
                    add_log(&logs, current->username, "用户详情");
                    break;
                case '3':
                    printf("---------------添加用户--------------\n");
                    reg(); // 注册模块
                    add_log(&logs, current->username, "添加用户");
                    break;
                case '4':
                    printf("---------------删除用户--------------\n");
                    printf("请输入要删除的用户名：");
                    scanf("%s", user);
                    index = check_user_exists(user); // 调用函数检查用户名是否存在，获取其索引
                    if (index == -1)
                    {
                        printf("用户名不存在, 请重新输入\n");
                    }
                    else
                    // {
                    //     users[index].status = 0; // 设置异常状态指代删除
                    //     printf("删除成功。\n");
                    // }
                    {
                        User *temp = NULL;
                        User *p = head;
                        // 通过索引找到目标节点和其前驱节点
                        for (int i = 0; i < index && p != NULL; i++)
                        {
                            temp = p;
                            p = p->next;
                        }
                        temp->next = p->next;
                        free(p);
                        count--;
                        printf("删除成功。\n");
                    }
                    sprintf(info, "删除用户 %s", user);
                    add_log(&logs, current->username, info);
                    break;
                case '5':
                    printf("---------------重置密码--------------\n");
                    printf("请输入用户名：");
                    scanf("%s", user);
                    index = check_user_exists(user); // 调用函数检查用户名是否存在，获取其索引
                    if (index == -1)
                    {
                        printf("用户名不存在, 请重新输入\n");
                    }
                    else
                    {
                        User *p = find(index);
                        printf("请输入密码：");
                        scanf("%s", pwd);
                        if (check_string_length(pwd, 6, 10) == 0)
                        {
                            printf("密码长度为6-10,请重新输入\n");
                        }
                        else if (check_string_2(pwd) == 0)
                        {
                            printf("密码必须同时包含字母、数字、下划线, 请重新输入\n");
                        }
                        printf("请输入确认密码：");
                        scanf("%s", repwd);
                        if (strcmp(pwd, repwd) == 0)
                        {

                            // strcpy(users[index].password, pwd);
                            strcpy(p->password, pwd);
                            printf("重置密码成功");
                            break;
                        }
                        else
                        {
                            printf("密码与确认密码不一致，请重新输入\n");
                        }
                        sprintf(info, "重置%s密码", user);
                        add_log(&logs, current->username, info);
                    }
                    break;
                case '6':
                    printf("---------------修改手机号--------------\n");
                    printf("请输入用户名：");
                    scanf("%s", user);
                    index = check_user_exists(user); // 调用函数检查用户名是否存在，获取其索引
                    if (index == -1)
                    {
                        printf("用户名不存在, 请重新输入\n");
                    }
                    else
                    {
                        User *p = find(index);
                        printf("请输入新手机号：");
                        scanf("%s", phe);
                        if (check_phone(phe) == 0)
                        {
                            printf("手机号非法,请重新输入\n");
                        }
                        else
                        {
                            // strcpy(users[index].phone, phe);
                            strcpy(p->phone, phe);
                            printf("修改成功");
                        }
                        sprintf(info, "修改%s手机号", user);
                        add_log(&logs, current->username, info);
                    }
                    break;
                case '7':
                    printf("---------------修改门牌号--------------\n");
                    printf("请输入用户名：");
                    scanf("%s", user);
                    index = check_user_exists(user); // 调用函数检查用户名是否存在，获取其索引
                    if (index == -1)
                    {
                        printf("用户名不存在, 请重新输入\n");
                    }
                    else
                    {
                        User *p = find(index);
                        printf("请输入新门牌号：");
                        // scanf("%s", users[index].address);
                        scanf("%s", p->address);
                        printf("修改成功\n");
                        sprintf(info, "修改%s门派号", user);
                        add_log(&logs, current->username, info);
                    }
                    break;
                case '8':
                    printf("---------------修改状态--------------\n");
                    printf("请输入用户名：");
                    scanf("%s", user);
                    index = check_user_exists(user); // 调用函数检查用户名是否存在，获取其索引
                    if (index == -1)
                    {
                        printf("用户名不存在, 请重新输入\n");
                    }
                    else
                    {
                        User *p = find(index);
                        printf("请输入状态(1启用/0禁用)：");
                        // scanf(" %c", &users[index].status);
                        scanf(" %c", &p->status);
                        printf("修改成功\n");
                    }
                    sprintf(info, "修改%s状态", user);
                    add_log(&logs, current->username, info);
                    break;
                case '9':
                    printf("---------------解除锁定--------------\n");
                    printf("请输入用户名：");
                    scanf("%s", user);
                    index = check_user_exists(user); // 调用函数检查用户名是否存在，获取其索引
                    if (index == -1)
                    {
                        printf("用户名不存在, 请重新输入\n");
                    }
                    else
                    {
                        User *p = find(index);
                        // printf("请输入锁定状态(1启用/0禁用):");
                        // scanf(" %c", &users[index].lock);
                        // users[index].lock_time = users[index].lock_time + 400;
                        p->lock = '0';
                        p->lock_time = 0;
                        printf("用户已解除锁定\n");
                    }
                    sprintf(info, "解除%s锁定", user);
                    add_log(&logs, current->username, info);
                    break;
                default:
                    login_status = '0';
                    add_log(&logs, current->username, "注销登陆");
                    break;
                }
            }
            else
            {
                printf("1-用户详情\n2-修改密码\n3-修改手机号\n4-修改门牌号\n0-注销\n");
                printf("请选择需要的服务：");
                scanf(" %c", &opt);
                switch (opt)
                {
                case '1':
                    printf("---------------用户详情--------------\n");
                    // printf("用户名         密码            姓名        手机号           门牌号     \n");
                    // printf("%s\t%s\t%s\t%s\t%s\t", users[index].username, users[index].password, users[index].realname, users[index].phone, users[index].address);
                    printf("用户名:%s\n密码:%s\n姓名:%s\n手机号:%s\n门牌号:%s\n", current->username, current->password, current->realname, current->phone, current->address);
                    printf("\n");
                    sprintf(info, "用户详情 %s", current->username);
                    add_log(&logs, current->username, info);
                    break;

                case '2':
                    printf("---------------修改密码--------------\n");
                    printf("请输入密码：");
                    scanf("%s", pwd);
                    if (check_string_length(pwd, 6, 10) == 0)
                    {
                        printf("密码长度为6-10,请重新输入\n");
                    }
                    else if (check_string_2(pwd) == 0)
                    {
                        printf("密码必须同时包含字母、数字、下划线, 请重新输入\n");
                    }
                    printf("请输入确认密码：");
                    scanf("%s", repwd);
                    if (strcmp(pwd, repwd) == 0)
                    {

                        // strcpy(users[index].password, pwd);
                        strcpy(current->password, pwd);
                        printf("重置密码成功");
                        break;
                    }
                    else
                    {
                        printf("密码与确认密码不一致，请重新输入\n");
                    }
                    sprintf(info, "修改%s密码", current->username);
                    add_log(&logs, current->username, info);
                    break;
                case '3':
                    printf("---------------修改手机号--------------\n");

                    printf("请输入新手机号：");
                    scanf("%s", phe);
                    if (check_phone(phe) == 0)
                    {
                        printf("手机号非法,请重新输入\n");
                    }
                    else
                    {
                        // strcpy(users[index].phone, phe);
                        strcpy(current->phone, phe);
                        printf("修改成功");
                    }
                    sprintf(info, "修改%s手机号", current->username);
                    add_log(&logs, current->username, info);
                    break;
                case '4':
                    printf("---------------修改门牌号--------------\n");
                    printf("请输入新门牌号：");
                    // scanf("%s", users[index].address);
                    scanf("%s", current->address);
                    printf("修改成功\n");
                    sprintf(info, "修改%s门牌号", current->username);
                    add_log(&logs, current->username, info);
                    break;
                default:
                    login_status = '0';
                    add_log(&logs, current->username, "注销登陆");
                    break;
                }
            }
        }
    }
}