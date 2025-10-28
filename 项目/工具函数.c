#include "工具.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // 定义静态互斥锁

/**
 * 文件追加
 * @param file   文件名
 * @param line   追加的行
 * @return       成功返回0，失败返回-1
 */
int add_line(char *file, char *line)
{
    pthread_mutex_lock(&mutex);
    // 使用追加模式打开文件
    FILE *fp = fopen(file, "a");
    if (fp == NULL)
    {
        pthread_mutex_unlock(&mutex);
        return -1;
    }
    // 将新行添加到文件内
    fprintf(fp, "%s\n", line);
    fclose(fp);
    pthread_mutex_unlock(&mutex);
    return 0;
}

/**
 * 文件修改删除
 * @param file   文件名
 * @param key     关键字
 * @param new_line  新行
 * @return  成功返回0，失败返回-1
 */
int change(char *file, char *key, char *new_line)
{
    pthread_mutex_lock(&mutex);
    FILE *fp = fopen(file, "r");
    if (fp == NULL)
    {
        pthread_mutex_unlock(&mutex);
        return -1;
    }
    // 创建副本文件存储
    FILE *tmp = fopen("tmp.txt", "w");
    if (tmp == NULL)
    {
        fclose(fp);
        pthread_mutex_unlock(&mutex);
        return -1;
    }
    char line[LINE];
    // 逐行读取文件进行处理
    while (fgets(line, sizeof(line), fp))
    {
        // 找到对应数据则替换
        if (key && strstr(line, key) != NULL)
        {
            if (new_line != NULL)
            {
                fprintf(tmp, "%s\n", new_line); // 替换或是删除
            }
        }
        // 没找到则移入副本文件
        else
        {
            fputs(line, tmp);
        }
    }
    fclose(fp);
    fclose(tmp);

    remove(file);            // 删除旧文件
    rename("tmp.txt", file); // 重命名替换文件
    pthread_mutex_unlock(&mutex);
    return 0;
}

/**
 * 查看文件
 * @param file    文件名
 */
int print(char *file){
    FILE *fp = fopen(file, "r");
        if (fp == NULL) {
        return -1;
    }
    char bu[1024], *temp;
    while (1) {
        temp = fgets(bu, sizeof(bu)-1, fp);
        if(temp == NULL){
            break;
        }
        printf("%s", bu);
    }
    fclose(fp); 
}

/**
 * 查询指定前缀的行
 * @param file    文件名
 * @param key       关键字
 * @return        行内容
 */
char *search(char *file, char *key)
{
    char cmd[100];
    // 查找指定前缀的行并输出一行
    snprintf(cmd, sizeof(cmd), "grep '^%s' %s | head -n 1", key, file);
    FILE *fp = popen(cmd, "r");
    if (fp == NULL)
    {
        return NULL;
    }
    // 定义一个可以存储行的变量作为返回值
    static char buf[LINE];
    if (fgets(buf, sizeof(buf), fp) == NULL)
    {
        pclose(fp);
        return NULL;
    }
    pclose(fp);
    return buf;
}


/**
 * 获取时间
 * @param t 时间戳
 * @param buf 时间字符串
 * @param len 时间字符串长度
 */
void time_buf(time_t t, char *buf, int len)
{
    struct tm *tm = localtime(&t);
    strftime(buf, len, "%Y-%m-%d %H:%M:%S", tm);
}

/**
 * 时间转整数
 */
int time_int(char *date) {
    int year, month, day;
    if (sscanf(date, "%d-%d-%d", &year, &month, &day) != 3) {
        return -1;
    }
    return year * 10000 + month * 100 + day;
}


/**
 * 添加日志
 * @param msg 日志信息
 * @return 0 成功
 */
int add_logs(char *msg)
{
    char buf[LINE];
    time_t t = time(NULL);
    char dt[30];
    time_buf(t, dt, sizeof(dt));
    strcpy(buf, dt);
    strcat(buf, msg); // 拼接日志消息
    return add_line("logs.txt", buf);
}


/**
 * 校验车位号
 * @param num  车位号
 * @return 1 成功 0 失败
 */
int cheak_space(char *num)
{
    if (num == NULL)
    {
        printf("车位号不能为空\n");
        return 0;
    }
    int len = strlen(num);
    if (len != 4)
    {
        printf("车位号长度错误\n");
        return 0;
    }
    for (int i = 0; i < len; i++)
    {
        if (!((num[i] >= 'A' && num[i] <= 'Z') || (num[i] >= '0' && num[i] <= '9')))
        {
            printf("车位号格式错误\n");
            return 0;
        }
    }
    return 1;
}

/**
 * 校验车牌号
 * @param card  车牌号
 * @return 1:成功 0:失败
 */
int cheak_card(char *card)
{
    if (card == NULL)
    {
        printf("车牌号不能为空\n");
        return 0;
    }
    if (strlen(card) != 9)
    {
        printf("车牌号长度错误（字节数不对）\n");
        return 0;
    }
    if (!((unsigned char)*card >= 0xE0))
    {
        printf("车牌号格式错误（首字符不是汉字）\n");
        return 0;
    }
    for (int i = 3; i < 9; i++)
    { // 跳过汉字的3字节，从第4字节开始
        if (!((card[i] >= 'A' && card[i] <= 'Z') ||(card[i] >= '0' && card[i] <= '9')))
        {
            printf("车牌号格式错误（包含非法字符）\n");
            return 0;
        }
    }
    
    return 1;
}

/**
 * 查询空车位
 * @param num_buf  存储车位的数组
 * @return 0:找到 1:找到
 */
int free_space(char *num_buf)
{
    FILE *fp = fopen("车位信息.txt", "r");
    if (fp == NULL) {return -1;}

    char line[LINE];
    while (fgets(line, sizeof(line), fp)) {
        char num[5];
        int status;
        // 检测到车位有空位
        if (sscanf(line, "%s %d", num, &status) == 2 && status == 0) {
            // 提取车位号码
            strcpy(num_buf, num);
            fclose(fp);
            return 0;
        }
    }
    fclose(fp);
    return -1;
}