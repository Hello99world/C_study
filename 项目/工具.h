#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#define LINE 512


extern pthread_mutex_t mutex;

int add_line(char *file,char *line);  // 文件增加
int change(char *file, char *key, char *new_line); // 文件修改和删除
char *search(char *file, char *key); // 系统命令查询
int print(char *file);
int add_logs(char *msg);    // 写日志
int cheak_space(char *num); // 检查车位号规则
int cheak_card(char *card); // 检查车牌号规则
void time_buf(time_t t, char *buf, int len);
int time_int(char *date);
int free_space(char *num_buf);