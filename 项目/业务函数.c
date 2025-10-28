#include "工具.h"

/**
 * 添加车位
 * @param num 车位编号
 * @return 0 成功 -1 失败
 */
int add_space(char *num)
{
    if (cheak_space(num) == 0)
    {
        return -1;
    }
    char *lina = search("车位信息.txt", num);
    if (lina != NULL)
    {
        printf("车位已存在");
        return -1;
    }
    char line[LINE];
    sprintf(line, "%s 0", num); // 默认空闲
    return add_line("车位信息.txt", line);
}

/**
 * 修改车位状态
 * @param num 车位编号
 * @param status 状态
 * @return 0 成功 -1 失败
 */
int change_space(char *num, int status)
{
    char *line = search("车位信息.txt", num);
    if (line == NULL)
    {
        printf("车位不存在");
        return -1;
    }
    char new_line[LINE];
    sprintf(new_line, "%s %d", num, status);
    return change("车位信息.txt", num, new_line);
}

/**
 * 删除车位
 * @param num 车位编号
 * @return 0 成功 -1 失败
 */
int delete_space(char *num)
{
    char *line = search("车位信息.txt", num);
    if (line == NULL)
    {
        printf("车位不存在");
        return -1;
    }
    int status;
    sscanf(line, "%*s %d", &status);
    if (status != 0)
    {
        return -2;
    }
    return change("车位信息.txt", num, NULL); // 删除
}

/**
 * 添加月租车辆
 * @param card 车牌
 * @param num 车位
 * @param start 开始时间
 * @param end 结束时间
 * @return 0 成功 -1 失败
 */
int add_monthly(char *card, char *num, char *start, char *end)
{
    if (cheak_card(card) == 0 || cheak_space(num) == 0)
    {
        printf("输入信息非法");
        return -1;
    }
    char *lina = search("车位信息.txt", num);
    if (lina == NULL)
    {
        printf("车位不存在,请重新输入");
        return -1;
    }
    int status;
    sscanf(lina, "%*s %d", &status);
    if (status != 0)
    {
        printf("车位正在使用中");
        return -2;
    }
    char *linc = search("月租车辆.txt", card);
    if (linc != NULL)
    {
        printf("车牌已存在,请重新输入");
        return -1;
    }
    // change_space(num, 1);
    char line[LINE];
    sprintf(line, "%s %s 1 %s %s", card, num, start, end);
    return add_line("月租车辆.txt", line);
}
/**
 * 修改月租车辆
 * @param card 车牌
 * @param num 车位
 * @param end 结束时间
 * @return 0 成功 -1 失败
 */
int change_monthly(char *card, char *num, char *start, char *end)
{
    char line[LINE];
    sprintf(line, "%s %s 1 %s %s", card, num, start, end);
    if (cheak_card(card) == 0 || cheak_space(num) == 0)
    {
        printf("输入信息非法");
        return -1;
    }
    char *lina = search("车位信息.txt", num);
    if (lina == NULL)
    {
        printf("车位不存在,请重新输入");
        return -1;
    }
    int status;
    sscanf(lina, "%*s %d", &status);
    if (status != 0)
    {
        printf("车位正在使用中");
        return -2;
    }
    return change("月租车辆.txt", card, line);
}

/**
 * 删除月租车辆
 * @param card 车牌
 * @return 0 删除成功 -1 删除失败
 */
int delete_monthly(char *card)
{
    char *lina = search("月租车辆.txt", card);
    if (lina == NULL)
    {
        printf("车辆不存在,请重新输入");
        return -1;
    }
    char num[5];
    sscanf(lina, "%*s %s", num);
    change_space(num, 0);
    return change("月租车辆.txt", card, NULL);
}

/**
 * 添加长期车辆
 * @param card 车牌
 * @param space 车位
 * @return 0 添加成功 -1 添加失败
 */
int add_year(char *card, char *num)
{
    if (cheak_card(card) == 0 || cheak_space(num) == 0)
    {
        return -1;
    }
    char *lina = search("车位信息.txt", num);
    if (lina == NULL)
    {
        printf("车位不存在,请重新输入");
        return -1;
    }
    int status;
    sscanf(lina, "%*s %d", &status);
    if (status != 0)
    {
        printf("车位正在使用中");
        return -2;
    }
    char *linc = search("长期车辆.txt", card);
    if (linc != NULL)
    {
        printf("车牌已存在,请重新输入");
        return -1;
    }
    // change_space(num, 1);
    char line[LINE];
    sprintf(line, "%s %s 2 ", card, num);
    return add_line("长期车辆.txt", line);
}

/**
 * 修改长期车辆
 * @param card 车牌
 * @param num 车位
 * @return 0 添加成功 -1 添加失败
 */
int change_year(char *card, char *num)
{
    char line[LINE];
    sprintf(line, "%s %s 2 ", card, num);
    if (cheak_card(card) == 0 || cheak_space(num) == 0)
    {
        printf("输入信息非法");
        return -1;
    }
    char *lina = search("车位信息.txt", num);
    if (lina == NULL)
    {
        printf("车位不存在,请重新输入");
        return -1;
    }
    int status;
    sscanf(lina, "%*s %d", &status);
    if (status != 0)
    {
        printf("车位正在使用中");
        return -2;
    }
    return change("长期车辆.txt", card, line);
}

/**
 * 删除长期车辆
 * @param card 车牌
 * @return 0 添加成功 -1 添加失败
 */
int delete_year(char *card)
{
    char *lina = search("长期车辆.txt", card);
    if (lina == NULL)
    {
        printf("车辆不存在,请重新输入");
        return -1;
    }
    return change("长期车辆.txt", card, NULL);
}

/**
 * 车辆入场
 * @param card 车牌
 * @param type 类型
 */
int car_run(char *card, int type)
{
    char num[5];
    char line[LINE];
    // 检查车牌
    if (cheak_card(card) == 0)
    {
        printf("车牌号非法\n");
        return -1;
    }
    time_t now = time(NULL); // 直接使用秒数计算时间
    if (type == 3)
    { // 临停车查找空闲车位
        if (free_space(num) != 0)
        {
            printf("没有空闲车位，入场失败\n");
            return -2;
        }
        // 记录车辆信息
        sprintf(line, "%s 3 %ld", num, now);
        char rec[LINE];
        // 记录日志
        sprintf(rec, "%s %s 3 %ld", card, num, now);
        add_line("cars_now.txt", rec);
    }
    else if (type == 1)
    {
        // 查找月租车记录
        char *rec = search("月租车辆.txt", card);
        if (rec == NULL)
        {
            printf("月租车不存在\n");
            return -3;
        }
        char com[16], start[16], end[16];
        int attr;
        sscanf(rec, "%*s %s %d %s %s", com, &attr, start, end);
        // 提取车位信息
        strcpy(num, com);
        // 检查月租是否到期
        char buf[30];
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        strftime(buf, sizeof(buf), "%Y-%m-%d", tm);
        int timA = time_int(buf);
        int timB = time_int(end);
        if (timA > timB)
        {
            printf("月租已到期，请按照临时车入场\n");
            return -4;
        }
        // 记录车辆信息
        sprintf(line, "%s %d %ld", num, type, now);
        char rec2[LINE];
        sprintf(rec2, "%s %s %d %ld", card, num, type, now);
        add_line("cars_now.txt", rec2);
    }
    else if (type == 2)
    { // 长期车
        char *rec = search("长期车辆.txt", card);
        if (rec == NULL)
        {
            printf("长期车不存在\n");
            return -5;
        }
        char com[16];
        int attr;
        sscanf(rec, "%*s %s %d", com, &attr);
        strcpy(num, com);
        sprintf(line, "%s %d %ld", num, type, now);
        char rec2[LINE];
        sprintf(rec2, "%s %s %d %ld", card, num, type, now);
        add_line("cars_now.txt", rec2);
    }
    else
    {
        printf("车辆类型错误\n");
        return -6;
    }
    // 更新车位
    sprintf(line, "%s 1", num);
    change("车位信息.txt", num, line);
    // 写日志
    char log[128];
    sprintf(log, " 车辆入场，车牌%s，车位%s", card, num);
    add_logs(log);
    printf("车辆入场成功，车位：%s\n", num);
    return 0;
}

// 车辆离场处理
int car_out(char *card)
{
    char line[LINE];
    char num[16];
    int type;
    long time_sec; // 入场时间秒数
    // 查询车辆
    char *rec = search("cars_now.txt", card);
    if (rec == NULL)
    {
        printf("车辆未在场\n");
        return -1;
    }
    sscanf(rec, "%*s %s %d %ld", num, &type, &time_sec);
    // 计算费用
    time_t now = time(NULL);
    int fee = 0;
    int hours;
    int minute;
    if (type == 3)
    {
        long second = now - time_sec; // 秒数差
        int hour = second / 3600;     // 小时
        hours = hour;
        int c_second = second % 3600; // 剩余秒数
        minute = c_second / 60;       // 剩余分钟
        if (c_second > 0)
            hour++; // 不满1小时按1小时计算
        if (hour <= 2)
            fee = 4;
        else
            fee = 4 + (hour - 2) * 3;
    }
    // 写日志
    char timebuf[32];
    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    char log[128];
    if (type == 3)
    {
        sprintf(log, " %s 离场，停车%d小时%d分钟，停放费用：%d元", card, hours, minute, fee);
    }
    else
    {
        sprintf(log, " %s 离场，月租/长期车，费用0元", card);
    }
    add_logs(log);
    // 删除在场记录
    change("cars_now.txt", card, NULL);
    // 释放车位
    char new_line[LINE];
    sprintf(new_line, "%s 0", num);
    change("车位信息.txt", num, new_line);
    printf("车辆离场完成，费用：%d元\n", fee);
    return fee;
}