#pragma once
typedef struct user
{
    // 用户名，密码，姓名，手机号，门牌号，角色，状态，锁定状态，锁定时间
    long lock_time;
    char role;         // 0管理
    char status;       // 状态 1正常
    char lock;         // 锁定状态，1锁定
    char username[11]; // 用户名
    char password[11]; // 密码
    char realname[20]; // 姓名
    char phone[12];    // 手机号
    char address[20];  // 门牌号
    struct user *next; // 链表
} User;

/*
2025-10-16 17:28:35 user001 登录系统
2025-10-16 17:29:35 user001 修改密码
2025-10-16 17:38:35 admin 删除用户user002
*/

// typedef struct note
// {
//     char time[100];
//     char name[20];
//     char run[100];
// } Note;

typedef struct list
{
    int cout;    // 已保存的数据量
    int size;    // 容量
    char **head; // 起始地址
} List;

extern List logs;
extern User *head;
extern User *current;

extern char role;
extern char login_status;
extern int count;
// extern User users[20];
// extern int current;
int check_user_exists(char username[]);
User *find(int index);
void login();
void reg();
void reset_size(List *p);
void add_log(List *p, char name[], char run[]);