#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "./门禁V4_业务.h"
#include "./门禁V4_工具.h"

int main()
{
    // 初始化用户数据
    User p0 = {0, '-', '-', '-', "---", "---", "---", "---", "---"};
    //User p1 = {0, '0', '1', '0', "admin", "123qwe_", "管理员", "13000000000", "0-0-0"};
    //User p2 = {0, '1', '1', '0', "user001", "123qwe_", "王余杭", "13512345678", "2-1-101"};
    head = create_node(&p0); // 头指针指向头节点
    //add_node(head, &p1);
    //add_node(head, &p2);

    load_users("users.txt", head);
    load_logs("logs.txt", mylog);

    // 初始化日志
    mylog = create_log(10);
    // 进入一级界面
    char opt;
    while (1)
    {
        char flag = '1';
        while (flag == '1')
        {
            printf("- - - - - - - - - - - - - 一级界面 - - - - - - - - - - - - -\n");
            printf("1-登录\n2-注册\n0-退出\n");
            printf("请选择需要的服务: ");
            scanf(" %c", &opt);
            switch (opt)
            {
            case '1':
                printf("- - - - - - - - - - - - - 登录操作 - - - - - - - - - - - - -\n");
                login(head);
                if (login_status == '1')
                    flag = '0';
                break;
            case '2':
                printf("- - - - - - - - - - - - - 注册操作 - - - - - - - - - - - - -\n");
                add(head);
                display(head);
                break;
            default:
                //注销系统
                printf("谢谢使用,再见!\n");
                display_log(mylog);
                save_users("users.txt", head);
                save_logs("logs.txt", mylog);
                free_node(head);
                free_log(mylog); 
                return 0;
                break;
            }
        }
        while (login_status == '1')
        {
            printf("- - - - - - - - - - - - - 二级界面 - - - - - - - - - - - - -\n");
            char pwd[20], repwd[20], phone[20];
            if (current->user->role == '0')
            {
                void (*func[10])() = {logout, user_list, user_detail, add, del_user, reset_passwd, modify_phone, modify_address, modify_status, unlock};
                char user[20];          // 用户名
                char user_exists = '0'; // 用户名是否存在， 0-不存在，1-存在
                printf("1-用户列表\n2-用户详情\n3-添加用户\n4-删除用户\n5-重置密码\n6-修改手机号\n7-修改门牌号\n8-修改状态\n9-解除锁定\n0-注销\n");
                printf("请选择需要的服务: ");
                scanf(" %c", &opt);
                func[opt - '0']();
            }
            else
            {
                printf("1-用户详情\n2-修改密码\n3-修改手机号\n4-修改门牌号\n0-注销\n");
                printf("请选择需要的服务: ");
                scanf(" %c", &opt);
                void (*func1[10])() = {logout, user_detail, reset_passwd, modify_phone, modify_address};
                func1[opt - '0']();
            }
        }
    }
}