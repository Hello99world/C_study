// 如检查字符串是否组成合理。
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

/**
 * 返回当前时间
 */
long get_timec()
{
    return time(NULL);
}

/**
 * 检查字符串长度
 * @param char str[], 字符串
 * @param int min, 最小长度
 * @param int max, 最大长度
 * @return 长度合法返回1,非法返回0
 */
int check_string_length(char str[], int min, int max)
{
    if (strlen(str) >= min && strlen(str) <= max) // 限制字符串长度
        return 1;
    return 0;
}

/**
 * 检查字符串由字母或者数字组成
 * @param char str[], 字符串
 * @return 合法返回1,非法返回0
 */
int check_string_1(char str[])
{
    int other = 0; // 保存除数字和字母以外的其他字符的数量
    for (int i = 0; str[i] != '\0'; i++)
    { // 检查字符串中的每一个字符（除去数字和大小写字母，剩余字符的数目）
        if (!(str[i] >= '0' && str[i] <= '9' || str[i] >= 'A' && str[i] <= 'Z' || str[i] >= 'a' && str[i] <= 'z'))
        {
            other += 1;
        }
    }
    if (other == 0)
        return 1;
    return 0;
}

/**
 * 检查字符串同时包含字母、数字、下划线
 * @param char str[], 字符串
 * @return 合法返回1,非法返回0
 */
int check_string_2(char str[])
{
    // 保存数字、字母、下划线、其他字符的数量
    int num = 0, let = 0, line = 0, other = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= '0' && str[i] <= '9') // 数字
        {
            num += 1;
        }
        else if (str[i] >= 'A' && str[i] <= 'Z' || str[i] >= 'a' && str[i] <= 'z') // 字母
        {
            let += 1;
        }
        else if (str[i] == '_') // 下划线
        {
            line += 1;
        }
        else
        {
            other += 1; // 其他字符
        }
    }
    if (num != 0 && let != 0 && line != 0 && other == 0) // 同时包含字母、数字、下划线
        return 1;
    return 0;
}

/**
 * 检查手机号是否合法（长度11位纯数字组组成,第1位是1,第2位是3/5/7/8/9）
 * @param char str[], 字符串
 * @return 合法返回1,非法返回0
 */
int check_phone(char str[])
{
    if (check_string_length(str, 11, 11) == 0) // 限制长度
        return 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!(str[i] >= '0' && str[i] <= '9')) // 限制数字
            return 0;
    }
    if (str[0] != '1')
        return 0;
    if (str[1] != '3' && str[1] != '9' && str[1] != '5' && str[1] != '7' && str[1] != '8')
        return 0;
    return 1;
}
