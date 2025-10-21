#pragma once  // 防止重复包含

typedef struct user{
    // 用户名/密码/姓名/手机号/门牌号/角色/状态/锁定状态/锁定时间
    long lock_time;
    char role;          // 角色，0-管理员，1-普通用户
    char status;        // 状态，1-正常，0-异常
    char lock;          // 锁定状态, 1-已锁定，0-未锁定
    char username[11];  // 用户名
    char passwrod[11];  // 密码
    char realname[20];  // 姓名
    char phone[12];     // 手机号
    char address[20];   // 门牌号
}User;

// 定义结构体, 表示节点的成员
typedef struct node{
    User *user;    // 数据域, 保存即即节点数据
    struct node *next;  // 指针域, 保存直接后继节点的地址
    struct node *prev;  // 指针域, 保存直接前驱节点的地址
}Node;

// 定义结构体，表示动态数组信息（保存日志）
typedef struct log{
    char **argv;
    int length;
    int size;
}mlog;

extern char dt[30];
long get_timec();
int check_string_length(char str[], int min, int max);
int check_string_1(char str[]);
int check_string_2(char str[]);
int check_phone(char str[]);
void get_dt();
mlog* create_log(int size);
void log_add (mlog *p, char *q);
void display_log(mlog  *p);

Node * create_node(User *user);
Node * search(Node *head, char *username);
int add_node(Node *head, User *user);
void del_node(Node *head, char *username);
void display(Node *head);