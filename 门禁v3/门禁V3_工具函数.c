// 封装工具函数，如检查字符串是否在指定长度，检查在在自字符串的组成，检查手机号是否合法等
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "./门禁V3_工具.h"

/**
 * 创建1个节点
 * @param User *user, 节点保存的数据
 * @return Node *, 返回节点地址
 */
Node * create_node(User *user){
    Node *p = (Node *)malloc(sizeof(Node));  // 申请内存, 保存新节点的信息
    if(p==NULL) return NULL;  // 分配内存失败
    // 分配内存成功, 将数据保存杂节点的数据域 
    p->user = user;
    p->next = NULL;
    p->prev = NULL;
    return p;
}

/**
 * 打印链表每个节点的数据
 * @param Node *head, 头指针
 */
void display(Node *head){
    Node *temp = head->next;
    printf("链表每个节点的数据为: ");
    while(temp != NULL){
        printf("%s ", temp->user->username);
        temp = temp->next;  // 每循环1次temp指针指向下一个节点
    }
    printf("\n");
}

/**
 * 释放节点内存
 * @param Node *head, 头指针
 */
void free_node(Node *head){
    Node *temp = head;
    while(temp != NULL){
        Node *p = temp;     // 保存当前节点
        temp = temp->next;  // 找到当前节点的直接后继
        free(p);            // 释放当前节点
    }
}

/**
 * 查找包含指定数据的第1个节点
 * @param Node *head, 头指针
 * @param char * username, 目标数据
 * @return Node *, 返回包含数据的节点
 */
Node * search(Node *head, char *username){
    Node *temp = head->next;
    while(temp != NULL){
        if(strcmp(temp->user->username, username) == 0) return temp;
        temp = temp->next;
    }
    return NULL;
}

/**
 * 添加用户（头插）
 * @param Node *head, 头指针
 * @param User *user, 用户数据
 * @return int, 成功返回1, 失败返回-1
 */
int add_node(Node *head, User *user){
    Node *new = create_node(user);  // 创建节点
    if(new == NULL) return -1;
    if(head->next != NULL){
        new->next = head->next;  // 新节点的next指针指向原首元节点
        head->next->prev = new;  // 原首元节点prev指针指向头节点
    }
    head->next = new;  // 头节点的next指针指向新节点
    new->prev = head;  // 新节点的prev指针指向头节点
    return 1;
}

/**
 * 删除节点
 * @param Node *head, 头指针
 * @param char *username, 用户名
 */
void del_node(Node *head, char *username){
    Node *node = search(head, username);  // 查找包含指定数据的节点
    if(node == NULL){
        printf("用户%s不存在\n", username);
        return;
    }
    
    if(node->next == NULL){  // 删除链表的最后1个节点
        node->prev->next = NULL;
    }else{  // 不是链表的最后1个节点
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    free(node);
}

/**
 * 返回当前时间戳
 */
long get_timec(){
    return time(NULL);
}

/**
 * 返回当前日期时间
 */
char dt[30];
void get_dt(){
    long tc = time(NULL);   // 时间戳
    struct tm *tm = localtime(&tc);
    // %Y-4位数的年，%m-月，%d-天，%H-小时，%M-分钟，%S-秒
    strftime(dt,1023,"%Y-%m-%d %H:%M:%S", tm);
}

/**
 * 初始化动态数组，保存日志
 * @return mlog *, 日志结构体指针
 * @param int size, 动态数组的初始大小
 */
mlog* create_log(int size){
    mlog *p = (mlog *)malloc(sizeof(mlog));
    if(p == NULL) return NULL;
    p->size = size;
    p->length = 0;
    p->argv = (char **)malloc(sizeof(char *) * p->size);
    if(p->argv == NULL) return NULL;
    return p;
}

/**
 * 添加日志
 * @param mlog *p, 日志结构体指针
 * @param char *q, 日志信息
 */
void log_add (mlog *p, char *q){
    if(p == NULL) return;
    if(p->length == p->size){  // 判断动态数 NULL组是否已满
        p->size += 10;
        p->argv = (char **)realloc(p->argv, sizeof(char *) * p->size);
        if(p->argv == NULL) return;
    }
    p->argv[p->length++] = q;   // 保存日志信息, 日志数量加1
}

/**
 * 打印日志
 * @param mlog *p, 日志结构体指针
 */
void display_log(mlog  *p){
    printf("日志为: \n");
    for(int i=0; i<p->length; i++){
        printf("%s ", p->argv[i]);
    }
    printf("\n");
}

/**
 * 释放日志内存
 * @param mlog *p, 日志结构体指针
 */
void free_log(mlog *p){
    if(p == NULL) return;
    for(int i=0; i<p->length; i++){
        free(p->argv[i]);
    }
    free(p->argv);
    free(p);
}

/**
 * 检查字符串长度
 * @param char str[], 字符串
 * @param int min, 最小长度
 * @param int max, 最大长度
 * @return 长度合法返回1,非法返回0
 */
int check_string_length(char str[], int min, int max){
    if(strlen(str) >= min && strlen(str) <= max) return 1;
    return 0;
}

/**
 * 检查字符串由字母或者数字组成
 * @param char str[], 字符串
 * @return 合法返回1,非法返回0
 */
int check_string_1(char str[]){
    int other = 0; // 保存除数字和字母以外的其他字符的数量
    for(int i=0; str[i]!='\0'; i++){ // 检查字符串中的每一个字符
        if(!(str[i]>='0' && str[i]<='9' || str[i]>='A' && str[i]<='Z' || str[i]>='a' && str[i]<='z')){
            other += 1;
        }
    }
    if(other == 0) return 1;
    return 0;
}

/**
 * 检查字符串同时包含字母、数字、下划线
 * @param char str[], 字符串
 * @return 合法返回1,非法返回0
 */
int check_string_2(char str[]){
    // 保存数字、字母、下划线、其他字符的数量
    int num = 0, let = 0, line = 0, other = 0;
    for(int i=0; str[i]!='\0'; i++){
        if(str[i]>='0' && str[i]<='9'){
            num += 1;
        }else if(str[i]>='A' && str[i]<='Z' || str[i]>='a' && str[i]<='z'){
            let += 1;
        }else if(str[i] == '_'){
            line += 1;
        }else{
            other += 1;
        }
    }
    if(num!=0 && let!=0 && line!=0 && other==0) return 1;
    return 0;
}

/**
 * 检查手机号是否合法（长度11位纯数字组组成,第1位是1,第2位是3/5/7/8/9）
 * @param char str[], 字符串
 * @return 合法返回1,非法返回0
 */
int check_phone(char str[]){
    if(check_string_length(str, 11, 11) == 0) return 0;
    for(int i=0; str[i]!='\0'; i++){
        if(!(str[i]>='0' && str[i]<='9')) return 0;
    }
    if(str[0] != '1') return 0;
    if(str[1]!='3' && str[1]!='9' && str[1]!='5' && str[1]!='7' && str[1]!='8') return 0;
    return 1;
}